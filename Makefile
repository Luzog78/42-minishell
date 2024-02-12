# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bcarolle <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/01 00:00:00 by ysabik            #+#    #+#              #
#    Updated: 2024/02/12 03:59:26 by bcarolle         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC					= cc
CFLAGS				= -Werror -Wall -Wextra -g #-fsanitize=address
CLIBS				= -lreadline
NAME				= minishell
BUILD_DIR			= ./build
INCLUDES			= ./includes
SRC_FILES			= \
						src/parsing/parse.c \
						src/execution/exec.c \
						src/execution/exec_bin.c \
						src/execution/redirection.c \
						src/execution/exec_cmds.c \
						src/execution/exec_subshell.c \
						src/execution/exec_utils.c \
						src/execution/wildcards.c \
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
						src/utils/ft_env_overwrite.c \
						src/utils/ft_strcpy.c \
						src/utils/ft_strcat.c \
						src/utils/ft_printf_err.c \
						src/utils/ft_putstr_fd.c \
						src/utils/ft_strstr.c \
						src/utils/ft_strjoin.c \
						src/utils/ft_strncmp.c \
						src/utils/ft_free.c \
						src/utils/ft_split.c \
						src/utils/ft_quote.c \
						src/utils/ft_getenv.c \
						src/utils/ft_substr.c \
						src/utils/ft_strchr.c \
						src/utils/ft_get_parent.c \
						src/utils/ft_get_value_from_env.c \
						src/utils/ft_itoa.c \
						src/utils/ft_calloc.c \
						src/utils/ft_strtrim.c \
						src/ft_sig_handling.c \
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

VALGRIND_SUPPR		= $(BUILD_DIR)/.val_suppr
VALGRIND_OUT		= $(BUILD_DIR)/.val_out
VALGRIND_ARGS		= --leak-check=full \
						--show-leak-kinds=all \
						--track-origins=yes \
						--suppressions=$(VALGRIND_SUPPR)

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

$(VALGRIND_SUPPR):
	@echo '' > $(VALGRIND_SUPPR)

	@echo	'{'						>> $(VALGRIND_SUPPR)
	@echo	'	readline'			>> $(VALGRIND_SUPPR)
	@echo	'	Memcheck:Leak'		>> $(VALGRIND_SUPPR)
	@echo	'	...'				>> $(VALGRIND_SUPPR)
	@echo	'	fun:readline'		>> $(VALGRIND_SUPPR)
	@echo	'	...'				>> $(VALGRIND_SUPPR)
	@echo	'	}'					>> $(VALGRIND_SUPPR)
	@echo	''						>> $(VALGRIND_SUPPR)
	@echo	'	{'					>> $(VALGRIND_SUPPR)
	@echo	'	readline'			>> $(VALGRIND_SUPPR)
	@echo	'	Memcheck:Leak'		>> $(VALGRIND_SUPPR)
	@echo	'	...'				>> $(VALGRIND_SUPPR)
	@echo	'	fun:add_history'	>> $(VALGRIND_SUPPR)
	@echo	'	...'				>> $(VALGRIND_SUPPR)
	@echo	'}'						>> $(VALGRIND_SUPPR)

valgrind: all $(VALGRIND_SUPPR)
	@clear
	@echo -n "$(C_MAGENTA)$(C_BOLD)$(C_UNDERLINE)"
	@echo "Running valgrind... :$(C_RESET)"
	@echo ""
	@echo "" > $(VALGRIND_OUT)
	@valgrind $(VALGRIND_ARGS) ./$(NAME) 2>&1 | tee $(VALGRIND_OUT)
	@clear
	@echo -n "$(C_MAGENTA)$(C_BOLD)$(C_UNDERLINE)"
	@echo "Running valgrind... :$(C_RESET)"
	@echo ""
	@cat $(VALGRIND_OUT) | sed -r '/^==[0-9]*==/s/(^==[0-9]*==)(.*(definitely lost|indirectly lost|possibly lost|still reachable|Invalid read|Invalid write|\.c:).*)/'$$(printf "$(C_BLACK)")'\1'$$(printf "$(C_YELLOW)")'\2'$$(printf "$(C_RESET)")'/; /==[0-9]*==/s/(.*==[0-9]*==.*)((definitely lost|indirectly lost|possibly lost|still reachable): .*)/\1'$$(printf "$(C_RED)$(C_BOLD)")'\2'$$(printf "$(C_RESET)")'/; /==[0-9]*==/s/(.*==[0-9]*==.*)((definitely lost|indirectly lost|possibly lost|still reachable): 0 bytes.*)/\1'$$(printf "$(C_RESET)$(C_BLACK)")'\2'$$(printf "$(C_RESET)")'/; /^==[0-9]*==/s/(.*)/'$$(printf "$(C_BLACK)")'\1'$$(printf "$(C_RESET)")'/;'

test:
	@make && clear && python3 tester/tester.py -b ./minishell -s tester/minishell.souffrance -o

clean :
	$(call del, $(VALGRIND_SUPPR) $(VALGRIND_OUT) $(BUILD_DIR) $(BUILD_FILES))
	@rm -rf $(BUILD_FILES) $(BUILD_DIR)

fclean :
	$(call del, "./$(NAME)" $(VALGRIND_SUPPR) $(VALGRIND_OUT) $(BUILD_DIR) $(BUILD_FILES))
	@rm -rf $(NAME) $(BUILD_FILES) $(BUILD_DIR)

re : fclean m_line_break all

.PHONY : all bonus clean fclean re valgrind m_line_break test
