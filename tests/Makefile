# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vlnikola <vlnikola@student.42prague.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/09/09 00:23:04 by vlnikola          #+#    #+#              #
#    Updated: 2026/09/09 01:03:18 by vlnikola         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ---VARIABLES------------------------------------------------------------------

CC			= cc
CFLAGS		= -Wall -Wextra -Werror -pthread
INCLUDES	= -I../include

SRC			= ../src/parser/flagged_atoi.c \
			../src/parser/process_args.c

TEST_SRC	= test_parser.c
TEST_BIN	= run_tests

G			= \033[1;32m
Y			= \033[1;33m
R			= \033[1;31m
RS			= \033[90m

# ---TARGETS---------------------------------------------------------------------

all: $(TEST_BIN)

$(TEST_BIN): $(TEST_SRC) $(SRC)
	@printf "$(RS)"
	$(CC) $(CFLAGS) $(INCLUDES) $(TEST_SRC) $(SRC) -o $(TEST_BIN)
	@printf "$(G)$(TEST_BIN) compiled successfully! 🚀\n$(RS)"

run: $(TEST_BIN)
	@if ./$(TEST_BIN) 2>/tmp/codexion_test.err >/dev/null; then \
		printf "$(G)All tests passed! ✅\n$(RS)"; \
	else \
		printf "$(R)Tests failed:\n$(RS)"; \
		cat /tmp/codexion_test.err; \
		rm -f /tmp/codexion_test.err; \
		exit 1; \
	fi

test: run

clean:
	@printf "$(RS)"
	@rm -f $(TEST_BIN)
	@printf "$(Y)Test binary removed 🚮$(RS)\n"

fclean: clean

re: fclean all

.PHONY: all run test clean fclean re
