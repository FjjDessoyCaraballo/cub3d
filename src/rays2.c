/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdessoy- <fdessoy-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 12:11:16 by fdessoy-          #+#    #+#             */
/*   Updated: 2024/11/04 13:20:32 by fdessoy-         ###   ########.fr       */
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
			return (EAST);
		else
			return (WEST);
	}
	else
	{
		if (ray_y > 0)
			return (SOUTH);
		else			
			return (NORTH);
	}
	return (0);
}

/**
 * out of bounds check, could be improved and checked that we are not checking nonsense
 */
int	outof_bounds_check(t_data *data, double rpos_pixel_y, double rpos_pixel_x)
{
	if (rpos_pixel_y / T_SIZE > data->map_length || rpos_pixel_x / T_SIZE > data->map_width)
		return (FAILURE);		
	if (rpos_pixel_y < 0 || rpos_pixel_x / T_SIZE >= data->map_width)
		return (FAILURE);
	if (rpos_pixel_y < 0 || rpos_pixel_x / T_SIZE >= HEIGHT)
		return (FAILURE);
	if (data->y_ppos - STEP > data->map_length)
		return (FAILURE);
	if (data->x_ppos + STEP > data->map_width)
		return (FAILURE);	
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

/**
 * We collect the length of a ray from player to wall and put it in an array
 * array not malloced seperatley, only malloced with data struct, ray_len[120]
 * ~~cheat sheet~~
 * 1. translate players positon iin 2d array to position in pixels;
 * 2. set ray position to pixels;
 * 3. convert ray position back to a comparible number to compare with 2darray
 * for wall hit check;
 * 4. i think here we will need to implement if ray hits wall render 3d or collect data;
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
		draw_wall(data, i);
		i++;
	}
	mlx_image_to_window(data->mlx, data->im_ray, 0, 0);
}