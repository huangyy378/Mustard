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

#include "Mustard/Utility/FunctionAttribute.h++"

#include "fmt/color.h"

#include <cstdio>

namespace Mustard::inline Utility {

MUSTARD_NOINLINE auto PrintStackTrace(int depth = 64, int skip = 0, std::FILE* f = stderr, const fmt::text_style& ts = {}) -> void;

} // namespace Mustard::inline Utility
