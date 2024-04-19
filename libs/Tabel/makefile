COMPILLER = gcc

PATH_LIB_FILES = $(ARG)

NAME_FILE = tabel.c

NAME_OBJECT_FILE = tabel

all: creat

make_object_file:
	$(COMPILLER) -c $(PATH_LIB_FILES)$(NAME_FILE) -o $(NAME_OBJECT_FILE).o -fPIC -Wall -Wextra -g

creat: make_object_file
	ar r $(NAME_OBJECT_FILE).a $(NAME_OBJECT_FILE).o
	rm $(NAME_OBJECT_FILE).o

creat_dynamic: make_object_file
	$(COMPILLER) -shared -o $(NAME_OBJECT_FILE).so $(NAME_OBJECT_FILE).o
	rm $(NAME_OBJECT_FILE).o