#pragma once
// find_if.hpp

namespace eecs390 {

  // REQUIRES: Iterator must be a LegacyRandomAccessIterator (see
  //           https://en.cppreference.com/w/cpp/named_req/RandomAccessIterator);
  //           begin must be before or equal to end;
  //           pred must be invocable on each element in [begin, end)
  // EFFECTS: Returns an iterator to the first element in [begin, end)
  //          for which pred returns a true value, or end if no such
  //          element exists.
  template<typename Iterator, typename Predicate>
  Iterator find_if(Iterator begin, Iterator end, Predicate pred) {
    return end;  // replace with your code
  }

}
