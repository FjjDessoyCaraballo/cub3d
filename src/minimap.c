/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araveala <araveala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 08:32:58 by araveala          #+#    #+#             */
/*   Updated: 2024/10/14 13:54:13 by araveala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cubd.h"

/*int adjust_tilesize(t_data *data)
{
	size_t	x_comp;
	size_t	y_comp;
	if (data->map_width * data->t_size > WIDTH || data->map_length * data->t_size > HEIGHT)
	{
		x_comp = data->map_width * data->t_size;
		y_comp = data->map_length * data->t_size;
		if (x_comp > y_comp && x_comp > WIDTH)
		{
			while (data->map_width * data->t_size > WIDTH)
			{
				data->t_size -= 1;
				if (data->t_size < 21)
					printf("error in tile size\n");
			}
		}
		else if (data->map_length * data->t_size > HEIGHT)
		{
			while (data->map_length * data->t_size > HEIGHT)
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
	int start_x = (data->x_ppos * 64) + 32 - half_size;
	int start_y = (data->y_ppos * 64) + 32 - half_size;

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
void	draw_first_line(t_data *data)
{
	uint32_t	red;
	int			i;
	int			start_x;
	int			start_y;
	int			draw_x;
	int			draw_y;

	red = 0xFF00FFF0;
	i = 0;
	start_x = (data->x_ppos * 64) + 32;
	start_y = (data->y_ppos * 64) + 32;
	data->im_ray = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	// if north draw up so -y
	while (i <= 40)
	{
		// this part would draw a line up to down 
		draw_x = start_x + (int)(data->p_dir_x * i);
		draw_y = start_y + (int)(data->p_dir_y * i);
		if (draw_x >= 0 && draw_x < WIDTH && draw_y >= 0 && draw_y < HEIGHT)
			mlx_put_pixel(data->im_ray, draw_x, draw_y, red);
		i++;
	}
}

void	draw_line(t_data *data, int i)
{
	uint32_t	red;
	int			len;
	int			start_x;
	int			start_y;
	int			draw_x;
	int			draw_y;

	len = 0;
	red = 0xFF00FFF0;
	start_x = (data->x_ppos * 64) + 32;
	start_y = (data->y_ppos * 64) + 32;
	// if north draw up so -y
	while (len <= data->ray_len[i])
	{
		draw_x = start_x + (int)(data->ray_dir_x * len);
		draw_y = start_y + (int)(data->ray_dir_y * len);
		if (draw_x >= 0 && draw_x < WIDTH && draw_y >= 0 && draw_y < HEIGHT)
			mlx_put_pixel(data->im_ray, draw_x, draw_y, red);
		len++;
	}
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

// lets draw a circle
void	draw_player(t_data *data)
{
	uint32_t	red;
	int			radius;
	int			center_x;
	int			center_y;
	int			y;
	int			x;
	int			draw_x;
	int			draw_y;

	red = 0xFF0000FF;
	radius = 20 / 2;
	data->im_mini_player = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	center_x = (int)(data->x_ppos * 64) + 32;
	center_y = (int)(data->y_ppos * 64) + 32;
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
	while (y < data->map_length)
	{
		while (x < data->map_width)
		{
			if (data->map[y][x] == '1' && x < data->map_width)
			{
				// starting should be dependant on if n/s/w/e
				mlx_image_to_window(data->mlx, data->im_mini_wall, x * T_SIZE, y * T_SIZE);
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
	while (y < data->map_length)
	{
		printf("what char = %c\n", data->map[y][x]);
		while (x < data->map_width)
		{
			if (data->map[y][x] == '0' || data->map[y][x] == 'N') // char for player
				mlx_image_to_window(data->mlx, data->im_mini_floor, x * T_SIZE, y * T_SIZE);
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
	while (y < data->map_length)
	{
		while (x < data->map_width)
		{
			if (data->map[y][x] == 'N' && x < data->map_width) // N ret char
			{
				//data->x_ppos = (double)x; //remove once parsing has it
				//data->y_ppos = (double)y;
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

int	init_mini_imgs(t_data *data)
{
	data->tx_mini_floor = mlx_load_png("./minimap_textures/floor.png");
	data->tx_mini_wall = mlx_load_png("./minimap_textures/grass.png");
	//data->tx_mini_player = mlx_load_png("./minimap_textures/player.png");
	if (data->tx_mini_floor == NULL || data->tx_mini_wall == NULL)
		return (err_msg(NULL, TEXTURE_FAIL, FAILURE));
	data->im_mini_floor = mlx_texture_to_image(data->mlx, data->tx_mini_floor);
	data->im_mini_wall = mlx_texture_to_image(data->mlx, data->tx_mini_wall);
	if (data->im_mini_floor == NULL || data->im_mini_wall == NULL)
		return (err_msg(NULL, IMAGE_FAIL, FAILURE));
	mlx_resize_image(data->im_mini_floor, T_SIZE, T_SIZE);
	mlx_resize_image(data->im_mini_wall, T_SIZE, T_SIZE);
	return (0);
}
//mlx_resize_image(data->im_mini_player, data->t_size, data->t_size); //T_SIZE, T_SIZE);

//adjust_tilesize(data); maybe
int	initlize_minimap(t_data *data)
{
	init_mini_imgs(data);
	init_mini_floor(data);
	init_mini_walls(data);
	init_mini_player(data);
	return (0);
}
