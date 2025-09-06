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

namespace Mustard::inline IO {

template<char L, typename... Ts>
auto Print(fmt::format_string<Ts...> fmt, Ts&&... args) -> void {
    if (not Env::VerboseLevelReach<L>()) {
        return;
    }
    fmt::print(std::move(fmt), std::forward<Ts>(args)...);
}

template<char L, typename... Ts>
auto PrintLn(fmt::format_string<Ts...> fmt, Ts&&... args) -> void {
    if (not Env::VerboseLevelReach<L>()) {
        return;
    }
    fmt::println(std::move(fmt), std::forward<Ts>(args)...);
}

template<char L, typename... Ts>
auto Print(fmt::text_style ts, fmt::format_string<Ts...> fmt, Ts&&... args) -> void {
    if (not Env::VerboseLevelReach<L>()) {
        return;
    }
    fmt::print(ts, std::move(fmt), std::forward<Ts>(args)...);
}

template<char L, typename... Ts>
auto Print(std::FILE* f, fmt::format_string<Ts...> fmt, Ts&&... args) -> void {
    if (not Env::VerboseLevelReach<L>()) {
        return;
    }
    fmt::print(f, std::move(fmt), std::forward<Ts>(args)...);
}

template<char L, typename... Ts>
auto PrintLn(std::FILE* f, fmt::format_string<Ts...> fmt, Ts&&... args) -> void {
    if (not Env::VerboseLevelReach<L>()) {
        return;
    }
    fmt::println(f, std::move(fmt), std::forward<Ts>(args)...);
}

template<char L, typename... Ts>
auto Print(std::FILE* f, fmt::text_style ts, fmt::format_string<Ts...> fmt, Ts&&... args) -> void {
    if (not Env::VerboseLevelReach<L>()) {
        return;
    }
    fmt::print(f, ts, std::move(fmt), std::forward<Ts>(args)...);
}

template<char L, typename... Ts>
auto Print(std::ostream& os, fmt::format_string<Ts...> fmt, Ts&&... args) -> void {
    if (not Env::VerboseLevelReach<L>()) {
        return;
    }
    fmt::print(os, std::move(fmt), std::forward<Ts>(args)...);
}

template<char L, typename... Ts>
auto PrintLn(std::ostream& os, fmt::format_string<Ts...> fmt, Ts&&... args) -> void {
    if (not Env::VerboseLevelReach<L>()) {
        return;
    }
    fmt::println(os, std::move(fmt), std::forward<Ts>(args)...);
}

template<char L, typename... Ts>
auto Print(std::ostream& os, fmt::text_style ts, fmt::format_string<Ts...> fmt, Ts&&... args) -> void {
    if (not Env::VerboseLevelReach<L>()) {
        return;
    }
    fmt::print(os, ts, std::move(fmt), std::forward<Ts>(args)...);
}

template<char L, typename... Ts>
auto Print(std::wostream& os, fmt::wformat_string<Ts...> fmt, Ts&&... args) -> void {
    if (not Env::VerboseLevelReach<L>()) {
        return;
    }
    fmt::print(os, std::move(fmt), std::forward<Ts>(args)...);
}

template<char L, typename... Ts>
auto PrintLn(std::wostream& os, fmt::wformat_string<Ts...> fmt, Ts&&... args) -> void {
    if (not Env::VerboseLevelReach<L>()) {
        return;
    }
    fmt::println(os, std::move(fmt), std::forward<Ts>(args)...);
}

template<char L, typename... Ts>
auto Print(std::wostream& os, fmt::text_style ts, fmt::wformat_string<Ts...> fmt, Ts&&... args) -> void {
    if (not Env::VerboseLevelReach<L>()) {
        return;
    }
    fmt::print(os, ts, std::move(fmt), std::forward<Ts>(args)...);
}

template<char L>
auto VPrint(auto&&... args) -> void {
    if (not Env::VerboseLevelReach<L>()) {
        return;
    }
    fmt::vprint(std::forward<decltype(args)>(args)...);
}

template<char L, typename... Ts>
auto MasterPrint(fmt::format_string<Ts...> fmt, Ts&&... args) -> void {
    if (not mplr::available() or
        mplr::comm_world().rank() == 0) {
        Print(std::move(fmt), std::forward<Ts>(args)...);
    }
}

template<char L, typename... Ts>
auto MasterPrintLn(fmt::format_string<Ts...> fmt, Ts&&... args) -> void {
    if (not mplr::available() or
        mplr::comm_world().rank() == 0) {
        PrintLn(std::move(fmt), std::forward<Ts>(args)...);
    }
}

template<char L, typename... Ts>
auto MasterPrint(fmt::text_style ts, fmt::format_string<Ts...> fmt, Ts&&... args) -> void {
    if (not mplr::available() or
        mplr::comm_world().rank() == 0) {
        Print(ts, std::move(fmt), std::forward<Ts>(args)...);
    }
}

template<char L, typename... Ts>
auto MasterPrint(std::FILE* f, fmt::format_string<Ts...> fmt, Ts&&... args) -> void {
    if (not mplr::available() or
        mplr::comm_world().rank() == 0) {
        Print(f, std::move(fmt), std::forward<Ts>(args)...);
    }
}

template<char L, typename... Ts>
auto MasterPrintLn(std::FILE* f, fmt::format_string<Ts...> fmt, Ts&&... args) -> void {
    if (not mplr::available() or
        mplr::comm_world().rank() == 0) {
        PrintLn(f, std::move(fmt), std::forward<Ts>(args)...);
    }
}

template<char L, typename... Ts>
auto MasterPrint(std::FILE* f, fmt::text_style ts, fmt::format_string<Ts...> fmt, Ts&&... args) -> void {
    if (not mplr::available() or
        mplr::comm_world().rank() == 0) {
        Print(f, ts, std::move(fmt), std::forward<Ts>(args)...);
    }
}

template<char L, typename... Ts>
auto MasterPrint(std::ostream& os, fmt::format_string<Ts...> fmt, Ts&&... args) -> void {
    if (not mplr::available() or
        mplr::comm_world().rank() == 0) {
        Print(os, std::move(fmt), std::forward<Ts>(args)...);
    }
}

template<char L, typename... Ts>
auto MasterPrintLn(std::ostream& os, fmt::format_string<Ts...> fmt, Ts&&... args) -> void {
    if (not mplr::available() or
        mplr::comm_world().rank() == 0) {
        PrintLn(os, std::move(fmt), std::forward<Ts>(args)...);
    }
}

template<char L, typename... Ts>
auto MasterPrint(std::ostream& os, fmt::text_style ts, fmt::format_string<Ts...> fmt, Ts&&... args) -> void {
    if (not mplr::available() or
        mplr::comm_world().rank() == 0) {
        Print(os, ts, std::move(fmt), std::forward<Ts>(args)...);
    }
}

template<char L, typename... Ts>
auto MasterPrint(std::wostream& os, fmt::wformat_string<Ts...> fmt, Ts&&... args) -> void {
    if (not mplr::available() or
        mplr::comm_world().rank() == 0) {
        Print(os, std::move(fmt), std::forward<Ts>(args)...);
    }
}

template<char L, typename... Ts>
auto MasterPrintLn(std::wostream& os, fmt::wformat_string<Ts...> fmt, Ts&&... args) -> void {
    if (not mplr::available() or
        mplr::comm_world().rank() == 0) {
        PrintLn(os, std::move(fmt), std::forward<Ts>(args)...);
    }
}

template<char L, typename... Ts>
auto MasterPrint(std::wostream& os, fmt::text_style ts, fmt::wformat_string<Ts...> fmt, Ts&&... args) -> void {
    if (not mplr::available() or
        mplr::comm_world().rank() == 0) {
        Print(os, ts, std::move(fmt), std::forward<Ts>(args)...);
    }
}

template<char L>
auto MasterVPrint(auto&&... args) -> void {
    if (not mplr::available() or
        mplr::comm_world().rank() == 0) {
        VPrint(std::forward<decltype(args)>(args)...);
    }
}

} // namespace Mustard::inline IO
