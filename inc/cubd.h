/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cubd.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araveala <araveala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 14:36:20 by fdessoy-          #+#    #+#             */
/*   Updated: 2024/11/12 14:42:42 by fdessoy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBD_H
# define CUBD_H

/*************************************************/
/* User defined headers **************************/
/*************************************************/
# include "libft.h"
# include "MLX42/MLX42.h"

/*************************************************/
/* external libraries ****************************/
/*************************************************/
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <sys/time.h>
# include <stdlib.h>
# include <math.h>

/*************************************************/
/* questionable libraries ************************/
/*************************************************/
# include <stdbool.h>
# include <limits.h>
# include <stdint.h>

/*************************************************/
/* macros ****************************************/
/*************************************************/
# define MAP "Error\nCan't open map. File may be corrupted.\n"
# define NAME "Error\nMap name is invalid\n"
# define MALLOC "Error\nMalloc Failure\n"
# define FILE "Error\nElements may be incorrect. Check map conditions.\n"
# define SPRITE "Error\nCould not find/load sprites.\n"
# define SPRITE2 "Error\nExtra sprites defined for same direction.\n"
# define SPRITE3 "Error\nSprites are not in PNG format\n"
# define SPRITE4 "Error\nDirectories are not valid PNG files.\n"
# define RGB69 "Error\nRGB information is incorrect\n"
# define RGB1 "Error\nRGB (ceiling) values: value must be between 0-255\n"
# define RGB2 "Error\nRGB (floor) values: value must be between 0-255\n"
# define RGB3 "Error\nRGB (floor) extra information present in file\n"
# define RGB4 "Error\nRGB (ceiling) extra information present in file\n"
# define RGB5 "Error\nRGB extra information present in file\n"
# define RGB6 "Error\nRGB values: value must be between 0-255\n"
# define RGB7 "Error\nRGB values: for God sake, use F or C to define RGB\n"
# define RGB8 "Error\nFor Gods sake, please stop trying to break this\n"
# define PLAYER "Error\nMust have one player character(N, W, S, or E)\n"
# define BRK_MAP "Error\nMap is broken/not positioned correctly ):\n"
# define CLOSE "Error\nMap is not walled correctly ):<\n"
# define MLX1 "Error\nMLX function error\n"
# define MLX2 "Error\nMLX couldn't load images\n"
# define MLX3 "Error\nMLX couldn't load RGB scheme\n"
# define MLX4 "Error\nMLX couldn't draw ceiling and floor\n"
# define TEXTURE_FAIL "texture invalid or simply missing\n"
# define IMAGE_FAIL "image invalid\n"
# define IMG_TO_WIN "image could not put to window, check image not corrupt\n"
# define NEW_IMG "MLX new image allocation failure, clean chache?\n"
# define RESIZE "MLX failed to resize image\n"

# define SUCCESS 0
# define FAILURE 1

/*************************************************/
/* usage macros **********************************/
/*************************************************/
# define USAGE1 "\nWelcome to cub3d "
# define USAGE2 "and you already have committed a folly."
# define USAGE3 " Follow the usage below:\n\n"
# define USAGE4 "1. Map must have the suffix '.cub';\n"
# define USAGE5 "2. In command line just execute the program and map;\n"
# define USAGE6 "3. File must contain all elements (sprites with \n"
# define USAGE7 "cardinal orientation, proper walled map, and \n"
# define USAGE8 "RGB notated instructions [numerical value]);\n"
# define USAGE9 "4. Textures should be in PNG format;\n"
# define USAGE10 "5. Any other misconfiguration results in error.\n"
# define USAGE11 "This game has no exit for now, so use ESC to "
# define USAGE12 "finish the game (:\n\n"
# define USAGE13 "By: fdessoy- && araveala\n"

/*************************************************/
/*mlx macros / graphics macros********************/
/*************************************************/
# define WIDTH			1920
# define HEIGHT			1080
# define MINI_WIDTH		40
# define MINI_HEIGHT	40
# define T_SIZE			64
# define MINI_T			32
# define RAY_MAX 		1920.0
# define FOV 			60.0
# define ROTATE_ANGLE	0.0872665
# define PI				3.14159265358979323846
# define STEP			0.4
# define DEG2RAD 		0.01745329252
# define RED 0xFF0000FF
# define M_RADIUS 8
# define M_RADIUS_M 64

