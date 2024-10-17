/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cubd.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araveala <araveala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 14:36:20 by fdessoy-          #+#    #+#             */
/*   Updated: 2024/10/17 14:08:16 by araveala         ###   ########.fr       */
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
# define SPRITE "Error\nCould not find/load sprites."
# define SPRITE2 "Error\nExtra sprites defined for same direction.\n"
# define RGB1 "Error\nRGB (ceiling) values: value must be between 0-255\n"
# define RGB2 "Error\nRGB (floor) values: value must be between 0-255\n"
# define RGB3 "Error\nRGB (floor) extra information present in file\n"
# define RGB4 "Error\nRGB (ceiling) extra information present in file\n"
# define RGB5 "Error\nRGB extra information present in file\n"
# define RGB6 "Error\nRGB values: value must be between 0-255\n"
# define RGB7 "Error\nRGB values: for God sake, use F or C to define RGB\n"
# define PLAYER "Error\nMust have one player character(N, W, S, or E)\n"
# define BRK_MAP "Error\nMap is broken ):\n"
# define CLOSE "Error\nMap is not walled correctly ):<\n"

# define SUCCESS 0
# define FAILURE 1
# define SUFFER 65

/*************************************************/
/* usage macros **********************************/
/*************************************************/
# define USAGE1 "\nWelcome to cub3d "
# define USAGE2 "and you already have committed a folly."
# define USAGE3 " Follow the usage below:\n"
# define USAGE4 "1. map must have the suffix '.cub';\n"
# define USAGE5 "2. In clt just execute the program and map;\n"
# define USAGE6 "3. Map must contain all elements (sprites with \n"
# define USAGE7 "cardinal orientation, proper walled map, and \n"
# define USAGE8 "RGB notated instructions [numerical value]);\n\n"
# define USAGE9 "This game has no exit for now, so use ESC to "
# define USAGE10 "finish the game (:\n\n"
# define USAGE11 "By: fdessoy- && araveala\n"

/*************************************************/
/* fail mssgs   **********************************/
/*************************************************/
# define TEXTURE_FAIL "texture invalid or simply missing\n"
# define IMAGE_FAIL "image invalid\n"
# define IMG_TO_WIN "image could not put to window, check image not corrupt\n"
# define NEW_IMG "MLX new image allocation failure, clean chache?\n"
# define RESIZE "MLX failed to resize image, did you ask for something unreasonable?\n"
/*************************************************/
/*mlx macros / graphics macros********************/
/*************************************************/
# define WIDTH 1920 //~~ will play with sizes 
# define HEIGHT 1080 //~~ will play with sizes
# define MINI_WIDTH 40
# define MINI_HEIGHT 40
# define T_SIZE 64 //~~ tile size
# define MINI_T 32
# define MINI_OFFSET 10
# define MINI_SCALE 4 //maybe for minimap
# define RAY_MAX 220.0 // could be 240
# define FOV 90.0 //~~ angle of field of view degrees 
/*************************************************/
/* math macros ***************************************/
/*************************************************/
# define ROTATE_ANGLE	0.0872665 // 5 degrees in radians
# define PI				3.14159265358979323846
# define DEG2RAD 		(PI / 180.0)
# define STEP			0.1
/*************************************************/
/* structs ***************************************/
/*************************************************/
/*1.map_width and map_length maps width and height*/
/*2. p_x and p_y player position p_dir_x and p_dir_y players sight direction*/
/*3. doubles are better than floats, more percise*/
typedef	struct s_data
{
	mlx_t	*mlx;
	mlx_t	*main_window; //~~ not sure if needed yet
	mlx_t	*mini_window;
	char	**map;
	bool	broken_map;
	char	**file;
	double	ray_len[220]; // could be 240	
	double	ray_hit[220];
	char	key_pressed[264]; // num of highest key
	//int		file_len;

	int		map_width; // this was size_t before, needs to change in parsing
	int		map_length; // this was size_t before, needs to change in parsing

	//int		ray_hit;
	int		side_hit; // if we want to handle shading
	double	ray_size;
	double	p_dir_x;
	double	p_dir_y;

	double	ray_x;
	double	ray_y;
	double	ray_dir_x;
	double	ray_dir_y; // coul maybe me player dirs

	
	double	ray_step_x;
	double	ray_step_y;
	//distance measures check which side is closest wall.
	double	ray_side_dis_x;
	double	ray_side_dis_y;
	
	double	distance_to_wall;
	// side distance to wall????
	double	ray_delta_x;
	double	ray_delta_y; // i no other deltas needed , shorten name
	double	ray_delta_dis_x;
	double	ray_delta_dis_y; // i no other deltas needed , shorten name

	// from parsing
	int8_t	file_len;
	int		map_start;
	int		map_end;
	char	*floor_info;
	char	*ceiling_info;
	size_t	c_red;
	size_t	c_green;
	size_t	c_blue;
	size_t	f_red;
	size_t	f_green;
	size_t	f_blue;
	char	*n_sprite;
	char	*s_sprite;
	char	*e_sprite;
	char	*w_sprite;
	bool	s_player;
	bool	n_player;
	bool	e_player;
	bool	w_player;
	double	y_ppos;
	double	x_ppos;
	char	**mp_cpy;
	int		repeat_test;

	mlx_texture_t	*tx_n_wall;
	mlx_texture_t	*tx_s_wall;
	mlx_texture_t	*tx_e_wall;
	mlx_texture_t	*tx_w_wall;
	mlx_image_t		*im_n_wall;	
	mlx_image_t		*im_s_wall;
	mlx_image_t		*im_e_wall;
	mlx_image_t		*im_w_wall;

	mlx_image_t		*im_current_wall; // could be useful for keeping track which wall we are drawing


	//bool	quit; // might no need
	/*~~bonus stuff~~*/

	mlx_texture_t	*tx_mini_floor;
	mlx_texture_t	*tx_mini_wall;
	mlx_texture_t	*tx_mini_player;
	mlx_image_t		*im_map;
	mlx_image_t		*im_mini_floor;
	mlx_image_t		*im_mini_wall;
	mlx_image_t		*im_mini_player;
	mlx_image_t		*im_map_player; //effectivly miniplayer
	mlx_image_t		*im_ray;

}		t_data;

