##
## EPITECH PROJECT, 2021
## Makefile
## File description:
## makefile
##

NAME		=	42sh

TESTS		=	unit_test

CC		=	gcc

RM		=	rm -f

GCOVR		=	gcovr

LIB		=	-L./lib/my -lmy

INC		=	-I./include

CRIT		=	-lcriterion

COVER		=	--coverage

BRANCH		=	--branches

EXCLUD		=	--exclude

CFLAGS 		=	-Wall -Wextra

CPPFLAGS        =       $(INC)

SRC_DIR		=	src/

BUILT_DIR	=	$(SRC_DIR)builtins/

LIB_DIR		=	lib/my

TESTS_DIR	=	tests/

OBJ		=	$(SRC:.c=.o)

UNIT_TEST	=	$(TESTS_DIR)tests_mysh.c			\

SRC		=	$(SRC_DIR)main.c                                \
			$(SRC_DIR)minishell.c                           \
			$(SRC_DIR)my_env.c                              \
			$(SRC_DIR)handle_error.c			\
			$(SRC_DIR)operator.c				\
			$(BUILT_DIR)echo.c				\
			$(BUILT_DIR)my_setenv.c				\
			$(BUILT_DIR)my_unsetenv.c				\
			$(BUILT_DIR)my_cd.c				\

all:	$(NAME)

$(NAME):	$(OBJ)
	$(MAKE) -C $(LIB_DIR)
	$(CC) -o $(NAME) $(OBJ) $(LIB) $(CSFML) -lm

db:     CFLAGS += -g3
db:		$(OBJ)
	$(MAKE) -C $(LIB_DIR)
	$(CC) -o $(NAME) $(OBJ) $(LIB) $(CSFML) -lm

unit_tests:
	$(MAKE) -C $(LIB_DIR)
	$(CC) -o $(TESTS) $(UNIT_TEST) $(LIB) $(INC) $(COVER) $(CRIT)

run_tests: unit_tests
	./unit_test
	$(GCOVR) $(EXCLUD) $(TESTS_DIR)
	$(GCOVR) $(EXCLUD) $(TESTS_DIR) $(BRANCH)

clean:
	$(MAKE) -C $(LIB_DIR) clean
	$(RM) $(OBJ) *gc*

fclean:	clean
	$(MAKE) -C $(LIB_DIR) fclean
	$(RM) $(NAME) $(TESTS)

re:	fclean all

redb:   fclean db

.PHONY:         all tests fclean re db redb
