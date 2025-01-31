#pragma once

#include <sstream>

extern std::ostringstream tdbg;

void tdbg_report_failure(const char * file, unsigned int line);
void tdbg_clear_output(const char * file, unsigned int line);
bool tdbg_empty();

#undef UTEST_ASSERT

#if defined(__clang__)
#define UTEST_ASSERT(x, y, cond)                                               \
  UTEST_SURPRESS_WARNING_BEGIN do {                                            \
    _Pragma("clang diagnostic push")                                           \
        _Pragma("clang diagnostic ignored \"-Wlanguage-extension-token\"")     \
            _Pragma("clang diagnostic ignored \"-Wc++98-compat-pedantic\"")    \
                _Pragma("clang diagnostic ignored \"-Wfloat-equal\"")          \
                    UTEST_AUTO(x) xEval = (x);                                 \
    UTEST_AUTO(y) yEval = (y);                                                 \
    if (!((xEval)cond(yEval))) {                                               \
      _Pragma("clang diagnostic pop")                                          \
          UTEST_PRINTF("%s:%u: Failure\n", __FILE__, __LINE__);                \
      UTEST_PRINTF("  Expected : ");                                           \
      utest_type_printer(xEval);                                               \
      UTEST_PRINTF("\n");                                                      \
      UTEST_PRINTF("    Actual : ");                                           \
      utest_type_printer(yEval);                                               \
      UTEST_PRINTF("\n");                                                      \
      tdbg_report_failure(__FILE__, __LINE__);                                                   \
      *utest_result = 1;                                                       \
      return;                                                                  \
    } else {                                                                   \
      tdbg_clear_output(__FILE__, __LINE__);                                                     \
    }                                                                          \
  }                                                                            \
  while (0)                                                                    \
  UTEST_SURPRESS_WARNING_END
#elif defined(__GNUC__)
#define UTEST_ASSERT(x, y, cond)                                               \
  UTEST_SURPRESS_WARNING_BEGIN do {                                            \
    UTEST_AUTO(x) xEval = (x);                                                 \
    UTEST_AUTO(y) yEval = (y);                                                 \
    if (!((xEval)cond(yEval))) {                                               \
      UTEST_PRINTF("%s:%u: Failure\n", __FILE__, __LINE__);                    \
      UTEST_PRINTF("  Expected : ");                                           \
      utest_type_printer(xEval);                                               \
      UTEST_PRINTF("\n");                                                      \
      UTEST_PRINTF("    Actual : ");                                           \
      utest_type_printer(yEval);                                               \
      UTEST_PRINTF("\n");                                                      \
      tdbg_report_failure(__FILE__, __LINE__);                                                   \
      *utest_result = 1;                                                       \
      return;                                                                  \
    } else {                                                                   \
      tdbg_clear_output(__FILE__, __LINE__);                                                     \
    }                                                                          \
  }                                                                            \
  while (0)                                                                    \
  UTEST_SURPRESS_WARNING_END
#else
#define UTEST_ASSERT(x, y, cond)                                               \
  UTEST_SURPRESS_WARNING_BEGIN do {                                            \
    if (!((x)cond(y))) {                                                       \
      UTEST_PRINTF("%s:%u: Failure\n", __FILE__, __LINE__);                    \
      tdbg_report_failure(__FILE__, __LINE__);                                                   \
      *utest_result = 1;                                                       \
      return;                                                                  \
    } else {                                                                   \
      tdbg_clear_output(__FILE__, __LINE__);                                                     \
    }                                                                          \
  }                                                                            \
  while (0)                                                                    \
  UTEST_SURPRESS_WARNING_END
#endif


