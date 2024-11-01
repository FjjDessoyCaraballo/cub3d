/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araveala <araveala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 11:54:10 by araveala          #+#    #+#             */
/*   Updated: 2024/11/01 12:33:21 by araveala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cubd.h"

/**
 * Finds which wall is being hit and matches it to a texture.
 */
int	find_direction(int side, double ray_x, double ray_y)
{
	if (side == 0)
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
	return (0);
}

/**
 * out of bounds check, could be improved and checked that we are not checking nonsense
 */
static int	outof_bounds_check(t_data *data, double rpos_pixel_y, double rpos_pixel_x)
{

	if (rpos_pixel_y / T_SIZE > data->map_length || rpos_pixel_x / T_SIZE > data->map_width)
	{
		//printf("y top bound = %d x top bound = %d\n", data->map_length, data->map_width);
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

/*
We collect the length of a ray from player to wall and put it in an array
array not malloced seperatley, only malloced with data struct, ray_len[120]
~~cheat sheet~~
	1. translate players positon iin 2d array to position in pixels
	2. set ray position to pixels
	3. convert ray position back to a comparible number to compare with 2darray for wall hit check
	4. i think #here# we will need to implement if ray hits wall render 3d or collect data
*/
void	stack_ray_data(t_data *data, int i)
{
	double	current_angle;
	double	player_angle;
	double	ray_angle;

    current_angle = 0;
    ray_angle = 0;
	player_angle = atan2(data->p_dir_y, data->p_dir_x); 
	clear_image(data);
	
/**
 * please keep for now incase of potential use
 * 	//double plane_x = -data->p_dir_y * (FOV / 2);
 *  //double plane_y = data->p_dir_x * (FOV / 2);// perpendicular to player direction
 * Also note, can we change clear_image to be :
 * ft_memset(data->im_ray, 0, (data->im_ray->height * data->im_ray->width) * 4);
 * i could not make it work , it has potential to improve perfomance
 */
	while (i < RAY_MAX)
	{
		//current_angle = STARTING_ANGLE + i * ANGLE_INCREMENT;
		//ray_angle = player_angle + current_angle;
		ray_angle = player_angle + (i - RAY_MAX / 2) * ANGLE_INCREMENT; //caera_x ?
		data->ray_dir_x = cos(ray_angle);
		data->ray_dir_y = sin(ray_angle);
		collect_ray(data, i, player_angle, ray_angle);
		draw_wall(data, i, 0, 0);
		i++;
	}
	//mlx_image_to_window(data->mlx, data->im_ray, 0, 0);
}

/**
 * collects ray information based on when a wall is hit using a size of pixels
 */
void collect_ray(t_data *data, int i, double ray_distance, double ray_angle)
{
    double ppos_pixel_x = (data->x_ppos) * T_SIZE;
    double ppos_pixel_y = (data->y_ppos) * T_SIZE;

	double player_angle = ray_distance; 
	double delta_dist_x = fabs(1/ data->ray_dir_x);
    double delta_dist_y = fabs(1 / data->ray_dir_y);
    double side_dist_x, side_dist_y;
    int step_x, step_y;
    double map_x = (int)(data->x_ppos);
    double map_y = (int)(data->y_ppos);
    double perp_wall_dist;
	if (data->ray_dir_x < 0)
	{
        step_x = -1;
        side_dist_x = (ppos_pixel_x - map_x * T_SIZE) * delta_dist_x;
    }
	else
	{
        step_x = 1;
        side_dist_x = ((map_x + 1) * T_SIZE - ppos_pixel_x) * delta_dist_x;
    }
    if (data->ray_dir_y < 0)
	{
        step_y = -1;
        side_dist_y = (ppos_pixel_y - map_y * T_SIZE) * delta_dist_y;
    }
	else
	{
        step_y = 1;
        side_dist_y = ((map_y + 1) * T_SIZE - ppos_pixel_y) * delta_dist_y;
    }
    int hit = 0;
    int side = 0;
    while (hit == 0)
	{
        if (side_dist_x < side_dist_y) {
            side_dist_x += delta_dist_x * T_SIZE;
            map_x += step_x;
            side = 0;
        } else {
            side_dist_y += delta_dist_y * T_SIZE;
            map_y += step_y;
            side = 1;
        }
        if (outof_bounds_check(data, map_y, map_x) == FAILURE)
            return;
		if (data->map[(int)map_y][(int)map_x] == '1')
			hit = 1;
	}
    if (side == 0)
		perp_wall_dist = ((map_x * T_SIZE - ppos_pixel_x) + (1 - step_x) * T_SIZE / 2) / data->ray_dir_x;
    else
		perp_wall_dist = ((map_y * T_SIZE - ppos_pixel_y) + (1 - step_y) * T_SIZE / 2) / data->ray_dir_y;
	data->ray_len[i] = perp_wall_dist * cos(ray_angle - player_angle);
	// im keeping this for an idea, if the idea is easy, idea = shadowing
	//data->ray_x = ppos_pixel_x + perp_wall_dist * data->ray_dir_x;
	//data->ray_y = ppos_pixel_y + perp_wall_dist * data->ray_dir_y;
    data->ray_hit[i] = find_direction(side, data->ray_dir_x, data->ray_dir_y);
}

/**
 * original collect ray we where using, incase of needed reference, after testing over 50 times 
 * we can remove!
 */

/*void	collect_ray(t_data *data, int i, double ray_distance, double ray_angle)
{
	double	ppos_pixel_x;
	double	ppos_pixel_y;
	double	rpos_pixel_x;
	double	rpos_pixel_y;
	
	int grid_x, grid_y;
	(void)ray_angle;
	ppos_pixel_x = (data->x_ppos * T_SIZE);
	ppos_pixel_y = (data->y_ppos * T_SIZE);
	while (data->x_ppos >= 0 && data->x_ppos < WIDTH && data->y_ppos >= 0 && data->y_ppos < HEIGHT)
	{

		rpos_pixel_x = ppos_pixel_x + (data->ray_dir_x * ray_distance);
		rpos_pixel_y = ppos_pixel_y + (data->ray_dir_y * ray_distance);
		grid_x = (int)(rpos_pixel_x / T_SIZE);
        grid_y = (int)(rpos_pixel_y / T_SIZE);

		if (outof_bounds_check(data, rpos_pixel_y, rpos_pixel_x) == FAILURE)
			return ;
		if (data->map[grid_y][grid_x] == '1')
		{
			//plotLine(data , i, ppos_pixel_x, ppos_pixel_y, rpos_pixel_x, rpos_pixel_y);
			data->ray_len[i] = sqrt(pow(rpos_pixel_x - ppos_pixel_x, 2) + pow(rpos_pixel_y - ppos_pixel_y, 2));
			//if (i > 0)
			printf("check ray lemn = %f\n", data->ray_len[i]);
			//	printf("the i = %d difference between i prevand now i = %f\n",i, data->ray_len[i - 1] - data->ray_len[i]);
			//data->ray_len[i] = ray_distance + cos(FOV / 2 - ray_angle);
			data->ray_hit[i] = find_direction(data->ray_dir_x, data->ray_dir_y);
			return ;
		}
		ray_distance += 0.1;
	}
}*/

