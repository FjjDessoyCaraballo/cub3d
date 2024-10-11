/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cubd.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araveala <araveala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 14:36:20 by fdessoy-          #+#    #+#             */
/*   Updated: 2024/10/11 17:27:07 by araveala         ###   ########.fr       */
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
# define MAP "Error opening map. Maybe file does not exist.\n"
# define NAME "Map name is invalid\n"
# define MALLOC "Malloc Failure\n"

# define SUCCESS 0
# define FAILURE 1

/*************************************************/
/* usage macros **********************************/
/*************************************************/
# define USAGE1 "Welcome to cub3d "
# define USAGE2 "and you already have committed your first mistake."
# define USAGE3 " Follow the usage below:\n"
# define USAGE4 "1. map must have the suffix '.cub';\n"
# define USAGE5 "2. In clt just execute the program and map;\n"
# define USAGE6 "3. Map must contain all elements (sprites with "
# define USAGE7 "cardinal orientation, proper walled map, and "
# define USAGE8 "RGB notated instructions [numerical value]);\n\n"
# define USAGE9 "This game has no exit for now, so use ESC to "
# define USAGE10 "finish the game (:\n\n"
# define USAGE11 "By: fdessoy- | araveala\n"

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

	// neeed some camera suff i gues pov?

	bool	s_flag;
	bool	n_flag;
	bool	e_flag;
	bool	w_flag;	
	
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

/* in initializer.c */
void	initializer(t_data *data);

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
void	printer(char **array);
/* bonus */
int		initlize_minimap(t_data *data);
void	draw_player(t_data *data);
void	draw_first_line(t_data *data); // simple draw a line from center
void	draw_line(t_data *data, int i);

#endif