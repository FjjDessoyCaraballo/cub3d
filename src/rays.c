/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdessoy- <fdessoy-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 11:54:10 by araveala          #+#    #+#             */
/*   Updated: 2024/10/31 10:00:00 by fdessoy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cubd.h"

//ray_data->dist_to_wall = sqrtf((ray_x - data->x_ppos) * (ray_x - data->x_ppos) 
int	find_direction(double ray_x, double ray_y)//, double p_x , double p_y)
{
	if (fabs(ray_x) > (fabs(ray_y)))
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
}

static int	outof_bounds_check(t_data *data, double rpos_pixel_y, double rpos_pixel_x)
{

	if (rpos_pixel_y / T_SIZE > data->map_length || rpos_pixel_x / T_SIZE > data->map_width)
	{
		printf("ray bounds000 rpos x = %f also rpos y = %f\n", rpos_pixel_x / 64, rpos_pixel_y / 64);
		return (FAILURE);		
	}
	if (rpos_pixel_y < 0 || rpos_pixel_x / T_SIZE >= data->map_width)//WIDTH)
	{
		printf("ray bounds111 rpos x = %f also rpos y = %f and  WIDTH = %d\n", rpos_pixel_x, rpos_pixel_y, WIDTH);
		return (FAILURE);
	}
	if (rpos_pixel_y < 0 || rpos_pixel_x / T_SIZE >= HEIGHT)
	{
		printf("ray bounds2222 ray x = %f\n", rpos_pixel_x);
		return (FAILURE);
	}
	if (data->y_ppos - STEP > data->map_length)// - 1)
	{
		printf("ray bounds3333\n");	
		return (FAILURE);	
	}
	if (data->x_ppos + STEP > data->map_width)// - 1)
	{
		printf("ray bounds4444\n");	
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
// might need to malloc array before all of this
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
/*void	stack_ray_data(t_data *data, int i)
{
	//double	starting_angle;
	//double	angle_increment;
	double	current_angle;
	double	player_angle;
	double	ray_angle;

    current_angle = 0;
    ray_angle = 0;
	player_angle = atan2(data->p_dir_y, data->p_dir_x); //?
	clear_image(data);
	//ft_memset(data->im_ray, 0, (data->im_ray->height * data->im_ray->width) * 4);
	while (i < RAY_MAX)
	{
		current_angle = STARTING_ANGLE + i * ANGLE_INCREMENT;
		ray_angle = player_angle + current_angle;
		data->ray_dir_x = cos(ray_angle);
		data->ray_dir_y = sin(ray_angle);
		//data->ray_hit[i] = find_direction(data->ray_dir_x, data->ray_dir_y);
		collect_ray(data, i, 0.0, ray_angle);
		draw_wall(data, i, 0, 0);
		i++;
	}
	mlx_image_to_window(data->mlx, data->im_ray, 0, 0); //WIDTH, HEIGHT);
}*/

