UV = uv
PYTHON = $(UV) run python
GREEN		= \033[1;32m
RESET		= \033[0m
YELLOW		= \033[1;33m

CC = cc
CFLAGS = -Wall -Wextra -Werror -fPIC -I../coders

SRC_DIR = ../coders
OBJ_DIR_PY = ../obj_py
SRCS = $(SRC_DIR)/parser.c $(SRC_DIR)/atoi_codex.c $(SRC_DIR)/util_strings.c
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR_PY)/%.o)

all: test

install:
	@printf "$(YELLOW)Installing dependencies...$(RESET)\n"
	$(UV) sync

$(OBJ_DIR_PY):
	mkdir -p $(OBJ_DIR_PY)

$(OBJ_DIR_PY)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR_PY)
	$(CC) $(CFLAGS) -c $< -o $@

libcodexion.so: $(OBJS)
	$(CC) -shared -o $@ $^

clean:
	rm -rf $(OBJ_DIR_PY) __pycache__ .pytest_cache
	@printf "$(YELLOW)Caches in tests/ removed...$(RESET)\n"
	rm -rf $(OBJ_DIR_PY)
	@printf "$(YELLOW)Object files in tests/ removed...$(RESET)\n"
	rm -rf $(OBJ_DIR_PY) libcodexion.so
	@printf "$(YELLOW)Shared library in tests/ removed...$(RESET)\n"


test: install libcodexion.so
	@printf "$(GREEN)Running tests...$(RESET)\n"
	@$(PYTHON) test_parser.py
	@printf "$(GREEN)✔ All tests passed$(RESET)\n"

.PHONY: all install test clean