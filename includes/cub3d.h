/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchampli <rchampli@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 03:58:15 by rchampli          #+#    #+#             */
/*   Updated: 2022/11/17 00:43:40 by rchampli         ###   ########.fr       */
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

# define WIN_HEIGHT 800
# define WIN_WIDTH 800
# define PC_HEIGHT .5
# define PC_FOV 100.

typedef struct s_vec
{
	double			x;
	double			y;
}					t_vec;

typedef struct s_img
{
	void			*img;
	char			*addr;
	int				bpp;
	int				length;
	int				endian;
}					t_img;

typedef struct s_inter
{
	double	dst;
	int		face;
	double	pos1;
	t_vec	pos2;
	char	type;
}			t_inter;

typedef struct s_mlx
{
	int				win_x;
	int				win_y;
	double			fov;
	void			*mlx_ptr;
	void			*win_ptr;
	double			*x_ray;
	double			*y_ray;
	double			z;
	t_img			img;
	t_img			west;
	t_img			east;
	t_img			north;
	t_img			south;
	u_int32_t		north_array[64][64];
	u_int32_t		south_array[64][64];
	u_int32_t		west_array[64][64];
	u_int32_t		east_array[64][64];
}			t_mlx;

typedef struct s_player
{
	double			x;
	double			y;
	double			rot;
	double			height;
	double			dir_x;
	double			dir_y;
	double			plane_x;
	double			plane_y;
	double			dir;
	char			dir_symbol;
	int				count;
	int				move;
}					t_player;

typedef struct s_map
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
}					t_map;

typedef struct s_data
{
	t_player	player;
	t_mlx		mlx;
	t_map		map;
}	t_data;

//Parsing
void	parse(char *file, t_data *data);
void	parse_map(char *line, int fd, t_data *data);
int		parse_m(t_data *data);
void	parse_m2(int i, int j, t_data *data);
void	player_dir(t_data *data); //?
void	ft_parse(char *line, int n, t_data *data);
void	fill_map(char *line, int n, t_data *data);
int		parse_texture(char **temp, t_data *data);
int		parse_texture2(char **temp, t_data *data);
int		ft_parse_color(char **temp, t_data *data);
void	ft_map(t_data *data);
void	map_size(char *file, t_data *data);
void	map_size_process(char *line, int *n, t_data *data);

//Checker for parsing
int		check1(char *line);
int		check2(char c);
void	check3(int i, int j, t_data *data);

//Texture
void		load_texture(t_data *data);
void		texture_load_array(t_img *src, u_int32_t dest[64][64]);
u_int32_t	take_pixel(t_img *img, int x, int y);
void		texture_load(char *path, t_img *dest, t_data *data);

//Get next line
int			get_next_line(int fd, char **line, t_data *data);

//Free and exit
void	cub3D_error(char *str, t_data *data);
//void		cleanup(void);

//2d vector
void		vec_norm(t_vec *vec);
t_vec		vec_rot(t_vec const *vec, double cosa, double sina);

//mlx
void	data_mlx_init(t_mlx	*mlx);
void	render(t_data *data);

#endif
