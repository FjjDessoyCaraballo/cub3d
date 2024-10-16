/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araveala <araveala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 14:01:56 by araveala          #+#    #+#             */
/*   Updated: 2024/10/16 18:06:06 by araveala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cubd.h"

/*void initialize_player_direction(t_data *data, char initial_facing) {
	if (initial_facing == 'N') {
		data->p_dir_x = 0;
		data->p_dir_y = -1;
	} else if (initial_facing == 'S') {
		data->p_dir_x = 0;
		data->p_dir_y = 1;
	} else if (initial_facing == 'E') {
		data->p_dir_x = 1;
		data->p_dir_y = 0;
	} else if (initial_facing == 'W') {
		data->p_dir_x = -1;
		data->p_dir_y = 0;
	}
}*/
/*~~ bonus stuff but easier for visualisation~~*/
/*static void	update_array(t_data *data, int flag)
{
	data->map[data->y_ppos][data->x_ppos] = '0';
	if (flag == 1)
		data->x_ppos = data->x_ppos + 1;
	if (flag == 2)
		data->x_ppos = data->x_ppos - 1;
	if (flag == 3)
		data->y_ppos = data->y_ppos + 1;
	if (flag == 4)
		data->y_ppos = data->y_ppos - 1;
	data->map[data->y_ppos][data->x_ppos] = 'N'; // this should adjust to which way we are facing
	//d->steps += 1;
}*/

/*This computes the magnitude of the vector using the Pythagorean theorem, 
to simplyfy our directin numbers in an attempt to make math on these numbers easier*/
void	normalize_vector(double *x, double *y)
{
	double	length;

	length = sqrt((*x) * (*x) + (*y) * (*y));
	*x /= length;
	*y /= length;
}

void	strafe_player(t_data *data, double step)
{
	double	new_x;
	double	new_y;
	double	radius;
	char	map_char;
	
	radius = 10.0 / (double)T_SIZE;
	normalize_vector(&data->p_dir_x, &data->p_dir_y);
	new_x = (data->x_ppos) + (-data->p_dir_y) * step;
	new_y = (data->y_ppos) + (data->p_dir_x) * step;
	if ((new_x + radius) < 0 || (new_x - radius) > (data->map_width) || (new_y + radius) < 0 || (new_y - radius) > (data->map_length))
	{
		//printf("Out of bounds\n");
		return ;
	}
	if (new_x > data->map_width || new_y > data->map_length)
	{
		//printf("Out of bounds new\n");	
		return ;	
	}
	map_char = data->map[(int)floor(new_y)][(int)floor(new_x)];
	if (new_x < data->map_width && new_y < data->map_length)
	{	
		if (map_char == ' ' || map_char == '\0' || map_char == '\n')
		{
			//double dify = new_y - (int)floor(new_y);
			//double difx = new_x -  (int)floor(new_x);
			//printf("dify = %f dif x = %f\n", dify, difx);
			//data->x_ppos -= (-data->p_dir_y) - dify;// - STEP;//(STEP * 2); // 0.5 worked good
    	    //data->y_ppos -= (data->p_dir_x) - difx;// - STEP;//(STEP * 2);
			//printf("strafe new x = %f and new y = %f\n", new_x , new_y);
			return ;	
		}
		else if (map_char == '0' || map_char == '1') //bonus ====== != '1')		
//		else if (data->map[(int)new_y][(int)new_x] == '0' || data->map[(int)new_y][(int)new_x] == '1') //bonus ====== != '1')
		{
			data->x_ppos = new_x;
			data->y_ppos = new_y;
		}		
	}

}