/*typedef struct s_img
{
	mlx_image_t	*img;
	uint32_t 	*pixels; // for pllayer rotation, maybe only minimap
}	t_img;*/

/*************************************************/
/* functions *************************************/
/*************************************************/

/* in parsing1.c */
int8_t	map_handling(t_data *data, char *argv);

/* in parsing2.c */
int8_t	extract(t_data *data);

/* in parsing3.c */
int8_t	search_sprites(t_data *data);

/* in parsing_utils.c */
char	*sprite_path(char *str);
int8_t	rgb_parse(t_data *data, char *str, int flag);

/* in parsing_utils2.c */
int8_t	rgb_assignment(t_data *data, char **array, int flag);
int8_t	allocate_mapmem(t_data *data);
int8_t	is_map(char *str);
void	remove_nl(char **map);

/* in parsing_utils3.c */
int8_t	only_nl(char *str);
int8_t	player_exists(t_data *data, char **map);
int8_t	check_original_length(t_data *data);
uint8_t	get_width(char **map);
int8_t	extra_rgb(char **rgb, int flag);

/* in flood_fill.c */
int8_t	check_if_walled(t_data *data);
int8_t	copy_map(t_data *data);
void	flood_fill(t_data *data, size_t y, size_t x);

/* in error.c */
int		err_msg(char *obj, char *msg, int exit_code);

/* in usage.c */
void	usage(void);

/* in base.c*/
int		open_window(t_data *data);
/* in key_hooks.c */
void	keyhookfunc(mlx_key_data_t keydata, void *param);
void	update_player(t_data *data);
/* in movement.c */
void	keyhookfunc(mlx_key_data_t keydata, void *param);
void    update_player(t_data *data);

//~~~~~~~~~~~~~~//
void	rotate_player(t_data *data, double angle);
void    strafe_player(t_data *data, double step);
void    move_player(t_data *data, double step);

/* in rays.c */
void	stack_ray_data(t_data *data, int i);
void	collect_ray(t_data *data, int i, double ray_distance);
//void	collect_ray(t_data *data); // simle one ray from middle

void    rotate_left(t_data *data);
void    rotate_right(t_data *data);


/* printer REMOVE LATER */
void	printer(t_data *data);

/* bonus */
int		initlize_minimap(t_data *data);
void	draw_mini_player(t_data *data);
void	draw_player(t_data *data);
void	draw_first_line(t_data *data); // simple draw a line from center
void	draw_line(t_data *data, int i);

/* minimap.c */

/* mimimap_utils_bonus.c */
void	adjust_mapstart(int *p_x, int *p_y);
void	draw_first_line(t_data *data);
void	draw_line(t_data *data, int i);
void	draw_mini_player(t_data *data);

/* in free.c */
void	free_data(t_data *data);
void	draw_mini_map(t_data *data, int x, int y, int index);
//void	draw_map(t_data *data);

#endif