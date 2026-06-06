#include <hashtaroth.hpp>
#include <gtest/gtest.h>


TEST(HashtarothTest, ctor_dtor) {
  const hashtaroth::Hashtaroth test;
}

TEST(HashtarothTest, start_dtor) {
  hashtaroth::Hashtaroth test;
  test.start();
}