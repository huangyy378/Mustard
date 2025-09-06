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

#include "Mustard/Env/Memory/internal/SingletonDeleter.h++"
#include "Mustard/Env/Memory/internal/SingletonPool.h++"
#include "Mustard/Env/Memory/internal/WeakSingletonPool.h++"
#include "Mustard/Env/internal/EnvBase.h++"
#include "Mustard/IO/PrettyLog.h++"
#include "Mustard/Utility/FormatToLocalTime.h++"

#include "muc/bit"
#include "muc/utility"

#include "gsl/gsl"

#include "fmt/color.h"

#include <csignal>
#include <exception>
#include <limits>
#include <typeinfo>

#if MUSTARD_SIGNAL_HANDLER

#    include "Mustard/IO/Print.h++"
#    include "Mustard/Utility/FunctionAttribute.h++"
#    include "Mustard/Utility/PrintStackTrace.h++"

#    include "mplr/mplr.hpp"

#    include <chrono>
#    include <cstdio>
#    include <cstdlib>
#    include <ctime>

#endif

namespace Mustard::Env::internal {

namespace {

[[noreturn]] auto TerminateHandler() -> void {
    try {
        const auto exception{std::current_exception()};
        if (exception) {
            std::signal(SIGABRT, SIG_DFL);
            std::rethrow_exception(exception);
        } else {
            const auto ts{fmt::emphasis::bold | fg(fmt::color::white) | bg(fmt::color::dark_orange)};
            Print<'E'>(ts | fmt::emphasis::blink, "***");
            Print<'E'>(ts, " terminate called without an active exception");
            Print<'E'>("\n");
        }
    } catch (const std::exception& e) {
        std::string_view what{e.what()};
        if (not what.empty() and what.ends_with('\n')) {
            what.remove_suffix(1);
        }
        const auto ts{fmt::emphasis::bold | fg(fmt::color::white) | bg(fmt::color::red)};
        Print<'E'>(ts | fmt::emphasis::blink, "***");
        Print<'E'>(ts, " terminate called after throwing an instance of '{}'\n", muc::try_demangle(typeid(e).name()));
        Print<'E'>(ts | fmt::emphasis::blink, "***");
        Print<'E'>(ts, "   what(): {}", what);
        Print<'E'>("\n");
    } catch (...) {
        const auto ts{fmt::emphasis::bold | fg(fmt::color::white) | bg(fmt::color::red)};
        Print<'E'>(ts | fmt::emphasis::blink, "***");
        if constexpr (requires { std::current_exception().__cxa_exception_type()->name(); }) {
            Print<'E'>(ts, " terminate called after throwing an instance of '{}'", muc::try_demangle(std::current_exception().__cxa_exception_type()->name()));
        } else {
            Print<'E'>(ts, " terminate called after throwing a non-std::exception instance");
        }
        Print<'E'>("\n");
    }
    std::abort();
}

#if MUSTARD_SIGNAL_HANDLER

extern "C" {

auto Mustard_SIGINT_SIGTERM_Handler(int sig) -> void {
    std::signal(sig, SIG_DFL);
    if (static auto called{false};
        called) {
        std::abort();
    } else {
        called = true;
    }
    static struct Handler {
        MUSTARD_ALWAYS_INLINE Handler(int sig) {
            const auto now{std::chrono::system_clock::now()};
            const auto lineHeader{mplr::available() ?
                                      fmt::format("MPI{}> ", mplr::comm_world().rank()) :
                                      ""};
            const auto ts{fmt::emphasis::bold};
            Print<'E'>(stderr, "\n");
            switch (sig) {
            case SIGINT:
                Print<'E'>(stderr, ts, "{}***** INTERRUPT (SIGINT) received\n", lineHeader);
                break;
            case SIGTERM:
                Print<'E'>(stderr, ts, "{}***** TERMINATE (SIGTERM) received\n", lineHeader);
                break;
            }
            if (mplr::available()) {
                Print<'E'>(stderr, ts, "{}***** in MPI process {} (node: {})\n",
                           lineHeader, mplr::comm_world().rank(), mplr::processor_name());
            }
            Print<'E'>(stderr, ts, "{}***** at {}\n", lineHeader, FormatToLocalTime(now));
            PrintStackTrace(64, 2, stderr, ts);
            Print<'E'>(stderr, "\n");
            switch (sig) {
            case SIGINT:
                Print<'E'>(stderr, ts, "Ctrl-C pressed or an external interrupt received."); // no '\n' looks good for now
                break;
            case SIGTERM:
                Print<'E'>(stderr, ts, "The process is terminated.\n");
                break;
            }
            Print<'E'>(stderr, "\n");
            std::fflush(stderr);
            std::raise(sig);
        }
    } handler{sig};
}

[[noreturn]] auto Mustard_SIGABRT_Handler(int) -> void {
    std::signal(SIGABRT, SIG_DFL);
    const auto now{std::chrono::system_clock::now()};
    const auto lineHeader{mplr::available() ?
                              fmt::format("MPI{}> ", mplr::comm_world().rank()) :
                              ""};
    const auto ts{fmt::emphasis::bold | fg(fmt::color::orange)};
    Print<'E'>(stderr, "\n");
    Print<'E'>(stderr, ts, "{}***** ABORT (SIGABRT) received\n", lineHeader);
    if (mplr::available()) {
        Print<'E'>(stderr, ts, "{}***** in MPI process {} (node: {})\n",
                   lineHeader, mplr::comm_world().rank(), mplr::processor_name());
    }
    Print<'E'>(stderr, ts, "{}***** at {}\n", lineHeader, FormatToLocalTime(now));
    PrintStackTrace(64, 2, stderr, ts);
    Print<'E'>(stderr, "\n");
    Print<'E'>(stderr, ts, "The process is aborted. View the logs just before receiving SIGABRT for more information.\n");
    Print<'E'>(stderr, "\n");
    std::fflush(stderr);
    std::abort();
}

auto Mustard_SIGFPE_SIGILL_SIGSEGV_Handler(int sig) -> void {
    std::signal(sig, SIG_DFL);
    if (static auto called{false};
        called) {
        std::abort();
    } else {
        called = true;
    }
    static struct Handler {
        MUSTARD_ALWAYS_INLINE Handler(int sig) {
            const auto now{std::chrono::system_clock::now()};
            const auto lineHeader{mplr::available() ?
                                      fmt::format("MPI{}> ", mplr::comm_world().rank()) :
                                      ""};
            const auto ts{fmt::emphasis::bold | fg(fmt::color::red)};
            Print<'E'>(stderr, "\n");
            switch (sig) {
            case SIGFPE:
                Print<'E'>(stderr, ts, "{}***** ERRONEOUS ARITHMETIC OPERATION (SIGFPE) received\n", lineHeader);
                break;
            case SIGILL:
                Print<'E'>(stderr, ts, "{}***** ILLEGAL INSTRUCTION (SIGILL) received\n", lineHeader);
                break;
            case SIGSEGV:
                Print<'E'>(stderr, ts, "{}***** SEGMENTATION VIOLATION (SIGSEGV) received\n", lineHeader);
                break;
            }
            if (mplr::available()) {
                Print<'E'>(stderr, ts, "{}***** in MPI process {} (node: {})\n",
                           lineHeader, mplr::comm_world().rank(), mplr::processor_name());
            }
            Print<'E'>(stderr, ts, "{}***** at {}\n", lineHeader, FormatToLocalTime(now));
            PrintStackTrace(64, 2, stderr, ts);
            Print<'E'>(stderr, "\n");
            Print<'E'>(stderr, ts, "It is likely that the program has one or more errors. Try seeking help from debugging tools.\n");
            Print<'E'>(stderr, "\n");
            std::fflush(stderr);
            std::raise(sig);
        }
    } handler{sig};
}

} // extern "C"

#endif

} // namespace

EnvBase::EnvBase() :
    NonCopyableBase{},
    fWeakSingletonPool{},
    fSingletonPool{},
    fSingletonDeleter{} {

    static_assert("三清庇佑 运行稳定 结果无偏");
    static_assert("God bless no bugs");

    CheckFundamentalType();

    std::set_terminate(internal::TerminateHandler);

#if MUSTARD_SIGNAL_HANDLER
    std::signal(SIGABRT, internal::Mustard_SIGABRT_Handler);
    std::signal(SIGFPE, internal::Mustard_SIGFPE_SIGILL_SIGSEGV_Handler);
    std::signal(SIGILL, internal::Mustard_SIGFPE_SIGILL_SIGSEGV_Handler);
    std::signal(SIGINT, internal::Mustard_SIGINT_SIGTERM_Handler);
    std::signal(SIGSEGV, internal::Mustard_SIGFPE_SIGILL_SIGSEGV_Handler);
    std::signal(SIGTERM, internal::Mustard_SIGINT_SIGTERM_Handler);
#endif

    if (static bool gInstantiated{false};
        gInstantiated) {
        Throw<std::logic_error>("Trying to construct environment twice");
    } else {
        gInstantiated = true;
    }

    fWeakSingletonPool = std::make_unique_for_overwrite<Memory::internal::WeakSingletonPool>();
    fSingletonPool = std::make_unique_for_overwrite<Memory::internal::SingletonPool>();
    fSingletonDeleter = std::make_unique_for_overwrite<Memory::internal::SingletonDeleter>();
}

EnvBase::~EnvBase() = default;

auto EnvBase::CheckFundamentalType() -> void {
    constexpr auto lp32{muc::bit_size<char> == 8 and
                        muc::bit_size<short> == 16 and
                        muc::bit_size<int> == 16 and
                        muc::bit_size<long> == 32 and
                        muc::bit_size<long long> == 64 and
                        muc::bit_size<void*> == 32};
    constexpr auto ilp32{muc::bit_size<char> == 8 and
                         muc::bit_size<short> == 16 and
                         muc::bit_size<int> == 32 and
                         muc::bit_size<long> == 32 and
                         muc::bit_size<long long> == 64 and
                         muc::bit_size<void*> == 32};
    constexpr auto llp64{muc::bit_size<char> == 8 and
                         muc::bit_size<short> == 16 and
                         muc::bit_size<int> == 32 and
                         muc::bit_size<long> == 32 and
                         muc::bit_size<long long> == 64 and
                         muc::bit_size<void*> == 64};
    constexpr auto lp64{muc::bit_size<char> == 8 and
                        muc::bit_size<short> == 16 and
                        muc::bit_size<int> == 32 and
                        muc::bit_size<long> == 64 and
                        muc::bit_size<long long> == 64 and
                        muc::bit_size<void*> == 64};
    if constexpr (not lp64) {
        if constexpr (llp64) {
            fmt::print(stderr, fg(fmt::color::orange), "Warning: The fundamental data model is LLP64 (not LP64)\n");
        } else if constexpr (ilp32) {
            fmt::print(stderr, fg(fmt::color::orange), "Warning: The fundamental data model is ILP32 (not LP64)\n");
        } else if constexpr (lp32) {
            fmt::print(stderr, fg(fmt::color::orange), "Warning: The fundamental data model is LP32 (not LP64)\n");
        } else {
            fmt::print(stderr, fg(fmt::color::orange), "Warning: Using a rare fundamental data model "
                                                       "[{}-bits char, {}-bits short, {}-bits int, {}-bits long, {}-bits long long, {}-bits pointer], "
                                                       "run at your own risk\n",
                       muc::bit_size<char>, muc::bit_size<short>, muc::bit_size<int>, muc::bit_size<long>, muc::bit_size<long long>, muc::bit_size<void*>);
        }
    }
    if constexpr (not std::numeric_limits<float>::is_iec559) {
        fmt::print(stderr, fg(fmt::color::orange), "Warning: 'float' does not fulfill the requirements of IEC 559 (IEEE 754)\n");
    }
    if constexpr (not std::numeric_limits<double>::is_iec559) {
        fmt::print(stderr, fg(fmt::color::orange), "Warning: 'double' does not fulfill the requirements of IEC 559 (IEEE 754)\n");
    }
    if constexpr (not std::numeric_limits<long double>::is_iec559) {
        fmt::print(stderr, fg(fmt::color::orange), "Warning: 'long double' does not fulfill the requirements of IEC 559 (IEEE 754)\n");
    }
}

} // namespace Mustard::Env::internal
