#ifndef TEST_HELPERS_H
#define TEST_HELPERS_H

#include <iostream>
#include <stdexcept>
#include <cmath>

/*
#include <iostream>
#include "test_helpers.h"
#include "functions.h"  // <== your header file(s) here

using std::cout, std::endl;

bool test_() {
  bool pass = true;

  {
    // TEST
  }

  RESULT(pass);
  return pass;
}

int main() {
  unsigned pass_cnt = 0, fail_cnt = 0, skip_cnt = 0;

  //TEST(test_);
  //SKIP(test_);

  cout << "passing " << pass_cnt << "/" << (pass_cnt + fail_cnt) << " tests" << endl;
  if (skip_cnt > 0) {
    cout << "skipped " << skip_cnt << " tests" << endl;
  } else if (fail_cnt == 0) {
    cout << "ALL TESTS PASSING" << endl;
  }
}
*/

typedef struct cout_redirect {
 private:
    std::streambuf* old;
 public:
    cout_redirect(std::streambuf* new_buffer) : old(std::cout.rdbuf(new_buffer)){}

    ~cout_redirect() { std::cout.rdbuf(old); }
} cout_redirect;

#define RESULT(X) std::cout << (X?"PASS":"FAIL") << ": " << __FUNCTION__ << std::endl;

#define FUNC_ARGS(X, Y) #X, X, #Y, Y, __FUNCTION__, __LINE__

#define TRY(X,Y,Z,COND,FUNC) \
try {\
  if (COND) {\
    FUNC(FUNC_ARGS(X, Y));\
    Z;\
  }\
} catch (const std::exception& err) {\
  std::cout << err.what() << std::endl;\
  Z;\
} catch (...) {\
  std::cout << "non-std::exception thrown" << std::endl;\
  Z;\
}
#define CHECK_EQ(X, Y, Z) TRY(X,Y,Z,!(X == Y),explain_eq)
#define EXPECT_EQ(X, Y) CHECK_EQ(X, Y, pass = false)
#define ASSERT_EQ(X, Y) CHECK_EQ(X, Y, RESULT(false); return false)

#define CHECK_NE(X, Y, Z) TRY(X,Y,Z,!(X != Y),explain_ne)
#define EXPECT_NE(X, Y) CHECK_NE(X, Y, pass = false)
#define ASSERT_NE(X, Y) CHECK_NE(X, Y, RESULT(false); return false)

#define CHECK_LT(X, Y, Z) TRY(X,Y,Z,!(X < Y),explain_lt)
#define EXPECT_LT(X, Y) CHECK_LT(X, Y, pass = false)
#define ASSERT_LT(X, Y) CHECK_LT(X, Y, RESULT(false); return false)

#define CHECK_LE(X, Y, Z) TRY(X,Y,Z,!(X <= Y),explain_le)
#define EXPECT_LE(X, Y) CHECK_LE(X, Y, pass = false)
#define ASSERT_LE(X, Y) CHECK_LE(X, Y, RESULT(false); return false)

#define CHECK_GT(X, Y, Z) TRY(X,Y,Z,!(X > Y),explain_gt)
#define EXPECT_GT(X, Y) CHECK_GT(X, Y, pass = false)
#define ASSERT_GT(X, Y) CHECK_GT(X, Y, RESULT(false); return false)

#define CHECK_GE(X, Y, Z) TRY(X,Y,Z,!(X >= Y), explain_ge)
#define EXPECT_GE(X, Y) CHECK_GE(X, Y, pass = false)
#define ASSERT_GE(X, Y) CHECK_GE(X, Y, RESULT(false); return false)

#define CHECK_NEAR(X, Y, Z, W) TRY(X,Y,W,!(std::fabs(X-Y) <= Z), explain_near)
#define EXPECT_NEAR3(X, Y, Z) CHECK_NEAR(X, Y, Z, pass = false)
#define ASSERT_NEAR3(X, Y, Z) CHECK_NEAR(X, Y, Z, RESULT(false); return false)
#define EXPECT_NEAR2(X, Y) EXPECT_NEAR3(X, Y, 0.00005)
#define ASSERT_NEAR2(X, Y) ASSERT_NEAR3(X, Y, 0.00005)

