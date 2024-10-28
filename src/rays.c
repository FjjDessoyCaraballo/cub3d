/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdessoy- <fdessoy-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 11:54:10 by araveala          #+#    #+#             */
/*   Updated: 2024/10/28 10:52:05 by fdessoy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cubd.h"

//ray_data->dist_to_wall = sqrtf((ray_x - data->x_ppos) * (ray_x - data->x_ppos) 
int	find_direction(t_data *data, double ray_x, double ray_y)//, double p_x , double p_y)
{
	
	data->ray_delta_x = fabs(1 / data->ray_dir_x);
	data->ray_delta_y = fabs(1 / data->ray_dir_y);
	// if (data->)
	if (fabs(ray_x) > (fabs(ray_y)))
	{
		if (ray_x > 0)
		{
			//printf("east\n");
			return (EAST);
		}
		else
		{
			//printf("west\n");
			return (WEST);
		}
	}
	else
	{
		if (ray_y > 0)
		{
			//printf("south\n");			
			return (SOUTH);
		}
		else
		{
			//printf("north\n");			
			return (NORTH);
		}
	}
}

static int	outof_bounds_check(t_data *data, double rpos_pixel_y, double rpos_pixel_x)
{

	if (rpos_pixel_y / T_SIZE > data->map_length || rpos_pixel_x / T_SIZE > data->map_width)
	{
		//printf("ray bounds000 rpos x = %f also rpos y = %f\n", rpos_pixel_x / 64, rpos_pixel_y / 64);
		return (FAILURE);		
	}
	if (rpos_pixel_y < 0 || rpos_pixel_x / T_SIZE >= data->map_width)//WIDTH)
	{
		//printf("ray bounds111 rpos x = %f also rpos y = %f and  WIDTH = %d\n", rpos_pixel_x, rpos_pixel_y, WIDTH);
		return (FAILURE);
	}
	if (rpos_pixel_y < 0 || rpos_pixel_x / T_SIZE >= HEIGHT)
	{
		//printf("ray bounds2222 ray x = %f\n", rpos_pixel_x);
		return (FAILURE);
	}
	if (data->y_ppos - STEP > data->map_length)// - 1)
	{
		//printf("ray bounds3333\n");	
		return (FAILURE);	
	}
	if (data->x_ppos + STEP > data->map_width)// - 1)
	{
		//printf("ray bounds4444\n");	
		return (FAILURE);	
	}
	return (SUCCESS);
}
/**
 * clears the whole buffer for a clean canvas for the next set of rays
 * by putting a transparent pixel everywhere, transparent allows us
 * to continue seeing the background.
 */
static void clear_image(t_data *data)
{
	int x;
	int	y;

	x = 0;
	y = 0;
    while (y < HEIGHT)
	{
        while (x < WIDTH)
		{
            mlx_put_pixel(data->im_ray, x, y, 0x00000000);
        	x++;
		}
		x = 0;
		y++;
    }
}
// might need to malloc array before all of this
/* collect and draw a ray based on math~~angles, pie and radians
to calculate and draw each ray , collecting usable data for each ray, 
we increment per ray and rays angle.
 collect_rays last argumentg is 0.0 to reset every call
	1. calculating angles and transalting degrees to radians for ray segments
	that will be used to calculate distance
	2. FOV field of view is degrees of view
	3. DEG2RAD calculating degrees to radian from pi
	4. RAY_MAX maximum number of rays we want (120) for now
*/
void	stack_ray_data(t_data *data, int i)
{
	//double	starting_angle;
	//double	angle_increment;
	double	current_angle;
	double	player_angle;
	double	ray_angle;

    current_angle = 0;
    ray_angle = 0;
	//starting_angle = -FOV / 2 * DEG2RAD;
	//angle_increment = (FOV / RAY_MAX) * DEG2RAD;
	player_angle = atan2(data->p_dir_y, data->p_dir_x);
	clear_image(data);
	while (i < RAY_MAX)
	{
		current_angle = STARTING_ANGLE + i * ANGLE_INCREMENT;
		ray_angle = player_angle + current_angle;
		data->ray_dir_x = cos(ray_angle); //array
		data->ray_dir_y = sin(ray_angle); //array
		//data->ray_hit[i] = find_direction(data->ray_dir_x, data->ray_dir_y);
		collect_ray(data, i, 0.0, ray_angle);
		draw_wall(data, i, 0, 0);
		i++;
	}
	mlx_image_to_window(data->mlx, data->im_ray, 0, 0); //WIDTH, HEIGHT);
}

/*
We collect the length of a ray from player to wall and put it in an array
array not malloced seperatley, only malloced with data struct, ray_len[120]
~~cheat sheet~~
	1. translate players positon iin 2d array to position in pixels
	2. set ray position to pixels
	3. convert ray position back to a comparible number to compare with 2darray for wall hit check
	4. i think #here# we will need to implement if ray hits wall render 3d or collect data
*/
void	collect_ray(t_data *data, int i, double ray_distance, double ray_angle)
{
	double	ppos_pixel_x;
	double	ppos_pixel_y;
	double	rpos_pixel_x;
	double	rpos_pixel_y;
	
	ppos_pixel_x = (data->x_ppos * T_SIZE) + T_SIZE / 2;
	ppos_pixel_y = (data->y_ppos * T_SIZE) + T_SIZE / 2;
	while (data->x_ppos >= 0 && data->x_ppos < WIDTH && data->y_ppos >= 0 && data->y_ppos < HEIGHT)
	{
		rpos_pixel_x = ppos_pixel_x + (int)(data->ray_dir_x * ray_distance);
		rpos_pixel_y = ppos_pixel_y + (int)(data->ray_dir_y * ray_distance);
		if (outof_bounds_check(data, rpos_pixel_y, rpos_pixel_x) == FAILURE)
			return ;
		if (data->map[(int)rpos_pixel_y / T_SIZE][(int)rpos_pixel_x / T_SIZE] == '1')
		{
			//#here#
			data->ray_len[i] = ray_distance + cos(FOV / 2 - ray_angle);
			data->ray_hit[i] = find_direction(data, data->ray_dir_x, data->ray_dir_y);
			//data->ray_hit[i] = find_direction(rpos_pixel_x, rpos_pixel_y);
			//draw_wall(data, i, 0, 0);
			return ;
		}
		//ray_distance++;
		ray_distance += 0.3;
	}
}
