# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: osalmine <osalmine@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/03/19 19:13:02 by osalmine          #+#    #+#              #
#    Updated: 2020/10/22 17:31:26 by osalmine         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = lem-in

FLAGS = -Wall -Werror -Wextra -g

SOURCES_DIR = ./src/
SOURCES_SUBDIR_READ = read/
SOURCES_SUBDIR_SOLVE = solve/
SOURCES_SUBDIR_UTILS = utils/

READ_DIR_SOURCES	= 	init.c read.c flags.c init_ants.c read_link.c
SOLVE_DIR_SOURCES	= 	guide_ants.c find_paths.c assign_paths.c \
						bfs.c ek_pathfinder.c
UTILS_DIR_SOURCES	= 	frees.c find.c print_paths.c utils.c \
						sort_paths.c utils2.c add_path.c assign_flows_weights.c
SOURCE_FILE_NAMES	=	lem_in.c $(READ_DIR_SOURCES) $(SOLVE_DIR_SOURCES) $(UTILS_DIR_SOURCES)
SOURCE_FILES		=	lem_in.c $(addprefix $(SOURCES_SUBDIR_READ), $(READ_DIR_SOURCES)) \
						$(addprefix $(SOURCES_SUBDIR_SOLVE), $(SOLVE_DIR_SOURCES)) \
						$(addprefix $(SOURCES_SUBDIR_UTILS), $(UTILS_DIR_SOURCES))
SOURCES = $(addprefix $(SOURCES_DIR), $(SOURCE_FILES))

HEADER_FILE = lem.h
HEADER_DIR = ./includes/
HEADER = $(addprefix $(HEADER_DIR), $(HEADER_FILE))

OBJECTS_DIR = ./obj/
OBJECTS_FILE = $(patsubst %.c, %.o, $(SOURCE_FILES))
OBJECTS	= $(addprefix $(OBJECTS_DIR), $(OBJECTS_FILE))

LIBFT_DIR = ./libft/
LIBFT = $(LIBFT_DIR)libft.a

LIBRARIES = -lft -L$(LIBFT_DIR)
INCLUDES = -I$(HEADER_DIR) -I$(LIBFT_DIR)

RESET		= \e[0m
YELLOW		= \e[33m
BLUE		= \e[34m
MAGENTA		= \e[35m

all: $(NAME)

$(NAME): $(LIBFT) $(OBJECTS_DIR) $(OBJECTS)
	@gcc $(FLAGS) $(LIBRARIES) $(INCLUDES) $(OBJECTS) -o $(NAME)
	@printf "$(MAGENTA)%-42s$(RESET)\n" "Compiled $(NAME)"

$(OBJECTS_DIR):
	@mkdir -p $(OBJECTS_DIR) $(OBJECTS_DIR)read $(OBJECTS_DIR)solve $(OBJECTS_DIR)utils
	@printf "$(OBJECTS_DIR) was created"

$(OBJECTS_DIR)%.o : $(SOURCES_DIR)%.c $(HEADER)
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
