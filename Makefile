CC = gcc
CFLAGS = -Wall -Wextra -std=c99
OBJECTS= main.c liste_chainee.c stats.c
EXEC= recherche 
STATFILE= *.gcov *.gcda *.gcno stats.txt

all: clean build cunits 

# Build
# -----
build:
	$(CC) $(CFLAGS) -o $(EXEC) $(OBJECTS)

# CUnit
# ----
cunits:
	$(CC) -o test test.c liste_chainee.c stats.c -lcunit -fprofile-arcs -ftest-coverage
	./test
	gcov test-stats.gcno
	gcov test-liste_chainee.gcno

# Clean
# ----

clean:
	rm -f test $(EXEC) $(STATFILE)


.PHONY: clean build cunits