/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 11:01:01 by mchardin          #+#    #+#             */
/*   Updated: 2022/05/17 20:47:35 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "mlx.h"
# include "libft.h"
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <math.h>
# include <sys/errno.h>

# define ITERATION_MAX 150
// # define NO_SOLVE_COLOR 
# define WINDOW_H 1000

# define FULLSCREEN_H 1400
# define FULLSCREEN_W 2560

# define INFO 54
# define COLOR_SHIFT 0
# define CAM_R 1
# define FORW 2
# define BCKW 3
# define LEFT 4
# define RGHT 5
# define MAP 6
# define UP 7
# define DWN 8
# define OBJ 9
# define ZOOM 11
# define DEZOOM 12
# define EVENTS 13

# define ESC_KEY 65307
# define UP_KEY 65362
# define DOWN_KEY 65364
# define RIGHT_KEY 65363
# define LEFT_KEY 65361
# define W_KEY 119
# define A_KEY 97
# define S_KEY 115
# define D_KEY 100
# define TAB_KEY 65289
# define C_KEY 99
# define Q_KEY 113
# define P_KEY 112
# define M_KEY 109
# define SPACE 32
# define F_KEY 102
# define E_KEY 101

#define JULIA 0
#define MANDELBROT 1

typedef union		u_squ
{
	float			f;
	uint32_t		i;
}					t_squ;

typedef struct		s_pos
{
	float			x;
	float			y;
}					t_pos;

typedef struct		s_idx
{
	int				i;
	int				j;
}					t_idx;

typedef struct		s_mlx_img
{
	char			*img;
	int				endian;
	int				bpp;
	int				len;
}					t_mlx_img;

typedef struct		s_rgb
{
	unsigned char	red;
	unsigned char	green;
	unsigned char	blue;
	int				true;
}					t_rgb;

typedef struct		s_colors
{
	t_rgb			zero;
	t_rgb			one;
	t_rgb			two;
	t_rgb			player;
}					t_colors;

typedef struct		s_params
{
	void			*ptr;
	void			*wdw;
	void			*fullscreen;
	t_idx			max;
	t_mlx_img		img;
	float		c_i;
	float		z_r;
	float		c_r;
	float		z_i;
	float		x1;
	float		x2;
	float		y1;
	float		y2;
	int				set;
	char			event[EVENTS];
	int				screenshot;
	int				decalage;
}					t_params;

int					initialisation(char *mapcub, t_params *params);
void				init_struct(t_params *params);
int					check_all_params(t_params *params);
int					conv_resolution(char *str, t_params *params);
void				line_put(t_params *params, double inc, int i, double angle);
void				rgb_to_img(t_mlx_img *img, t_rgb color, int i, int j);
void				key_events(t_params *params);
int					press_key(int keycode, t_params *params);
int					release_key(int keycode, t_params *params);
int					exit_wdw(t_params *params);
int					window_mlx(t_params *params, char *name);
void				loop_mlx(t_params *params);
int					draw_in_wdw(t_params *params);
void				full_scan(t_params *params);
void				screenshot_bmp(t_params *params);
int					check_args(int argc, char **argv, t_params *params);
void				free_all(t_params *params);
void				sprite(t_params *params, double angle, int i);
void				which_start(t_pos *scan, t_pos pos, double angle, int idx);
void				which_add(t_pos *add, double angle, int idx);
void				put_pix(t_mlx_img *img, t_mlx_img txtr, int dst, int src);
double				rsqrt(double number);
void				player_error(int pos);
void				txtr_error(char c);
int					error_conv(char c);
int					draw_mini_map(t_params *params);
void				put_cut_nb_fd(int nb, int fd, int len);
int					conv_params(char *str, t_params *params);
double				pct_calc(t_params *params);
void				dir_vect(t_pos *dir, t_pos *hit, double compas);
void				pre_color(t_colors *colors);
void				clear_void(t_mlx_img *map, t_idx max);
void				add_pix(t_mlx_img *img, t_mlx_img txtr, int dst, int src);
void		color_to_img(t_mlx_img *img, int color, t_idx coord, int decalage);
#endif
