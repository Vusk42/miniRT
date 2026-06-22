# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marudlof <marudlof@42angouleme.fr>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/06/22 16:48:00 by marudlof          #+#    #+#              #
#    Updated: 2026/06/22 16:48:00 by marudlof         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
#
# **************************************************************************** #
# 								NAME PROJECT				   				   #
# **************************************************************************** #
#
NAME	=	libvec.a

# **************************************************************************** #
#								COMMANDS									   #
# **************************************************************************** #
#
AR		=	@ar rcs
CC		=	@cc
CFLAGS	=	-Wall -Wextra -Werror
IFLAGS	=	-Iincludes
MK		=	@mkdir -p
RM		=	@rm -rf
FILE	=	$(shell ls -lR srcs/ | grep -F .c | wc -l)
CMP		=	1
CLEAR	=	@clear

# **************************************************************************** #
# 								   COLORS				   					   #
# **************************************************************************** #
#
GREEN	=	\033[38;5;76m
RED		=	\033[38;5;160m
YELLOW	=	\033[38;5;226m
ORANGE	=	\033[38;5;202m
PURPLE	=	\033[38;5;213m
LBLUE	=	\033[38;5;51m
BLUE	=	\033[38;5;117m
INDI	=	\033[38;5;99m
RESET	=	\033[00m


# **************************************************************************** #
# 								   EMOJIS				   					   #
# **************************************************************************** #
#
EMOJI_BUILD		=	🔨
EMOJI_OK		=	✅
EMOJI_CLEAN		=	🧹
EMOJI_FCLEAN	=	💥
EMOJI_LIB		=	📦
EMOJI_RE		=	🔄

# **************************************************************************** #
# 								   UI / BOX				  					   #
# **************************************************************************** #
# (largeur calée sur le Makefile principal : 70 colonnes)
BARLEN	:=	68
BOXW	:=	63
BAR		:=	$(shell printf '─%.0s' $$(seq 1 $(BARLEN)))

# $(call print_box,COLOR,EMOJI,TITRE)
define print_box
@printf "$(1)╭$(BAR)╮$(RESET)\n$(1)│$(RESET) $(2) %-*s$(1) │$(RESET)\n$(1)╰$(BAR)╯$(RESET)\n" $(BOXW) "$(3)"
endef

# **************************************************************************** #
# 								   PRINTS				  					   #
# **************************************************************************** #
#
RNBW	=	@printf "\r\033[2K$(EMOJI_LIB) $(RED)Lib$(ORANGE)vec$(YELLOW) is$(GREEN) re$(LBLUE)ady $(INDI)to $(PURPLE)use$(RESET)  $(EMOJI_OK)\n"

# **************************************************************************** #
# 								   SOURCES				     				   #
# **************************************************************************** #
#
# BASE
BASE_DIR	:=	base
SRC_BASE	:=	vec_new.c vec_add.c vec_sub.c vec_scale.c vec_neg.c
BASE		:=	$(SRC_BASE:%=$(BASE_DIR)/%)
# PROD
PROD_DIR	:=	prod
SRC_PROD	:=	vec_dot.c vec_cross.c vec_mul.c
PROD		:=	$(SRC_PROD:%=$(PROD_DIR)/%)
# NORM
NORM_DIR	:=	norm
SRC_NORM	:=	vec_len.c vec_len2.c vec_normalize.c vec_dist.c
NORM		:=	$(SRC_NORM:%=$(NORM_DIR)/%)
# RAY
RAY_DIR		:=	ray
SRC_RAY		:=	vec_reflect.c vec_lerp.c vec_clamp.c
RAY			:=	$(SRC_RAY:%=$(RAY_DIR)/%)
# ALL SOURCES
SRCS_DIR	:=	srcs
ALL_SRCS	:=	$(BASE) $(PROD) $(NORM) $(RAY)
SRCS		:=	$(ALL_SRCS:%=$(SRCS_DIR)/%)
# OBJECTS
OBJS_DIR	:=	.objs
OBJS		:=	$(addprefix $(OBJS_DIR)/, $(SRCS:%.c=%.o))

# **************************************************************************** #
# 								     RULES									   #
# **************************************************************************** #
all: $(NAME)

$(OBJS_DIR)/%.o: %.c
	$(MK) $(@D)
	@printf "\r\033[2K  $(EMOJI_BUILD) $(LBLUE)[$(RESET)$(CMP)$(LBLUE)/$(RESET)$(FILE)$(LBLUE)]$(RESET)  $(GREEN)$<$(RESET)"
	$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@
	@$(eval CMP=$(shell echo $$(($(CMP)+1))))

$(NAME): $(OBJS)
	$(AR) $(NAME) $(OBJS)
	$(RNBW)

# **************************************************************************** #
# 								     TESTS									   #
# **************************************************************************** #
TEST_SRC	:=	tests/test_vec.c
TEST_BIN	:=	tests/test_vec

test: $(NAME)
	$(call print_box,$(LBLUE),$(EMOJI_BUILD),Building libvec tests...)
	$(CC) $(CFLAGS) $(IFLAGS) $(TEST_SRC) $(NAME) -lm -o $(TEST_BIN)
	@./$(TEST_BIN)

clean:
	$(RM) $(OBJS_DIR)
	$(call print_box,$(YELLOW),$(EMOJI_CLEAN),libvec objects cleaned)

fclean: clean
	$(RM) $(NAME) $(TEST_BIN)
	$(call print_box,$(RED),$(EMOJI_FCLEAN),libvec.a removed)

re: fclean all
	$(call print_box,$(PURPLE),$(EMOJI_RE),libvec rebuilt from scratch)

.PHONY: all clean fclean re test