/*moving player so that they dont go out of bounds, challenge is preventing entry to existing tiles
*that are marked space, ive left some solutions in theory but i will move on for now, as im not sure this will
*have much value to our project, especially since this problem should go away in the bonus
*	1. floor and ceil are math.h functions, floor rounds down from decimal
*/
void	move_player(t_data *data, double step)
{
	double	new_x;
	double	new_y;
	double	radius;
	char	map_char;

	radius = 10.0 / (double)T_SIZE + STEP;
	normalize_vector(&data->p_dir_x, &data->p_dir_y);
	new_x = (data->x_ppos) + (data->p_dir_x) * step;
	new_y = (data->y_ppos) + (data->p_dir_y) * step;
	if ((new_x + radius) < 0 || (new_x + radius) > (data->map_width) || (new_y + radius) < 0 || (new_y + radius) > (data->map_length))	
	{
		//printf("Out of bounds\n");
		return ;
	}
	if (new_x < data->map_width && new_y < data->map_length)
	{
		map_char = data->map[(int)floor(new_y)][(int)floor(new_x)];
		if (map_char == ' ' || map_char == '\0' || map_char == '\n')
		{
			//data->x_ppos -= (data->p_dir_x) * STEP;//0.5;
            //data->y_ppos -= (data->p_dir_y) * STEP;//0.5;
			//printf("new x = %f and new y = %f\n", new_x , new_y);
			return ;
		}
		else if (map_char == '0' || map_char == '1') //bonus ====== != '1')
		//else if (data->map[(int)new_y][(int)new_x] == '0' || data->map[(int)new_y][(int)new_x] == '1') //bonus ====== != '1')
		{
			data->x_ppos = new_x;
			data->y_ppos = new_y;
		}		
	}

}

void	rotate_player(t_data *data, double angle)
{
	double	prev_dir_x;

	prev_dir_x = data->p_dir_x;
	data->p_dir_x = data->p_dir_x * cos(angle) - data->p_dir_y * sin(angle);
	data->p_dir_y = prev_dir_x * sin(angle) + data->p_dir_y * cos(angle);
	normalize_vector(&data->p_dir_x, &data->p_dir_y);
}

/* stick this in keyhooks .c */
/*~~ left and right arrows should spin you in either direction
wasd keys should move you around, darwing images here are bonus material used now for visualisation
of proggress */
void	update_player(t_data *data)
{
	if (data->key_pressed[MLX_KEY_RIGHT])
		rotate_player(data, ROTATE_ANGLE);
	if (data->key_pressed[MLX_KEY_LEFT])
		rotate_player(data, -ROTATE_ANGLE);
	if (data->key_pressed[MLX_KEY_W])
		move_player(data, STEP);
	if (data->key_pressed[MLX_KEY_S])
		move_player(data, -STEP);
	if (data->key_pressed[MLX_KEY_A])
		strafe_player(data, -STEP);
	if (data->key_pressed[MLX_KEY_D])
		strafe_player(data, STEP);
		//bonuses for minimap
	mlx_delete_image(data->mlx, data->im_ray);
	mlx_delete_image(data->mlx, data->im_mini_player);
	//mlx_delete_image(data->mlx, data->im_map);
	//printf("aaaaaaaaaaaaa\n");
	draw_map(data);
	
	draw_player(data);
	stack_ray_data(data, 0);
	mlx_image_to_window(data->mlx, data->im_ray, 0, 0);
	mlx_image_to_window(data->mlx, data->im_mini_player, 0, 0);
}

/*
~~cheat sheet~~
    1. key_pressed 0 = Set the key state to released
    2. key_pressed 1 = Set the key state to released
    3. end of game flag could be required should we allow player to loose
    4. step size could go in struct 
*/
void	keyhookfunc(mlx_key_data_t keydata, void *param)
{
	t_data	*data;

	data = param;
	if (keydata.key == MLX_KEY_ESCAPE)
	{
		if (data->mlx)
			mlx_close_window(data->mlx);
		else
			printf("mlx is null for some reason\n");
	}
	if (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)
		data->key_pressed[keydata.key] = 1;
	if (keydata.action == MLX_RELEASE)
		data->key_pressed[keydata.key] = 0;
	update_player(data);
}
