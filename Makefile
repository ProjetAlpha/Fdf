# **************************************************************************** #
#                                                           LE - /             #
#                                                               /              #
#    Makefile                                         .::    .:/ .      .::    #
#                                                  +:+:+   +:    +:  +:+:+     #
#    By: thbrouss <marvin@le-101.fr>                +:+   +:    +:    +:+      #
#                                                  #+#   #+    #+    #+#       #
#    Created: 2018/10/24 17:57:21 by thbrouss     #+#   ##    ##    #+#        #
#    Updated: 2019/03/11 18:44:52 by thbrouss    ###    #+. /#+    ###.fr      #
#                                                          /                   #
#                                                         /                    #
# **************************************************************************** #

.PHONY: all clean fclean re

NAME = fdf
MAKE = make
CC = gcc
FLAGS = -Wall -Wextra -Werror
INCLUDE = ./includes
MLX = -L mlx_lib/ -lmlx -framework OpenGL -framework AppKit

SRC_PATH = ./src/
BIN_PATH	=	./bins/
LIB_PATH = ./minilibx_macos/

#----------------------------------SOURCE--------------------------------------#

SRC = $(wildcard $(SRC_PATH)*.c)

BIN_RM = $(wildcard $(BIN_PATH)*.o)

#----------------------------------OBJECT--------------------------------------#

BIN	=	$(patsubst $(SRC_PATH)%.c,./bins/%.o,$(SRC))

#-----------------------------------RULE---------------------------------------#

LIB = ./mlx_lib/libmlx.a

all: $(NAME)

$(NAME): $(LIB) $(BIN)
	@echo "\033[1m|---------FDF COMPILE--------------|\033[0m"
	@$(CC) $(FLAGS) -I $(INCLUDE) $(MLX) -o $@ $^

$(LIB):
	@make -C $(LIB_PATH)
	@cp $(LIB_PATH)libmlx.a ./mlx_lib/

$(BIN_PATH)%.o: $(SRC_PATH)%.c $(INCLUDE)/fdf.h
		@mkdir -p $(BIN_PATH) && 2> /dev/null
		@$(CC) -I $(INCLUDE) $(FLAGS) -o $@ -c $<

clean:
	@echo "\033[1m|---------------------------------|\033[0m"
	@echo "\033[1m|-------Supprimer les OBJECTS------|\033[0m"
	@echo "\033[1m|---------------------------------|\033[0m"
	@rm -f $(BIN_RM)
	@make clean -C $(LIB_PATH)

fclean: clean
	@echo "\n"
	@echo "\033[1m|---------------------------------|\033[0m"
	@echo "\033[1m|-------Supprimer l'executable------|\033[0m"
	@echo "\033[1m|---------------------------------|\033[0m"
	@rm -f $(NAME)
	@mkdir -p $(BIN_PATH) && 2> /dev/null
	@rmdir $(BIN_PATH) && 2> /dev/null

re: fclean all

print-%  : ; @echo $* = $($*)
