COMPILLER = gcc

PATH_LIBS = ./libs

PATH_TABEL_LIB_FILES = Tabel

NAME_FILE = tabel.c

NAME_OBJECT_FILE = tabel

NAME_RUN_FILE = run

export LD_LIBRARY_PATH=.:LD_LIBRARY_PATH

all: compile_program

compile_program: make compile_funcrions compile_main compile

compile_program_dynamic: make_dynamic compile_funcrions compile_main compile_dynamic

compile_program_iter: make compile_funcrions_iter compile_main compile

compile_program_dynamic_iter: make_dynamic compile_funcrions_iter compile_main compile_dynamic

compile:
	$(COMPILLER) *.o -L./ -l:$(NAME_OBJECT_FILE).a -o $(NAME_RUN_FILE) -g
	rm ./$(NAME_OBJECT_FILE).a
	rm ./*.o

make:
	make -f $(PATH_LIBS)/$(PATH_TABEL_LIB_FILES)/makefile creat ARG=$(PATH_LIBS)/$(PATH_TABEL_LIB_FILES)/

compile_dynamic:
	$(COMPILLER) *.o -L./ -l:$(NAME_OBJECT_FILE).so -o $(NAME_RUN_FILE) -ldl -g
	rm ./*.o

make_dynamic:
	make -f $(PATH_LIBS)/$(PATH_TABEL_LIB_FILES)/makefile creat_dynamic ARG=$(PATH_LIBS)/$(PATH_TABEL_LIB_FILES)/

compile_main:
	$(COMPILLER) -c main.c -Wall -Wextra -g
	$(COMPILLER) -c program.c -Wall -Wextra -g
	$(COMPILLER) -c menu.c -Wall -Wextra -g
	$(COMPILLER) -c ./libs/Gets/gets.c -Wall -Wextra -g

compile_funcrions:
	$(COMPILLER) -c functions.c -Wall -Wextra -g

compile_funcrions_iter:
	$(COMPILLER) -c functions_iter.c -Wall -Wextra -g

start:
	./$(NAME_RUN_FILE)

start_valgrind:
	valgrind ./$(NAME_RUN_FILE)