/*
We collect the length of a ray from player to wall and put it in an array
array not malloced seperatley, only malloced with data struct, ray_len[120]
~~cheat sheet~~
	1. translate players positon in 2d array to position in pixels
	2. set ray position to pixels
	3. convert ray position back to a comparible number to compare with 2darray for wall hit check
	4. i think #here# we will need to implement if ray hits wall render 3d or collect data
*/
void	stack_ray_data(t_data *data, int i)
{
	//double	starting_angle;
	//double	angle_increment;
	double	current_angle;
	double	player_angle;
	double	ray_angle;

    current_angle = 0;
    ray_angle = 0;
	player_angle = atan2(data->p_dir_y, data->p_dir_x); //?
	clear_image(data);
	//ft_memset(data->im_ray, 0, (data->im_ray->height * data->im_ray->width) * 4);
	while (i < RAY_MAX)
	{
		current_angle = STARTING_ANGLE + i * ANGLE_INCREMENT;
		ray_angle = player_angle + current_angle;
		// converting raydirs into unit vectors. ??? explain
		data->ray_dir_x = cos(ray_angle); //data->p_dir_x;//
		data->ray_dir_y = sin(ray_angle); //data->p_dir_y; ///
		
		//data->ray_dir_x = data->p_dir_x;//
		//data->ray_dir_y = data->p_dir_y; ///

		collect_ray(data, i, player_angle, ray_angle);
		draw_wall(data, i, 0, 0);
		i++;
	}
	mlx_image_to_window(data->mlx, data->im_ray, 0, 0); //WIDTH, HEIGHT);
}
// this is functional
void	collect_ray(t_data *data, int i, double ray_distance, double ray_angle)
{
	double	ppos_pixel_x;
	double	ppos_pixel_y;
	double	rpos_pixel_x;
	double	rpos_pixel_y;
	int grid_x, grid_y;
	(void)ray_angle;
	ppos_pixel_x = (data->x_ppos * T_SIZE);
	ppos_pixel_y = (data->y_ppos * T_SIZE);
	while (data->x_ppos >= 0 && data->x_ppos < WIDTH && data->y_ppos >= 0 && data->y_ppos < HEIGHT)
	{

		rpos_pixel_x = ppos_pixel_x + (data->ray_dir_x * ray_distance);
		rpos_pixel_y = ppos_pixel_y + (data->ray_dir_y * ray_distance);
		grid_x = (int)(rpos_pixel_x / T_SIZE);
        grid_y = (int)(rpos_pixel_y / T_SIZE);

		if (outof_bounds_check(data, rpos_pixel_y, rpos_pixel_x) == FAILURE)
			return ;
		if (data->map[grid_y][grid_x] == '1')
		{
			//plotLine(data , i, ppos_pixel_x, ppos_pixel_y, rpos_pixel_x, rpos_pixel_y);
			data->ray_len[i] = sqrt(pow(rpos_pixel_x - ppos_pixel_x, 2) + pow(rpos_pixel_y - ppos_pixel_y, 2));
			//if (i > 0)
			//	printf("the i = %d difference between i prevand now i = %f\n",i, data->ray_len[i - 1] - data->ray_len[i]);
			//data->ray_len[i] = ray_distance + cos(FOV / 2 - ray_angle);
			data->ray_hit[i] = find_direction(data->ray_dir_x, data->ray_dir_y);
			return ;
		}
		ray_distance += 0.1;
	}
}


/*************************************************/
/* questionable functions ************************/
/*************************************************/

// void collect_ray(t_data *data, int i, double ray_distance, double ray_angle)
// {
//     double ppos_pixel_x = data->x_ppos;
//     double ppos_pixel_y = data->y_ppos;
// 	(void)ray_distance;
//     // Initialize ray direction
// 	(void)ray_angle;
//     // Initial intersections based on ray direction
//     double next_hor_intersect = get_horizontal(data, ppos_pixel_y);
//     double next_ver_intersect = get_vertical(data, ppos_pixel_x);

//     // Calculate initial steps
//     double next_hor_x = ppos_pixel_x + (next_hor_intersect - ppos_pixel_y) * (data->ray_dir_x / data->ray_dir_y);
//     double next_ver_y = ppos_pixel_y + (next_ver_intersect - ppos_pixel_x) * (data->ray_dir_y / data->ray_dir_x);

//     // Determine step sizes
//     double step_x = (data->ray_dir_x > 0) ? 1 : -1;
//     double step_y = (data->ray_dir_y > 0) ? 1 : -1;

