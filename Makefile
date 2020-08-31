# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: osalmine <osalmine@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/03/19 19:13:02 by osalmine          #+#    #+#              #
#    Updated: 2020/08/29 16:16:28 by osalmine         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = lem-in

FLAGS = -Wall -Werror -Wextra -g

SOURCES_DIR = ./src/
SOURCES_FILE =	lem_in.c init.c read.c flags.c free.c find.c guide_ants.c \
				init_ants.c find_paths.c assign_paths.c print_paths.c
SOURCES = $(addprefix $(SOURCES_DIR), $(SOURCES_FILE))

HEADERS_LIST = lem.h
HEADERS_DIR = ./includes/
HEADERS = $(addprefix $(HEADERS_DIR), $(HEADERS_LIST))

LIBFT_DIR = libft/
LIBFT = $(LIBFT_DIR)libft.a

LIBRARIES = -lft -L$(LIBFT_DIR)
INCLUDES = -I$(HEADERS_DIR) -I$(LIBFT_DIR)

OBJECTS_DIR = obj/
OBJECTS_FILE = $(patsubst %.c, %.o, $(SOURCES_FILE))
OBJECTS	= $(addprefix $(OBJECTS_DIR), $(OBJECTS_FILE))

RESET		= \e[0m
YELLOW		= \e[33m
BLUE		= \e[34m
MAGENTA		= \e[35m

$(NAME): all

all: $(LIBFT) $(OBJECTS_DIR) $(OBJECTS)
	@gcc $(FLAGS) $(LIBRARIES) $(INCLUDES) $(OBJECTS) -o $(NAME)
	@printf "$(MAGENTA)%-42s$(RESET)\n" "Compiled $(NAME)"

$(OBJECTS_DIR):
	@mkdir -p $(OBJECTS_DIR)
	@printf "$(OBJECTS_DIR) was created"

$(OBJECTS_DIR)%.o : $(SOURCES_DIR)%.c $(HEADERS)
	@gcc $(FLAGS) -c $(INCLUDES) $< -o $@
	@printf "$(ITALIC)$(BLUE)%-42.42s$(RESET)\r" "Compiled $@"

$(LIBFT):
	@$(MAKE) -sC $(LIBFT_DIR)
	@printf "$(BLUE)Compiled $(LIBFT)$(RESET)\n"

clean:
	@$(MAKE) -sC $(LIBFT_DIR) clean
	@rm -rf $(OBJECTS_DIR)
	@printf "$(YELLOW)Removed $(OBJECTS_DIR) directory$(RESET)\n"

fclean: clean
	@$(MAKE) -sC $(LIBFT_DIR) fclean
	@rm -f $(NAME)
	@printf "$(YELLOW)Removed $(NAME)$(RESET)\n"

re: fclean all

.PHONY: all clean fclean re