/*************************************************/
/* structs ***************************************/
/*************************************************/
typedef enum e_dirs
{
	NORTH = 1,
	SOUTH = 2,
	EAST = 3,
	WEST = 4
}	t_dirs;

typedef struct s_data
{

	mlx_t			*mlx;
	mlx_t			*main_window;
	mlx_t			*mini_window;
	char			**map;
	bool			broken_map;
	char			**file;
	double			ray_len[1920];
	double			ray_hit[1920];
	char			key_pressed[265];
	int				map_width;
	int				map_length;
	int				side_hit;

	double			door_x;
	double			door_y;
	int 			door_flag;

	double			time;
	double			ray_size;
	double			p_dir_x;
	double			p_dir_y;
	double			wall_scale;
	double			angle_increment;
	double			radius;
	double			ray_x;
	double			ray_y;
	double			ray_dir_x;
	double			ray_dir_y;
	int				step_x;
	int				step_y;
	int				map_x;
	int				map_y;
	int				side;
	int				hit;
	int				w_width;
	int				w_height;
	int8_t			index;
	double			ray_step_x;
	double			ray_step_y;
	double			ray_side_dis_x;
	double			ray_side_dis_y;
	double			exact_x;
	double			exact_y;
	double			distance_to_wall;
	double			ray_delta_x;
	double			ray_delta_y;
	double			ray_delta_dis_x;
	double			ray_delta_dis_y;
	double			perp_wall_dist;
	double			side_dist_y;
	double			side_dist_x;
	double			ppos_pix_x;
	double			ppos_pix_y;
	int				wall_line;
	int8_t			file_len;
	int				map_start;
	int				map_end;
	char			*floor_info;
	char			*ceiling_info;
	uint32_t		c_red;
	uint32_t		c_green;
	uint32_t		c_blue;
	uint32_t		f_red;
	uint32_t		f_green;
	uint32_t		f_blue;
	char			*n_sprite;
	char			*s_sprite;
	char			*e_sprite;
	char			*w_sprite;
	bool			s_player;
	bool			n_player;
	bool			e_player;
	bool			w_player;
	double			y_ppos;
	double			x_ppos;
	char			**mp_cpy;
	int				repeat_floor;
	int				repeat_ceiling;
	int				repeat_test;
	mlx_texture_t	*tx_n_wall;
	mlx_texture_t	*tx_s_wall;
	mlx_texture_t	*tx_e_wall;
	mlx_texture_t	*tx_w_wall;
	mlx_texture_t	*tx_mini_floor;
	mlx_texture_t	*tx_mini_wall;

	mlx_texture_t	*tx_player1;
	mlx_texture_t	*tx_player2;
	mlx_texture_t	*tx_player3;

	mlx_texture_t	*tx_door1;
	mlx_texture_t	*tx_door2;
	mlx_texture_t	*tx_door3;
	
	mlx_image_t		*im_n_wall;	
	mlx_image_t		*im_s_wall;
	mlx_image_t		*im_e_wall;
	mlx_image_t		*im_w_wall;
	mlx_image_t		*background;
	mlx_image_t		*im_current_wall;
	uint32_t		floor_color;
	uint32_t		ceiling_color;
	mlx_image_t		*im_ray;
	mlx_image_t		*im_map;
	mlx_image_t		*im_mini_floor;
	mlx_image_t		*im_mini_wall;
	mlx_image_t		*im_mini_ray;
	mlx_image_t		*im_map_player;
	mlx_image_t		*im_player1;
	mlx_image_t		*im_player2;
	mlx_image_t		*im_player3;

	mlx_image_t	*im_current_door;
	mlx_image_t	*im_door1;
	mlx_image_t	*im_door2;
	mlx_image_t	*im_door3;
}		t_data;

/*************************************************/
/* functions *************************************/
/*************************************************/

/* in parsing1.c */
int8_t		is_dir(char *fname);
int8_t		check_suffix(char *fname, char *target, int size);
int8_t		map_handling(t_data *data, char *argv);

/* in parsing2.c */
int8_t		extract(t_data *data);

/* in parsing3.c */
int8_t		search_sprites(t_data *data);

/* in parsing_utils1.c */
char		*sprite_path(char *str);
int8_t		separate_rgb(t_data *data, char *str, int flag);
int8_t		rgb_parse(t_data *data, char *str, int flag);

