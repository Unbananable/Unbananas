# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anleclab <anleclab@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/02/15 15:21:21 by anleclab          #+#    #+#              #
#    Updated: 2019/04/26 18:16:31 by anleclab         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = corewar

CFLAGS = -Wall -Wextra -Werror -g3 -fsanitize=address
SRC = main.c \
	  end.c \
	  get_champions.c \
	  initialize.c \
	  dev.c
SRCSFD = srcs_cor/
OBJSFD = objs_cor/
OBJS = $(addprefix $(OBJSFD),$(SRC:.c=.o))

HDR = corewar.h op.h 
HDRSFD = includes/
HDRS = $(addprefix $(HDRSFD),$(HDR))

HDR_INC = -I./$(HDRSFD)
LIBFT_HDR = -I./libft/inc
LIB_BINARY = -L./libft -lft
LIBFT= libft/libft.a

RED = \033[0;31m
GREEN = \033[0;32m
NONE = \033[0m
BOLD_UNDERLINED = \033[1;4m

all: make_start check_libft project $(NAME) $(HDRS)
	@echo "\n\033[1;4;42m!! Success !!$(NONE)\n"

$(NAME): $(OBJSFD) $(OBJS) $(LIBFT) $(HDRS)
	@gcc $(CFLAGS) $(OBJS) $(LIB_BINARY) -o $@
	@echo "[ $(GREEN)✔$(NONE) ] $@ executable"

make_start:
	@echo "\n\033[1;4;42mBeginning process...$(NONE)"

check_libft:
	@echo "\n$(BOLD_UNDERLINED)<| Checking libft |>$(NONE)\n"
	@make -C libft

project:
	@echo "\n$(BOLD_UNDERLINED)<| Checking project |>$(NONE)\n"

$(OBJSFD):
	@mkdir $@
	@echo "[ $(GREEN)✔$(NONE) ] objs/ directory"

$(OBJSFD)%.o: $(SRCSFD)%.c $(HDRS) $(LIBFT)
	@gcc $(CFLAGS) $(HDR_INC) $(LIBFT_HDR) -c $< -o $@
	@echo "[ $(GREEN)✔$(NONE) ] $@ object"

visualizer:
	@echo "\n$(BOLD_UNDERLINED)<| Adding visualizer |>$(NONE)"
	@make -C ./bonus_visualizer

clean:
	@/bin/rm -rf $(OBJSFD)
	@echo "[ $(RED)✗$(NONE) ] $(OBJSFD) directory"
	@make -C ./libft clean

fclean: clean
	@/bin/rm -f $(NAME) visualizer
	@echo "[ $(RED)✗$(NONE) ] $(NAME) executable"
	@make -C ./libft fclean

re: fclean all

.PHONY: make_start all check_libft project clean fclean re visualizer
