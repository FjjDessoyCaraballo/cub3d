/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cubd.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araveala <araveala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 14:36:20 by fdessoy-          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/10/11 17:27:07 by araveala         ###   ########.fr       */
=======
/*   Updated: 2024/10/11 13:28:23 by fdessoy-         ###   ########.fr       */
>>>>>>> parsing_branch
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
<<<<<<< HEAD
# define MAP "Error opening map. Maybe file does not exist.\n"
# define NAME "Map name is invalid\n"
# define MALLOC "Malloc Failure\n"
=======
# define MAP "Error\nCan't open map. File may be corrupted.\n"
# define NAME "Error\nMap name is invalid\n"
# define MALLOC "Error\nMalloc Failure\n"
# define FILE "Error\nElements may be incorrect. Check map conditions.\n"
# define SPRITE "Error\nCould not find/load sprites."
# define RGB1 "Error\nRGB (ceiling) values: value must be between 0-255\n"
# define RGB2 "Error\nRGB (floor) values: value must be between 0-255\n"
# define PLAYER "Error\nMust have one player character(N, W, S, or E)\n"
# define BRK_MAP "Error\nMap is broken ):\n"
# define CLOSE "Error\nMap is not walled correctly ):<\n"
>>>>>>> parsing_branch

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
/* usage macros **********************************/
/*************************************************/
# define TEXTURE_FAIL "texture invalid or simply missing\n"
# define IMAGE_FAIL "image invalid\n"

/*************************************************/
/*mlx macros / graphics macros********************/
/*************************************************/
# define WIDTH 1920 //~~ will play with sizes 
# define HEIGHT 1080 //~~ will play with sizes
# define T_SIZE 64 //~~ tile size
# define RAY_MAX 120.0 // could be 240
# define FOV 60.0 //~~ angle of field of view degrees 
/*************************************************/
/* math macros ***************************************/
/*************************************************/
# define ROTATE_ANGLE	0.0872665 // 5 degrees in radians
# define PI				3.14159265358979323846
# define DEG2RAD 		(PI / 180.0)
# define STEP			0.25
/*************************************************/
/* structs ***************************************/
/*************************************************/
/*1.map_x and map_y maps width and height*/
/*2. p_x and p_y player position p_dir_x and p_dir_y players sight direction*/
/*3. doubles are better than floats, more percise*/
typedef	struct s_data
{
	mlx_t	*mlx;
	mlx_t	*window; //~~ not sure if needed yet

	char	**map;
	bool	broken_map;
	size_t	map_width;
	size_t	map_length;
	char	**file;
	double	ray_len[120]; // could be 240	
	char	key_pressed[264]; // num of highest key
	int		file_len;

	int		map_x;
	int		map_y;

	int		ray_hit;
	int		side_hit; // if we want to handle shading
	double	ray_size;
	double	p_x;
	double	p_y;
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

	//bool	quit; // might no need
	/*~~bonus stuff~~*/
	mlx_texture_t	*tx_mini_floor;
	mlx_texture_t	*tx_mini_wall;
	mlx_texture_t	*tx_mini_player;
	mlx_image_t		*im_mini_floor;
	mlx_image_t		*im_mini_wall;
	mlx_image_t		*im_mini_player;
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

/* in parsing.c */
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

/* in flood_fill.c */
int8_t	copy_map(t_data *data);
void	flood_fill(t_data *data, int y, int x);

/* in error.c */
int		err_msg(char *obj, char *msg, int exit_code);

/* in usage.c */
void	usage(void);
/* in base.c*/
int		open_window(t_data *data);
/* in movement.c */
void	keyhookfunc(mlx_key_data_t keydata, void *param);
void    update_player(t_data *data);
//~~~~~~~~~~~~~~//
void	rotate_player(t_data *data, double angle);
void    strafe_player(t_data *data, double step_x, double step_y);
void    move_player(t_data *data, double step_x, double step_y);
/* in rays.c */
void	stack_ray_data(t_data *data, int i);
void	collect_ray(t_data *data, int i, double ray_distance);
//void	collect_ray(t_data *data); // simle one ray from middle
//obsolete
void    move_forward(t_data *data);
void    move_backward(t_data *data);
void    rotate_left(t_data *data);
void    rotate_right(t_data *data);
/* printer REMOVE LATER */
void	printer(t_data *data);
/* bonus */
int		initlize_minimap(t_data *data);
void	draw_player(t_data *data);
void	draw_first_line(t_data *data); // simple draw a line from center
void	draw_line(t_data *data, int i);

/* in free.c */
void	free_data(t_data *data);

#endif