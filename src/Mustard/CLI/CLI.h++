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

#include "Mustard/CLI/Module/ModuleBase.h++"

#include "argparse/argparse.hpp"

#include "muc/type_traits"

#include <concepts>
#include <memory>
#include <optional>
#include <string_view>
#include <utility>

namespace Mustard::CLI {

template<std::derived_from<ModuleBase>... AModules>
    requires muc::is_type_set_v<AModules...>
class CLI;

template<>
class CLI<> {
public:
    CLI();
    virtual ~CLI() = 0;

public:
    auto ParseArgs(int argc, char* argv[]) -> void;
    auto Parsed() const -> bool { return fArgcArgv.has_value(); }
    auto ArgcArgv() const -> std::pair<int, char**>;

    auto operator->() const -> const auto* { return fArgParser.get(); }
    auto operator->() -> auto* { return fArgParser.get(); }
    auto operator[](std::string_view arg) -> auto& { return (*fArgParser)[arg]; }

protected:
    auto ArgParser() const -> const auto& { return *fArgParser; }
    auto ArgParser() -> auto& { return *fArgParser; }

protected:
    [[noreturn]] static auto ThrowParsed() -> void;
    [[noreturn]] static auto ThrowNotParsed() -> void;

private:
    std::optional<std::pair<int, char**>> fArgcArgv;
    std::unique_ptr<argparse::ArgumentParser> fArgParser;
};

template<std::derived_from<ModuleBase>... AModules>
    requires muc::is_type_set_v<AModules...>
class CLI : public CLI<>,
            public AModules... {
public:
    CLI();
};

} // namespace Mustard::CLI

#include "Mustard/CLI/CLI.inl"
