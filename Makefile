# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dtrigalo <dtrigalo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/02/15 15:21:21 by anleclab          #+#    #+#              #
#    Updated: 2019/07/05 09:50:35 by dtrigalo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = corewar
NAME2 = asm
NAME3 = unassembler

CFLAGS = -Wall -Wextra -Werror -g3 -fsanitize=address
SRC = op.c \
	  announce_winner.c \
	  arena_setup.c \
	  battle.c \
	  dump.c \
	  end.c \
	  get_champions.c \
	  get_options.c \
	  initialize.c \
	  instr_add.c \
	  instr_aff.c \
	  instr_and.c \
	  instr_fork.c \
	  instr_ld.c \
	  instr_ldi.c \
	  instr_lfork.c \
	  instr_live.c \
	  instr_lld.c \
	  instr_lldi.c \
	  instr_or.c \
	  instr_st.c \
	  instr_sti.c \
	  instr_sub.c \
	  instr_xor.c \
	  instr_zjmp.c \
	  introduce_champions.c \
	  main.c \
	  order_champions.c \
	  tools_get_champions.c \
	  tools_instr.c \
	  tools_instr2.c \
	  tools_procs.c \
	  get_attribute.c \
	  draw_arenas.c \
	  create_color_panel.c \
	  init_visu.c \
	  manage_arena_info.c \
	  manage_speed.c \
	  manage_arena_period_bar.c \
	  manage_arena.c \
	  tools_breakdowns.c

SRCASSEMBLER = check_instruction.c \
			   check_token.c \
				op.c\
			   error.c free.c\
			   get_token.c\
			   init.c\
			   label.c\
			   parsing.c\
			   recognize.c\
				test.c\
				token.c\
				verify.c\
				write_champion.c\
				desas_instruction.c\
				write_champion_code.c

MAIN_ASSEMBLER = asm.c
MAIN_UNASSEMBLER = desasssembler.c

SRCSFD = srcs/
OBJSFD = objs/
OBJSVM = $(addprefix $(OBJSFD)$(VMFOLDER),$(SRC:.c=.o))
OBJSASM = $(addprefix $(OBJSFD)$(ASMFOLDER),$(SRCASSEMBLER:.c=.o))
OBJSASM += $(addprefix $(OBJSFD)$(ASMFOLDER),$(MAIN_ASSEMBLER:.c=.o))
OBJSUNASM = $(addprefix $(OBJSFD)$(ASMFOLDER),$(SRCASSEMBLER:.c=.o))
OBJSUNASM += $(addprefix $(OBJSFD)$(ASMFOLDER),$(MAIN_UNASSEMBLER:.c=.o))
VMFOLDER = corewar/
ASMFOLDER = assembler/
HDR = corewar.h op.h asm.h
HDRSFD = includes/
HDRS = $(addprefix $(HDRSFD),$(HDR))

HDR_INC = -I./$(HDRSFD)
LIBFT_HDR = -I./ft_printf/includes -I./ft_printf/libft/inc
LIB_BINARY = -L./ft_printf -lftprintf -lncurses
LIBFT= ft_printf/libftprintf.a

RED = \033[0;31m
GREEN = \033[0;32m
NONE = \033[0m
BOLD_UNDERLINED = \033[1;4m

all: make_start check_libft project $(NAME) $(NAME2) $(NAME3) $(HDRS)
	@echo "\n\033[1;4;42m!! Success !!$(NONE)\n"

$(NAME): $(OBJSFD) $(OBJSVM) $(LIBFT) $(HDRS)
	@gcc $(CFLAGS) $(OBJSVM) $(LIB_BINARY) -o $@
	@echo "[ $(GREEN)✔$(NONE) ] $@ executable"

$(NAME2): $(OBJSFD) $(OBJSASM) $(LIBFT) $(HDRS)
	@gcc  $(OBJSASM) $(LIB_BINARY) -o $@
	@echo "[ $(GREEN)✔$(NONE) ] $@ executable"

$(NAME3): $(OBJSFD) $(OBJSUNASM) $(LIBFT) $(HDRS)
	@gcc  $(OBJSUNASM) $(LIB_BINARY) -o $@
	@echo "[ $(GREEN)✔$(NONE) ] $@ executable"

make_start:
	@echo "\n\033[1;4;42mBeginning process...$(NONE)"

check_libft:
	@echo "\n$(BOLD_UNDERLINED)<| Checking libft_printf |>$(NONE)\n"
	@make -C ft_printf

project:
	@echo "\n$(BOLD_UNDERLINED)<| Checking project |>$(NONE)\n"

$(OBJSFD):
	@mkdir $@
	@mkdir $@/$(VMFOLDER)
	@mkdir $@/$(ASMFOLDER)
	@echo "[ $(GREEN)✔$(NONE) ] objs/ directory"

$(OBJSFD)$(VMFOLDER)%.o: $(SRCSFD)$(VMFOLDER)%.c $(HDRS) $(LIBFT)
	@gcc $(CFLAGS) $(HDR_INC) $(LIBFT_HDR) -c $< -o $@
	@echo "[ $(GREEN)✔$(NONE) ] $@ object"

$(OBJSFD)$(ASMFOLDER)%.o: $(SRCSFD)$(ASMFOLDER)%.c $(HDRS) $(LIBFT)
	@gcc  $(HDR_INC) $(LIBFT_HDR) -c $< -o $@
	@echo "[ $(GREEN)✔$(NONE) ] $@ object"

clean:
	@/bin/rm -rf $(OBJSFD)
	@echo "[ $(RED)✗$(NONE) ] $(OBJSFD) directory"
	@make -C ./ft_printf clean

fclean: clean
	@/bin/rm -f $(NAME) $(NAME2) $(NAME3)
	@echo "[ $(RED)✗$(NONE) ] $(NAME), $(NAME2), $(NAME3) executables"
	@make -C ./ft_printf fclean

re: fclean all

.PHONY: make_start all check_libft project clean fclean re
