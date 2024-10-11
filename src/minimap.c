/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araveala <araveala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 08:32:58 by araveala          #+#    #+#             */
/*   Updated: 2024/10/11 13:22:28 by araveala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cubd.h"

/*int adjust_tilesize(t_data *data)
{
	size_t	x_comp;
	size_t	y_comp;
	if (data->map_x * data->t_size > WIDTH || data->map_y * data->t_size > HEIGHT)
	{
		x_comp = data->map_x * data->t_size;
		y_comp = data->map_y * data->t_size;
		if (x_comp > y_comp && x_comp > WIDTH)
		{
			while (data->map_x * data->t_size > WIDTH)
			{
				data->t_size -= 1;
				if (data->t_size < 21)
					printf("error in tile size\n");
			}
		}
		else if (data->map_y * data->t_size > HEIGHT)
		{
			while (data->map_y * data->t_size > HEIGHT)
			{
				data->t_size -= 1;	
				if (data->t_size < 21)
					printf("error in tile size\n");
			}
		}
	}
	return (0);
}*/
/*
this draws a square
void	draw_player(t_data *data)
{
	int dot_size = 20; // Change this to make the dot bigger or smaller.
	int red = 0x0000FF; // Hex color code for red. 0xFFFFFF;//
	int i;
	int x;
	int half_size = dot_size / 2;
	
	x = 0;
	i = 0;//-dot_size / 2;
	int start_x = (data->p_x * 64) + 32 - half_size;
    int start_y = (data->p_y * 64) + 32 - half_size;

	data->im_mini_player = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	// Function to draw the dot.
	while (i <= dot_size)
	{
		printf("bug hunting 2\n");
		printf("the iii = %d\n", i);
		// this part would draw a line up to down 
		while (x <= dot_size)
		{
			int draw_x = start_x + i;
            int draw_y = start_y + x;
			if (draw_x >= 0 && draw_x < WIDTH && draw_y >= 0 && draw_y < HEIGHT)
			{
				printf("draw x = %d\n", draw_x);
				printf("draw y = %d\n", draw_y);

                mlx_put_pixel(data->im_mini_player, draw_x, draw_y, red);
				printf("the xxx = %d\n", x);
				printf("bug hunting 3\n");
			}
			//ends here 
			x++;
		}
		x = 0;
		printf("bug hunting 4\n");	
		i++;
	}
}*/
/// simple draw a line
void    draw_first_line(t_data *data)
{
	uint32_t	red = 0xFF00FFF0;//0xFF0000FF;//stick in bonus.h
	int i;
	
	int start_x = (data->p_x * 64) + 32;
    int start_y = (data->p_y * 64) + 32;
	i = 0;
	data->im_ray = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	// if north draw up so -y
	while (i <= 40)
	{
//		printf("the iii = %d\n", i);
		// this part would draw a line up to down 
		int draw_x = start_x + (int)(data->p_dir_x * i);
        int draw_y = start_y+ (int)(data->p_dir_y * i);
		if (draw_x >= 0 && draw_x < WIDTH && draw_y >= 0 && draw_y < HEIGHT)
		{
			//printf("draw x = %d\n", draw_x);
			//printf("draw y = %d\n", draw_y);
            mlx_put_pixel(data->im_ray, draw_x, draw_y, red);
			//printf("the xxx = %d\n", x);
			//printf("bug hunting 3\n");
		}
		i++;
	}
}


void    draw_line(t_data *data, int i)
{
	uint32_t	red = 0xFF00FFF0;//0xFF0000FF;//stick in bonus.h
	int len;
	
	int start_x = (data->p_x * 64) + 32;
    int start_y = (data->p_y * 64) + 32;
	len = 0;
	//data->im_ray = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	// if north draw up so -y
	while (len <= data->ray_len[i])
	{
//		printf("the iii = %d\n", i);
		// this part would draw a line up to down 
		//int draw_x = start_x + (int)(data->p_dir_x * len);
        //int draw_y = start_y+ (int)(data->p_dir_y * len);
		int draw_x = start_x + (int)(data->ray_dir_x * len);
        int draw_y = start_y+ (int)(data->ray_dir_y * len);

		if (draw_x >= 0 && draw_x < WIDTH && draw_y >= 0 && draw_y < HEIGHT)
		{
			//printf("draw x = %d\n", draw_x);
			//printf("draw y = %d\n", draw_y);
            mlx_put_pixel(data->im_ray, draw_x, draw_y, red);
			//printf("the xxx = %d\n", x);
			//printf("bug hunting 3\n");
		}
		len++;
	}
	//if south draw like this
	/*while (i <= ray_size)
	{
		printf("bug hunting 2\n");
		printf("the iii = %d\n", i);
		// this part would draw a line up to down 
		int draw_x = start_x; // + i
        int draw_y = start_y + i; // + x
		if (draw_x >= 0 && draw_x < WIDTH && draw_y >= 0 && draw_y < HEIGHT)
		{
			printf("draw x = %d\n", draw_x);
			printf("draw y = %d\n", draw_y);
            mlx_put_pixel(data->im_ray, draw_x, draw_y, red);
			printf("the xxx = %d\n", x);
			printf("bug hunting 3\n");
		}
		x++;
		printf("bug hunting 4\n");	
		i++;
	}*/

}

