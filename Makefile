NAME = minishell
CC = gcc
CFLAGS = -g -Wall -Wextra -Werror -I.
SRC_DIR = srcs/

SRC =           srcs/main.c \
                srcs/env/env_lib.c \
                srcs/env/env_lib_utils.c \
                srcs/env/env_lib_2.c \
                srcs/env/env_utils.c \
                srcs/env/env_utils_2.c \
                srcs/utils/utils.c \
				srcs/utils/utils_2.c \
				srcs/utils/prompt.c \
                srcs/utils/free.c \
				srcs/utils/free_2.c \
                srcs/parsing/parsing.c \
                srcs/parsing/split_tokens.c \
                srcs/parsing/split_tokens_utils.c \
                srcs/parsing/tocken.c \
				srcs/parsing/tocken_utils.c \
                srcs/parsing/export.c \
				srcs/parsing/export_utils.c \
                srcs/parsing/export_quot_utils.c \
                srcs/parsing/syntaxe.c \
                srcs/parsing/quote.c \
                srcs/ast/ast.c \
                srcs/ast/utils_ast.c \
                srcs/exec/exec.c \
                srcs/exec/exec_pipe.c \
                srcs/exec/utils_exec.c \
                srcs/exec/redirection/utils_redirection.c \
				srcs/exec/redirection/redirection_lib.c \
				srcs/exec/path/path.c \
				srcs/exec/path/utils_path.c \
				srcs/exec/here_doc/here_doc.c \
				srcs/exec/here_doc/pre_here_doc.c \
				srcs/exec/here_doc/expend_here_doc.c \
				srcs/exec/here_doc/utils_here_doc.c\
				srcs/exec/here_doc/utils_here_doc_bis.c \
                srcs/builtins/builtins_utils.c \
                srcs/builtins/ft_pwd.c \
                srcs/builtins/ft_echo.c \
                srcs/builtins/ft_env.c \
                srcs/builtins/ft_unset.c \
                srcs/builtins/ft_export.c \
                srcs/builtins/ft_export_utils.c \
				srcs/builtins/ft_export_utils_bis.c \
				srcs/builtins/ft_export_print.c \
                srcs/builtins/ft_exit.c \
                srcs/builtins/ft_exit_utils.c \
                srcs/builtins/ft_cd.c \
                srcs/signal/signal.c \
                srcs/bonus/exec/wilercard/wilercard.c \
                srcs/bonus/exec/wilercard/wilercard_sort_bonus.c \
                srcs/bonus/exec/wilercard/wilercard_filtre_bonus.c \
                srcs/bonus/exec/wilercard/wilercard_utils.c

SRC_BONUS =     srcs/main_bonus.c \
                srcs/bonus/utils/main_utils_bonus.c \
                srcs/env/env_lib.c \
                srcs/env/env_lib_utils.c \
                srcs/env/env_lib_2.c \
                srcs/env/env_utils.c \
                srcs/env/env_utils_2.c \
                srcs/utils/utils.c \
				srcs/utils/utils_2.c \
				srcs/utils/prompt.c \
                srcs/utils/free.c \
				srcs/utils/free_2.c \
                srcs/parsing/parsing.c \
                srcs/parsing/split_tokens.c \
                srcs/parsing/split_tokens_utils.c \
                srcs/parsing/tocken.c \
				srcs/bonus/parsing/tocken_utils_bonus.c \
                srcs/parsing/export.c \
				srcs/parsing/export_utils.c \
                srcs/parsing/export_quot_utils.c \
                srcs/parsing/syntaxe.c \
                srcs/parsing/quote.c \
                srcs/ast/ast.c \
                srcs/ast/utils_ast.c \
                srcs/exec/exec.c \
                srcs/exec/exec_pipe.c \
                srcs/bonus/exec/utils_exec_bonus.c \
                srcs/bonus/exec/utils_bis_exec_bonus.c \
                srcs/exec/redirection/utils_redirection.c \
				srcs/exec/redirection/redirection_lib.c \
				srcs/exec/path/path.c \
                srcs/exec/path/utils_path.c \
				srcs/exec/here_doc/here_doc.c \
				srcs/exec/here_doc/pre_here_doc.c \
                srcs/exec/here_doc/expend_here_doc.c \
				srcs/exec/here_doc/utils_here_doc.c\
                srcs/exec/here_doc/utils_here_doc_bis.c \
                srcs/builtins/builtins_utils.c \
                srcs/builtins/ft_pwd.c \
                srcs/builtins/ft_echo.c \
                srcs/builtins/ft_env.c \
                srcs/builtins/ft_unset.c \
                srcs/builtins/ft_export.c \
				srcs/builtins/ft_export_utils.c \
				srcs/builtins/ft_export_utils_bis.c \
				srcs/builtins/ft_export_print.c \
                srcs/builtins/ft_exit.c \
                srcs/builtins/ft_exit_utils.c \
                srcs/builtins/ft_cd.c \
                srcs/signal/signal.c \
                srcs/bonus/here_doc_bonus.c \
                srcs/bonus/exec/wilercard/wilercard.c \
                srcs/bonus/exec/wilercard/wilercard_sort_bonus.c \
                srcs/bonus/exec/wilercard/wilercard_filtre_bonus.c \
                srcs/bonus/exec/wilercard/wilercard_utils.c \
                srcs/bonus/parsing/parsing_bonus.c \
                srcs/bonus/parsing/syntaxe_bonus.c \
                srcs/bonus/parsing/syntaxe_bonus_utils.c \
                srcs/bonus/parsing/syntaxe_utils_bonus.c\
                srcs/bonus/parsing/split_bonus.c \
                srcs/bonus/parsing/token_bonus.c \
                srcs/bonus/ast/ast_bonus.c \
                srcs/bonus/ast/ast_utils_bonus.c \
                srcs/bonus/ast/ast_lib_bonus.c \
                srcs/bonus/exec/exec_bonus.c
