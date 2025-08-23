CC = gcc
FLAGS = -Werror -Wextra -std=c11 -Wall
OS = = $(shell uname -s)
ifeq (${OS}, Darwin)
	CFLAGS = -lrt -lcheck -lpthread
	GCFLAGS = -lrt -lcheck -lpthread -fprofile-arcs -ftest-coverage
else
	CFLAGS = -lrt -lcheck -lpthread -lsubunit
	GCFLAGS = -lrt -lcheck -lpthread -lsubunit -fprofile-arcs -ftest-coverage
endif
GAME_DIR = new_tetris_game
PROJECT_NAME = BrickGame_tetris
ZIP_DIR = tetris_zip
LATEX_DIR = docs/latex
VERSION = 1

all: clean install play

clang:
	mv ../materials/linters/.clang-format ./
	clang-format -n ./*/*/*.h
	clang-format -n ./*/*/*.c
	clang-format -n ./*/*.c
	clang-format -n ./*.h
	clang-format -n ./*.c
	mv ./.clang-format ../materials/linters

frontend.o:
	$(CC) $(FLAGS) -c ./gui/cli/frontend.c -o frontend.o

tetris.a:
	$(CC) $(FLAGS) -c ./brick_game/tetris/backend.c -o ./brick_game/tetris/backend.o
	$(CC) $(FLAGS) -c ./brick_game/tetris/common.c -o ./brick_game/tetris/common.o
	ar -crs ./brick_game/tetris/tetris.a ./brick_game/tetris/backend.o ./brick_game/tetris/common.o
	ranlib ./brick_game/tetris/tetris.a
	rm -rf ./brick_game/tetris/*.o

install: make_dir tetris.a frontend.o
	@$(CC) $(FLAGS) tetris.c frontend.o ./brick_game/tetris/tetris.a -lncurses -lm -o $(GAME_DIR)/tetris
	rm -rf frontend.o
	chmod +x $(GAME_DIR)/tetris

uninstall:
	rm -rf high_score.txt
	rm -rf $(GAME_DIR)

play:
	./$(GAME_DIR)/tetris

clean:
	rm -rf *.o *.out ./*/*.gcno ./*/*.gcda high_score.txt *.html test/test */*.c.gcov html tetris_z docs */*.css */*.gcda */*.gcno */*.html */*/*.a *.c.gcov test/tetris.a $(PROJECT_NAME)-$(VERSION) $(GAME_DIR) $(PROJECT_NAME)-$(VERSION).tar.gz $(ZIP_DIR)

test: make_dir
	$(CC) $(FLAGS) $(GCFLAGS) -c ./brick_game/tetris/backend.c -o ./test/backend.o
	$(CC) $(FLAGS) $(GCFLAGS) -c ./brick_game/tetris/common.c -o ./test/common.o
	ar -crs test/tetris.a test/backend.o test/common.o
	ranlib test/tetris.a
	rm -rf test/*.o
	$(CC) $(FLAGS) ./test/test.c test/tetris.a -o ./test/test $(GCFLAGS) -lm
	./test/test

gcov_report: test
	gcov test/backend.gcda test/backend.gcno test/common.gcda test/common.gcno
	find ./test/ ! -name "backend.*" ! -name "common.*" ! -name "test.c" ! -name "*.check" -type f -delete
	gcovr -r . --html --html-details -o test/coverage_report.html
	open test/coverage_report.html

dvi: latex_dir
	@doxygen
	@cd $(LATEX_DIR) && $(MAKE)
	open docs/html/files.html

dist: clean make_dist_dir zip_dir
	cp -r brick_game $(PROJECT_NAME)-$(VERSION)
	cp -r gui $(PROJECT_NAME)-$(VERSION)
	cp -r test $(PROJECT_NAME)-$(VERSION)
	cp -r latex $(PROJECT_NAME)-$(VERSION)
	cp tetris.h $(PROJECT_NAME)-$(VERSION)
	cp state_machine.png $(PROJECT_NAME)-$(VERSION)
	cp Makefile $(PROJECT_NAME)-$(VERSION)
	cp tetris.c $(PROJECT_NAME)-$(VERSION)
	cp Doxyfile $(PROJECT_NAME)-$(VERSION)
	tar -czvf ./$(ZIP_DIR)/$(PROJECT_NAME)-$(VERSION).tar.gz $(PROJECT_NAME)-$(VERSION)
	rm -rf $(PROJECT_NAME)-$(VERSION)

make_dir:
	mkdir -p $(GAME_DIR)

make_dist_dir:
	mkdir -p $(PROJECT_NAME)-$(VERSION)

zip_dir:
	mkdir -p $(ZIP_DIR)

latex_dir:
	mkdir -p $(LATEX_DIR)