//     // Main loop to advance the ray
//     while (1)
// 	{
//         if (fabs(next_hor_x - ppos_pixel_x) < fabs(next_ver_y - ppos_pixel_y))
// 		{
//             ppos_pixel_x = next_hor_x;
//             ppos_pixel_y = next_hor_intersect;
//             next_hor_intersect += step_y;
// 			if (outof_bounds_check(data, ppos_pixel_y, ppos_pixel_x) == FAILURE)
// 				return ;
//             if (data->map[(int)ppos_pixel_y][(int)ppos_pixel_x] == '1')
// 			{
//                 data->ray_len[i] = sqrt(pow(ppos_pixel_x - (data->x_ppos * 64), 2) + pow(ppos_pixel_y - (data->y_ppos * 64), 2));
// 				//pow(ppos_pixel_x - (data->x_ppos), 2) + pow(ppos_pixel_y - (data->y_ppos), 2);
//                 data->ray_hit[i] = find_direction(data->ray_dir_x, data->ray_dir_y);
//                 return;
//             }
//             next_hor_x += step_x;
//         } else
// 		{
//             ppos_pixel_x = next_ver_intersect;
//             ppos_pixel_y = next_ver_y;
//             next_ver_intersect += step_x;
// 			if (outof_bounds_check(data, ppos_pixel_y, ppos_pixel_x) == FAILURE)
// 				return ;
//             if (data->map[(int)(ppos_pixel_y)][(int)(ppos_pixel_x)] == '1') {
//                 data->ray_len[i] = sqrt(pow(ppos_pixel_x - (data->x_ppos * 64), 2) + pow(ppos_pixel_y - (data->y_ppos * 64), 2));
// 				//pow(ppos_pixel_x - (data->x_ppos), 2) + pow(ppos_pixel_y - (data->y_ppos), 2);
//                 data->ray_hit[i] = find_direction(data->ray_dir_x, data->ray_dir_y);
//                 return;
//             }
//             next_ver_y += step_y;
//         }
//     }
// }


// void	collect_ray(t_data *data, int i, double ray_distance, double ray_angle)
// {
// 	double	ppos_pixel_x;
// 	double	ppos_pixel_y;
// 	double	rpos_pixel_x;
// 	double	rpos_pixel_y;
// 	int grid_x, grid_y;
// 	double step_x;
// 	double step_y;

// 	if (data->ray_dir_x < 0)
// 	{
//         step_x = (double)-T_SIZE;
//     //    side_dist_x = (ppos_pixel_x - map_x) * delta_dist_x;
//     }
// 	else
// 	{
//         step_x = (double)T_SIZE;
//      //   side_dist_x = (map_x + T_SIZE - ppos_pixel_x) * delta_dist_x;
//     }
//     if (data->ray_dir_y < 0)
// 	{
//         step_y = (double)-T_SIZE;
//     //    side_dist_y = (ppos_pixel_y - map_y) * delta_dist_y;
//     } else {
//         step_y = (double)T_SIZE;
//     //    side_dist_y = (map_y * T_SIZE - ppos_pixel_y) * delta_dist_y;
//     }

			
// 	ppos_pixel_x = (data->x_ppos * T_SIZE);
// 	ppos_pixel_y = (data->y_ppos * T_SIZE);

// 	double distance_to_next_horizontal = get_first_horizontal(data, ppos_pixel_y);
// 	double distance_to_next_vertical = get_first_vertical(data, ppos_pixel_x);
// 	if (data->map[(int)distance_to_next_horizontal / 64][(int)distance_to_next_vertical / 64] == '1')
// 	{
// 		if (distance_to_next_horizontal > distance_to_next_vertical)
// 			data->ray_len[i] = distance_to_next_horizontal + cos(FOV / 2 - ray_angle);
// 		else 
// 			data->ray_len[i] = distance_to_next_vertical + cos(FOV / 2 - ray_angle);
// 		data->ray_hit[i] = find_direction(data->ray_dir_x, data->ray_dir_y);
// 		printf("ret on first thingy\n");
// 		return ;

