NAME = libft.a

OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))
OBJ_DIR = obj

VPATH = gnl:ft_printf:libft

SRC =	ft_bzero.c\
		ft_calloc.c\
		ft_free_array.c\
		ft_isalnum.c\
		ft_isalpha.c\
		ft_isascii.c\
		ft_isdigit.c\
		ft_isprint.c\
		ft_memchr.c\
		ft_memcmp.c\
		ft_memcpy.c\
		ft_memmove.c\
		ft_memset.c\
		ft_strchr.c\
		ft_strdup.c\
		ft_strlcat.c\
		ft_strlcpy.c\
		ft_strncat.c\
		ft_strlen.c\
		ft_strncmp.c\
		ft_strnstr.c\
		ft_strrchr.c\
		ft_tolower.c\
		ft_toupper.c\
		ft_atoi.c\
		ft_substr.c\
		ft_strjoin.c\
		ft_strsjoin.c\
		ft_strtrim.c\
		ft_split.c\
		ft_itoa.c\
		ft_putchar_fd.c\
		ft_strmapi.c\
		ft_striteri.c\
		ft_strcmp.c\
		ft_putnbr_fd.c\
		ft_putstr_fd.c\
		ft_putendl_fd.c\
		ft_lstadd_front_bonus.c\
		ft_lstnew_bonus.c\
		ft_lstsize_bonus.c\
		ft_lstlast_bonus.c\
		ft_lstadd_back_bonus.c\
		ft_lstdelone_bonus.c\
		ft_lstclear_bonus.c\
		ft_lstiter_bonus.c\
		format_check.c\
		ft_hex.c\
		ft_char.c\
		ft_pointer.c\
		ft_printf.c\
		ft_nbr.c\
		ft_str.c\
		ft_unsig_nbr.c\
		get_next_line.c\
		get_next_line_utils.c


CFLAGS = -Wall -Wextra -Werror -MMD -g
INCFLAGS = -Iincludes

all:  $(NAME)

$(NAME): $(OBJ)
	@ar rc $(NAME) $(OBJ)
	@echo "\033[1;34m[✨] Creating libft.a...\033[0m"

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(OBJ_DIR)
	@cc $(CFLAGS) $(INCFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJ_DIR) 

fclean: clean
	@rm -f $(NAME)
re: fclean all

.PHONY: all clean fclean re