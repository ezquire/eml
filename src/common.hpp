#ifndef EML_COMMON_HPP
#define EML_COMMON_HPP

#include <string_view>

/**
 * @file common.hpp
 * @brief Compile time configurations and utilitize macros and functions
 *
 * This header contains macros and defines used across the entire EML
 * implementation. In particular, it contains compile time configurations
 * defines that control how EML works.
 */

#define EML_STRINGIFY_DETAIL(x) #x
#define EML_STRINGIFY(x) EML_STRINGIFY_DETAIL(x)
#undef EML_STRINGIFY_DETAIL

namespace eml {

struct BuildOptions {
#ifdef EML_VM_DEBUG_TRACE_EXECUTION
  constexpr static bool vm_debug_trace_execution = true;
#else
  constexpr static bool vm_debug_trace_execution = false;
#endif
};
inline constexpr BuildOptions build_options;

struct version {
  static constexpr int major = EML_MAJOR_VERSION;
  static constexpr int minor = EML_MINOR_VERSION;
  static constexpr int patch = EML_PATCH_VERSION;
  static constexpr std::string_view to_string()
  {
    return EML_VERSION;
  }
};

} // namespace eml

#ifdef EML_DEBUG
#define EML_ASSERT(condition, message)                                         \
  do {                                                                         \
    if (!(condition)) {                                                        \
      std::cerr << "[" << __FILE__ << ":" << __LINE__ << "] "                  \
                << "Assert failed in "                                         \
                << std::string_view{static_cast<const char*>(__func__)}        \
                << ": " << (message) << '\n';                                  \
    }                                                                          \
  } while (0)

// Indicates that we know execution should never reach this point in the
// program. In debug mode, we assert this fact because it's a bug to get here.
//
// In release mode, we use compiler-specific built in functions to tell the
// compiler the code can't be reached. This avoids "missing return" warnings
// in some cases and also lets it perform some optimizations by assuming the
// code is never reached.
#define EML_UNREACHABLE()                                                      \
  do {                                                                         \
    std::cerr << "[" << __FILE__ << ":" << __LINE__ << "] "                    \
              << "This code should not be reached in "                         \
              << std::string_view{static_cast<const char*>(__func__)} << '\n'; \
    std::abort();                                                              \
  } while (0)
#else
#define EML_ASSERT(condition, message)                                         \
  do {                                                                         \
  } while (0)

// Tell the compiler that this part of the code will never be reached.
#if defined(_MSC_VER)
#define EML_UNREACHABLE() __assume(0)
#elif defined(__GNUC__) || defined(__GNUG__) || defined(__clang__)
#define EML_UNREACHABLE() __builtin_unreachable()
#else
#define EML_UNREACHABLE()
#endif
#endif

#endif // EML_COMMON_HPP