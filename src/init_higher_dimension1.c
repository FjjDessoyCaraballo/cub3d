/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_higher_dimension1.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araveala <araveala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 10:50:15 by araveala          #+#    #+#             */
/*   Updated: 2024/11/15 13:09:58 by araveala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cubd.h"

/**
 * Calculate img_x to grab the correct pixel from out texture,
 * using pre collected ray_x and ray_y (wall hit locations in pixels).
 * We normalize the result with T_SIZE (64) so that we can wrap the data to
 * stick within bounds of T_SIZE.
 * 
 * @param data data struct containing most varaibles
 * 
 * @return texture position reduced by T_SIZE so that we can re adjust
 * the number to fit withing the texture width. 
 */
double	calculate_img_x(t_data *data)
{
	double	texture_pos;
	double	offset;

	if (data->side == 0)
		texture_pos = data->ray_y;
	else
		texture_pos = data->ray_x;
	texture_pos = fabs(fmod(texture_pos, T_SIZE));
	offset = fmod(data->ppos_pix_x * 0.0001 + data->ppos_pix_y * 0.0001, 1.0);
	texture_pos += offset;
	texture_pos = fmod(texture_pos, T_SIZE);
	return ((texture_pos / T_SIZE) * data->im_current_wall->width);
}

/** 
 * Initializes key variables for the wall drawing process
 * 
 * @param data data structure to be passed down
 * @param i index given previously
 * @param wall_h
 * @param img_x
*/
void	initialize_wall_params(t_data *data, int i, double *w_h, double *img_x)
{
	data->wall_line = i * (WIDTH / RAY_MAX);
	*img_x = calculate_img_x(data);
	*w_h = HEIGHT / data->ray_len[i] * data->wall_scale;
}

/**
 * Draws a stretched wall when its height exceeds the screen
 * 
 * @param data data structure to be passed down
 * @param img_x the x location of wanted pixel on the texture 
 * @param wall_h
 * @param fset calculated offset for finding part of texture, we match
 * wall pixels based on being so close to wall that we do not
 * "see" the top or bottom 
 * 
*/
void	draw_stretched_wall(t_data *data, double img_x, double w_h, \
	double fset)
{
	double		img_y_inc;
	double		current_wall_pos;
	double		img_y;
	uint32_t	colour;

	img_y_inc = data->im_current_wall->height / w_h;
	fset = (((w_h / T_SIZE) - diff(w_h)) / 2.0) * img_y_inc - 0.75;
	current_wall_pos = 0;
	while (current_wall_pos < HEIGHT)
	{
		img_y = current_wall_pos * img_y_inc - fset;
		colour = fetch_pixel_rgb(data->im_current_wall, img_x, img_y, 0);
		if (colour != 0)
		{
			mlx_put_pixel(data->im_ray, data->wall_line, \
				current_wall_pos, colour);
		}
		current_wall_pos++;
	}
}

/**
 * Draws a regular wall when its height is within the screen bounds
 * 
 * @param data data structure to be passed down
 * @param w_h wall height
 * @param img_x 
 * @param w_t (top of the wall) data regarding the position in the screen to the 
 * top of the wall
*/
void	draw_regular_wall(t_data *data, double w_h, double img_x, double w_t)
{
	double		img_y_inc;
	double		current_wall_pos;
	double		max_wall_h;
	uint32_t	colour;
	double		img_y;

	img_y_inc = data->im_current_wall->height / w_h ;
	current_wall_pos = w_t;
	max_wall_h = w_t + w_h;
	while (current_wall_pos < max_wall_h && current_wall_pos < HEIGHT)
	{
		img_y = (current_wall_pos - w_t) * img_y_inc;
		colour = fetch_pixel_rgb(data->im_current_wall, img_x, img_y, 0);
		if (colour == 0)
			break ;
		mlx_put_pixel(data->im_ray, data->wall_line, current_wall_pos, colour);
		current_wall_pos++;
	}
}

/**
 * Takes the ray length and calulate the height of the wall and draws 
 * the wall one pixel at a time. Each pixel is chosen from a texture 
 * provided and calculated to fit the 3d world.
 * 
 * if wall_h > hscreen height we set wall_h to be 1 less than HEIGTH 
 * so we enter the drawing loop this small if loop is supposed to speed
 * things up when turning around close to a wall, it dosnt but it could be 
 * possible to make iit work better.
 * 
 * We check for colour != 0 to avoid segfaults.
 * 
 * @param data data structure to be passed down
 * @param i index given previously
 * 
 * @return draw_wall() returns SUCCESS if no error occurred;
 * In case of error, we return FAILURE.
 */

int	draw_wall(t_data *data, int i)
{
	double	wall_h;
	double	img_x;
	double	top_of_wall;

	if (check_for_wall_failure(data, i) == FAILURE)
		return (FAILURE);
	initialize_wall_params(data, i, &wall_h, &img_x);
	if (wall_h > HEIGHT)
	{
		draw_stretched_wall(data, img_x, wall_h, 0);
		return (SUCCESS);
	}
	top_of_wall = (HEIGHT - wall_h) / 2;
	draw_regular_wall(data, wall_h, img_x, top_of_wall);
	return (SUCCESS);
}
