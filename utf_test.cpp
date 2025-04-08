#include "utf.hpp"

TEST(foo) {
  ASSERT_TRUE(1);
  ASSERT_EQUAL(3, 4 - 1);
}

TEST(bar) {
  ASSERT_TRUE(0);
}

TEST(baz) {
  ASSERT_EQUAL(0, 2 - 1);
}

TEST(qux) {
  throw std::exception();
}

TEST(xyzzy) {
  throw "xyzzy";
}

TEST_MAIN()
