# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bcarolle <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/01 00:00:00 by ysabik            #+#    #+#              #
#    Updated: 2024/01/21 16:28:39 by bcarolle         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC					= cc
CFLAGS				= -Werror -Wall -Wextra -g
CLIBS				= -lreadline
NAME				= minishell
BUILD_DIR			= ./build
INCLUDES			= ./includes
SRC_FILES			= \
						src/parsing/parse.c \
						src/execution/exec.c \
						src/execution/redirection.c \
						src/builtins/cd.c \
						src/builtins/echo.c \
						src/builtins/env.c \
						src/builtins/exit.c \
						src/builtins/export.c \
						src/builtins/pwd.c \
						src/builtins/unset.c \
						src/utils/ft_strdup.c \
						src/utils/ft_strlen.c \
						src/utils/ft_strcmp.c \
						src/utils/ft_envcpy.c \
						src/utils/ft_strcpy.c \
						src/utils/ft_strcat.c \
						src/utils/ft_putstr_fd.c \
						src/utils/ft_strstr.c \
						src/main.c

C_RESET				= \033[0m
C_BOLD				= \033[1m
C_DIM				= \033[2m
C_UNDERLINE			= \033[4m
C_BLINK				= \033[5m
C_BLACK				= \033[30m
C_RED				= \033[31m
C_GREEN				= \033[32m
C_YELLOW			= \033[33m
C_BLUE				= \033[34m
C_MAGENTA			= \033[35m
C_CYAN				= \033[36m
C_WHITE				= \033[37m

OBJ_FILES			= $(SRC_FILES:.c=.o)
BUILD_FILES			= $(SRC_FILES:%.c=$(BUILD_DIR)/%.o)

TO_COMPILE			= 0

all : $(NAME)

$(NAME) : $(BUILD_FILES)
	@echo -n "  > $(C_YELLOW)$(C_BOLD)./$(NAME)$(C_RESET):  $(C_DIM)"
	$(CC) -o $(NAME) $(BUILD_FILES) -I $(INCLUDES) $(CFLAGS) $(CLIBS)
	@echo "$(C_RESET)"
	@echo ""
	@echo -n "$(C_BOLD)$(C_MAGENTA)>$(C_BLUE)>$(C_CYAN)>$(C_GREEN)"
	@echo -n " Compilation success ! "
	@echo "$(C_CYAN)<$(C_BLUE)<$(C_MAGENTA)<$(C_RESET)"
	@echo ""

m_line_break :
	@echo ""

bonus:
	@echo "$(C_RED)$(C_BOLD)There is no bonus for this project.$(C_RESET)"

$(BUILD_DIR)/%.o : %.c
	@if [ $(TO_COMPILE) -eq 0 ] ; then \
		echo -n "$(C_CYAN)$(C_BOLD)$(C_UNDERLINE)" ; \
		echo "Compiling $(C_YELLOW)./$(NAME)$(C_CYAN)... :$(C_RESET)" ; \
		echo "" ; \
	fi
	@$(eval TO_COMPILE := 1)
	@echo -n "  - $(C_GREEN)$<$(C_RESET):  $(C_DIM)"
	@mkdir -p $(@D)
	$(CC) -c $< -o $@ -I $(INCLUDES) $(CFLAGS)
	@echo -n "$(C_RESET)"

define del =
	@echo -n "$(C_RED)$(C_BOLD)$(C_UNDERLINE)"
	@echo "Deleting files... :$(C_RESET)$(C_RED)"
	@\
	l=-1 ; \
	for file in $(1) ; do \
		if [ $${#file} -gt $$l ] ; then \
			l=$${#file} ; \
		fi ; \
	done ; \
	cols=$$((64 / $$l)) ; \
	i=0 ; \
	for file in $(1) ; do \
		if [ $$i -eq 0 ] ; then \
			echo -n "    " ; \
		fi ; \
		if [ "$$file" = "./$(NAME)" ] ; then \
			printf "$(C_YELLOW)%-$$((l))s  $(C_RED)" "$$file" ; \
		else \
			printf "%-$$((l))s  " "$$file" ; \
		fi ; \
		if [ $$i -gt $$cols ] ; then \
			echo "" ; \
			i=-1; \
		fi ; \
		i=$$(($$i + 1)); \
	done ; \
	if [ $$i -ne -1 ] ; then \
		echo "" ; \
	fi
	@echo "$(C_RESET)"
endef

clean :
	$(call del, $(BUILD_DIR) $(BUILD_FILES))
	@rm -rf $(BUILD_FILES) $(BUILD_DIR)

fclean :
	$(call del, "./$(NAME)" $(BUILD_DIR) $(BUILD_FILES))
	@rm -rf $(NAME) $(BUILD_FILES) $(BUILD_DIR)

re : fclean m_line_break all

.PHONY : all bonus clean fclean re
