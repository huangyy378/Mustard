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
#include "Mustard/Env/VerboseLevel.h++"

#include "gsl/gsl"

#include <optional>
#include <type_traits>

namespace Mustard::CLI::inline Module {

class BasicModule : public ModuleBase {
public:
    BasicModule(gsl::not_null<CLI<>*> cli);

    auto VerboseLevel() const -> std::optional<Env::VerboseLevel>;
    auto ShowBanner() const -> bool;

private:
    std::underlying_type_t<Env::VerboseLevel> fVerboseLevelValue;
};

} // namespace Mustard::CLI::inline Module
