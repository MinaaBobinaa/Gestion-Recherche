build:
	gcc -o exec main.c liste_chainee.c stats.c

# CUnit
# ----
cunits:
	gcc -o test test.c liste_chainee.c stats.c -lcunit -fprofile-arcs -ftest-coverage
	./test
	gcov test-stats.gcno
	gcov test-liste_chainee.gcno

# Clean
# ----

clean:
	rm -f test *.gcov *.gcda *.gcno