/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_higher_dimension.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araveala <araveala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 10:50:15 by araveala          #+#    #+#             */
/*   Updated: 2024/10/17 13:01:55 by araveala         ###   ########.fr       */
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
/*int	draw_walls(t_data *data)
{
	
	int i;
	double	wall_h;
	double	cieling_me;
	double	floor_me;

	i = 0;
	wall_h = 0.0;
	cieling_me = 0.0;
	floor_me = 0.0;
	while (i <= RAY_MAX)
	{
		//data->im_current__wall = get_texture();
		
		//draw_piece(t_data *data, i);
		i++;
	}
	//if (data->hitdir[]	
}*/
// draw walls
// draw floor
// draw cieling
// adjust fisheye (tan)