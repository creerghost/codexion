# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vlnikola <vlnikola@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/09/08 22:00:53 by vlnikola          #+#    #+#              #
#    Updated: 2026/09/13 15:31:22 by vlnikola         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ---VARIABLES------------------------------------------------------------------

NAME		= codexion
SRC_DIR		= src
OBJ_DIR		= obj
CC			= cc
CFLAGS		= -Wall -Wextra -Werror -pthread
INCLUDES	= -Iinclude

SRC			= $(SRC_DIR)/main.c \
				$(SRC_DIR)/application/application_init.c \
				$(SRC_DIR)/application/application_run.c \
				$(SRC_DIR)/application/application_free.c \
				$(SRC_DIR)/parser/parse_number.c \
				$(SRC_DIR)/parser/parse_args.c \
				$(SRC_DIR)/context/context_init.c \
				$(SRC_DIR)/context/context_state.c \
				$(SRC_DIR)/queue/queue_init.c \
				$(SRC_DIR)/queue/queue_heap.c \
				$(SRC_DIR)/queue/queue_compare.c \
				$(SRC_DIR)/dongle/dongle_init.c \
				$(SRC_DIR)/dongle/dongle_request.c \
				$(SRC_DIR)/dongle/dongle_release.c \
				$(SRC_DIR)/coder/coder_init.c \
				$(SRC_DIR)/coder/coder_data.c \
				$(SRC_DIR)/coder/coder_routine.c \
				$(SRC_DIR)/gate/gate.c \
				$(SRC_DIR)/scheduler/scheduler_init.c \
				$(SRC_DIR)/scheduler/scheduler_request.c \
				$(SRC_DIR)/scheduler/scheduler_routine.c \
				$(SRC_DIR)/scheduler/scheduler_grant.c \
				$(SRC_DIR)/monitor/monitor_init.c \
				$(SRC_DIR)/monitor/monitor_routine.c \
				$(SRC_DIR)/utils/logger.c \
				$(SRC_DIR)/utils/time.c

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
	@printf "  help         - Show this help message\n"

.PHONY: all clean fclean re valgrind helgrind help
