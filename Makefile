CXX ?= g++ # C++ compiler
CXXFLAGS ?= --std=c++20 -O3
FIND_IF_ARGS1 ?= 100000000 390 404 1
FIND_IF_ARGS2 ?= 100000000 280 285 8

ifneq ("$(shell which clang-format)","")
  export FORMAT=clang-format
else
  export FORMAT=cat
endif

test: find_if_tests utf_test

find_if_tests: find_if_test1 find_if_test2

find_if_test1: find_if_test.exe
	./find_if_test.exe $(FIND_IF_ARGS1) | grep result > $@.out
	diff $@.out $@.out.correct

find_if_test2: find_if_test.exe
	./find_if_test.exe $(FIND_IF_ARGS2) | grep result > $@.out
	diff $@.out $@.out.correct

utf_test: utf_test.exe
	-./$@.exe > $@.out
	diff $@.out $@.out.correct

find_if_test.exe: find_if_test.cpp find_if.hpp async_find_if.hpp
	$(CXX) $(CXXFLAGS) $(@:.exe=.cpp) -o $@

utf_test.exe: utf_test.cpp utf.hpp
	$(CXX) $(CXXFLAGS) $(@:.exe=.cpp) -o $@

utf_test.preprocess:
	cat utf.hpp utf_test.cpp | grep -v -e '#\s*include' -e '#\s*pragma' | \
		$(CXX) $(CXXFLAGS) -E -xc++ - | $(FORMAT) > utf_test.E.cpp

clean:
	rm -rf *.out *.exe *.E.cpp
