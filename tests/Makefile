# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vlnikola <vlnikola@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/07/08 22:36:59 by vlnikola          #+#    #+#              #
#    Updated: 2026/07/09 00:53:13 by vlnikola         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

UV = uv
PYTHON = $(UV) run python -m pytest -v -s --no-header

OBJ_DIR = ../obj
C_MAINS_DIR = c_mains
PY_DIR = scripts
EXEC_DIR = execs

CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread -I../includes

OBJS = $(OBJ_DIR)/heap.o \
	$(OBJ_DIR)/parser.o \
	$(OBJ_DIR)/utils/logging.o \
	$(OBJ_DIR)/utils/atoi_codex.o \
	$(OBJ_DIR)/utils/heap_utils.o \
	$(OBJ_DIR)/utils/time_utils.o \
	$(OBJ_DIR)/utils/utils.o \
	$(OBJ_DIR)/utils/util_strings.o \
	$(OBJ_DIR)/inits/init_coders.o \
	$(OBJ_DIR)/inits/init_dongles.o \
	$(OBJ_DIR)/inits/init_context.o

GREEN		= \033[1;32m
RESET		= \033[90m
YELLOW		= \033[1;33m

all: test_all

install:
	@printf "$(YELLOW)Installing dependencies...$(RESET)\n"
	$(UV) sync

$(EXEC_DIR):
	mkdir -p $(EXEC_DIR)

$(EXEC_DIR)/test_parser: $(C_MAINS_DIR)/test_parser.c $(OBJS) | $(EXEC_DIR)
	$(CC) $(CFLAGS) -o $@ $^

$(EXEC_DIR)/test_heap: $(C_MAINS_DIR)/test_heap.c $(OBJS) | $(EXEC_DIR)
	$(CC) $(CFLAGS) -o $@ $^

test_parser: install $(EXEC_DIR)/test_parser
	@printf "$(GREEN)Running parser tests...$(RESET)\n"
	@$(PYTHON) $(PY_DIR)/test_parser.py
	@printf "$(GREEN)Parser tests passed$(RESET)\n"

test_heap: install $(EXEC_DIR)/test_heap
	@printf "$(GREEN)Running heap tests...$(RESET)\n"
	@$(PYTHON) $(PY_DIR)/test_heap.py
	@printf "$(GREEN)Heap tests passed$(RESET)\n"

test_all: test_parser test_heap
	@printf "$(GREEN)\nAll tests passed!$(RESET)\n"

clean:
	rm -rf __pycache__ .pytest_cache
	@printf "$(YELLOW)Caches in tests/ removed...$(RESET)\n"
	rm -rf $(EXEC_DIR)
	@printf "$(YELLOW)Test executables in tests/ removed...$(RESET)\n"

.PHONY: all install clean test_parser test_heap test_all