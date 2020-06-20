# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: osalmine <osalmine@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/03/19 19:13:02 by osalmine          #+#    #+#              #
#    Updated: 2020/06/19 19:50:18 by osalmine         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = lem_in

FLAGS = -Wall -Werror -Wextra

SOURCES_DIR = ./src/
SOURCES_FILE = lem_in.c init.c read.c flags.c free.c find.c
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

$(NAME): all

all: $(LIBFT) $(OBJECTS_DIR) $(OBJECTS)
	gcc $(FLAGS) $(LIBRARIES) $(INCLUDES) $(OBJECTS) -o $(NAME)

$(OBJECTS_DIR):
	mkdir -p $(OBJECTS_DIR)
	@echo "$(OBJECTS_DIR) was created"

$(OBJECTS_DIR)%.o : $(SOURCES_DIR)%.c $(HEADERS)
	gcc $(FLAGS) -c $(INCLUDES) $< -o $@
	@echo ". \c"

$(LIBFT):
	$(MAKE) -sC $(LIBFT_DIR)

$(ECHO):
	@echo "Echoing"

clean:
	$(MAKE) -sC $(LIBFT_DIR) clean
	rm -rf $(OBJECTS_DIR)

fclean: clean
	$(MAKE) -sC $(LIBFT_DIR) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
