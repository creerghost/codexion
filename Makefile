# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vlnikola <vlnikola@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/07/08 22:38:27 by vlnikola          #+#    #+#              #
#    Updated: 2026/07/09 16:03:11 by vlnikola         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= codexion

SRC_DIR		= src
OBJ_DIR		= obj
TEST_DIR	= tests

CC			= cc
CFLAGS		= -Wall -Wextra -Werror -pthread
INCLUDES	= -Iincludes

ARGS ?=

SRC			= $(SRC_DIR)/main.c \
				$(SRC_DIR)/heap.c \
				$(SRC_DIR)/parser.c \
				$(SRC_DIR)/dongle.c \
				$(SRC_DIR)/routine.c \
				$(SRC_DIR)/monitor.c \
				$(SRC_DIR)/utils/logging.c \
				$(SRC_DIR)/utils/atoi_codex.c \
				$(SRC_DIR)/utils/heap_utils.c \
				$(SRC_DIR)/utils/time_utils.c \
				$(SRC_DIR)/utils/utils.c \
				$(SRC_DIR)/utils/util_strings.c \
				$(SRC_DIR)/inits/init_coders.c \
				$(SRC_DIR)/inits/init_dongles.c \
				$(SRC_DIR)/inits/init_context.c

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

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@printf "$(RESET)"
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

valgrind: all
	valgrind ./$(NAME) $(ARGS)

helgrind: all
	valgrind --tool=helgrind ./$(NAME) $(ARGS)


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
	@$(MAKE) -C $(TEST_DIR) test_sim

test-all: re
	@$(MAKE) -C $(TEST_DIR) test_all

test-parser: re
	@$(MAKE) -C $(TEST_DIR) test_parser

test-heap: re
	@$(MAKE) -C $(TEST_DIR) test_heap

test-dongle: re
	@$(MAKE) -C $(TEST_DIR) test_dongle

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
	@printf "  test-parser  - Run parser tests\n"
	@printf "  test-heap    - Run heap tests\n"
	@printf "  test-dongle  - Run dongle tests\n"
	@printf "  help         - Show this help message\n"

.PHONY: all clean fclean re test test-parser test-heap test-dongle help