/* in parsing_utils2.c */
int8_t		rgb_assignment(t_data *data, char **array, int flag);
int8_t		allocate_mapmem(t_data *data);
int8_t		is_map(char *str);
void		rem_map_nl(char **map);

/* in parsing_utils3.c */
int8_t		only_nl(char *str);
int8_t		player_exists(t_data *data, char **map);
int8_t		check_original_length(t_data *data);
uint8_t		get_width(char **map);

/* in parsing_utils4.c */
void		remove_nl(char *str);
int8_t		repeated_rgb(char **file);
int8_t		repeated_inline(char **file);
int8_t		extra_info(char *rgb);

/* in parsing_utils5.c */
int8_t		rgb_parse2(t_data *data, char **info, int flag);
int8_t		is_png(char *sprite);

/* in parsing_utils6.c */
char		*extract_sprite(char **sprite);

/* in flood_fill.c */
int8_t		check_if_walled(t_data *data);
int8_t		copy_map(t_data *data);
void		flood_fill(t_data *data, size_t y, size_t x);

/* in img_handling1.c */
int8_t		draw_floor_ceiling(t_data *data);
int8_t		image_handling(t_data *data);
uint32_t	load_rgb(uint32_t r, uint32_t g, uint32_t b, uint32_t a);

/* in img_handling2.c */
uint32_t	fetch_pixel_rgb(mlx_image_t *img, int x, int y, int pos);
void		delete_pngs(t_data *data);
void		delete_images(t_data *data);

/* in error.c */
int			err_msg(char *obj, char *msg, int exit_code);

/* in usage.c */
void		usage(void);
void		wrap_up(t_data *data, int option);

/* in base.c*/
int			open_window(t_data *data);

/* in key_hooks.c */
void		keyhookfunc(mlx_key_data_t keydata, void *param);
void		update_player(t_data *data);

/* in movement.c */
void		keyhookfunc(mlx_key_data_t keydata, void *param);
void		update_player(t_data *data);
void		update(void *param);
//~~~~~~~~~~~~~~//
void		rotate_player(t_data *data, double angle);
void		strafe_player(t_data *data, double step);
void		move_player(t_data *data, double step);

/* in rays1.c */
void		collect_ray(t_data *data, int i, double ray_distance, \
						double ray_angle);
double		calculate_perpendicular_distance(t_data *data);
void		perform_dda(t_data *data, double delta_dist_x, double delta_dist_y);
void		calculate_side_distances(t_data *data, double delta_dist_x, \
						double delta_dist_y);
double		calculate_initial_position(double position);

/* in rays2.c */
int			find_direction(int side, double ray_x, double ray_y);
int			outof_bounds_check(t_data *data, double rpos_pixel_y, \
						double rpos_pixel_x);
void		stack_ray_data(t_data *data, int i);

/* init_higher_dimension1.c */
void		initialize_wall_params(t_data *data, int i, double *w_h, \
						double *img_x);
void		draw_stretched_wall(t_data *data, double img_x, double w_h, \
						double fset);
void		draw_regular_wall(t_data *data, double wall_h, double img_x, \
						double top_of_wall);
int			draw_wall(t_data *data, int i);

/* init_higher_dimension2.c */
int			find_wall(t_data *data, int i);
int			check_for_wall_failure(t_data *data, int i);

/* higher_dimensinal_utils.c */
double		diff(double wall_h);
double		calculate_depth(t_data *data);
void		calculate_hit_coords(t_data *data);

/* bonus */
int			initialize_minimap(t_data *data);
void		draw_player(t_data *data);
void		draw_first_line(t_data *data);

/* minimap.c */
int			init_map(t_data *data, int x, int y, uint32_t colour);
void		draw_mini_line(t_data *data, int new_x, int new_y);

/* mimimap_utils_bonus.c */
void		draw_line(t_data *data, int i);
void		draw_mini_player(t_data *data, int y, int x);
void		wipe_line(t_data *data, int new_x, int new_y);
int			set_view(t_data *data);

/* handle_bonuses.c */
int			init_player_texture(t_data *data);
void		delete_bonuses(t_data *data);

/* bonus key hooks */
void		animation(void *param);

/* in free.c */
void		free_data(t_data *data);
void		draw_mini_map(t_data *data, int x, int y, int index);
int	find_door_location(t_data *data);
#endif