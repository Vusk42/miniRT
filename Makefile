# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marudlof <marudlof@42.angouleme.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/06/22 12:00:04 by marudlof          #+#    #+#              #
#    Updated: 2026/06/22 12:10:27 by marudlof         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ==============================================================================
# NAME & PROJECT
# ==============================================================================
NAME	=	miniRT

# ==============================================================================
# COMMANDS
# ==============================================================================
CC		=	@cc
CFLAGS	=	-Wall -Wextra -Werror -g
MK		=	@mkdir -p
RM		=	@rm -rf
FILE	=	$(shell ls -lR srcs/ | grep -F .c | wc -l)
CMP		=	1
CLEAR	=	@clear

# ==============================================================================
# COLORS
# ==============================================================================
GREEN	=	\033[38;5;76m
RED		=	\033[38;5;160m
YELLOW	=	\033[38;5;226m
ORANGE	=	\033[38;5;202m
PURPLE	=	\033[38;5;213m
LBLUE	=	\033[38;5;51m
BLUE	=	\033[38;5;117m
INDI	=	\033[38;5;99m
RESET	=	\033[00m

# ==============================================================================
# EMOJIS
# ==============================================================================
EMOJI_BUILD		=	🔨
EMOJI_OK		=	✅
EMOJI_CLEAN		=	🧹
EMOJI_FCLEAN	=	💥
EMOJI_LIB		=	📦
EMOJI_RE		=	🔄
EMOJI_LINK		=	🔗

# ==============================================================================
# UI / BOX (largeur calée sur l'art : 70 colonnes)
# ==============================================================================
BARLEN	:=	68
BOXW	:=	63
BAR		:=	$(shell printf '─%.0s' $$(seq 1 $(BARLEN)))

# $(call print_box,COLOR,EMOJI,TITRE)
define print_box
@printf "$(1)╭$(BAR)╮$(RESET)\n$(1)│$(RESET) $(2) %-*s$(1) │$(RESET)\n$(1)╰$(BAR)╯$(RESET)\n" $(BOXW) "$(3)"
endef

# ==============================================================================
# PRINTS
# ==============================================================================
PRINTS	=	@printf "$(RED)█▀▀▀▀▀▀▀▀▀▄▀▀▀▀▀▄  █▀▀▀▀█ █▀▀▀▀▀▀▀▀▀▄  █▀▀▀▀█ █▀▀▀▀▀▀▀▀▀▄  █▀▀▀▀▀▀▀▀▀▀█$(RESET)\n" && \
			printf "$(ORANGE)▀    ▄▄     ▄    █ ▀    ▓ ▀    ▄▄    █ ▀    ▓ ▀    ▄▄  ∙ █ █▄▄▄·   ▄▄▄█$(RESET)\n" && \
			printf "$(YELLOW)▓    ▓ ▌   ▓ ▌   ▓ ▓    ▓ ▓    ▓ ▌   ▓ ▓    ▓ ▓    ▓▄▌   ▓    ▓  . ▓   $(RESET)\n" && \
			printf "$(GREEN)▒    ▒ ▒ · ▒ ▒ · ▒ ▒   ·▒ ▒    ▒ ▒ · ▒ ▒   ·▒ ▒   ·▄▄▄  ▀▄    ▒ ∙  ▒   $(RESET)\n" && \
			printf "$(LBLUE)░   ∙░ ░   ░ ░   ░ ░ .  ░ ░   ∙░ ░   ░ ░ .  ░ ░ .  ░ ░  .░    ░    ░   $(RESET)\n" && \
			printf "$(INDI)█ ∙  █ █   █ █   █ █    █ █ ∙  █ █   █ █    █ █    █ █∙  █    █    █   $(RESET)\n" && \
			printf "$(PURPLE)█▄▄▄▄█ █▄▄▄█ █▄▄▄█ █▄▄▄▄█ █▄▄▄▄█ █▄▄▄█ █▄▄▄▄█ █▄▄▄▄█ █▄▄▄█    █▄▄▄▄█   $(RESET)\n" && \
			printf "                        by $(PURPLE)dakaymak$(RESET) & $(PURPLE)marudlof$(RESET) $(EMOJI_OK)\n"

# ==============================================================================
# SOURCES
# ==============================================================================
SRCS_DIR	=	srcs
OBJS_DIR	=	.objs

ALL_SRCS	=	main.c \
				window/window.c \
				window/hooks.c \
				render/render.c \
				utils/color.c \
				utils/exit.c
SRCS		=	$(ALL_SRCS:%=$(SRCS_DIR)/%)

OBJS	=	$(addprefix $(OBJS_DIR)/, $(SRCS:%.c=%.o))

LIB_PATH	=	./libft --no-print-directory
LIB_NAME	=	./libft/libft.a

VEC_PATH	=	./libvec --no-print-directory
VEC_NAME	=	./libvec/libvec.a

MLX_DIR		=	./MLX42
MLX_BUILD	=	$(MLX_DIR)/build
MLX_NAME	=	$(MLX_BUILD)/libmlx42.a
MLX_FLAGS	=	$(MLX_NAME) -ldl -lglfw -pthread -lm

IFLAGS		=	-Iincludes -Ilibft/includes -Ilibvec/includes -I$(MLX_DIR)/include

# ==============================================================================
# RULES
# ==============================================================================
all: $(MLX_NAME) $(LIB_NAME) $(VEC_NAME) $(NAME)

$(OBJS_DIR)/%.o: %.c
	$(MK) $(@D)
	@printf "\r\033[2K  $(EMOJI_BUILD) $(LBLUE)[$(RESET)$(CMP)$(LBLUE)/$(RESET)$(FILE)$(LBLUE)]$(RESET)  $(GREEN)$<$(RESET)"
	$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@
	@$(eval CMP=$(shell echo $$(($(CMP)+1))))

$(LIB_NAME):
	$(call print_box,$(YELLOW),$(EMOJI_LIB),Building libft...)
	@make -C $(LIB_PATH)

$(VEC_NAME):
	$(call print_box,$(LBLUE),$(EMOJI_LIB),Building libvec...)
	@make -C $(VEC_PATH)

$(MLX_NAME):
	$(call print_box,$(ORANGE),$(EMOJI_LIB),Building MLX42...)
	@cmake -B $(MLX_BUILD) $(MLX_DIR) -Wno-dev >/dev/null
	@cmake --build $(MLX_BUILD) -j4 >/dev/null

$(NAME): $(MLX_NAME) $(OBJS)
	@printf "\r\033[2K  $(EMOJI_OK) $(GREEN)$(FILE) files compiled$(RESET)\n"
	$(call print_box,$(BLUE),$(EMOJI_LINK),Linking $(NAME)...)
	$(CC) $(CFLAGS) $(IFLAGS) $(OBJS) $(LIB_NAME) $(VEC_NAME) $(MLX_FLAGS) -lreadline -o $(NAME)
	$(PRINTS)

clean:
	$(RM) $(OBJS_DIR)
	$(call print_box,$(YELLOW),$(EMOJI_CLEAN),Objects cleaned)

fclean: clean
	@make fclean -C $(LIB_PATH)
	@make fclean -C $(VEC_PATH)
	$(RM) $(NAME)
	$(RM) $(MLX_BUILD)
	$(call print_box,$(RED),$(EMOJI_FCLEAN),$(NAME), libft, libvec and MLX42 removed)

re: fclean all
	$(call print_box,$(PURPLE),$(EMOJI_RE),Rebuilt from scratch)

# Dev : recompile uniquement miniRT, garde libft.a et libmlx42.a
re-dev:
	$(RM) $(OBJS_DIR) $(NAME)
	@make --no-print-directory all
	$(call print_box,$(PURPLE),$(EMOJI_RE),Dev rebuild (libs kept))

# clangd : (re)génère compile_commands.json (pour nvim/LSP)
cdb:
	@python3 tools/gen_cdb.py
	$(call print_box,$(LBLUE),$(EMOJI_LINK),compile_commands.json generated)

.PHONY: all clean fclean re re-dev cdb
