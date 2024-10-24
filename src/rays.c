/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdessoy- <fdessoy-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 11:54:10 by araveala          #+#    #+#             */
/*   Updated: 2024/10/24 10:58:56 by fdessoy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cubd.h"

//ray_data->dist_to_wall = sqrtf((ray_x - data->x_ppos) * (ray_x - data->x_ppos) 
int	find_direction(double ray_x, double ray_y)//, double p_x , double p_y)
{
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
	if (rpos_pixel_y < 0 || rpos_pixel_x / T_SIZE >= data->map_width)//data->w_width)
	{
		//printf("ray bounds111 rpos x = %f also rpos y = %f and  data->w_width = %d\n", rpos_pixel_x, rpos_pixel_y, data->w_width);
		return (FAILURE);
	}
	if (rpos_pixel_y < 0 || rpos_pixel_x / T_SIZE >= data->w_height)
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
	double	starting_angle;
	double	angle_increment;
	double	current_angle;
	double	player_angle;
	double	ray_angle;

    current_angle = 0;
    ray_angle = 0;
	starting_angle = -FOV / 2 * DEG2RAD;
	angle_increment = (FOV / RAY_MAX) * DEG2RAD;
	player_angle = atan2(data->p_dir_y, data->p_dir_x);
	while (i < RAY_MAX)
	{
		current_angle = starting_angle + i * angle_increment;
		ray_angle = player_angle + current_angle;
		data->ray_dir_x = cos(ray_angle);
		data->ray_dir_y = sin(ray_angle);
		collect_ray(data, i, 0.0, ray_angle);
		draw_wall(data, i, 0, 0);
		i++;
	}
	mlx_image_to_window(data->mlx, data->im_ray, 0, 0); //WIDTH, data->w_height);
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
	(void) ray_angle;
	ppos_pixel_x = (data->x_ppos * T_SIZE) + T_SIZE / 2;
	ppos_pixel_y = (data->y_ppos * T_SIZE) + T_SIZE / 2;
	while (data->x_ppos >= 0 && data->x_ppos < data->w_width && data->y_ppos >= 0 && data->y_ppos < data->w_height)
	{
		rpos_pixel_x = ppos_pixel_x + (int)(data->ray_dir_x * ray_distance);
		rpos_pixel_y = ppos_pixel_y + (int)(data->ray_dir_y * ray_distance);
		if (outof_bounds_check(data, rpos_pixel_y, rpos_pixel_x) == FAILURE)
			return ;
		if (data->map[(int)rpos_pixel_y / T_SIZE][(int)rpos_pixel_x / T_SIZE] == '1')
		{
			//#here#
			data->ray_len[i] = ray_distance + cos(FOV / 2 - ray_angle);
			data->ray_hit[i] = find_direction(data->ray_dir_x, data->ray_dir_y);
			return ;
		}
		//ray_distance++;
		ray_distance += 0.5;
	}
}
/*void	collect_ray(t_data *data, int i, double ray_distance, double ray_angle)
{
	double	ppos_pixel_x;
	double	ppos_pixel_y;
	double	rpos_pixel_x;
	double	rpos_pixel_y;
	(void) ray_angle;
	ppos_pixel_x = (data->x_ppos * T_SIZE) + T_SIZE / 2;
	ppos_pixel_y = (data->y_ppos * T_SIZE) + T_SIZE / 2;
	//printf("/t/t/twhat is ray angle at start = %f\n", ray_angle);
	//while (data->x_ppos >= 0 && data->x_ppos < data->map_width && data->y_ppos >= 0 && data->y_ppos < data->map_length)
	while (data->x_ppos >= 0 && data->x_ppos < data->w_width && data->y_ppos >= 0 && data->y_ppos < data->w_height)
	{
		rpos_pixel_x = ppos_pixel_x + (int)(data->ray_dir_x * ray_distance);
		rpos_pixel_y = ppos_pixel_y + (int)(data->ray_dir_y * ray_distance);
		//rpos_pixel_x = ppos_pixel_x + cos(ray_angle) * ray_distance;
        //rpos_pixel_y = ppos_pixel_y + sin(ray_angle) * ray_distance;
		if (outof_bounds_check(data, rpos_pixel_y, rpos_pixel_x) == FAILURE)
			return ;
		if (data->map[(int)rpos_pixel_y / T_SIZE][(int)rpos_pixel_x / T_SIZE] == '1')
		{
			//#here#
			//double r_angle = atan2(rpos_pixel_y, rpos_pixel_x);
			double r_angle = atan2(rpos_pixel_y - ppos_pixel_y, ppos_pixel_x - rpos_pixel_x);
			double p_angle = atan2(data->p_dir_y, data->p_dir_x);

			double angle_diff = r_angle - p_angle;
			angle_diff = fmod(angle_diff + PI, 2 * PI) - PI;
			double cos_angle_diff = cos(angle_diff);			
			if (fabs(cos_angle_diff) < 1e-6)//cos_angle_diff)
			{
				//data->ray_len[i] = 1e-0;
				cos_angle_diff = (cos_angle_diff < 0) ? -1e-2 : 1e-2;
				//if (fabs(cos_angle_diff) < 1e-6)//cos_angle_diff)
				//	printf("stilllaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\n");
				//return ;
			}
				//printf("ray len = %f\n", data->ray_len[i]);
			data->ray_len[i] = ray_distance + cos_angle_diff / 2;
			//printf("ray len = %e\n", data->ray_len[i]);
			//printf("ray len just after = %f\n", data->ray_len[i]);
			//data->rayx[i] = data->ray_dir_x;
			//data->rayy[i] = data->ray_dir_y;
			data->ray_hit[i] = find_direction(data->ray_dir_x, data->ray_dir_y);
			//printf("ray len before print = %f\n", data->ray_len[i]);
			return ;
		}
		ray_distance ++;//= 0.1;
	}
	
	//if (data->ray_len[i] == 0)
	//	data->ray_len = 
}*/