#undef ASSERT_TRUE
#define ASSERT_TRUE(x)                                                         \
  UTEST_SURPRESS_WARNING_BEGIN do {                                            \
    bool xEval = (!(x) == 0);                                                \
    if (!(xEval)) {                                       \
      UTEST_PRINTF("%s:%u: Failure\n", __FILE__, __LINE__);                    \
      UTEST_PRINTF("  Expected : true\n");                                     \
      UTEST_PRINTF("    Actual : %s\n", (xEval) ? "true" : "false");               \
      tdbg_report_failure(__FILE__, __LINE__);                                                   \
      *utest_result = 1;                                                       \
      return;                                                                  \
    } else {                                                                   \
      tdbg_clear_output(__FILE__, __LINE__);                                                     \
    }                                                                          \
  }                                                                            \
  while (0)                                                                    \
  UTEST_SURPRESS_WARNING_END

#define ASSERT_TRUE_(x, s) \
  do {                      \
    (tdbg << (s));          \
    ASSERT_TRUE(x);        \
  } while(0)

#undef ASSERT_FALSE
#define ASSERT_FALSE(x)                                                        \
  UTEST_SURPRESS_WARNING_BEGIN do {                                            \
    bool xEval = (!(x) == 0);                                                \
    if (xEval) {                                                                   \
      UTEST_PRINTF("%s:%u: Failure\n", __FILE__, __LINE__);                    \
      UTEST_PRINTF("  Expected : false\n");                                    \
      UTEST_PRINTF("    Actual : %s\n", (xEval) ? "true" : "false");               \
      tdbg_report_failure(__FILE__, __LINE__);                                                   \
      *utest_result = 1;                                                       \
      return;                                                                  \
    } else {                                                                   \
      tdbg_clear_output(__FILE__, __LINE__);                                                     \
    }                                                                          \
  }                                                                            \
  while (0)                                                                    \
  UTEST_SURPRESS_WARNING_END

#define ASSERT_FALSE_(x, s) \
  do {                      \
    (tdbg << (s));          \
    ASSERT_FALSE(x);        \
  } while(0)

#undef ASSERT_EQ
#define ASSERT_EQ(x, y) UTEST_ASSERT(x, y, ==)
#define ASSERT_EQ_(x, y, s) \
  do {                      \
    (tdbg << (s));          \
    ASSERT_EQ(x, y);        \
  } while(0)

#undef ASSERT_NE
#define ASSERT_NE(x, y) UTEST_ASSERT(x, y, !=)
#define ASSERT_NE_(x, y, s) \
  do {                      \
    (tdbg << (s));          \
    ASSERT_NE(x, y);        \
  } while(0)

#undef ASSERT_LT
#define ASSERT_LT(x, y) UTEST_ASSERT(x, y, <)
#define ASSERT_LT_(x, y, s) \
  do {                      \
    (tdbg << (s));          \
    ASSERT_LT(x, y);        \
  } while(0)

#undef ASSERT_LE
#define ASSERT_LE(x, y) UTEST_ASSERT(x, y, <=)
#define ASSERT_LE_(x, y, s) \
  do {                      \
    (tdbg << (s));          \
    ASSERT_LE(x, y);        \
  } while(0)

#undef ASSERT_GT
#define ASSERT_GT(x, y) UTEST_ASSERT(x, y, >)
#define ASSERT_GT_(x, y, s) \
  do {                      \
    (tdbg << (s));          \
    ASSERT_GT(x, y);        \
  } while(0)

#undef ASSERT_GE
#define ASSERT_GE(x, y) UTEST_ASSERT(x, y, >=)
#define ASSERT_GE_(x, y, s) \
  do {                      \
    (tdbg << (s));          \
    ASSERT_GE(x, y);        \
  } while(0)

#define MK_ASSERT(function, ...)                             \
  UTEST_SURPRESS_WARNING_BEGIN do {                          \
    function(tdbg, __VA_ARGS__);                             \
    if(!tdbg_empty()) {                                      \
      UTEST_PRINTF("%s:%u: Failure\n", __FILE__, __LINE__);  \
      tdbg_report_failure(__FILE__, __LINE__);               \
      *utest_result = 1;                                     \
      return;                                                \
    } else {                                                 \
      tdbg_clear_output(__FILE__, __LINE__);                 \
    }                                                        \
  } while (0)                                                \
  UTEST_SURPRESS_WARNING_END
