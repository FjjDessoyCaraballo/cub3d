/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araveala <araveala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 11:54:10 by araveala          #+#    #+#             */
/*   Updated: 2024/10/11 13:23:34 by araveala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cubd.h"

//ray_data->dist_to_wall = sqrtf((ray_x - data->p_x) * (ray_x - data->p_x) 

//can i call this function anywhere else????
int outof_bounds_check(t_data *data)
{
    if (data->p_y - 0.25 > data->map_y - 1)
        return(FAILURE);
    if (data->p_x + 0.25 > data->map_x - 1)
        return(FAILURE);
    return(SUCCESS);
}

// might need to malloc array before all of this 
void    stack_ray_data(t_data *data) // i == array count
{
    int i;
    double starting_angle;
    double angle_increment;
    double  current_angle;
    double  player_angle;
    double  ray_angle;

    i = 0;
    //deg2rads degrees to radians. we are trying to work with olny 
    // radians lets see if that causes problems 
    starting_angle = -FOV / 2 * DEG2RAD;// 60 / 2 - 60 gives us minus 30 alternative = 0
    angle_increment = (FOV / RAY_MAX) * DEG2RAD;
    current_angle = 0;
    ray_angle = 0;
    player_angle = atan2(data->p_dir_y, data->p_dir_x); // ?? not sure
    //printf("/t/t fov = %f ray max = %f \n", FOV, RAY_MAX);
   // printf("/t/tStarting Angle (radians): %f\n", starting_angle);
   // printf("/t/tAngle Increment (radians): %f\n", angle_increment);
    //printf("/t/tPlayer Angle (radians): %f\n", player_angle);
    //sleep(4);
    //printf("whats an atan = %f\n", player_angle);
    //data->ray_dir_x = data->p_dir_x;
    //data->ray_dir_y = data->p_dir_y;
    while (i <= RAY_MAX) // 120 is ray count define in .h
    {
        current_angle = starting_angle + i * angle_increment;
        ray_angle = player_angle + current_angle;
        //data->ray_dir_x = cos(ray_angle);
        //data->ray_dir_y = sin(ray_angle);
        data->ray_dir_x = data->p_dir_x * cos(ray_angle) - data->p_dir_y * sin(ray_angle);
        data->ray_dir_y = data->p_dir_x * sin(ray_angle) + data->p_dir_y * cos(ray_angle);
        //data->ray_dir_x = data->p_dir_x;
        //data->ray_dir_y = data->p_dir_y;
        collect_ray(data, i);
        i++;
    }
    i = 0;
    /*int p = 0;
    while(p <= RAY_MAX)
    {
        if (p % 2 == 0)
            printf("checking the array is working num = %d = %f\n", p, data->ray_len[p]);
        p++;
    }*/
    data->im_ray = mlx_new_image(data->mlx, WIDTH, HEIGHT);
    while (i <= RAY_MAX)
    {
        draw_line(data, i);
        i++;
    }
}

void    collect_ray(t_data *data, int i)
{
    double         size;
	
	int start_x = (data->p_x * 64) + 32;
    int start_y = (data->p_y * 64) + 32;
    size = 0;
    int test_x;
    int test_y;

	test_x = start_x + (int)(data->ray_dir_x * size);
    test_y = start_y+ (int)(data->ray_dir_y * size);

//	test_x = start_x + (int)(data->p_dir_x * size);
//    test_y = start_y+ (int)(data->p_dir_y * size);
    while (data->p_x >= 0 && data->p_x < WIDTH && data->p_y >= 0 && data->p_y < HEIGHT)
    {
        if (outof_bounds_check(data) == FAILURE)
            return;
        if (test_x >= 0 && test_x < WIDTH  && test_y >= 0 && test_y < HEIGHT )
        {
            if (data->map[test_y / 64][test_x / 64] == '1')
            {
                data->ray_len[i] = size;
                //data->ray_size = size;
                return;                
            }
        }
    	test_x = start_x + (int)(data->ray_dir_x * size);
        test_y = start_y+ (int)(data->ray_dir_y * size);

		//test_x = start_x + (int)(data->p_dir_x * size);
        //test_y = start_y+ (int)(data->p_dir_y * size);
        size++;
    }
}
            //printf("t 1 = %d and t2 = %d\n", test_x, test_y);
            //printf("player sq = %c\n", data->map[(int)data->p_y][(int)data->p_x]);
            //printf("checkies p x = %f, p_y = %f\n", data->p_x, data->p_y - 0.25);
            //printf("lets look at athe char = %c\n", data->map[test_y / 64][test_x / 64]);

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
/*void draw_rays(t_data *data)
{
    int x;
    for (x = 0; x < WIDTH; x++)
    {
        t_ray ray;
        double camera_x = 2 * x / (double)WIDTH - 1; // Map x-coordinate to camera space
        ray.dir_x = data->p_dir_x + data->p_dir_y * camera_x;
        ray.dir_y = data->p_dir_y + data->p_dir_x * camera_x;

        // Determine the grid square where the player is located
        int map_x = (int)data->p_x;
        int map_y = (int)data->p_y;

        // Length of ray from current position to next x or y-side
        ray.delta_dist_x = fabs(1 / ray.dir_x);
        ray.delta_dist_y = fabs(1 / ray.dir_y);

        collect_ray(data, &ray, map_x, map_y);

        // Use ray.perp_wall_dist for rendering
        // For example, calculate the height of the wall to be drawn:
        int line_height = (int)(HEIGHT / ray.perp_wall_dist);

        // Calculate drawing coordinates
        int draw_start = -line_height / 2 + HEIGHT / 2;
        if (draw_start < 0) draw_start = 0;
        int draw_end = line_height / 2 + HEIGHT / 2;
        if (draw_end >= HEIGHT) draw_end = HEIGHT - 1;

        // Set color based on wall side
        uint32_t color = (ray.side == 1) ? 0xAAAAAA : 0xFFFFFF;

        // Draw the vertical line for the wall slice
        for (int y = draw_start; y < draw_end; y++)
            mlx_put_pixel(data->im_ray, x, y, color);
    }*/