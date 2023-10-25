CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c11
OS := $(shell uname)

ifeq ($(OS),Linux)
FLAGS = -lcheck -lm -lpthread -lrt -lsubunit -fprofile-arcs -ftest-coverage
else
FLAGS = -lcheck -lm -lpthread -fprofile-arcs -ftest-coverage
endif

all: clean s21_matrix.a

test: clean s21_matrix.a
	$(CC) unit_test.c s21_matrix.a $(FLAGS) -o unit_test
	./unit_test

test2: clean s21_matrix.a
	$(CC) ./tests/* s21_matrix.a $(FLAGS) -o unit_test
	./unit_test

s21_matrix.a:
	$(CC) $(CFLAGS) -c s21_matrix.c
	ar -crs s21_matrix.a s21_matrix.o

gcov_report: clean
	$(CC) unit_test.c s21_matrix.c $(FLAGS) -o unit_test
	./unit_test
	lcov -t "./unit_test"  -o report.info --no-external -c -d .
	genhtml -o report report.info
	open ./report/index.html

	rm -rf *.gcno *gcda *.gco

clean:
	rm -rf *.o *.a unit_test
	rm -rf *.gcno *gcda *.gcov gcov
	rm -rf report report.info

valgrind: test
	CK_FORK=no valgrind --vgdb=no --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose ./unit_test

leak: test
	leaks --atExit -- ./unit_test
