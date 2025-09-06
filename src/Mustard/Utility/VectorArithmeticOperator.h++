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

#include "Mustard/Concept/NumericVector.h++"

#include "muc/concepts"

#include <type_traits>

namespace Mustard::inline Utility::VectorArithmeticOperator {

inline namespace Vector2ArithmeticOperator {

#define MUSTARD_UTILITY_VECTOR_ARITHMETIC_OPERATOR_VECTOR2_VECTOR_OPERATORS(T, U) \
                                                                                  \
    auto operator+(const Concept::NumericVector2<T> auto& u,                      \
                   const Concept::NumericVector2<U> auto& v)                      \
        ->std::conditional_t<sizeof(T) >= sizeof(U),                              \
                             std::decay_t<decltype(u)>,                           \
                             std::decay_t<decltype(v)>> {                         \
        return {u[0] + v[0],                                                      \
                u[1] + v[1]};                                                     \
    }                                                                             \
                                                                                  \
    auto operator-(const Concept::NumericVector2<T> auto& u,                      \
                   const Concept::NumericVector2<U> auto& v)                      \
        ->std::conditional_t<sizeof(T) >= sizeof(U),                              \
                             std::decay_t<decltype(u)>,                           \
                             std::decay_t<decltype(v)>> {                         \
        return {u[0] - v[0],                                                      \
                u[1] - v[1]};                                                     \
    }                                                                             \
                                                                                  \
    auto operator*(const Concept::NumericVector2<T> auto& u,                      \
                   const Concept::NumericVector2<U> auto& v)                      \
        ->auto {                                                                  \
        return u[0] * v[0] +                                                      \
               u[1] * v[1];                                                       \
    }                                                                             \
                                                                                  \
    auto operator+=(Concept::NumericVector2<T> auto& u,                           \
                    const Concept::NumericVector2<U> auto& v)                     \
        ->auto& {                                                                 \
        u[0] += v[0];                                                             \
        u[1] += v[1];                                                             \
        return u;                                                                 \
    }                                                                             \
                                                                                  \
    auto operator-=(Concept::NumericVector2<T> auto& u,                           \
                    const Concept::NumericVector2<U> auto& v)                     \
        ->auto& {                                                                 \
        u[0] -= v[0];                                                             \
        u[1] -= v[1];                                                             \
        return u;                                                                 \
    }

#define MUSTARD_UTILITY_VECTOR_ARITHMETIC_OPERATOR_VECTOR2_SCALAR_OPERATORS(T) \
                                                                               \
    auto operator-(const Concept::NumericVector2<T> auto& u)                   \
        ->std::decay_t<decltype(u)> {                                          \
        return {-u[0],                                                         \
                -u[1]};                                                        \
    }                                                                          \
                                                                               \
    auto operator*(const Concept::NumericVector2<T> auto& u,                   \
                   muc::arithmetic auto c)                                     \
        ->std::decay_t<decltype(u)> {                                          \
        return {u[0] * c,                                                      \
                u[1] * c};                                                     \
    }                                                                          \
                                                                               \
    auto operator*(muc::arithmetic auto c,                                     \
                   const Concept::NumericVector2<T> auto& u)                   \
        ->std::decay_t<decltype(u)> {                                          \
        return {c * u[0],                                                      \
                c * u[1]};                                                     \
    }                                                                          \
                                                                               \
    auto operator/(const Concept::NumericVector2<T> auto& u,                   \
                   muc::arithmetic auto c)                                     \
        ->std::decay_t<decltype(u)> {                                          \
        return {u[0] / c,                                                      \
                u[1] / c};                                                     \
    }                                                                          \
                                                                               \
    auto operator*=(Concept::NumericVector2<T> auto& u,                        \
                    muc::arithmetic auto c)                                    \
        ->auto& {                                                              \
        u[0] *= c;                                                             \
        u[1] *= c;                                                             \
        return u;                                                              \
    }                                                                          \
                                                                               \
    auto operator/=(Concept::NumericVector2<T> auto& u,                        \
                    muc::arithmetic auto c)                                    \
        ->auto& {                                                              \
        u[0] /= c;                                                             \
        u[1] /= c;                                                             \
        return u;                                                              \
    }

MUSTARD_UTILITY_VECTOR_ARITHMETIC_OPERATOR_VECTOR2_VECTOR_OPERATORS(float, float)
MUSTARD_UTILITY_VECTOR_ARITHMETIC_OPERATOR_VECTOR2_VECTOR_OPERATORS(float, double)
MUSTARD_UTILITY_VECTOR_ARITHMETIC_OPERATOR_VECTOR2_VECTOR_OPERATORS(float, long double)
MUSTARD_UTILITY_VECTOR_ARITHMETIC_OPERATOR_VECTOR2_VECTOR_OPERATORS(double, float)
MUSTARD_UTILITY_VECTOR_ARITHMETIC_OPERATOR_VECTOR2_VECTOR_OPERATORS(double, double)
MUSTARD_UTILITY_VECTOR_ARITHMETIC_OPERATOR_VECTOR2_VECTOR_OPERATORS(double, long double)
MUSTARD_UTILITY_VECTOR_ARITHMETIC_OPERATOR_VECTOR2_VECTOR_OPERATORS(long double, float)
MUSTARD_UTILITY_VECTOR_ARITHMETIC_OPERATOR_VECTOR2_VECTOR_OPERATORS(long double, double)
MUSTARD_UTILITY_VECTOR_ARITHMETIC_OPERATOR_VECTOR2_VECTOR_OPERATORS(long double, long double)
MUSTARD_UTILITY_VECTOR_ARITHMETIC_OPERATOR_VECTOR2_SCALAR_OPERATORS(float)
MUSTARD_UTILITY_VECTOR_ARITHMETIC_OPERATOR_VECTOR2_SCALAR_OPERATORS(double)
MUSTARD_UTILITY_VECTOR_ARITHMETIC_OPERATOR_VECTOR2_SCALAR_OPERATORS(long double)

#undef MUSTARD_UTILITY_VECTOR_ARITHMETIC_OPERATOR_VECTOR2_SCALAR_OPERATORS
#undef MUSTARD_UTILITY_VECTOR_ARITHMETIC_OPERATOR_VECTOR2_VECTOR_OPERATORS

} // namespace Vector2ArithmeticOperator

inline namespace Vector3ArithmeticOperator {

#define MUSTARD_UTILITY_VECTOR_ARITHMETIC_OPERATOR_VECTOR3_VECTOR_OPERATORS(T, U) \
                                                                                  \
    auto operator+(const Concept::NumericVector3<T> auto& u,                      \
                   const Concept::NumericVector3<U> auto& v)                      \
        ->std::conditional_t<sizeof(T) >= sizeof(U),                              \
                             std::decay_t<decltype(u)>,                           \
                             std::decay_t<decltype(v)>> {                         \
        return {u[0] + v[0],                                                      \
                u[1] + v[1],                                                      \
                u[2] + v[2]};                                                     \
    }                                                                             \
                                                                                  \
    auto operator-(const Concept::NumericVector3<T> auto& u,                      \
                   const Concept::NumericVector3<U> auto& v)                      \
        ->std::conditional_t<sizeof(T) >= sizeof(U),                              \
                             std::decay_t<decltype(u)>,                           \
                             std::decay_t<decltype(v)>> {                         \
        return {u[0] - v[0],                                                      \
                u[1] - v[1],                                                      \
                u[2] - v[2]};                                                     \
    }                                                                             \
                                                                                  \
    auto operator*(const Concept::NumericVector3<T> auto& u,                      \
                   const Concept::NumericVector3<U> auto& v)                      \
        ->auto {                                                                  \
        return u[0] * v[0] +                                                      \
               u[1] * v[1] +                                                      \
               u[2] * v[2];                                                       \
    }                                                                             \
                                                                                  \
    auto operator+=(Concept::NumericVector3<T> auto& u,                           \
                    const Concept::NumericVector3<U> auto& v)                     \
        ->auto& {                                                                 \
        u[0] += v[0];                                                             \
        u[1] += v[1];                                                             \
        u[2] += v[2];                                                             \
        return u;                                                                 \
    }                                                                             \
                                                                                  \
    auto operator-=(Concept::NumericVector3<T> auto& u,                           \
                    const Concept::NumericVector3<U> auto& v)                     \
        ->auto& {                                                                 \
        u[0] -= v[0];                                                             \
        u[1] -= v[1];                                                             \
        u[2] -= v[2];                                                             \
        return u;                                                                 \
    }

#define MUSTARD_UTILITY_VECTOR_ARITHMETIC_OPERATOR_VECTOR3_SCALAR_OPERATORS(T) \
                                                                               \
    auto operator-(const Concept::NumericVector3<T> auto& u)                   \
        ->std::decay_t<decltype(u)> {                                          \
        return {-u[0],                                                         \
                -u[1],                                                         \
                -u[2]};                                                        \
    }                                                                          \
                                                                               \
    auto operator*(const Concept::NumericVector3<T> auto& u,                   \
                   muc::arithmetic auto c)                                     \
        ->std::decay_t<decltype(u)> {                                          \
        return {u[0] * c,                                                      \
                u[1] * c,                                                      \
                u[2] * c};                                                     \
    }                                                                          \
                                                                               \
    auto operator*(muc::arithmetic auto c,                                     \
                   const Concept::NumericVector3<T> auto& u)                   \
        ->std::decay_t<decltype(u)> {                                          \
        return {c * u[0],                                                      \
                c * u[1],                                                      \
                c * u[2]};                                                     \
    }                                                                          \
                                                                               \
    auto operator/(const Concept::NumericVector3<T> auto& u,                   \
                   muc::arithmetic auto c)                                     \
        ->std::decay_t<decltype(u)> {                                          \
        return {u[0] / c,                                                      \
                u[1] / c,                                                      \
                u[2] / c};                                                     \
    }                                                                          \
                                                                               \
    auto operator*=(Concept::NumericVector3<T> auto& u,                        \
                    muc::arithmetic auto c)                                    \
        ->auto& {                                                              \
        u[0] *= c;                                                             \
        u[1] *= c;                                                             \
        u[2] *= c;                                                             \
        return u;                                                              \
    }                                                                          \
                                                                               \
    auto operator/=(Concept::NumericVector3<T> auto& u,                        \
                    muc::arithmetic auto c)                                    \
        ->auto& {                                                              \
        u[0] /= c;                                                             \
        u[1] /= c;                                                             \
        u[2] /= c;                                                             \
        return u;                                                              \
    }

MUSTARD_UTILITY_VECTOR_ARITHMETIC_OPERATOR_VECTOR3_VECTOR_OPERATORS(float, float)
MUSTARD_UTILITY_VECTOR_ARITHMETIC_OPERATOR_VECTOR3_VECTOR_OPERATORS(float, double)
MUSTARD_UTILITY_VECTOR_ARITHMETIC_OPERATOR_VECTOR3_VECTOR_OPERATORS(float, long double)
MUSTARD_UTILITY_VECTOR_ARITHMETIC_OPERATOR_VECTOR3_VECTOR_OPERATORS(double, float)
MUSTARD_UTILITY_VECTOR_ARITHMETIC_OPERATOR_VECTOR3_VECTOR_OPERATORS(double, double)
MUSTARD_UTILITY_VECTOR_ARITHMETIC_OPERATOR_VECTOR3_VECTOR_OPERATORS(double, long double)
MUSTARD_UTILITY_VECTOR_ARITHMETIC_OPERATOR_VECTOR3_VECTOR_OPERATORS(long double, float)
MUSTARD_UTILITY_VECTOR_ARITHMETIC_OPERATOR_VECTOR3_VECTOR_OPERATORS(long double, double)
MUSTARD_UTILITY_VECTOR_ARITHMETIC_OPERATOR_VECTOR3_VECTOR_OPERATORS(long double, long double)
MUSTARD_UTILITY_VECTOR_ARITHMETIC_OPERATOR_VECTOR3_SCALAR_OPERATORS(float)
MUSTARD_UTILITY_VECTOR_ARITHMETIC_OPERATOR_VECTOR3_SCALAR_OPERATORS(double)
MUSTARD_UTILITY_VECTOR_ARITHMETIC_OPERATOR_VECTOR3_SCALAR_OPERATORS(long double)

#undef MUSTARD_UTILITY_VECTOR_ARITHMETIC_OPERATOR_VECTOR3_SCALAR_OPERATORS
#undef MUSTARD_UTILITY_VECTOR_ARITHMETIC_OPERATOR_VECTOR3_VECTOR_OPERATORS

} // namespace Vector3ArithmeticOperator

inline namespace Vector4ArithmeticOperator {

#define MUSTARD_UTILITY_VECTOR_ARITHMETIC_OPERATOR_VECTOR4_VECTOR_OPERATORS(T, U) \
                                                                                  \
    auto operator+(const Concept::NumericVector4<T> auto& u,                      \
                   const Concept::NumericVector4<U> auto& v)                      \
        ->std::conditional_t<sizeof(T) >= sizeof(U),                              \
                             std::decay_t<decltype(u)>,                           \
                             std::decay_t<decltype(v)>> {                         \
        return {u[0] + v[0],                                                      \
                u[1] + v[1],                                                      \
                u[2] + v[2],                                                      \
                u[3] + v[3]};                                                     \
    }                                                                             \
                                                                                  \
    auto operator-(const Concept::NumericVector4<T> auto& u,                      \
                   const Concept::NumericVector4<U> auto& v)                      \
        ->std::conditional_t<sizeof(T) >= sizeof(U),                              \
                             std::decay_t<decltype(u)>,                           \
                             std::decay_t<decltype(v)>> {                         \
        return {u[0] - v[0],                                                      \
                u[1] - v[1],                                                      \
                u[2] - v[2],                                                      \
                u[3] - v[3]};                                                     \
    }                                                                             \
                                                                                  \
    auto operator+=(Concept::NumericVector4<T> auto& u,                           \
                    const Concept::NumericVector4<U> auto& v)                     \
        ->auto& {                                                                 \
        u[0] += v[0];                                                             \
        u[1] += v[1];                                                             \
        u[2] += v[2];                                                             \
        u[3] += v[3];                                                             \
        return u;                                                                 \
    }                                                                             \
                                                                                  \
    auto operator-=(Concept::NumericVector4<T> auto& u,                           \
                    const Concept::NumericVector4<U> auto& v)                     \
        ->auto& {                                                                 \
        u[0] -= v[0];                                                             \
        u[1] -= v[1];                                                             \
        u[2] -= v[2];                                                             \
        u[3] -= v[3];                                                             \
        return u;                                                                 \
    }

#define MUSTARD_UTILITY_VECTOR_ARITHMETIC_OPERATOR_VECTOR4_SCALAR_OPERATORS(T) \
                                                                               \
    auto operator-(const Concept::NumericVector4<T> auto& u)                   \
        ->std::decay_t<decltype(u)> {                                          \
        return {-u[0],                                                         \
                -u[1],                                                         \
                -u[2],                                                         \
                -u[3]};                                                        \
    }                                                                          \
                                                                               \
    auto operator*(const Concept::NumericVector4<T> auto& u,                   \
                   muc::arithmetic auto c)                                     \
        ->std::decay_t<decltype(u)> {                                          \
        return {u[0] * c,                                                      \
                u[1] * c,                                                      \
                u[2] * c,                                                      \
                u[3] * c};                                                     \
    }                                                                          \
                                                                               \
    auto operator*(muc::arithmetic auto c,                                     \
                   const Concept::NumericVector4<T> auto& u)                   \
        ->std::decay_t<decltype(u)> {                                          \
        return {c * u[0],                                                      \
                c * u[1],                                                      \
                c * u[2],                                                      \
                c * u[3]};                                                     \
    }                                                                          \
                                                                               \
    auto operator/(const Concept::NumericVector4<T> auto& u,                   \
                   muc::arithmetic auto c)                                     \
        ->std::decay_t<decltype(u)> {                                          \
        return {u[0] / c,                                                      \
                u[1] / c,                                                      \
                u[2] / c,                                                      \
                u[3] / c};                                                     \
    }                                                                          \
                                                                               \
    auto operator*=(Concept::NumericVector4<T> auto& u,                        \
                    muc::arithmetic auto c)                                    \
        ->auto& {                                                              \
        u[0] *= c;                                                             \
        u[1] *= c;                                                             \
        u[2] *= c;                                                             \
        u[3] *= c;                                                             \
        return u;                                                              \
    }                                                                          \
                                                                               \
    auto operator/=(Concept::NumericVector4<T> auto& u,                        \
                    muc::arithmetic auto c)                                    \
        ->auto& {                                                              \
        u[0] /= c;                                                             \
        u[1] /= c;                                                             \
        u[2] /= c;                                                             \
        u[3] /= c;                                                             \
        return u;                                                              \
    }

MUSTARD_UTILITY_VECTOR_ARITHMETIC_OPERATOR_VECTOR4_VECTOR_OPERATORS(float, float)
MUSTARD_UTILITY_VECTOR_ARITHMETIC_OPERATOR_VECTOR4_VECTOR_OPERATORS(float, double)
MUSTARD_UTILITY_VECTOR_ARITHMETIC_OPERATOR_VECTOR4_VECTOR_OPERATORS(float, long double)
MUSTARD_UTILITY_VECTOR_ARITHMETIC_OPERATOR_VECTOR4_VECTOR_OPERATORS(double, float)
MUSTARD_UTILITY_VECTOR_ARITHMETIC_OPERATOR_VECTOR4_VECTOR_OPERATORS(double, double)
MUSTARD_UTILITY_VECTOR_ARITHMETIC_OPERATOR_VECTOR4_VECTOR_OPERATORS(double, long double)
MUSTARD_UTILITY_VECTOR_ARITHMETIC_OPERATOR_VECTOR4_VECTOR_OPERATORS(long double, float)
MUSTARD_UTILITY_VECTOR_ARITHMETIC_OPERATOR_VECTOR4_VECTOR_OPERATORS(long double, double)
MUSTARD_UTILITY_VECTOR_ARITHMETIC_OPERATOR_VECTOR4_VECTOR_OPERATORS(long double, long double)
MUSTARD_UTILITY_VECTOR_ARITHMETIC_OPERATOR_VECTOR4_SCALAR_OPERATORS(float)
MUSTARD_UTILITY_VECTOR_ARITHMETIC_OPERATOR_VECTOR4_SCALAR_OPERATORS(double)
MUSTARD_UTILITY_VECTOR_ARITHMETIC_OPERATOR_VECTOR4_SCALAR_OPERATORS(long double)

#undef MUSTARD_UTILITY_VECTOR_ARITHMETIC_OPERATOR_VECTOR4_SCALAR_OPERATORS
#undef MUSTARD_UTILITY_VECTOR_ARITHMETIC_OPERATOR_VECTOR4_VECTOR_OPERATORS

} // namespace Vector4ArithmeticOperator

} // namespace Mustard::inline Utility::VectorArithmeticOperator
