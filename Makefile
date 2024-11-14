# Executable
NAME = cub3D
BONUS_NAME = cub3D_bonus

# Directories
SRC_DIR = src
OBJ_DIR = obj
LIBFT_DIR = libft
VPATH = src:libft:includes
LIBMLX = ./MLX42

# Compiler flags
CFLAGS = -Wall -Wextra -Werror -g -Wunreachable-code -Ofast #-fsanitize=address
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
			parsing_utils5.c\
			parsing_utils6.c\
			flood_fill.c\
			usage.c\
			error.c\
			base.c\
			img_handling1.c\
			img_handling2.c\
			key_hooks.c\
			rays1.c\
			rays2.c\
			init_higher_dimension1.c\
			init_higher_dimension2.c\
			higher_dimensional_utils.c \
			movement.c\

BONUS = 	main_bonus.c\
			free.c\
			parsing1.c\
			parsing2.c\
			parsing3.c\
			parsing_utils1.c\
			parsing_utils2.c\
			parsing_utils3.c\
			parsing_utils4.c\
			parsing_utils5.c\
			parsing_utils6.c\
			flood_fill.c\
			usage.c\
			error.c\
			base.c\
			img_handling1.c\
			img_handling2.c\
			movement_bonus.c\
			key_hooks_bonus.c\
			rays1.c\
			rays2.c\
			init_higher_dimension1.c\
			init_higher_dimension2_bonus.c\
			higher_dimensional_utils.c\
			minimap_bonus.c\
			minimap_utils_bonus.c\
			handle_bonuses.c\

# Object files
OBJ_FILES = $(SRC_FILES:.c=.o)
BONUS_OBJ_FILES = $(BONUS_FILES:.c=.o)

# Libft
LIBFT_MAKEFILE = $(LIBFT_DIR)/Makefile
LIBFT = $(LIBFT_DIR)/libft.a
LIBFT_INC = -I$(LIBFT_DIR)/includes
LIBFT_LINK = -L$(LIBFT_DIR) -lft

# mlx
MLX_FLAGS = ./MLX42/build/libmlx42.a -ldl -lglfw -pthread -lm

# Default rule to compile the main project
all: libmlx $(NAME)
	@echo "\033[1;32m[✔] Compiled main executable: $(NAME)\033[0m"

bonus: $(BONUS_NAME) link_bonus
	@echo "\033[1;32m[✔] Compiled bonus executable: $(NAME) with BONUS!\033[0m"

%.o: %.c
	@$(CC) $(CFLAGS) $(INCFLAGS) $(LIBFT_INC) -g -c $< -o $@

libmlx:
	@if [ ! -d "$(LIBMLX)" ]; then git clone https://github.com/codam-coding-college/MLX42.git $(LIBMLX); fi
	@cmake ./MLX42 -B ./MLX42/build
	@make -C ./MLX42/build -j4

# Compile the main executable
$(NAME): $(OBJ_FILES) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJ_FILES) $(LIBFT_LINK) $(MLX_FLAGS) -o $(NAME)
	@echo "\033[1;33m[✔] Compiling $(NAME) (main version)...\033[0m"

# Compile the bonus executable without renaming
$(BONUS_NAME): $(BONUS_OBJ_FILES) $(LIBFT)
	@$(CC) $(CFLAGS) $(BONUS_OBJ_FILES) $(LIBFT_LINK) $(MLX_FLAGS) -o $(BONUS_NAME)
	@echo "\033[1;33m[✔] Compiling $(BONUS_NAME) (bonus version)...\033[0m"

# Create a symbolic link named cub3D that points to cub3D_bonus
link_bonus:
	@ln -sf $(BONUS_NAME) $(NAME)
	@echo "\033[1;33m[✔] Created symbolic link $(NAME) -> $(BONUS_NAME)\033[0m"

$(LIBFT): $(LIBFT_MAKEFILE)
	@$(MAKE) -C $(LIBFT_DIR)
	@echo "\033[1;33m[✔] Linking to libft Makefile...\033[0m"

clean:
	@$(MAKE) -C $(LIBFT_DIR) clean
	@echo "\033[1;33m[X] Cleaning...\033[0m"
	@rm -f $(OBJ_FILES) $(BONUS_OBJ_FILES)
	@rm -rf .bonus

fclean: clean
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@echo "\033[1;31m[XXX] Cleaning it GOOOOOOD...\033[0m"
	@rm -f $(NAME) $(BONUS_NAME)
	@rm -rf $(LIBMLX)

re: fclean all

.PHONY: all clean fclean re libmlx bonus link_bonus
