/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araveala <araveala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 11:54:10 by araveala          #+#    #+#             */
/*   Updated: 2024/10/11 18:02:49 by araveala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cubd.h"

//ray_data->dist_to_wall = sqrtf((ray_x - data->p_x) * (ray_x - data->p_x) 

int	outof_bounds_check(t_data *data, double rpos_pixel_y, double rpos_pixel_x)
{
	if (rpos_pixel_y < 0 || rpos_pixel_x >= WIDTH)
		return (FAILURE);
	if (rpos_pixel_y < 0 || rpos_pixel_x >= HEIGHT)
		return (FAILURE);
	if (data->p_y - 0.25 > data->map_y - 1)
		return (FAILURE);
	if (data->p_x + 0.25 > data->map_x - 1)
		return (FAILURE);
	return (SUCCESS);
}

// might need to malloc array before all of this
/* collect and draw a ray based on math~~angles, pie and radians
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
	data->im_ray = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	while (i <= RAY_MAX)
	{
		current_angle = starting_angle + i * angle_increment;
		ray_angle = player_angle + current_angle;
		data->ray_dir_x = cos(ray_angle);
		data->ray_dir_y = sin(ray_angle);
		collect_ray(data, i, 0.0);
		draw_line(data, i);
		i++;
	}
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
void	collect_ray(t_data *data, int i, double ray_distance)
{
	int	ppos_pixel_x;
	int	ppos_pixel_y;
	int	rpos_pixel_x;
	int	rpos_pixel_y;

	ppos_pixel_x = (data->p_x * 64) + 32;
	ppos_pixel_y = (data->p_y * 64) + 32;
	while (data->p_x >= 0 && data->p_x < WIDTH && data->p_y >= 0 && data->p_y < HEIGHT)
	{
		rpos_pixel_x = ppos_pixel_x + (int)(data->ray_dir_x * ray_distance);
		rpos_pixel_y = ppos_pixel_y + (int)(data->ray_dir_y * ray_distance);
		if (outof_bounds_check(data, rpos_pixel_y, rpos_pixel_x) == FAILURE)
			return ;
		if (data->map[rpos_pixel_y / 64][rpos_pixel_x / 64] == '1')
		{
			//#here#
			data->ray_len[i] = ray_distance;
			return ;
		}
		ray_distance++;
	}
}

// the old collect ray, we could use to draw jus center ray for minimap direction indicator
/*void    collect_ray(t_data *data)
{
	int			x;
	int i;
    int size;
	
	i = 0;
	x = 0;
	int start_x = (data->p_x * 64) + 32;
    int start_y = (data->p_y * 64) + 32;
    size = 0;
    int test_x;
    int test_y;

	test_x = start_x + (int)(data->p_dir_x * size);
    test_y = start_y+ (int)(data->p_dir_y * size);
    while (data->p_x >= 0 && data->p_x < WIDTH && data->p_y >= 0 && data->p_y < HEIGHT)
    {
        if (outof_bounds_check(data) == FAILURE)
            return;
        if (test_x >= 0 && test_x < WIDTH  && test_y >= 0 && test_y < HEIGHT )
        {
            //printf("t 1 = %d and t2 = %d\n", test_x, test_y);
            //printf("player sq = %c\n", data->map[(int)data->p_y][(int)data->p_x]);
            //printf("checkies p x = %f, p_y = %f\n", data->p_x, data->p_y - 0.25);
            //printf("lets look at athe char = %c\n", data->map[test_y / 64][test_x / 64]);
            if (data->map[test_y / 64][test_x / 64] == '1')
            {
                data->ray_size = size; // data->ray_len[];
                return;                
            }
        }
		test_x = start_x + (int)(data->p_dir_x * size);
        test_y = start_y+ (int)(data->p_dir_y * size);
        size++;
    }
}
*/
////cheat sheet for 3d.
/*#define NUM_RAYS 120
#define FOV 60.0
#define SCREEN_HEIGHT 480
#define SCREEN_WIDTH 640
#define DEG2RAD (M_PI / 180.0)

void render_3d_scene(t_data *data) {
    double angle_step = FOV / NUM_RAYS;
    double start_angle = -FOV / 2.0;

    for (int i = 0; i < NUM_RAYS; i++) {
        double current_angle = start_angle + i * angle_step;
        double ray_dir_x = data->p_dir_x * cos(current_angle * DEG2RAD) - data->p_dir_y * sin(current_angle * DEG2RAD);
        double ray_dir_y = data->p_dir_x * sin(current_angle * DEG2RAD) + data->p_dir_y * cos(current_angle * DEG2RAD);

        double ray_length = shoot_ray_and_get_length(data, ray_dir_x, ray_dir_y);
        double wall_height = SCREEN_HEIGHT / ray_length;

        double ceiling = (SCREEN_HEIGHT / 2.0) - (wall_height / 2.0);
        double floor = (SCREEN_HEIGHT / 2.0) + (wall_height / 2.0);

        draw_wall_slice(data, i, ceiling, floor, ray_length);
    }
}

void draw_wall_slice(t_data *data, int x, double ceiling, double floor, double ray_length) {
    for (int y = 0; y < SCREEN_HEIGHT; y++) {
        if (y < ceiling) {
            // Draw ceiling
            mlx_put_pixel(data->im_screen, x, y, ceiling_color);
        } else if (y > floor) {
            // Draw floor
            mlx_put_pixel(data->im_screen, x, y, floor_color);
        } else {
            // Draw wall
            int texture_y = (y - ceiling) * TEXTURE_HEIGHT / (floor - ceiling);
            mlx_put_pixel(data->im_screen, x, y, get_wall_texture_color(ray_length, texture_y));
        }
    }
}

double shoot_ray_and_get_length(t_data *data, double ray_dir_x, double ray_dir_y) {
    double length = 0;
    // Your raycasting logic to determine the length
    return length;
}

uint32_t get_wall_texture_color(double ray_length, int texture_y) {
    // Determine the color from the texture based on ray length and y position on the texture
    return wall_texture[texture_y]; // Example return, should be based on actual texture lookup
}
*/