// 	}	
// 	rpos_pixel_x = distance_to_next_vertical;
// 	rpos_pixel_y = distance_to_next_horizontal;
// 	if (distance_to_next_horizontal > distance_to_next_vertical)
// 		ray_distance =  distance_to_next_horizontal;// + cos(FOV / 2 - ray_angle);
// 	else 
// 		ray_distance = distance_to_next_
// 		if (outof_bounds_check(data, rpos_pixel_y, rpos_pixel_x) == FAILURE)
// 			return ;
// 		if (data->map[grid_y][grid_x] == '1')
// 		{
// 			rpos_pixel_y = ppos_pixel_y + (int)(data->ray_dir_y * ray_distance);	
// 			grid_x = (int)(rpos_pixel_x) / T_SIZE;
//     	    grid_y = (int)(rpos_pixel_y) / T_SIZE;
// 			if (outof_bounds_check(data, rpos_pixel_y, rpos_pixel_x) == FAILURE)
// 				return ;
// 			if (data->map[grid_y][grid_x] == '1')
// 			{
// 				data->ray_len[i] = ray_distance + cos(FOV / 2 - ray_angle);
// 				//data->ray_len[i] = rpos_pixel_y * cos(FOV / 2 - ray_angle);
// 				data->ray_hit[i] = find_direction(data->ray_dir_x, data->ray_dir_y);
// 				return ;
// 			}

// 		}
// 		else 
// 		{
// 			rpos_pixel_x = ppos_pixel_x + (int)(data->ray_dir_x * ray_distance);		
// 			grid_x = (int)(rpos_pixel_x) / T_SIZE;
//     	    grid_y = (int)(rpos_pixel_y) / T_SIZE;
// 			if (outof_bounds_check(data, rpos_pixel_y, rpos_pixel_x) == FAILURE)
// 				return ;
// 			if (data->map[grid_y][grid_x] == '1')
// 			{
// 				data->ray_len[i] = ray_distance + cos(FOV / 2 - ray_angle);
// 				//data->ray_len[i] = rpos_pixel_x * cos(FOV / 2 - ray_angle);
// 				data->ray_hit[i] = find_direction(data->ray_dir_x, data->ray_dir_y);
// 				return ;
// 			}
// 		}
// 		ray_distance += 1;
// 	}
// }

// int get_first_horizontal(t_data *data, double ppos_pixel_y)
// {
// 	double ret;

// 	ret = 0;
// 	if (data->ray_dir_y > 0)
// 		ret = 64 - fmod(ppos_pixel_y, 64);
// 	else
// 		ret = fmod(ppos_pixel_y, 64);
// 	return (ret);	
// }

// int get_first_vertical(t_data *data, double ppos_pixel_x)
// {
// 	double ret;

// 	ret = 0;
// 	if (data->ray_dir_x > 0)
// 		ret = 64 - fmod(ppos_pixel_x, 64);
// 	else
// 		ret = fmod(ppos_pixel_x, 64);

// 	return (ret);
// }

// int get_first_horizontal(t_data *data)
// {
	
// }

// int get_first_horizontal(t_data *data)
// {
	
// }

// int get_horizontal(t_data *data, double ppos_pixel_y)
// {
// 	double ret;

// 	ret = 0;
// 	if (data->ray_dir_y > 0)
// 	{
// 		ret = (floor(ppos_pixel_y));
// 	}
// 	else
// 	{
// 		ret = (ceil(ppos_pixel_y));
// 	}
// 	printf("next ho = %f\n", ret);
// 	return (ret);
// }

// int get_vertical(t_data *data, double ppos_pixel_x)
// {
// 	double ret;

// 	ret = 0;
// 	if (data->ray_dir_x > 0)
// 	{
// 		ret = (floor(ppos_pixel_x));
// 	}
// 	else
// 	{
// 		ret = (ceil(ppos_pixel_x));
// 	}
// 	printf("next ve = %f\n", ret);
// 	return (ret);
// }

// void plotLine(t_data *data, int i, int x0, int y0, int x1, int y1)
// {
//     int dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
//     int dy = -abs(y1 - y0), sy = y0 < y1 ? 1 : -1; 
//     int err = dx + dy, e2; 

//     while (1) {
//         // Add your collision detection logic here:
//         if (data->map[y0 / T_SIZE][x0 / T_SIZE] == '1') {
//             // Calculate the actual distance
//             double distance = sqrt(pow(x0 - (data->x_ppos * T_SIZE), 2) + pow(y0 - (data->y_ppos * T_SIZE), 2));
//             data->ray_len[i] = distance;
// 			printf("our distance = %f\n", distance);
//             data->ray_hit[i] = find_direction(data->ray_dir_x, data->ray_dir_y);
//             return;
//         }
        
