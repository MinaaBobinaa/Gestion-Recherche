build:
	gcc -o exec main.c stats.c

# CUnit
# ----
cunits:
	gcc -o test test.c stats.c -lcunit -fprofile-arcs -ftest-coverage
	./test
	gcov test-stats.gcno

# Clean
# ----

clean:
	rm -f test *.gcov *.gcda *.gcno