TEST=tests
CC=g++
CFLAGS=-Wall -Wextra -Werror -std=c++17
FILE_EXISTS=0

all: clean $(TEST)

$(TEST): $(TEST).cpp
	@ $(CC) $(CFLAGS) $^ -lgtest -o $@
	@ ./$@

leaks: $(TEST).cpp
ifneq ("$(wildcard $(TEST))","")
	@ leaks --atExit -- ./$(TEST)
else
	@ $(CC) $(CFLAGS) $^ -lgtest -o $(TEST)
	@ leaks --atExit -- ./$(TEST)
endif

cpplint :
	@ cp ../materials/linters/CPPLINT.cfg ./
	@-python3 ../materials/linters/cpplint.py --extensions=cpp *.cpp
	@-python3 ../materials/linters/cpplint.py --extensions=hpp *.hpp
	@ $(RM) CPPLINT.cfg

cppcheck :
	@ cppcheck --std=c++17 --enable=all --check-config --suppress=missingIncludeSystem --suppress=missingInclude --suppress=unmatchedSuppression *.cpp *.hpp *.h


clean:
	@rm -f *.o *.a $(TEST)