#define GET_EXPECT_NEAR(_1,_2,_3,NAME) NAME
#define EXPECT_NEAR(...) GET_EXPECT_NEAR(__VA_ARGS__, EXPECT_NEAR3, EXPECT_NEAR2)(__VA_ARGS__)

#define TRY_TF(X,Y,Z,COND) \
try {\
  if (COND) {\
    explain_tf(#X, X, Y, __FUNCTION__, __LINE__);\
    Z;\
  }\
} catch (const std::exception& err) {\
  std::cout << err.what() << std::endl;\
  Z;\
}
#define CHECK_TRUE(X, Y, Z) TRY_TF(X,Y,Z,!(X))
#define EXPECT_TRUE(X) CHECK_TRUE(X, true, pass = false)
#define ASSERT_TRUE(X) CHECK_TRUE(X, true, RESULT(false); return false)

#define CHECK_FALSE(X, Y, Z) TRY_TF(X,Y,Z,X)
#define EXPECT_FALSE(X) CHECK_FALSE(X, false, pass = false)
#define ASSERT_FALSE(X) CHECK_FALSE(X, false, RESULT(false); return false)

#define EXPECT_THROW(X,Y) \
try {\
  X;\
  std::cout << "expected " << #X << " to throw " << #Y <<", but nothing thrown" << std::endl;\
  pass = false;\
} catch (const Y& err) {}\
catch (const std::exception& err) {\
  std::cout << "expected " << #X << " to throw " << #Y <<", but got " << err.what() << std::endl;\
  pass = false;\
}\
catch (...) {\
  std::cout << "expected " << #X << " to throw " << #Y <<", but got a non-std::exception" << std::endl;\
  pass = false;\
}

#define ASSERT_THROW(X,Y) \
try {\
  X;\
  std::cout << "expected " << #X << " to throw " << #Y <<", but nothing thrown" << std::endl;\
  RESULT(false);\
  return false;\
} catch (const Y& err) {}\
catch (const std::exception& err) {\
  std::cout << "expected " << #X << " to throw " << #Y <<", but got " << err.what() << std::endl;\
  RESULT(false);\
  return false;\
}\
catch (...) {\
  std::cout << "expected " << #X << " to throw " << #Y <<", but got a non-std::exception" << std::endl;\
  RESULT(false);\
  return false;\
}

#define EXPECT_NO_THROW(X) \
try {\
  X;\
} catch (const std::exception& err) {\
  std::cout << "expected " << #X << " to throw no exception, but got " << err.what() << std::endl;\
  pass = false;\
}\
catch (...) {\
  std::cout << "expected " << #X << " to throw no exception, but got a non-std::exception" << std::endl;\
  pass = false;\
}

#define ASSERT_NO_THROW(X) \
try {\
  X;\
} catch (const std::exception& err) {\
  std::cout << "expected " << #X << " to throw no exception, but got " << err.what() << std::endl;\
  RESULT(false);\
  return false;\
}\
catch (...) {\
  std::cout << "expected " << #X << " to throw no exception, but got a non-std::exception" << std::endl;\
  RESULT(false);\
  return false;\
}

#define STARTING(X) std::cout << "Starting test_" << #X << "..." << std::endl;
#define TEST(X) STARTING(X); test_##X() ? pass_cnt++ : fail_cnt++;
#define SKIP(X) std::cout << "Skipping test_" << #X << "..." << std::endl; skip_cnt++;

std::ostream& operator<<(std::ostream& os, std::nullptr_t) {
  os << "nullptr";
  return os;
}

template <typename T1, typename T2>
void explain_eq(
    const char n1[],
    const T1& o1,
    const char n2[],
    const T2& o2,
    const char func[],
    const size_t line) {
  std::cout << func << ":" << line << ": Failure" << std::endl;
  std::cout << "Expected equality of these values:" << std::endl;
  std::cout << " " << n1 << std::endl;
  std::cout << "  Which is: " << o1 << std::endl;
  std::cout << " " << n2 << std::endl;
  std::cout << "  Which is: " << o2 << std::endl;
}

template <typename T1, typename T2>
void explain_ne(
    const char n1[],
    const T1& o1,
    const char n2[],
    const T2& o2,
    const char func[],
    const size_t line) {
  std::cout << func << ":" << line << ": Failure" << std::endl;
  std::cout << "Expected inequality of these values:" << std::endl;
  std::cout << " " << n1 << std::endl;
  std::cout << "  Which is: " << o1 << std::endl;
  std::cout << " " << n2 << std::endl;
  std::cout << "  Which is: " << o2 << std::endl;
}

void explain_tf(
    const char name[],
    bool actual,
    bool expected,
    const char func[],
    const size_t line) {
  std::cout << func << ":" << line << ": Failure" << std::endl;
  std::cout << "Value of " << name << std::endl;
  std::cout << "  Actual: " << (actual?"true":"false") << std::endl;
  std::cout << " Expected: " << (expected?"true":"false") << std::endl;
}

template <typename T1, typename T2>
void explain_lt(
    const char n1[],
    const T1& o1,
    const char n2[],
    const T2& o2,
    const char func[],
    const size_t line) {
  std::cout << func << ":" << line << ": Failure" << std::endl;
  std::cout << "Expected" << std::endl;
  std::cout << " " << n1 << std::endl;
  std::cout << "  Which is: " << o1 << std::endl;
  std::cout << "to be <" << std::endl;
  std::cout << " " << n2 << std::endl;
  std::cout << "  Which is: " << o2 << std::endl;
}

template <typename T1, typename T2>
void explain_le(
    const char n1[],
    const T1& o1,
    const char n2[],
    const T2& o2,
    const char func[],
    const size_t line) {
  std::cout << func << ":" << line << ": Failure" << std::endl;
  std::cout << "Expected" << std::endl;
  std::cout << " " << n1 << std::endl;
  std::cout << "  Which is: " << o1 << std::endl;
  std::cout << "to be <=" << std::endl;
  std::cout << " " << n2 << std::endl;
  std::cout << "  Which is: " << o2 << std::endl;
}

template <typename T1, typename T2>
void explain_gt(
    const char n1[],
    const T1& o1,
    const char n2[],
    const T2& o2,
    const char func[],
    const size_t line) {
  std::cout << func << ":" << line << ": Failure" << std::endl;
  std::cout << "Expected" << std::endl;
  std::cout << " " << n1 << std::endl;
  std::cout << "  Which is: " << o1 << std::endl;
  std::cout << "to be >" << std::endl;
  std::cout << " " << n2 << std::endl;
  std::cout << "  Which is: " << o2 << std::endl;
}

template <typename T1, typename T2>
void explain_ge(
    const char n1[],
    const T1& o1,
    const char n2[],
    const T2& o2,
    const char func[],
    const size_t line) {
  std::cout << func << ":" << line << ": Failure" << std::endl;
  std::cout << "Expected" << std::endl;
  std::cout << " " << n1 << std::endl;
  std::cout << "  Which is: " << o1 << std::endl;
  std::cout << "to be >=" << std::endl;
  std::cout << " " << n2 << std::endl;
  std::cout << "  Which is: " << o2 << std::endl;
}

template <typename T1, typename T2>
void explain_near(
    const char n1[],
    const T1& o1,
    const char n2[],
    const T2& o2,
    const char func[],
    const size_t line) {
  std::cout << func << ":" << line << ": Failure" << std::endl;
  std::cout << "Expected" << std::endl;
  std::cout << " " << n1 << std::endl;
  std::cout << "  Which is: " << o1 << std::endl;
  std::cout << "to be near" << std::endl;
  std::cout << " " << n2 << std::endl;
  std::cout << "  Which is: " << o2 << std::endl;
}

#endif  // TEST_HELPERS_H
