# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vlnikola <vlnikola@student.42prague.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/09/08 22:00:53 by vlnikola          #+#    #+#              #
#    Updated: 2026/09/08 22:14:59 by vlnikola         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ---VARIABLES------------------------------------------------------------------

NAME		= codexion
SRC_DIR		= src
OBJ_DIR		= obj
TEST_DIR	= tests
CC			= cc
CFLAGS		= -Wall -Wextra -Werror -pthread
INCLUDES	= -Iincludes

SRC			= $(SRC_DIR)/main.c

OBJ			= $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

G			= \033[1;32m
Y			= \033[1;33m
R			= \033[1;31m
RS			= \033[90m

# ---TARGETS---------------------------------------------------------------------

all: $(NAME)

$(NAME): $(OBJ)
	@printf "$(RS)"
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
	@printf "$(G)$(NAME) compiled successfully! 🚀\n$(RS)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@printf "$(RS)"
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

clean:
	@printf "$(RS)"
	@$(MAKE) -C $(TEST_DIR) clean
	@rm -rf $(OBJ_DIR)
	@printf "$(Y)Object files removed 🚮$(RS)\n"

fclean: clean
	@printf "$(RS)"
	@rm -f $(NAME)
	@printf "$(R)$(NAME) removed $(RS)\n"

re: fclean all

valgrind: all
	valgrind ./$(NAME) $(ARGS)

helgrind: all
	valgrind --tool=helgrind ./$(NAME) $(ARGS)

help:
	@printf "Welcome to the Makefile for the project!\n"
	@printf "This project has been created as a part of 42 curriculum by vlnikola.\n"
	@printf "\n"
	@printf "Available targets:\n"
	@printf "  all          - Compile the project\n"
	@printf "  valgrind     - Run ./codexion with valgrind. Args should be provided. Usage: make valgrind ARGS='3 800 200 200 7 0 FIFO'\n"
	@printf "  helgrind     - Run ./codexion with helgrind. Args should be provided. Usage: make helgrind ARGS='3 800 200 200 7 0 FIFO'\n"
	@printf "  clean        - Remove object files and caches\n"
	@printf "  fclean       - Remove object files, caches and the project\n"
	@printf "  re           - Recompile the project\n"
	@printf "  test         - Run all tests\n"
	@printf "  help         - Show this help message\n"

.PHONY: all clean fclean re valgrind helgrind help