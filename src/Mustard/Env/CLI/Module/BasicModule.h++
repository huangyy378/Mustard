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

#pragma once

#include "Mustard/Env/CLI/Module/ModuleBase.h++"
#include "Mustard/Env/VerboseLevel.h++"

#include <optional>
#include <type_traits>

namespace Mustard::Env::CLI::inline Module {

class BasicModule : public ModuleBase {
public:
    BasicModule(argparse::ArgumentParser& argParser);

    auto VerboseLevel() const -> std::optional<enum VerboseLevel>;
    auto ShowBanner() const -> auto { return not ArgParser().is_used("--lite"); }

private:
    std::underlying_type_t<enum VerboseLevel> fVerboseLevelValue;
};

} // namespace Mustard::Env::CLI::inline Module