// lets draw a circle
void draw_player(t_data *data)
{
	uint32_t red;
    int radius; // we can do this differently for bonus
	int center_x;
	int center_y;
	int y;
	int x;
	int draw_x;
	int draw_y;
	
	red = 0xFF0000FF;
	radius  = 20 / 2;
	data->im_mini_player = mlx_new_image(data->mlx, WIDTH, HEIGHT);
    // Translate player coordinates to pixel coordinates.
	//printf("data x = %f, data y= %f\n", data->p_x, data->p_y);
    center_x = (int)(data->p_x * 64) + 32;
    center_y = (int)(data->p_y * 64) + 32;
	//printf("c y = %d and c x = %d\n", center_y, center_x);
    y = -radius;
    while (y <= radius) 
	{
        x = -radius;
        while (x <= radius)
		{
            if ((x * x) + (y * y) <= (radius * radius))
			{
                draw_x = center_x + x;
                draw_y = center_y + y;
                if (draw_x >= 0 && draw_x < WIDTH && draw_y >= 0 && draw_y < HEIGHT)
					mlx_put_pixel(data->im_mini_player, draw_x, draw_y, red);
            }
            x++;
        }
        y++;
    }
}

void	init_mini_walls(t_data *data)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (y < data->map_y)
	{
		while (x < data->map_x)
		{
			if (data->map[y][x] == '1' && x < data->map_x)
			{
				// starting should be dependant on if n/s/w/e
				mlx_image_to_window(data->mlx, data->im_mini_wall, x * data->t_size, y * data->t_size);
				//mlx_image_to_window(data->mlx, data->im_mini_wall, 0, 0);
			}
			x++;
		}
		x = 0;
		y++;
	}
}

void	init_mini_floor(t_data *data)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (y < data->map_y)
	{
		printf("what char = %c\n", data->map[y][x]);
		while (x < data->map_x)
		{
			if (data->map[y][x] == '0' ||  data->map[y][x] == 'N') // char for player
				mlx_image_to_window(data->mlx, data->im_mini_floor, x * data->t_size, y * data->t_size);
			x++;
 		}
		x = 0;
		y++;
	}
}

void	init_mini_player(t_data *data)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	//~~ char p = loop through bool to find which one is true, return char.
	while (y < data->map_y)
	{
		while (x < data->map_x)
		{
			if (data->map[y][x] == 'N' && x < data->map_x) // N ret char
			{
				data->p_x = (double)x; //remove once parsing has it
				data->p_y = (double)y;
				// reps north right now .
				data->p_dir_x = 0;
	        	data->p_dir_y = -1;
				if (data->ray_size == 0)
					data->ray_size = 40;
				data->map[y][x] = '0'; // we dont need the n anymore
				draw_player(data);
				draw_first_line(data);
				mlx_image_to_window(data->mlx, data->im_mini_player, 0, 0);
				//mlx_image_to_window(data->mlx, data->im_ray, 0, 0);
			}
			x++;
 		}
		x = 0;
		y++;
	}
}

int init_mini_imgs(t_data *data)
{
    data->tx_mini_floor = mlx_load_png("./minimap_textures/floor.png");
    data->tx_mini_wall = mlx_load_png("./minimap_textures/grass.png");
    //data->tx_mini_player = mlx_load_png("./minimap_textures/player.png");
    if (data->tx_mini_floor == NULL || data->tx_mini_wall == NULL)// || data->tx_mini_player == NULL)
		return (err_msg(NULL, TEXTURE_FAIL, FAILURE));
    data->im_mini_floor = mlx_texture_to_image(data->mlx, data->tx_mini_floor);
    data->im_mini_wall = mlx_texture_to_image(data->mlx, data->tx_mini_wall);
    if (data->im_mini_floor == NULL || data->im_mini_wall == NULL)// || data->im_mini_player == NULL)
		return (err_msg(NULL, IMAGE_FAIL, FAILURE));
   	mlx_resize_image(data->im_mini_floor, data->t_size, data->t_size); //T_SIZE, T_SIZE);
    mlx_resize_image(data->im_mini_wall, data->t_size, data->t_size); //T_SIZE, T_SIZE);
	//mlx_resize_image(data->im_mini_player, data->t_size, data->t_size); //T_SIZE, T_SIZE);
    return (0);
}

int initlize_minimap(t_data *data)
{
	data->t_size = T_SIZE;
	//adjust_tilesize(data); // does it do anything ?
    init_mini_imgs(data);
    init_mini_floor(data);
    init_mini_walls(data);
	init_mini_player(data);
    return (0);
}
