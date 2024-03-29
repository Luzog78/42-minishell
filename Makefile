# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/01 00:00:00 by ysabik            #+#    #+#              #
#    Updated: 2024/02/17 14:27:50 by ysabik           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC					= cc
CFLAGS				= -Werror -Wall -Wextra -g #-fsanitize=address
CLIBS				= -lreadline
NAME				= minishell
BUILD_DIR			= ./build
INCLUDES			= ./includes
SRC_FILES			= \
						src/parsing/subshell/ft_on_redir.c \
						src/parsing/subshell/ft_on_separator.c \
						src/parsing/subshell/ft_on_subshell.c \
						src/parsing/subshell/ft_parse_subshell.c \
						src/parsing/ft_check_parenthesis_and_quotes.c \
						src/parsing/ft_concat_lst.c \
						src/parsing/ft_error.c \
						src/parsing/ft_free_str_list.c \
						src/parsing/ft_get_next_int.c \
						src/parsing/ft_get_next_word.c \
						src/parsing/ft_get_out_redirection.c \
						src/parsing/ft_is_empty.c \
						src/parsing/ft_is_next_a_fd.c \
						src/parsing/ft_out_add.c \
						src/parsing/ft_parse_redirection.c \
						src/parsing/ft_set_parents.c \
						src/parsing/ft_set_prevs.c \
						src/parsing/ft_skip_parenthesis.c \
						src/parsing/ft_skip_whitespace.c \
						src/parsing/ft_starts_with.c \
						src/parsing/ft_stdin_add.c \
						src/parsing/ft_subshell_add.c \
						src/parsing/parse.c \
						\
						src/execution/redirections/ft_dup_infiles.c \
						src/execution/redirections/ft_dup_outfiles.c \
						src/execution/redirections/ft_heredoc.c \
						src/execution/redirections/ft_get_right_limiter.c \
						src/execution/redirections/ft_stdin.c \
						src/execution/utils/ft_allow_next_cmd.c \
						src/execution/utils/ft_args_append_str.c \
						src/execution/utils/ft_args_realloc.c \
						src/execution/utils/ft_args_reallocs.c \
						src/execution/utils/ft_str_lst_to_args.c \
						src/execution/wildcards/ft_append_wildcard.c \
						src/execution/wildcards/wc_allow.c \
						src/execution/wildcards/wc_allow_start.c \
						src/execution/wildcards/wc_allow_middle.c \
						src/execution/wildcards/wc_allow_end.c \
						src/execution/wildcards/wc_is_wildcard.c \
						src/execution/wildcards/wc_tokenize.c \
						src/execution/ft_exec.c \
						src/execution/ft_execve_bin.c \
						src/execution/ft_exec_cmd.c \
						src/execution/ft_exec_subshell.c \
						src/execution/ft_exec_next.c \
						\
						src/builtins/misc/bi_add_double_quotes.c \
						src/builtins/misc/bi_add_env.c \
						src/builtins/misc/bi_check_var.c \
						src/builtins/misc/bi_get_var.c \
						src/builtins/misc/bi_is_var_in_env.c \
						src/builtins/misc/bi_printenv.c \
						src/builtins/misc/bi_update_env.c \
						src/builtins/misc/bi_var_concat.c \
						src/builtins/cd.c \
						src/builtins/echo.c \
						src/builtins/env.c \
						src/builtins/exit.c \
						src/builtins/export.c \
						src/builtins/pwd.c \
						src/builtins/unset.c \
						\
						src/utils/libft/ft_calloc.c \
						src/utils/libft/ft_isalnum.c \
						src/utils/libft/ft_is_whitespace.c \
						src/utils/libft/ft_itoa.c \
						src/utils/libft/ft_split.c \
						src/utils/libft/ft_strcat.c \
						src/utils/libft/ft_strchr.c \
						src/utils/libft/ft_strcmp.c \
						src/utils/libft/ft_strcmp_ignore_case.c \
						src/utils/libft/ft_strcpy.c \
						src/utils/libft/ft_strdup.c \
						src/utils/libft/ft_strjoin.c \
						src/utils/libft/ft_strlen.c \
						src/utils/libft/ft_str_lst_add_back.c \
						src/utils/libft/ft_str_lst_add.c \
						src/utils/libft/ft_str_lst_pop_back.c \
						src/utils/libft/ft_strncmp.c \
						src/utils/libft/ft_strstr.c \
						src/utils/libft/ft_strtrim.c \
						src/utils/libft/ft_substr.c \
						src/utils/libft/ft_tolower.c \
						src/utils/libft/ft_memcpy.c \
						src/utils/ft_arr_char_cpy.c \
						src/utils/ft_envcpy.c \
						src/utils/ft_env_overwrite.c \
						src/utils/ft_free.c \
						src/utils/ft_getenv.c \
						src/utils/ft_get_parent.c \
						src/utils/ft_get_value_from_env.c \
						src/utils/ft_printf_err.c \
						src/utils/ft_putstr_fd.c \
						src/utils/ft_get_bash_string.c \
						src/utils/ft_get_bash_lst.c \
						src/utils/ft_quote_utils.c \
						src/utils/ft_sort_env.c \
						src/utils/ft_sort_list.c \
						src/utils/ft_subshell_init.c \
						\
						src/signals/ft_sig_handlers.c \
						src/signals/ft_sig_activer.c \
						\
						src/ft_wait_line.c \
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

bonus: all
#	@echo "$(C_RED)$(C_BOLD)There is no bonus for this project.$(C_RESET)"

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
