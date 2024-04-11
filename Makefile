CC = gcc
CFLAGS = -Wall -Wextra -std=c99
OBJECTS= main.c liste_chainee.c stats.c
EXEC= recherche 
STATFILE= *.gcov *.gcda *.gcno stats.txt resultat_recettes.txt
README=README.md
README_HTML=README.html


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

# HTML
# ----

html:
	pandoc $(README) -o $(README_HTML)


# Clean
# ----

clean:
	rm -f test $(EXEC) $(STATFILE)
	rm -f $(README_HTML)


.PHONY: clean build cunits html