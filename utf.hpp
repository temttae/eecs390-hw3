#pragma once
// utf.hpp
// A simple unit-test framework, based on the one in EECS 280.

#include <exception>
#include <iostream>
#include <string>
#include <vector>

// used for assertion failures
class UTFFailure : std::exception {
public:
  UTFFailure(const std::string &message) : message(message) {}
  const char* what() const noexcept override {
    return message.c_str();
  }
private:
  std::string message;
};

// base class for test cases
class UTFTestCase {
public:
  // declaration only -- ctor registers test case, which requires the
  // definition to come after UTFTestSuite
  UTFTestCase(const std::string &name);
  const std::string& get_name() const { return name; }
  virtual void run() = 0;
private:
  std::string name;
};

// singleton for test registration
class UTFTestSuite {
public:
  // EFFECTS: Returns a pointer to the singleton instance of this class.
  static UTFTestSuite* get() {
    // replace with your code
  }

  // EFFECTS: Registers the given test case.
  void register_test(UTFTestCase *test) {
    tests.push_back(test);
  }

  // EFFECTS: Runs all the test cases in order, reporting their results.
  int run_tests() {
    int failed = 0;
    for (auto test : tests) {
      try {
        test->run();
        std::cout << "Test " << test->get_name() << " passed"
                  << std::endl;
      } catch (const UTFFailure &error) {
        ++failed;
        std::cout << "Test " << test->get_name() << " failed "
                  << error.what() << std::endl;
      } catch (const std::exception &error) {
        ++failed;
        std::cout << "Test " << test->get_name()
                  << " failed with exception: " << error.what()
                  << std::endl;
      } catch (...) {
        ++failed;
        std::cout << "Test " << test->get_name()
                  << " failed with unknown exception" << std::endl;
      }
      endl(std::cout);
    }
    std::cout << "Passed " << (tests.size() - failed) << " of "
              << tests.size() << " test(s) " << std::endl;
    if (failed) {
      std::cout << "Failed " << failed << " of " << tests.size()
                << " test(s)" << std::endl;
    } else {
      std::cout << "All tests passed" << std::endl;
    }
    return failed;
  }

private:
  static UTFTestSuite *test_suite; // pointer to the singleton instance
  // private ctor does not allow anyone else to create a UTFTestSuite,
  // ensuring we have a singleton
  UTFTestSuite() = default;
  // deleted copy ctor also needed to ensure singleton
  UTFTestSuite(const UTFTestSuite &) = delete;
  // not strictly necessary, but why not
  UTFTestSuite& operator=(const UTFTestSuite &) = delete;
  std::vector<UTFTestCase*> tests; // the test cases in this suite
};

// now we can define the UTFTestCase ctor
// EFFECTS: Registers this test case with the singleton test suite.
UTFTestCase::UTFTestCase(const std::string &name) : name(name) {
  UTFTestSuite::get()->register_test(this);
}

// Defines a test case. See utf_test.cpp for what a test case looks
// like.
// This needs to:
// 1) Define a derived class of UTFTestCase, with the appropriate
//    constructor and a declaration of the run() method.
// 2) Create an instance of the derived class.
// 3) Define the run() method of the derived class, using the body
//    that follows the TEST(...) invocation.
#define TEST(name)  // replace with your code

// Defines the main() function for the test file.
#define TEST_MAIN()                                     \
  UTFTestSuite *UTFTestSuite::test_suite;               \
  int main() {                                          \
    UTFTestSuite *test_suite = UTFTestSuite::get();     \
    int result = test_suite->run_tests();               \
    delete test_suite;                                  \
    return result;                                      \
  }

// Checks whether or not the given value is true, throwing a
// UTFFailure if it is not. See utf_test.out.correct for the format of
// message that should be passed to the UTFFailure constructor.
// diagnostic is the actual text of the assertion.
#define UTF_CHECK(value, diagnostic)  // replace with your code

#define ASSERT_TRUE(expr)                       \
  UTF_CHECK(expr, "ASSERT_TRUE(" # expr ")")

#define ASSERT_EQUAL(expr1, expr2)                                      \
  UTF_CHECK(expr1 == expr2, "ASSERT_EQUAL(" #expr1 ", " #expr2 ")")