//         if (x0 == x1 && y0 == y1) break;
//         e2 = 2 * err;
//         if (e2 >= dy) { err += dy; x0 += sx; }
//         if (e2 <= dx) { err += dx; y0 += sy; }
// 	}
// }

////lets fuck about and find out !


// void collect_ray(t_data *data, int i, double ray_distance, double ray_angle)
// {
//     double ppos_pixel_x = (data->x_ppos) * 64;
//     double ppos_pixel_y = (data->y_ppos) * 64; //?

// 	double player_angle = ray_distance; 
// 	//(void)player_angle;
// 	(void)ray_angle;

// 	double delta_dist_x = fabs(T_SIZE / data->ray_dir_x);
//     double delta_dist_y = fabs(T_SIZE / data->ray_dir_y);
//     double side_dist_x, side_dist_y;
//     double step_x, step_y;
//     int map_x = (int)(data->x_ppos);
//     int map_y = (int)(data->y_ppos);

//     if (data->ray_dir_x < 0)
// 	{
//         step_x = -1;
//         side_dist_x = (ppos_pixel_x - map_x * T_SIZE) / delta_dist_x;
//     }
// 	else
// 	{
//         step_x = 1;
//         side_dist_x = ((map_x + 1) * T_SIZE  + T_SIZE - ppos_pixel_x) / delta_dist_x;
//     }
//     if (data->ray_dir_y < 0)
// 	{
//         step_y = -1;
//         side_dist_y = (ppos_pixel_y - map_y * T_SIZE) / delta_dist_y;
//     } else {
//         step_y = 1;
//         side_dist_y = ((map_y + 1)* T_SIZE + T_SIZE - ppos_pixel_y) / delta_dist_y;
//     }
//     int hit = 0;
//     int side = 0;
//     while (hit == 0)
// 	{
//         if (side_dist_x < side_dist_y) {
//             side_dist_x += delta_dist_x / T_SIZE;
//             map_x += step_x;
//             side = 0;
//         } else {
//             side_dist_y += delta_dist_y / T_SIZE;
//             map_y += step_y;
//             side = 1;
//         }
// 		// Debug prints to check values
//        // printf("map_x: %d, map_y: %d, side_dist_x: %f, side_dist_y: %f\n", map_x, map_y, side_dist_x, side_dist_y);
//         if (outof_bounds_check(data, map_y, map_x) == FAILURE)
//             return;
//         if (data->map[(int)map_y][(int)map_x] == '1')
// 			hit = 1;
//     }
//     double perp_wall_dist;
//     if (side == 0)
//         perp_wall_dist = ((map_x * T_SIZE - ppos_pixel_x) + (1 - step_x) * T_SIZE / 2) / data->ray_dir_x;
//     else
//        perp_wall_dist = ((map_y * T_SIZE - ppos_pixel_y) + (1 - step_y) * T_SIZE / 2) / data->ray_dir_y;
//     data->ray_len[i] = perp_wall_dist * cos(ray_angle - player_angle);
//     data->ray_hit[i] = find_direction(data->ray_dir_x, data->ray_dir_y);
// }

////original down here 

