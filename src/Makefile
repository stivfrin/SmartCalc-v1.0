BD=build/
CC = gcc
FLAGS = -Wall -Werror -Wextra -std=c11
TST_LIBS = -lcheck
APP=$(BD)SmartCalcc.app

all:

install: 
	mkdir $(BD)
	cd $(BD); qmake ../Core/SmartCalcc.pro
	cd $(BD); make
	
uninstall:
	rm -rf $(BD)

dist: clean
	mkdir SmartCalc
	cp Core/*.c Core/*.h Core/*.ui Core/SmartCalcc.pro Core/SmartCalcc.pro.user Makefile Doxyfile SmartCalc
	tar -cvzf dist.tar.gz SmartCalc
	-rm -rf SmartCalc

dvi:
	doxygen Doxyfile && mv html documentation
	open documentation/index.html

test:
	$(CC) $(FLAGS) Core/s21_tests.c Core/s21_SmartCalc_v1_0.c $(TST_LIBS) -lm  -lsubunit -o test
	./test

gcov_report:
	$(CC) $(FLAGS)  Core/s21_tests.c Core/s21_SmartCalc_v1_0.c $(TST_LIBS) -o unit-test -lm  -lsubunit --coverage
	./unit-test
	lcov -t "test" -o test.info -c -d .
	genhtml -o report test.info
	open report/index.html

clean:
	@rm -rf $(OUT) *.a *.gch *.gcno *.gcna *.gcda *.info *.dSYM test_html .qmake.stash unit-test test report documentation latex *.gz SmartCalc