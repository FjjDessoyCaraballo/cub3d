/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cubd.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdessoy- <fdessoy-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 14:36:20 by fdessoy-          #+#    #+#             */
/*   Updated: 2024/10/11 11:09:00 by fdessoy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBD_H
# define CUBD_H

/*************************************************/
/* User defined headers **************************/
/*************************************************/
# include "libft.h"

/*************************************************/
/* external libraries ****************************/
/*************************************************/
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <sys/time.h>
# include <stdlib.h>
# include <math.h>

/*************************************************/
/* questionable libraries ************************/
/*************************************************/
# include <stdbool.h>
# include <limits.h>
# include <stdint.h>

/*************************************************/
/* macros ****************************************/
/*************************************************/
# define MAP "Error\nCan't open map. File may be corrupted.\n"
# define NAME "Error\nMap name is invalid\n"
# define MALLOC "Error\nMalloc Failure\n"
# define FILE "Error\nElements may be incorrect. Check map conditions.\n"
# define SPRITE "Error\nCould not find/load sprites."
# define RGB1 "Error\nRGB (ceiling) values: value must be between 0-255\n"
# define RGB2 "Error\nRGB (floor) values: value must be between 0-255\n"
# define PLAYER "Error\nMust have one player character(N, W, S, or E)\n"
# define BRK_MAP "Error\nMap is broken ):\n"

# define SUCCESS 0
# define FAILURE 1
# define SUFFER 65

/*************************************************/
/* usage macros **********************************/
/*************************************************/
# define USAGE1 "\nWelcome to cub3d "
# define USAGE2 "and you already have committed a mistake."
# define USAGE3 " Follow the usage below:\n"
# define USAGE4 "1. map must have the suffix '.cub';\n"
# define USAGE5 "2. In clt just execute the program and map;\n"
# define USAGE6 "3. Map must contain all elements (sprites with \n"
# define USAGE7 "cardinal orientation, proper walled map, and \n"
# define USAGE8 "RGB notated instructions [numerical value]);\n\n"
# define USAGE9 "This game has no exit for now, so use ESC to "
# define USAGE10 "finish the game (:\n\n"
# define USAGE11 "By: fdessoy- && araveala\n"

/*************************************************/
/* structs ***************************************/
/*************************************************/
typedef	struct s_data
{
	int		map_start;
	int		map_end;
	char	**map;
	bool	broken_map;
	size_t	map_width;
	size_t	map_length;
	char	**file;
	int8_t	file_len;
	char	*floor_info;
	char	*ceiling_info;
	size_t	c_red;
	size_t	c_green;
	size_t	c_blue;
	size_t	f_red;
	size_t	f_green;
	size_t	f_blue;
	char	*n_sprite;
	char	*s_sprite;
	char	*e_sprite;
	char	*w_sprite;
	bool	s_player;
	bool	n_player;
	bool	e_player;
	bool	w_player;
	double	y_ppos;
	double	x_ppos;
}		t_data;


/*************************************************/
/* functions *************************************/
/*************************************************/

/* in parsing1.c */
int8_t	map_handling(t_data *data, char *argv);

/* in parsing2.c */
int8_t	extract(t_data *data);

/* in parsing3.c */
int8_t	search_sprites(t_data *data);

/* in parsing_utils.c */
char	*sprite_path(char *str);
int8_t	rgb_parse(t_data *data, char *str, int flag);

/* in parsing_utils2.c */
int8_t	rgb_assignment(t_data *data, char **array, int flag);
int8_t	allocate_mapmem(t_data *data);
int8_t	is_map(char *str);
void	remove_nl(char **map);

/* in parsing_utils3.c */
int8_t	only_nl(char *str);
int8_t	player_exists(t_data *data, char **map);
int8_t	check_original_length(t_data *data);

/* in error.c */
int		err_msg(char *obj, char *msg, int exit_code);

/* in usage.c */
void	usage(void);

/* in free.c */
void	free_data(t_data *data);

/* printer REMOVE LATER */
void	printer(t_data *data);

#endif
