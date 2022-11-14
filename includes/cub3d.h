/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchampli <rchampli@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 03:58:15 by rchampli          #+#    #+#             */
/*   Updated: 2022/11/14 14:18:54 by jalamell         ###   ########lyon.fr   */
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

typedef struct s_vec
{
	double	x;
	double	y;
}	t_vec;

typedef struct s_mlx
{
	int		win_x;
	int		win_y;
	double	fov;
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img_ptr;
	char	*img;
	t_vec	*x_ray;
	double	*y_ray;
	int		bpp;
	int		size_line;
	int		endian;
}				t_mlx;

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
	t_mlx				mlx;
	struct s_map		map;
}	t_data;

//Parsing
void	parse(char *file);
void	parse_map(char *line, int fd);
int		parse_m(void);
void	parse_m2(int i, int j);
void	ft_parse(char *line, int n);
void	fill_map(char *line, int n);
int		parse_texture(char **temp);
int		parse_texture2(char **temp);
int		ft_parse_color(char **temp);
void	ft_map(void);
void	map_size(char *file);
void	map_size_process(char *line, int *n);

//Checker for parsing
void	check1(char *line);
void	check2(char c);
void	check3(int i, int j);

//Get next line
int		get_next_line(int fd, char **line);

//Free and exit
void	cleanup(void);

//2d vector
void	vec_norm(t_vec *vec);
t_vec	vec_rot(t_vec const *vec, double cosa, double sina);

#endif
