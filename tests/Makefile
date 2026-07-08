UV = uv
PYTHON = $(UV) run python
GREEN		= \033[1;32m
RESET		= \033[0m
YELLOW		= \033[1;33m

CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread -I../coders

OBJ_DIR = ../obj
OBJS = $(OBJ_DIR)/parser.o $(OBJ_DIR)/atoi_codex.o $(OBJ_DIR)/util_strings.o
C_MAINS_DIR = c_mains
PY_DIR = scripts

all: test

install:
	@printf "$(YELLOW)Installing dependencies...$(RESET)\n"
	$(UV) sync

test_parser: $(C_MAINS_DIR)/test_parser.c $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -rf __pycache__ .pytest_cache
	@printf "$(YELLOW)Caches in tests/ removed...$(RESET)\n"
	rm -rf test_parser
	@printf "$(YELLOW)Test executable in tests/ removed...$(RESET)\n"

test: install test_parser
	@printf "$(GREEN)Running tests...$(RESET)\n"
	@$(PYTHON) $(PY_DIR)/test_parser.py
	@printf "$(GREEN)✔ All tests passed$(RESET)\n"

.PHONY: all install test clean