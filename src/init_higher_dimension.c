/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_higher_dimension.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araveala <araveala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 10:50:15 by araveala          #+#    #+#             */
/*   Updated: 2024/10/22 12:20:46 by araveala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cubd.h"

/**
 * set up for 3d stuff 
 * 
 */
/*int	init_bigmap(t_data *data)
{
	data->tx_n_wall = mlx_load_png("data->path...wall.png");
	data->tx_s_wall = mlx_load_png("data->path...wall.png");
	data->tx_e_wall = mlx_load_png("data->path...wall.png");
	data->tx_w_wall = mlx_load_png("data->path...wall.png");
	if (data->tx_n_wall == NULL || data->tx_s_wall == NULL 
	|| data->tx_e_wall == NULL || data->tx_w_wall)
		return (err_msg(NULL, TEXTURE_FAIL, FAILURE));
	data->im_n_wall = mlx_texture_to_image(data->mlx, data->tx_n_wall);
	data->im_s_wall = mlx_texture_to_image(data->mlx, data->tx_s_wall);
	data->im_e_wall = mlx_texture_to_image(data->mlx, data->tx_e_wall);
	data->im_w_wall = mlx_texture_to_image(data->mlx, data->tx_w_wall);
	if (data->im_n_wall == NULL || data->im_s_wall == NULL 
	|| data->im_e_wall == NULL || data->im_w_wall)
		return (err_msg(NULL, IMAGE_FAIL, FAILURE));
	// set floor to data->rgb values
	// set cieling to data->rgb values
}*/
/*char	get_texture(t_data *data)
{
	if (data->hitdir == 1)
		return (data->im_n_wall); ?? dont know what to return
	else if (data->hitdir == 2)
		return (south);
	else if (data->hitdir == 3)
		return ();
	else if (data->hitdir == 4)	
		return ();
}*/
//		get_texture[i];

/*void render_3d_scene(t_data *data) {
    for (int i = 0; i < NUM_RAYS; i++) {
        double ray_length = data->ray_len[i];
        int wall_face = data->hit_face[i];

        double wall_height = SCREEN_HEIGHT / ray_length;
        double ceiling = (SCREEN_HEIGHT / 2.0) - (wall_height / 2.0);
        double floor = (SCREEN_HEIGHT / 2.0) + (wall_height / 2.0);

        draw_wall_slice(data, i, ceiling, floor, wall_face);
    }
}

void draw_wall_slice(t_data *data, int x, double ceiling, double floor, int face) {
    uint32_t* texture = get_texture_for_face(face);
    for (int y = 0; y < SCREEN_HEIGHT; y++) {
        if (y < ceiling) {
            // Draw ceiling
            mlx_put_pixel(data->im_screen, x, y, ceiling_color);
        } else if (y > floor) {
            // Draw floor
            mlx_put_pixel(data->im_screen, x, y, floor_color);
        } else {
            // Draw wall with appropriate texture
            int texture_y = (y - ceiling) * TEXTURE_HEIGHT / (floor - ceiling);
            mlx_put_pixel(data->im_screen, x, y, texture[texture_y]);
        }
    }
}*/

/**
 * Clears a singular line of pixels so we can re draw ne set of pixels on 
 * a clear canvas, in theory this could only clear pixels that are previouse
 * wall and not new wall, this code was simpler and payoff for workload
 * does not have enough value for such low graphics
 */
static void	clear_img(t_data *data, int i)
{
	int	y;
	int	x;

	y = 0;
	x = i * (WIDTH / RAY_MAX);
	while (y < HEIGHT)
	{
		mlx_put_pixel(data->im_ray, x, y, 0x00000000);	
		y++;
	}	
}

int	draw_wall(t_data *data, int i)
{
	uint32_t red = 0xFF00FFF0;	

	double	wall_h;
	int x = 0;
	double top_of_wall = 0.0; // top of the wall
	double current_wall_pos = 0.0; //increment going down to the bottom of the floor
	double wall_bottom = 0.0; //new

	wall_h = 0.0;
	wall_h = HEIGHT / data->ray_len[i]; // we get the height of the wall based on len
	top_of_wall = (HEIGHT - wall_h) / 2; // we set our starting point to the top of where thw all begins
	current_wall_pos = top_of_wall; // we set our incrementer 
	wall_bottom = top_of_wall + wall_h;
	clear_img(data, i);
	while (current_wall_pos < wall_bottom)
	{
		if (current_wall_pos > 0 && current_wall_pos < HEIGHT)
		{
			x = i * (WIDTH / RAY_MAX);
			if (x >= 0 && x < WIDTH && data->ray_len[i] > 0) // or not 0
			{
				mlx_put_pixel(data->im_ray, x, (int)current_wall_pos, red);					
			}
		}
//		current_wall_pos += increment;
		current_wall_pos++;
	}	
	return (SUCCESS);
}