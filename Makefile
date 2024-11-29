CC = cc

#Directories
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
SRC_FILES = $(SRC_DIR)/main.c\
			$(SRC_DIR)/free.c\
			$(SRC_DIR)/parsing1.c\
			$(SRC_DIR)/parsing2.c\
			$(SRC_DIR)/parsing3.c\
			$(SRC_DIR)/parsing_utils1.c\
			$(SRC_DIR)/parsing_utils2.c\
			$(SRC_DIR)/parsing_utils3.c\
			$(SRC_DIR)/parsing_utils4.c\
			$(SRC_DIR)/parsing_utils5.c\
			$(SRC_DIR)/parsing_utils6.c\
			$(SRC_DIR)/flood_fill.c\
			$(SRC_DIR)/usage.c\
			$(SRC_DIR)/error.c\
			$(SRC_DIR)/base.c\
			$(SRC_DIR)/img_handling1.c\
			$(SRC_DIR)/img_handling2.c\
			$(SRC_DIR)/key_hooks.c\
			$(SRC_DIR)/rays1.c\
			$(SRC_DIR)/rays2.c\
			$(SRC_DIR)/init_higher_dimension1.c\
			$(SRC_DIR)/init_higher_dimension2.c\
			$(SRC_DIR)/higher_dimensional_utils.c \
			$(SRC_DIR)/movement.c\

BONUS = 	$(SRC_DIR)/main_bonus.c\
			$(SRC_DIR)/free.c\
			$(SRC_DIR)/parsing1.c\
			$(SRC_DIR)/parsing2_bonus.c\
			$(SRC_DIR)/parsing3.c\
			$(SRC_DIR)/parsing_utils1.c\
			$(SRC_DIR)/parsing_utils2_bonus.c\
			$(SRC_DIR)/parsing_utils3.c\
			$(SRC_DIR)/parsing_utils4.c\
			$(SRC_DIR)/parsing_utils5.c\
			$(SRC_DIR)/parsing_utils6.c\
			$(SRC_DIR)/flood_fill_bonus.c\
			$(SRC_DIR)/usage.c\
			$(SRC_DIR)/error.c\
			$(SRC_DIR)/base.c\
			$(SRC_DIR)/img_handling1.c\
			$(SRC_DIR)/img_handling2.c\
			$(SRC_DIR)/movement_bonus.c\
			$(SRC_DIR)/key_hooks_bonus.c\
			$(SRC_DIR)/rays1.c\
			$(SRC_DIR)/rays2.c\
			$(SRC_DIR)/init_higher_dimension1.c\
			$(SRC_DIR)/init_higher_dimension2_bonus.c\
			$(SRC_DIR)/higher_dimensional_utils_bonus.c\
			$(SRC_DIR)/minimap_bonus.c\
			$(SRC_DIR)/minimap_utils_bonus.c\
			$(SRC_DIR)/handle_bonuses.c\


# Object files
OBJ_FILES = $(SRC_FILES:.c=.o)

# Executable
NAME = cub3D
NAME_BONUS = cub3D_bonus

# Libft
LIBFT_MAKEFILE = $(LIBFT_DIR)/Makefile
LIBFT = $(LIBFT_DIR)/libft.a
LIBFT_INC = -I$(LIBFT_DIR)/includes
LIBFT_LINK = -L$(LIBFT_DIR) -lft

#mlx
MLX_FLAGS = ./MLX42/build/libmlx42.a -ldl -lglfw -pthread -lm #can combine

BOBJS = $(BONUS:.c=.o)

all:  $(NAME)
	@echo "\033[1;32m[✔] Compiled main executable: $(NAME)\033[0m"

bonus:  $(NAME_BONUS) link_bonus
	@echo "\033[1;32m[✔] Compiled bonus executable: $(NAME) with BONUS!\033[0m"

%.o: %.c
	@$(CC) $(CFLAGS) $(INCFLAGS) $(LIBFT_INC) -g -c $< -o $@

libmlx:
	@if [ ! -d "$(LIBMLX)" ]; then git clone https://github.com/codam-coding-college/MLX42.git $(LIBMLX); fi
	@cmake ./MLX42 -B ./MLX42/build
	@make -C ./MLX42/build -j4

# Compile the main executable
$(NAME): libmlx $(OBJ_FILES) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJ_FILES) $(LIBFT_LINK) $(MLX_FLAGS) -o $(NAME)
	@echo "\033[1;33m[✔] Compiling $(NAME) (main version)...\033[0m"

# Compile the bonus executable without renaming
$(NAME_BONUS): libmlx $(BOBJS) $(LIBFT)
	@$(CC) $(CFLAGS) $(BOBJS) $(LIBFT_LINK) $(MLX_FLAGS) -o $(NAME_BONUS)
	@echo "\033[1;33m[✔] Compiling $(NAME_BONUS) (bonus version)...\033[0m"

# Create a symbolic link named cub3D that points to cub3D_bonus
link_bonus:
	@ln -sf $(NAME_BONUS) $(NAME)
	@echo "\033[1;33m[✔] Created symbolic link $(NAME) -> $(NAME_BONUS)\033[0m"

$(LIBFT): $(LIBFT_MAKEFILE)
	@$(MAKE) -C $(LIBFT_DIR)
	@echo "\033[1;33m[✔] Linking to libft Makefile...\033[0m"

clean:
	@$(MAKE) -C $(LIBFT_DIR) clean
	@echo "\033[1;33m[X] Cleaning...\033[0m"
	@rm -f $(OBJ_FILES) $(BOBJS)
	@rm -rf .bonus

fclean: clean
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@echo "\033[1;31m[XXX] Cleaning it GOOOOOOD...\033[0m"
	@rm -f $(NAME) $(NAME_BONUS)
	@rm -rf $(LIBMLX)

re: fclean all

.PHONY: all clean fclean re libmlx bonus link_bonus