OBJ = $(SRC:.c=.o)
OBJ_BONUS = $(SRC_BONUS:.c=.o)
LIBFT_DIR = srcs/libft
LIBFT = $(LIBFT_DIR)/libft.a
INCLUDES = -I includes/ -I $(LIBFT_DIR)

RED=\033[0;31m
GREEN=\033[0;32m
BLUE=\033[0;34m
NC=\033[0m

TOTAL_FILES := $(words $(SRC))
COMPILED_FILES := 0

all: start $(NAME) compilated_minishell

bonus : start $(LIBFT) compilat_minishell_bonus $(OBJ_BONUS) compilated_minishell
	@$(CC) $(CFLAGS) $(INCLUDES) $(OBJ_BONUS) $(LIBFT) -o $(NAME) -lreadline

$(LIBFT):
	@make -s -C $(LIBFT_DIR)

$(NAME): $(LIBFT) compilat_minishell $(OBJ)
	@$(CC) $(CFLAGS) $(INCLUDES) $(OBJ) $(LIBFT) -o $(NAME) -lreadline

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)
	@$(eval COMPILED_FILES := $(shell echo $$(($(COMPILED_FILES) + 1))))
	@printf "\r\t[%3d%%] [%s]" $$(($(COMPILED_FILES) * 100 / $(TOTAL_FILES))) $<
	@tput el

clean:
	@rm -rf $(OBJ)
	@rm -rf $(OBJ_BONUS)
	@make -C $(LIBFT_DIR) clean

fclean: clean
	@rm -rf $(NAME) a.out
	@make -C $(LIBFT_DIR) fclean

re: fclean all

start :
	@clear;
	@echo "$(RED)"
	@echo '  ____    ____   _             _          __             __   __   '
	@echo ' |_   \  /   _| (_)           (_)        [  |           [  | [  |  '
	@echo '   |   \/   |   __   _ .--.   __   .--.   | |--.  .---.  | |  | |  '
	@echo '   | |\  /| |  [  | [ `.-. | [  | ( (`\]  | .-. |/ /__\\ | |  | |  '
	@echo '  _| |_\/_| |_  | |  | | | |  | |  ``.`.  | | | || \__., | |  | |  '
	@echo ' |_____||_____|[___][___||__][___][\__) )[___]|__] '.__.' [___][___] '
	@echo '                                                                   ' "$(NC)"
    


compilat_minishell:
	@echo "===================== [ Compiling $(NAME) ] ====================="

compilat_minishell_bonus:
	@echo "================== [ Compiling bonus $(NAME) ] ==================="

compilated_minishell:
	@echo "\n\n$(RED)./$(NAME)$(NC) was create by [$(GREEN)bberkrou$(NC)] && [$(GREEN)kbutor-b$(NC)]"
.SILENT: