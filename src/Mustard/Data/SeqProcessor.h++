// -*- C++ -*-
//
// Copyright (C) 2020-2025  The Mustard development team
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

#pragma once

#include "Mustard/Data/AsyncReader.h++"
#include "Mustard/Data/RDFEventSplit.h++"
#include "Mustard/Data/TakeFrom.h++"
#include "Mustard/Data/Tuple.h++"
#include "Mustard/Data/TupleModel.h++"
#include "Mustard/Data/internal/ProcessorBase.h++"
#include "Mustard/IO/PrettyLog.h++"
#include "Mustard/Utility/ProgressBar.h++"
#include "Mustard/gslx/index_sequence.h++"

#include "muc/concepts"
#include "muc/numeric"
#include "muc/ptrvec"
#include "muc/utility"

#include "gsl/gsl"

#include "fmt/core.h"

#include <algorithm>
#include <array>
#include <cmath>
#include <concepts>
#include <functional>
#include <future>
#include <limits>
#include <memory>
#include <optional>
#include <ranges>
#include <string>
#include <string_view>
#include <tuple>
#include <utility>
#include <vector>

namespace Mustard::Data {

/// @brief A sequential data processor.
class SeqProcessor : public internal::ProcessorBase<gsl::index> {
public:
    SeqProcessor();

    auto PrintProgress(bool val) -> void { fPrintProgress = val; }
    auto PrintProgress() const -> auto { return fPrintProgress; }

    template<TupleModelizable... Ts>
    auto Process(ROOT::RDF::RNode rdf,
                 std::invocable<std::shared_ptr<Tuple<Ts...>>> auto&& F) -> Index;

    template<TupleModelizable... Ts, std::integral AEventIDType>
    auto Process(ROOT::RDF::RNode rdf, muc::type_tag<AEventIDType>, std::string eventIDBranchName,
                 std::invocable<muc::shared_ptrvec<Tuple<Ts...>>> auto&& F) -> Index;
    template<TupleModelizable... Ts, std::integral AEventIDType>
    auto Process(ROOT::RDF::RNode rdf, muc::type_tag<AEventIDType>, std::vector<gsl::index> eventSplit,
                 std::invocable<muc::shared_ptrvec<Tuple<Ts...>>> auto&& F) -> Index;

    template<muc::instantiated_from<TupleModel>... Ts, std::integral AEventIDType>
    auto Process(std::array<ROOT::RDF::RNode, sizeof...(Ts)> rdf,
                 muc::type_tag<AEventIDType>, std::string eventIDBranchName,
                 std::invocable<muc::shared_ptrvec<Tuple<Ts>>...> auto&& F) -> Index;
    template<muc::instantiated_from<TupleModel>... Ts, std::integral AEventIDType>
    auto Process(std::array<ROOT::RDF::RNode, sizeof...(Ts)> rdf,
                 muc::type_tag<AEventIDType>, std::vector<std::string> eventIDBranchName,
                 std::invocable<muc::shared_ptrvec<Tuple<Ts>>...> auto&& F) -> Index;
    template<muc::instantiated_from<TupleModel>... Ts, std::integral AEventIDType>
    auto Process(std::array<ROOT::RDF::RNode, sizeof...(Ts)> rdf,
                 muc::type_tag<AEventIDType>, const std::vector<std::array<RDFEntryRange, sizeof...(Ts)>>& eventSplit,
                 std::invocable<muc::shared_ptrvec<Tuple<Ts>>...> auto&& F) -> Index;

private:
    template<typename AData>
    auto ProcessImpl(AsyncReader<AData>& asyncReader, Index n,
                     std::invocable<typename AData::value_type> auto&& F) -> Index;

private:
    auto LoopBeginAction(Index nTotal) -> void;
    auto IterationEndAction() -> void;
    auto LoopEndAction() -> void;

private:
    bool fPrintProgress;

    Mustard::ProgressBar fProgressBar;
};

} // namespace Mustard::Data

#include "Mustard/Data/SeqProcessor.inl"
