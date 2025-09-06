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

#include "Mustard/Env/Memory/WeakSingletonified.h++"
#include "Mustard/IO/PrettyLog.h++"
#include "Mustard/Utility/NonCopyableBase.h++"

#include "muc/hash_map"
#include "muc/utility"

#include "gsl/gsl"

#include "fmt/format.h"

#include <memory>
#include <mutex>
#include <stdexcept>
#include <string>
#include <typeindex>
#include <typeinfo>

namespace Mustard::Env::Memory::internal {

/// @brief Implementation detail of Mustard::Env::Memory::WeakSingleton.
/// Not API.
class WeakSingletonPool final : public NonCopyableBase {
public:
    WeakSingletonPool();
    ~WeakSingletonPool();

    static auto Instantiated() -> bool { return fgInstantiated; }
    static auto Available() -> bool { return fgInstance != nullptr; }
    static auto Expired() -> bool { return fgExpired; }

    static auto Instance() -> WeakSingletonPool&;

    template<WeakSingletonified AWeakSingleton>
    auto Find() -> std::shared_ptr<void*>;
    template<WeakSingletonified AWeakSingleton>
    auto Contains() const -> auto { return fInstanceMap.contains(typeid(AWeakSingleton)); }
    template<WeakSingletonified AWeakSingleton>
    [[nodiscard]] auto Insert(gsl::not_null<AWeakSingleton*> instance) -> std::shared_ptr<void*>;

    static auto Mutex() -> auto& { return fgMutex; }

private:
    muc::flat_hash_map<std::type_index, const std::weak_ptr<void*>> fInstanceMap;

    static WeakSingletonPool* fgInstance;
    static bool fgInstantiated;
    static bool fgExpired;
    static std::mutex fgMutex;
};

} // namespace Mustard::Env::Memory::internal

#include "Mustard/Env/Memory/internal/WeakSingletonPool.inl"
