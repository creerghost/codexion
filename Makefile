# **************************************************************************** #
#                                                                              #
#                                                                              #
#    Makefile                                                                  #
#                                                                              #
#                                                                              #
# **************************************************************************** #

NAME		= codexion

# ──────────────────────────── Directories ──────────────────────────────────── #
SRC_DIR		= coders
OBJ_DIR		= obj

# ──────────────────────────── Compiler / Flags ─────────────────────────────── #
CC			= cc
CFLAGS		= -Wall -Wextra -Werror -pthread
INCLUDES	= -I$(SRC_DIR)

# ──────────────────────────── Source Files ──────────────────────────────────── #
SRC			= $(wildcard $(SRC_DIR)/*.c) # remove wildcard later, just to make things easier for now
OBJ			= $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# ──────────────────────────── Colors ───────────────────────────────────────── #
GREEN		= \033[1;32m
YELLOW		= \033[1;33m
RED			= \033[1;31m
RESET		= \033[0m

# ──────────────────────────── Test ─────────────────────────────────────────── #
TEST_DIR	= tests

# ──────────────────────────── Rules ────────────────────────────────────────── #
all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
	@printf "$(GREEN)✔ $(NAME) compiled successfully$(RESET)\n"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

clean:
	@$(MAKE) -C $(TEST_DIR) clean
	@rm -rf $(OBJ_DIR)
	@printf "$(YELLOW)✔ Object files removed$(RESET)\n"

fclean: clean
	@rm -f $(NAME)
	@printf "$(RED)✔ $(NAME) removed$(RESET)\n"

fclean-venv: fclean
	@rm -rf $(TEST_DIR)/.venv
	@printf "$(YELLOW)✔ Virtual environment removed$(RESET)\n"

re: fclean all

test:
	@$(MAKE) -C $(TEST_DIR) test

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
	@printf "  test         - Run tests\n"
	@printf "  help         - Show this help message\n"

.PHONY: all clean fclean re test help
