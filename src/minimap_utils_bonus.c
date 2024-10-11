/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araveala <araveala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 08:37:11 by araveala          #+#    #+#             */
/*   Updated: 2024/10/11 17:25:09 by araveala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cubd.h"
#include <string.h> //~~ testing 

/*~~ the purpose of this function is to attempt to rotate a player texture
1. the image rotates around its center axis 
2. it should do it so that the image remains intact, unfortunatley there is heavy distortion
3. this is to be fixed only if we have time or interest 
~~*/
int rotate_player_marker(t_data *data)
{
    int width = T_SIZE;
    int height = T_SIZE;
    mlx_image_t *rotated_image = mlx_new_image(data->mlx, width, height);
    uint8_t *rotated_pixels = ( uint8_t*)rotated_image->pixels;

    double cos_angle = cos(ROTATE_ANGLE);
    double sin_angle = sin(ROTATE_ANGLE);
    int y = 0;
    int x = 0;
    int new_x = 0;
    int new_y = 0;
    int center_x = width / 2;
    int center_y = height / 2;
    // trying to clear the prev pixels but no worky
    memset(rotated_pixels, 0, width * height * 4);
    while (y < height)
    {
        x = 0;
        while (x < width)
        {
            //printf("show me x = %d\n", x);
            int src_x = x - center_x;
            int src_y = y - center_y;
            new_x = (int)(cos_angle * src_x - sin_angle * src_y + center_x);
            new_y = (int)(sin_angle * src_x + cos_angle * src_y + center_y);
            if (new_x >= 0 && new_x < width && new_y >= 0 && new_y < height)
            {
                int x1 = (int)new_x;
                int y1 = (int)new_y;
                int x2 = x1 + 1;
                int y2 = y1 + 1;

                if (x2 >= width) x2 = width - 1;
                if (y2 >= height) y2 = height - 1;

                double a = new_x - x1;
                double b = new_y - y1;

                for (int c = 0; c < 4; c++) // For each color channel (RGBA)
                {
                    rotated_pixels[(y * width + x) * 4 + c] =
                        (1 - a) * (1 - b) * data->im_mini_player->pixels[(y1 * width + x1) * 4 + c] +
                        a * (1 - b) * data->im_mini_player->pixels[(y1 * width + x2) * 4 + c] +
                        (1 - a) * b * data->im_mini_player->pixels[(y2 * width + x1) * 4 + c] +
                        a * b * data->im_mini_player->pixels[(y2 * width + x2) * 4 + c];
                }
                /*int src_index = (y * width + x) * 4; // Assuming 4 bytes per pixel (RGBA)
                int dest_index = (new_y * width + new_x) * 4;
                // rotate original image
                rotated_pixels[dest_index] = data->im_mini_player->pixels[src_index];
                rotated_pixels[dest_index + 1] = data->im_mini_player->pixels[src_index + 1];
                rotated_pixels[dest_index + 2] = data->im_mini_player->pixels[src_index + 2];
                rotated_pixels[dest_index + 3] = data->im_mini_player->pixels[src_index + 3];
               // rotated_pixels[dest_index + 4] = data->im_mini_player->pixels[src_index + 4];
                // definatley getting somewhere playng around with these , u have 1 hour in the morning to figure it out!
                //rotated_pixels[dest_index + 5] = data->im_mini_player->pixels[src_index + 5];
                //rotated_pixels[dest_index + 6] = data->im_mini_player->pixels[src_index + 6];
                //rotated_pixels[dest_index + 7] = data->im_mini_player->pixels[src_index + 7];
                //printf("roatting ?\n");*/
            }
            x++;
        }
        y++;
    }
    mlx_image_to_window(data->mlx, rotated_image, data->p_x * T_SIZE, data->p_y * T_SIZE);
    mlx_delete_image(data->mlx, data->im_mini_player); // Clean up the old image
    data->im_mini_player = rotated_image; // Update the image refer
    return (0);
}