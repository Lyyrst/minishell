NAME = libft.a
CC = gcc
CFLAGS = -Wall -Wextra -Werror -I.
SRC_DIR = src/
SRC = 			ft_atoi.c ft_isprint.c ft_putchar_fd.c ft_strjoin.c ft_strtrim.c \
				ft_bzero.c ft_itoa.c ft_putendl_fd.c ft_strlcat.c ft_substr.c \
				ft_calloc.c ft_putnbr_fd.c ft_strlcpy.c ft_tolower.c \
				ft_isalnum.c ft_putstr_fd.c ft_strlen.c ft_toupper.c \
				ft_isalpha.c ft_memchr.c ft_strmapi.c \
				ft_isascii.c ft_memcmp.c ft_split.c ft_strncmp.c \
				ft_isdigit.c ft_memcpy.c ft_strchr.c ft_strnstr.c \
				ft_memmove.c ft_strdup.c ft_strrchr.c ft_memset.c ft_striteri.c \
				ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c \
				ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c \
				ft_lstiter.c ft_lstmap.c \
				ft_ltoa.c \
				printf/srcs/bonus/ft_printf_bonus.c \
				printf/srcs/bonus/parse/ft_pars_bonus.c \
				printf/srcs/bonus/parse/ft_flag_bonus.c \
				printf/srcs/bonus/print/string_bonus.c \
				printf/srcs/bonus/print/int_bonus.c \
				printf/srcs/bonus/print/uint_bonus.c \
				printf/srcs/bonus/print/percent_bonus.c \
				printf/srcs/bonus/print/hexa_bonus.c \
				printf/srcs/bonus/print/pointeur_bonus.c \
				printf/srcs/bonus/utils/utils_print_bonus.c \
				printf/srcs/bonus/utils/utils_digit_bonus.c \
				printf/srcs/bonus/utils/utils_pars_bonus.c \
				gnl/get_next_line.c \
				gnl/get_next_line_utils.c
OBJ = 			$(SRC:.c=.o)
INCLUDES = -I includes/ -I printf/includes/

RED=\033[0;31m
GREEN=\033[0;32m
BLUE=\033[0;34m
NC=\033[0m

TOTAL_FILES := $(words $(SRC))
COMPILED_FILES := 0

all: $(NAME) $(PRINTF)

$(NAME): compilat_libft $(OBJ) return
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)
	@$(eval COMPILED_FILES := $(shell echo $$(($(COMPILED_FILES) + 1))))
	@printf "\r\t[%3d%%] [%s]" $$(($(COMPILED_FILES) * 100 / $(TOTAL_FILES))) $<
	@tput el

clean:
	@rm -rf $(OBJ)
	@rm -rf $(BONUS_OBJ)
	@rm -f $(NAME)

fclean: clean
	@rm -f $(PRINTF)

re: fclean all

compilat_libft:
	@echo "====================== [ Compiling $(NAME) ] ======================"

return:
	@echo "\n"


.PHONY: all clean fclean re
