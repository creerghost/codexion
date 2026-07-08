# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vlnikola <vlnikola@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/07/08 22:38:27 by vlnikola          #+#    #+#              #
#    Updated: 2026/07/08 22:45:56 by vlnikola         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= codexion

SRC_DIR		= src
OBJ_DIR		= obj
TEST_DIR	= tests

CC			= cc
CFLAGS		= -Wall -Wextra -Werror -pthread
INCLUDES	= -Iincludes

SRC			= $(SRC_DIR)/main.c \
				$(SRC_DIR)/atoi_codex.c \
				$(SRC_DIR)/heap.c \
				$(SRC_DIR)/heap_utils.c \
				$(SRC_DIR)/logging.c \
				$(SRC_DIR)/parser.c \
				$(SRC_DIR)/time_utils.c \
				$(SRC_DIR)/util_strings.c

OBJ			= $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

GREEN		= \033[1;32m
YELLOW		= \033[1;33m
RED			= \033[1;31m
RESET		= \033[90m


all: $(NAME)

$(NAME): $(OBJ)
	@printf "$(RESET)"
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
	@printf "$(GREEN)$(NAME) compiled successfully$(RESET)\n"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@printf "$(RESET)"
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

clean:
	@printf "$(RESET)"
	@$(MAKE) -C $(TEST_DIR) clean
	@rm -rf $(OBJ_DIR)
	@printf "$(YELLOW)Object files removed$(RESET)\n"

fclean: clean
	@rm -f $(NAME)
	@printf "$(RED)$(NAME) removed$(RESET)\n"

fclean-venv: fclean
	@rm -rf $(TEST_DIR)/.venv
	@printf "$(YELLOW)Virtual environment removed$(RESET)\n"

re: fclean all

test: re
	@$(MAKE) -C $(TEST_DIR) test_all

test_parser: re
	@$(MAKE) -C $(TEST_DIR) test_parser

test_heap: re
	@$(MAKE) -C $(TEST_DIR) test_heap

help:
	@printf "Welcome to the Makefile for the project!\n"
	@printf "This project has been created as a part of 42 curriculum by vlnikola.\n"
	@printf "\n"
	@printf "Available targets:\n"
	@printf "  all          - Compile the project\n"
	@printf "  clean        - Remove object files and caches\n"
	@printf "  fclean       - Remove object files, caches and the project\n"
	@printf "  fclean-venv  - Remove object files, caches, the project and virtual environment\n"
	@printf "  re           - Recompile the project\n"
	@printf "  test         - Run all tests\n"
	@printf "  test_parser  - Run parser tests\n"
	@printf "  test_heap    - Run heap tests\n"
	@printf "  help         - Show this help message\n"

.PHONY: all clean fclean re test test_parser test_heap help
