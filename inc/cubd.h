/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cubd.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdessoy- <fdessoy-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 14:36:20 by fdessoy-          #+#    #+#             */
/*   Updated: 2024/10/07 10:26:01 by fdessoy-         ###   ########.fr       */
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
# define MAP "Error opening map\n"
# define NAME "Map name is invalid\n"
# define MALLOC "Malloc Failure\n"

# define SUCCESS 0
# define FAILURE 1

/*************************************************/
/* usage macros **********************************/
/*************************************************/
# define USAGE1 "Welcome to cub3d "
# define USAGE2 "and you already have committed your first mistake."
# define USAGE3 " Follow the usage below:\n"
# define USAGE4 "1. map must have the suffix '.cub';\n"
# define USAGE5 "2. In clt just execute the program and map;\n"
# define USAGE6 "3. Map must contain all elements (sprites with "
# define USAGE7 "cardinal orientation, proper walled map, and "
# define USAGE8 "RGB notated instructions [numerical value]);\n\n"
# define USAGE9 "This game has no exit for now, so use ESC to "
# define USAGE10 "finish the game (:\n\n"
# define USAGE11 "By: fdessoy- | araveala\n"

/*************************************************/
/* structs ***************************************/
/*************************************************/
typedef	struct s_data
{
	char	**map;
	bool	s_flag;
	bool	n_flag;
	bool	e_flag;
	bool	w_flag;
}		t_data;


/*************************************************/
/* functions *************************************/
/*************************************************/

/* in parsing.c */
int8_t	map_handling(t_data *data, char **argv);
// int8_t	check_name(char **argv);
// int8_t	open_map(t_data *data, char **argv);

/* in initializer.c */
void	initializer(t_data *data);

/* in error.c */
int		err_msg(char *obj, char *msg, int exit_code);

/* in usage.c */
void	usage(void);

#endif