// void	collect_ray(t_data *data, int i, double ray_distance, double ray_angle)
// {
// 	double	ppos_pixel_x;
// 	double	ppos_pixel_y;
// 	double	rpos_pixel_x;
// 	double	rpos_pixel_y;
// 	int grid_x, grid_y;
// 	ppos_pixel_x = (int)data->x_ppos;// * T_SIZE) + T_SIZE / 2;
// 	ppos_pixel_y = (int)data->y_ppos;// * T_SIZE) + T_SIZE / 2; /// ofsetting for starting position + / t_Size
// 	while (data->x_ppos >= 0 && data->x_ppos < data->map_width && data->y_ppos >= 0 && data->y_ppos < data->map_length)
// 	{
// 		rpos_pixel_x = ppos_pixel_x + (int)(data->ray_dir_x * ray_distance);
// 		rpos_pixel_y = ppos_pixel_y + (int)(data->ray_dir_y * ray_distance);
// 		grid_x = (int)(rpos_pixel_x);// / T_SIZE);
//         grid_y = (int)(rpos_pixel_y);// / T_SIZE);
// 		if (outof_bounds_check(data, rpos_pixel_y, rpos_pixel_x) == FAILURE)
// 			return ;
// 		if (data->map[grid_y][grid_x] == '1')
// 		{
// 			data->ray_len[i] = ray_distance + cos(FOV / 2 - ray_angle);
// 			data->ray_hit[i] = find_direction(data->ray_dir_x, data->ray_dir_y);
// 			return ;
// 		}
// 		ray_distance += 0.5;
// 	}
// }


// void	collect_ray(t_data *data, int i, double ray_distance, double ray_angle)
// {
// 	double	ppos_pixel_x;
// 	double	ppos_pixel_y;
// 	double	rpos_pixel_x;
// 	double	rpos_pixel_y;
// 	int grid_x, grid_y;
// 	(void)ray_angle;
	
// 	// int step_x;
// 	// int step_y;
// 	// if (data->ray_dir_x < 0)
// 	// {
//     //     step_x = -1;
//     //  //   side_dist_x = (ppos_pixel_x - map_x) * delta_dist_x;
//     // }
// 	// else
// 	// {
//     //     step_x = 1;
//     //    // side_dist_x = (map_x + T_SIZE - ppos_pixel_x) * delta_dist_x;
//     // }
//     // if (data->ray_dir_y < 0)
// 	// {
//     //     step_y = -1;
//     //     //side_dist_y = (ppos_pixel_y - map_y) * delta_dist_y;
//     // } else {
//     //     step_y = 1;
//     //     //side_dist_y = (map_y * T_SIZE - ppos_pixel_y) * delta_dist_y;
//     // }

	
// 	ppos_pixel_x = (data->x_ppos * T_SIZE);
// 	ppos_pixel_y = (data->y_ppos * T_SIZE);
// 	grid_x = data->x_ppos;
// 	grid_y = data->y_ppos;
// 	while (data->x_ppos >= 0 && data->x_ppos < WIDTH && data->y_ppos >= 0 && data->y_ppos < HEIGHT)
// 	{
// 		grid_x = data->x_ppos + (int)(data->ray_dir_x * ray_distance);
// 		grid_y = data->y_ppos+ (int)(data->ray_dir_y * ray_distance);
// 		if (outof_bounds_check(data, grid_y, grid_x) == FAILURE)
// 			return ;
// 		if (data->map[grid_y][grid_x] == '1')
// 		{
// 			if (grid_y > grid_x)
// 			{
				
// 			}
// 			data->ray_len[i] = sqrt(pow(rpos_pixel_x - ppos_pixel_x, 2) + pow(rpos_pixel_y - ppos_pixel_y, 2));
// 			data->ray_hit[i] = find_direction(data->ray_dir_x, data->ray_dir_y);
// 		}
		
// 		rpos_pixel_x = ppos_pixel_x + (data->ray_dir_x * ray_distance);
// 		rpos_pixel_y = ppos_pixel_y + (data->ray_dir_y * ray_distance);
// 		grid_x = (int)(rpos_pixel_x / T_SIZE);
//         grid_y = (int)(rpos_pixel_y / T_SIZE);
		
	
// 		{
// 			//plotLine(data , i, ppos_pixel_x, ppos_pixel_y, rpos_pixel_x, rpos_pixel_y);

// 			//if (i > 0)
// 			//	printf("the i = %d difference between i prevand now i = %f\n",i, data->ray_len[i - 1] - data->ray_len[i]);
// 			//data->ray_len[i] = ray_distance + cos(FOV / 2 - ray_angle);
		
// 			return ;
// 		}
// 		ray_distance += 0.1;
// 	}
// }