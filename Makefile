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
	@rm -rf $(OBJ_DIR)
	@printf "$(YELLOW)✔ Object files removed$(RESET)\n"

fclean: clean
	@rm -f $(NAME)
	@printf "$(RED)✔ $(NAME) removed$(RESET)\n"

re: fclean all

.PHONY: all clean fclean re
