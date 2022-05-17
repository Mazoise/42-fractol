/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 18:21:54 by mchardin          #+#    #+#             */
/*   Updated: 2022/05/17 21:03:50 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <math.h>

void
	put_pix(t_mlx_img *img, t_mlx_img txtr, int dst, int src)
{
	int		i;
	int		opp_img;
	int		opp_txtr;

	i = 0;
	opp_txtr = txtr.bpp >> 3;
	opp_img = img->bpp >> 3;
	while (i < opp_txtr && i < opp_img)
	{
		img->img[dst + i] = txtr.img[src * opp_txtr + i];
		i++;
	}
}

void
	rgb_to_img(t_mlx_img *img, t_rgb color, int i, int j)
{
	int		tmp;

	tmp = ((img->len * j) + i * (img->bpp >> 3));
	img->img[tmp + 0] = color.blue;
	img->img[tmp + 1] = color.green;
	img->img[tmp + 2] = color.red;
}

void
	color_to_img(t_mlx_img *img, int color, t_idx coord, int decalage)
{
	int					tmp;
	unsigned char		switch_color[6];
	int					idx;

	idx = 0;
	tmp = ((img->len * coord.j) + coord.i * (img->bpp >> 3));
	switch_color[0] = color % 256;
	switch_color[1] = 255;
	switch_color[2] = 255;
	switch_color[3] = 255 - color % 256;
	switch_color[4] = 0;
	switch_color[5] = 0;
	while (idx < 3)
	{
		img->img[tmp + idx] = switch_color[(color / 256 + 4
				* idx + decalage) % 6];
		idx++;
	}
}

int
	set_params(t_params *p, t_idx scan, t_pos scale, int iter_max)
{
	int			i;
	float		tmp;

	if (p->set == JULIA)
	{
		p->z_r = scan.i / scale.x + p->x1;
		p->z_i = scan.j / scale.y + p->y1;
	}
	else if (p->set == MANDELBROT)
	{
		p->c_r = scan.i / scale.x + p->x1;
		p->c_i = scan.j / scale.y + p->y1;
		p->z_i = 0;
		p->z_r = 0;
	}
	i = 0;
	while (p->z_r * p->z_r + p->z_i * p->z_i < 4
		&& i < iter_max)
	{
		tmp = p->z_r;
		p->z_r = p->z_r * p->z_r - p->z_i * p->z_i + p->c_r;
		p->z_i = 2 * p->z_i * tmp + p->c_i;
		i++;
	}
	return (i);
}

void
	full_scan(t_params *params)
{
	const t_rgb	no_solve_color = {255, 255, 255, 1};
	const int	iteration_max = ITERATION_MAX;
	t_idx		scan;
	t_pos		scale;
	int			i;

	scale.x = params->max.i / (params->x2 - params->x1);
	scale.y = params->max.j / (params->y2 - params->y1);
	scan.i = 0;
	while (scan.i < params->max.i)
	{
		scan.j = 0;
		while (scan.j < params->max.j)
		{
			// color_to_img(&params->img, ((float)scan.i / params->max.i) * 1534, scan.i, scan.j, params->decalage);
			i = set_params(params, scan, scale, iteration_max);
			if (i == iteration_max)
				rgb_to_img(&params->img, no_solve_color, scan.i, scan.j);
			else
				color_to_img(&params->img, (int)(((float)i / iteration_max)
						* 1534 * 2) % 1534, scan, params->decalage);
			scan.j++;
		}
		scan.i++;
	}
}
