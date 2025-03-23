# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ide-dieg <ide-dieg@student.42madrid>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/04 21:33:00 by ide-dieg          #+#    #+#              #
#    Updated: 2025/03/23 20:22:08 by ide-dieg         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

SRC =	src/main.c \
		src/ft_execution.c \
		src/ft_parsing_pipex.c \
		src/fts_files.c \
		src/ft_split_quotes.c \
		src/ft_exits.c \

SRC_BONUS = src_bonus/main_bonus.c \
			src_bonus/ft_execution_bonus.c \
			src_bonus/ft_parsing_pipex_bonus.c \
			src_bonus/ft_split_quotes_bonus.c \
			src_bonus/ft_exits_bonus.c \
			src_bonus/ft_here_doc_bonus.c \
			src_bonus/ft_pipeline_bonus.c \

CC = cc

CFLAGS = -Wall -Wextra -Werror

LIBSA = 42_Libft/libft.a \

OBJDIR = obj
OBJ = $(SRC:src/%.c=$(OBJDIR)/%.o)
OBJDIR_BONUS = obj_bonus
OBJ_BONUS = $(SRC_BONUS:src_bonus/%.c=$(OBJDIR_BONUS)/%.o)

all: $(NAME)

$(OBJDIR)/%.o: src/%.c
	@mkdir -p $(OBJDIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR_BONUS)/%.o: src_bonus/%.c
	@mkdir -p $(OBJDIR_BONUS)
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): ide-dieg pipex_title update_submodules build_libft $(OBJ)
	@echo "$(NARANJA)Building $(NAME)...$(NC)"
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBSA)
	@tput cuu1 && tput el
	@echo "$(VERDE)$(NAME) built!$(NC)"

bonus: ide-dieg pipex_title update_submodules build_libft $(OBJ_BONUS)
	@echo "$(NARANJA)Building $(NAME)...$(NC)"
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ_BONUS) $(LIBSA)
	@tput cuu1 && tput el
	@echo "$(VERDE)$(NAME) built!$(NC)"

clean: fclean_libft
	@echo "Cleaning objects..."
	@rm -rf $(OBJDIR)
	@rm -rf $(OBJDIR_BONUS)
	@echo "Objects cleaned!"

fclean: clean
	@echo "Cleaning $(NAME)..."
	@rm -f $(NAME)
	@echo "$(NAME) cleaned!"

re: fclean $(NAME)

re_bonus: fclean bonus

build_libft:
	@if [ ! -f 42_Libft/libft.a ]; then \
		echo "$(NARANJA)Compiling Libft...$(NC)"; \
		make all -C 42_Libft > /dev/null 2>&1; \
		tput cuu1 && tput el; \
		echo "$(VERDE)Libft compiled!$(NC)"; \
	fi

fclean_libft:
	@echo "Cleaning Libft..."
	@make fclean -C 42_Libft > /dev/null 2>&1
	@echo "Libft cleaned!"

update_submodules:
	@echo "$(NARANJA)Updating submodules...$(NC)"
	@git submodule update --init --recursive > /dev/null 2>&1
	@tput cuu1 && tput el
	@echo "$(VERDE)Submodules updated!$(NC)"

ROJO = \033[0;31m
NC = \033[0m
NARANJA = \033[0;33m
AZUL = \033[0;34m
VERDE = \033[0;32m

ide-dieg:
	@clear	
	@echo "$(ROJO)██╗██████╗ ███████╗    ██████╗ ██╗███████╗ ██████╗ $(AZUL)         ██╗  ██╗██████╗ "
	@echo "$(ROJO)██║██╔══██╗██╔════╝    ██╔══██╗██║██╔════╝██╔════╝ $(AZUL)         ██║  ██║╚════██╗"
	@echo "$(ROJO)██║██║  ██║█████╗█████╗██║  ██║██║█████╗  ██║  ███╗$(AZUL)         ███████║ █████╔╝"
	@echo "$(ROJO)██║██║  ██║██╔══╝╚════╝██║  ██║██║██╔══╝  ██║   ██║$(AZUL)         ╚════██║██╔═══╝ "
	@echo "$(ROJO)██║██████╔╝███████╗    ██████╔╝██║███████╗╚██████╔╝$(AZUL)              ██║███████╗"
	@echo "$(ROJO)╚═╝╚═════╝ ╚══════╝    ╚═════╝ ╚═╝╚══════╝ ╚═════╝ $(AZUL)              ╚═╝╚══════╝"
	@echo "$(NARANJA)██╗  ██╗ ██████╗ ██████╗ ███╗   ███╗██╗██████╗ ███████╗██╗   ██╗$(VERDE)       ██╗  "
	@echo "$(NARANJA)██║  ██║██╔═══██╗██╔══██╗████╗ ████║██║██╔══██╗██╔════╝██║   ██║$(VERDE)   ██╗ ╚═██╗"
	@echo "$(NARANJA)███████║██║   ██║██████╔╝██╔████╔██║██║██║  ██║█████╗  ██║   ██║$(VERDE)   ╚═╝   ██║"
	@echo "$(NARANJA)██╔══██║██║   ██║██╔══██╗██║╚██╔╝██║██║██║  ██║██╔══╝  ╚██╗ ██╔╝$(VERDE)   ██╗   ██║"
	@echo "$(NARANJA)██║  ██║╚██████╔╝██║  ██║██║ ╚═╝ ██║██║██████╔╝███████╗ ╚████╔╝ $(VERDE)   ╚═╝ ██╔═╝"
	@echo "$(NARANJA)╚═╝  ╚═╝ ╚═════╝ ╚═╝  ╚═╝╚═╝     ╚═╝╚═╝╚═════╝ ╚══════╝  ╚═══╝  $(VERDE)       ╚═╝  $(NC)"

pipex_title:
	@echo " ____  __  ____  ____  _  _ "
	@echo "(  _ \(  )(  _ \(  __)( \/ )"
	@echo " ) __/ )(  ) __/ ) _)  )  ( "
	@echo "(__)  (__)(__)  (____)(_/\_)"
