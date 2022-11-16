/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchampli <rchampli@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 03:58:15 by rchampli          #+#    #+#             */
/*   Updated: 2022/11/15 13:54:31 by rchampli         ###   ########.fr       */
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

typedef struct 		s_vec
{
	double			x;
	double			y;
}					t_vec;

typedef struct 		s_img
{
	void			*img;
	char			*addr;
	int				bpp;
	int				length;
	int				endian;
}					t_img;

typedef struct s_win
{
	void	*mlx;
	void	*win;
	int		win_x;
	int		win_y;
	double	fov;
	int 	height;
	int 	width;
	t_vec	*x_ray;
	double	*y_ray;
	t_img	img;
	t_img	west;
	t_img	east;
	t_img	north;
	t_img	south;
}				t_win;

struct	s_player
{
	double			x;
	double			y;
	double			rot;
	double			heigth;
	double			dir_x;
	double			dir_y;
	double			plane_x;
	double			plane_y;
	double			dir;
	char			dir_symbol;
	int				count;
	int				move;
}					player;

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

typedef struct s_data
{
	struct s_player		player;
	t_win				win;
	struct s_map		map;
}	t_data;

//Parsing
void	parse(char *file, t_data *data);
void	parse_map(char *line, int fd, t_data *data);
int		parse_m(t_data *data);
void	parse_m2(int i, int j, t_data *data);
void	ft_parse(char *line, int n, t_data *data);
void	fill_map(char *line, int n, t_data *data);
int		parse_texture(char **temp, t_data *data);
int		parse_texture2(char **temp, t_data *data);
int		ft_parse_color(char **temp);
void	ft_map(t_data *data);
void	map_size(char *file, t_data *data);
void	map_size_process(char *line, int *n, t_data *data);

//Checker for parsing
void	check1(char *line);
void	check2(char c);
void	check3(int i, int j, t_data *data);

//Get next line
int		get_next_line(int fd, char **line);

//Free and exit
void	cleanup(void);

//2d vector
void	vec_norm(t_vec *vec);
t_vec	vec_rot(t_vec const *vec, double cosa, double sina);

#endif
