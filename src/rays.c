/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdessoy- <fdessoy-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 11:54:10 by araveala          #+#    #+#             */
/*   Updated: 2024/11/01 13:26:59 by fdessoy-         ###   ########.fr       */
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
	
	data->exact_x = data->x_ppos * T_SIZE / 2;
	data->exact_y = data->y_ppos * T_SIZE / 2;
	current_angle = 0;
	ray_angle = 0;
	player_angle = atan2(data->p_dir_y, data->p_dir_x); 
	clear_image(data);
	while (i < RAY_MAX)
	{
		ray_angle = player_angle + (i - RAY_MAX / 2) * ANGLE_INCREMENT;
		data->ray_dir_x = cos(ray_angle);
		data->ray_dir_y = sin(ray_angle);
		collect_ray(data, i, player_angle, ray_angle);
		draw_wall(data, i, 0, 0);
		i++;
	}
	mlx_image_to_window(data->mlx, data->im_ray, 0, 0);
}

/**
 * collects ray information based on when a wall is hit using a size of pixels
 */
void collect_ray(t_data *data, int i, double ray_distance, double ray_angle)
{
    double	ppos_pixel_x = (data->x_ppos) * T_SIZE;
    double	ppos_pixel_y = (data->y_ppos) * T_SIZE;
	double	player_angle = ray_distance; 
	double	delta_dist_x = fabs(1 / data->ray_dir_x);
    double	delta_dist_y = fabs(1 / data->ray_dir_y);
    double	perp_wall_dist;


    int		map_x = (int)(data->x_ppos);
    int		map_y = (int)(data->y_ppos);
    double	side_dist_x; // one function returning side_dist
    int 	step_x; // one function returning step
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
	
	int		step_y;
	double	side_dist_y;
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
            return ;
		if (data->map[(int)map_y][(int)map_x] == '1')
			hit = 1;
	}
    if (side == 0)
		perp_wall_dist = ((map_x * T_SIZE - ppos_pixel_x) + (1 - step_x) * T_SIZE / 2) / data->ray_dir_x;
    else
		perp_wall_dist = ((map_y * T_SIZE - ppos_pixel_y) + (1 - step_y) * T_SIZE / 2) / data->ray_dir_y;
	data->ray_len[i] = perp_wall_dist * cos(ray_angle - player_angle);
    data->ray_hit[i] = find_direction(side, data->ray_dir_x, data->ray_dir_y);
}
