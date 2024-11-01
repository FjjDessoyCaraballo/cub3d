CC = cc

#Directories
SRC_DIR = src
OBJ_DIR = obj
LIBFT_DIR = libft
VPATH = src:libft:includes
LIBMLX = ./MLX42

# Compiler flags
CFLAGS = -Wall -Wextra -Werror -g -Wunreachable-code -Ofast -fsanitize=undefined #wun and -0 for mlx
INCFLAGS = -I ./include -I ./MLX42/include -I /Users/include 

# Main project files
#~~ minimap.c is bonus, used for visual aid for this moment
SRC_FILES = main.c\
			free.c\
			parsing1.c\
			parsing2.c\
			parsing3.c\
			parsing_utils1.c\
			parsing_utils2.c\
			parsing_utils3.c\
			parsing_utils4.c\
			flood_fill.c\
			usage.c\
			error.c\
			base.c\
			img_handling1.c\
			img_handling2.c\
			movement.c\
			key_hooks.c\
			rays.c\
			window_resizing.c\
			init_higher_dimension.c\
			minimap.c\
			minimap_utils_bonus.c\
			printer.c #REMOVE LATER


# Object files
OBJ_FILES = $(SRC_FILES:.c=.o)

# Executable
NAME = cub3D

# Libft
LIBFT_MAKEFILE = $(LIBFT_DIR)/Makefile
LIBFT = $(LIBFT_DIR)/libft.a
LIBFT_INC = -I$(LIBFT_DIR)/includes
LIBFT_LINK = -L$(LIBFT_DIR) -lft

#mlx
MLX_FLAGS = ./MLX42/build/libmlx42.a -ldl -lglfw -pthread -lm #can combine


all: libmlx $(NAME)
	@echo "\033[1;32m[✔] GOOD HEAVENS! LOOK AT THE EXECUTABLE!\033[0m"

%.o: %.c
	@$(CC) $(CFLAGS) $(INCFLAGS) $(LIBFT_INC) -g -c $< -o $@
libmlx:
	@if [ ! -d "$(LIBMLX)" ]; then git clone https://github.com/codam-coding-college/MLX42.git $(LIBMLX); fi
	@cmake ./MLX42 -B ./MLX42/build
	@make -C ./MLX42/build -j4

$(NAME): libmlx $(OBJ_FILES) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJ_FILES) $(LIBFT_LINK) $(MLX_FLAGS) -o $(NAME)
	@echo "\033[1;33m[✔] Compiling $(NAME)...\033[0m"

$(LIBFT): $(LIBFT_MAKEFILE)
	@$(MAKE) -C $(LIBFT_DIR)
	@echo "\033[1;33m[✔] Linking to libft Makefile...\033[0m"

$(LIBFT_MAKEFILE):
	@echo "Creating symbolic link for libft Makefile..."
	@ln -s $(CURDIR)/$(LIBFT_MAKEFILE) $(LIBFT_MAKEFILE)

clean:
	@$(MAKE) -C $(LIBFT_DIR) clean
	@echo "\033[1;33m[X] Cleaning...\033[0m"
	@rm -f $(OBJ_FILES)

fclean: clean
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@echo "\033[1;31m[XXX] Cleaning it GOOOOOOD...\033[0m"
	@rm -f $(NAME)

re: fclean all $(NAME)

.PHONY: all clean fclean re libmlx
