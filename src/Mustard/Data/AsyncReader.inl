// -*- C++ -*-
//
// Copyright 2020-2024  The Mustard development team
//
// This file is part of Mustard, an offline software framework for HEP experiments.
//
// Mustard is free software: you can redistribute it and/or modify it under the
// terms of the GNU General Public License as published by the Free Software
// Foundation, either version 3 of the License, or (at your option) any later
// version.
//
// Mustard is distributed in the hope that it will be useful, but WITHOUT ANY
// WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
// A PARTICULAR PURPOSE. See the GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License along with
// Mustard. If not, see <https://www.gnu.org/licenses/>.

namespace Mustard::Data {

template<typename AData>
AsyncReader<AData>::AsyncReader() :
    fReaderThread{},
    fReading{},
    fReadStartSemaphore{0},
    fReadCompleteSemaphore{0},
    fFirst{},
    fLast{},
    fSentinel{},
    fData{},
    fExhausted{} {
    if (ROOT::IsImplicitMTEnabled()) {
        Throw<std::logic_error>("Async RDataFrame reader cannot be used when IMT is enabled");
    }
}

template<typename AData>
AsyncReader<AData>::~AsyncReader() {
    if (not fExhausted) { Throw<std::logic_error>("Data have not been exhausted"); }
    if (fReading) { Throw<std::logic_error>("Last read data not acquired"); }
}

template<typename AData>
auto AsyncReader<AData>::Read(gsl::index first, gsl::index last) -> void {
    if (fExhausted) { Throw<std::logic_error>("Data have been exhausted"); }
    if (fReading) { Throw<std::logic_error>("Try to start another read while reading"); }
    if (first < 0) { Throw<std::out_of_range>("first < 0"); }
    if (last < 0) { Throw<std::out_of_range>("last < 0"); }
    if (first > last) { Throw<std::out_of_range>("first > last"); }
    fFirst = first;
    fLast = last;
    fData.reserve(last - first);
    fReading = true;
    fReadStartSemaphore.release();
}

template<typename AData>
auto AsyncReader<AData>::Acquire() -> AData {
    if (not fReading) { Throw<std::logic_error>("Try to acquire result while not reading"); }
    fReadCompleteSemaphore.acquire();
    fReading = false;
    return std::move(fData);
}

template<typename AData>
auto AsyncReader<AData>::CompleteRead() -> void {
    do {
        fReadCompleteSemaphore.release();
        fReadStartSemaphore.acquire();
        fData.clear();
    } while (fFirst == fLast);
}

template<TupleModelizable... Ts>
AsyncEntryReader<Ts...>::AsyncEntryReader(ROOT::RDF::RNode data) :
    AsyncReader<muc::shared_ptrvec<Tuple<Ts...>>>{} {
    this->fSentinel = *data.Count();
    if (this->fSentinel == 0) {
        this->fExhausted = true;
        return;
    }
    this->fReaderThread = std::jthread{
        [this](ROOT::RDF::RNode data) {
            auto columnList{Tuple<Ts...>::NameVector()};
            columnList.emplace_back("rdfentry_");
            this->fReadStartSemaphore.acquire();
            data.Foreach([&]<gsl::index... Is>(gslx::index_sequence<Is...>) {
                return [&](const typename internal::ReadHelper<Ts...>::template ReadType<Is>&... value,
                           ULong64_t uEntry) {
                    const auto entry{muc::to_signed(uEntry)};
                    if (entry == this->fLast) {
                        this->CompleteRead();
                        if (entry > this->fFirst) [[unlikely]] {
                            Throw<std::logic_error>(fmt::format("Current entry ({}) is larger than the specified first entry ({})", entry, this->fFirst));
                        }
                    }
                    if (entry < this->fFirst) {
                        return;
                    }
                    this->fData.emplace_back(std::make_shared<Tuple<Ts...>>(
                        internal::ReadHelper<Ts...>::template As<
                            typename internal::ReadHelper<Ts...>::template TargetType<Is>>(value)...));
                };
            }(gslx::make_index_sequence<Tuple<Ts...>::Size()>{}),
                         std::move(columnList));
            this->fExhausted = true;
            this->fReadCompleteSemaphore.release();
        },
        std::move(data)};
}

// template<std::integral AEventIDType, muc::instantiated_from<TupleModel>... Ts>
// AsyncEventReader<AEventIDType, Ts...>::AsyncEventReader(std::array<ROOT::RDF::RNode, sizeof...(Ts)> data, std::string eventIDColumnName) :
//     AsyncEventReader{std::move(data), RDFSplitPoint<AEventIDType>(data, std::move(eventIDColumnName))} {}

// template<std::integral AEventIDType, muc::instantiated_from<TupleModel>... Ts>
// AsyncEventReader<AEventIDType, Ts...>::AsyncEventReader(std::array<ROOT::RDF::RNode, sizeof...(Ts)> data, std::array<std::string, sizeof...(Ts)> eventIDColumnName) :
//     AsyncEventReader{std::move(data), RDFSplitPoint<AEventIDType>(data, std::move(eventIDColumnName))} {}

// template<std::integral AEventIDType, muc::instantiated_from<TupleModel>... Ts>
// AsyncEventReader<AEventIDType, Ts...>::AsyncEventReader(std::array<ROOT::RDF::RNode, sizeof...(Ts)> data, std::vector<std::array<RDFEntryRange, sizeof...(Ts)>> eventSplit) :
//     AsyncReader<std::vector<muc::shared_ptrvec<Tuple<Ts...>>>>{},
//     fEventSplit{std::move(eventSplit)} {
// }

template<std::integral AEventIDType, TupleModelizable... Ts>
AsyncEventReader<AEventIDType, TupleModel<Ts...>>::AsyncEventReader(ROOT::RDF::RNode data, std::string eventIDColumnName) :
    AsyncEventReader{std::move(data), RDFSplitPoint<AEventIDType>(data, std::move(eventIDColumnName))} {}

template<std::integral AEventIDType, TupleModelizable... Ts>
AsyncEventReader<AEventIDType, TupleModel<Ts...>>::AsyncEventReader(ROOT::RDF::RNode data, std::vector<gsl::index> eventSplit) :
    AsyncReader<std::vector<muc::shared_ptrvec<Tuple<Ts...>>>>{},
    fEventSplit{std::move(eventSplit)} {
    const auto& es{fEventSplit};
    if (es.empty()) {
        this->fExhausted = true;
        return;
    }
    Expects(std::ranges::is_sorted(es));
    this->fSentinel = ssize(es) - 1;
    this->fReaderThread = std::jthread{
        [this, &es](ROOT::RDF::RNode data) {
            auto columnList{Tuple<Ts...>::NameVector()};
            columnList.emplace_back("rdfentry_");
            this->fReadStartSemaphore.acquire();
            auto nextEvent{this->fFirst};
            data.Foreach([&]<gsl::index... Is>(gslx::index_sequence<Is...>) {
                return [&](const typename internal::ReadHelper<Ts...>::template ReadType<Is>&... value,
                           ULong64_t uEntry) {
                    const auto entry{muc::to_signed(uEntry)};
                    if (entry == es[this->fLast]) {
                        this->CompleteRead();
                        if (entry > es[this->fFirst]) {
                            Throw<std::logic_error>(fmt::format("Current entry ({}) is larger than the specified first entry ({})", entry, es[this->fFirst]));
                        }
                        nextEvent = this->fFirst;
                    }
                    if (entry < es[this->fFirst]) {
                        return;
                    }
                    if (entry == es[nextEvent]) {
                        this->fData.emplace_back().reserve(es[nextEvent + 1] - es[nextEvent]);
                        ++nextEvent;
                    }
                    this->fData.back().emplace_back(std::make_shared<Tuple<Ts...>>(
                        internal::ReadHelper<Ts...>::template As<
                            typename internal::ReadHelper<Ts...>::template TargetType<Is>>(value)...));
                };
            }(gslx::make_index_sequence<Tuple<Ts...>::Size()>{}),
                         std::move(columnList));
            this->fExhausted = true;
            this->fReadCompleteSemaphore.release();
        },
        std::move(data)};
}

template<std::integral AEventIDType, TupleModelizable... Ts>
auto AsyncEventReader<AEventIDType, TupleModel<Ts...>>::Read(gsl::index first, gsl::index last) -> void {
    const auto nEvent{ssize(fEventSplit) - 1};
    if (first > nEvent) { Throw<std::out_of_range>("first > #event"); }
    if (last > nEvent) { Throw<std::out_of_range>("last > #event"); }
    AsyncReader<std::vector<muc::shared_ptrvec<Tuple<Ts...>>>>::Read(first, last);
}

} // namespace Mustard::Data
