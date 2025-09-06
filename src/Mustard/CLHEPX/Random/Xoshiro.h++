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

#include "Mustard/CLHEPX/Random/Wrap.h++"
#include "Mustard/Math/Random/Generator/Xoshiro256Plus.h++"
#include "Mustard/Math/Random/Generator/Xoshiro256PlusPlus.h++"
#include "Mustard/Math/Random/Generator/Xoshiro256StarStar.h++"
#include "Mustard/Math/Random/Generator/Xoshiro512Plus.h++"
#include "Mustard/Math/Random/Generator/Xoshiro512PlusPlus.h++"
#include "Mustard/Math/Random/Generator/Xoshiro512StarStar.h++"

namespace Mustard::CLHEPX::Random {

using Xoshiro256StarStar = CLHEPX::Random::Wrap<Math::Random::Xoshiro256StarStar>;
using Xoshiro256PlusPlus = CLHEPX::Random::Wrap<Math::Random::Xoshiro256PlusPlus>;
using Xoshiro256Plus = CLHEPX::Random::Wrap<Math::Random::Xoshiro256Plus>;
using Xoshiro512StarStar = CLHEPX::Random::Wrap<Math::Random::Xoshiro512StarStar>;
using Xoshiro512PlusPlus = CLHEPX::Random::Wrap<Math::Random::Xoshiro512PlusPlus>;
using Xoshiro512Plus = CLHEPX::Random::Wrap<Math::Random::Xoshiro512Plus>;

} // namespace Mustard::CLHEPX::Random
