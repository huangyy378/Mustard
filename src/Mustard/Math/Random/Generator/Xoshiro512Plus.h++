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

#include "Mustard/Math/Random/Generator/Xoshiro512Base.h++"
#include "Mustard/Utility/FunctionAttribute.h++"

namespace Mustard::Math::Random::inline Generator {

class Xoshiro512Plus final : public Xoshiro512Base<Xoshiro512Plus> {
public:
    constexpr Xoshiro512Plus() = default;
    constexpr explicit Xoshiro512Plus(SeedType seed);

    MUSTARD_ALWAYS_INLINE constexpr auto operator()() -> ResultType;
};

} // namespace Mustard::Math::Random::inline Generator

#include "Mustard/Math/Random/Generator/Xoshiro512Plus.inl"
