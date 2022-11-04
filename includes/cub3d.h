/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchampli <rchampli@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 03:58:15 by rchampli          #+#    #+#             */
/*   Updated: 2022/11/04 10:20:43 by rchampli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <string.h>
# include <sys/types.h>
# include <sys/stat.h>
# include "../mlx_linux/mlx.h"
# include "../libft/libft.h"

# define HEIGHT 64
# define WIDTH 64

typedef struct s_win
{
	void	*mlx;
	void	*win;
	int		width;
	int		height;
}				t_win;

struct s_path
{
	char	*north;
	char	*south;
	char	*west;
	char	*east;
	int 	no;
	int		so;
	int		we;
	int		ea;
}				t_path;

struct				s_map
{
	char			**map;
	char			*fd_no;
	char			*fd_so;
	char			*fd_we;
	char			*fd_ea;
	int				no;
	int				so;
	int				we;
	int				ea;
	int				height;
	int				width;
	int				max_width;
	int				count;
	int				ceiling;
	int				floor;
	int				gnl;
	int				f;
	int				c;
	int				n;
	int				flag;
}					map;



int		get_next_line(int fd, char **line);
int		parse_texture2(char **temp);
void	cleanup(void);

#endif