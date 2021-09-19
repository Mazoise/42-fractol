/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 18:21:54 by mchardin          #+#    #+#             */
/*   Updated: 2021/09/19 18:03:51 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <math.h>

void		put_pix(t_mlx_img *img, t_mlx_img txtr, int dst, int src)
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

void		rgb_to_img(t_mlx_img *img, t_rgb color, int i, int j)
{
	int		tmp;

	tmp = ((img->len * j) + i * (img->bpp >> 3));
	img->img[tmp + 0] = color.blue;
	img->img[tmp + 1] = color.green;
	img->img[tmp + 2] = color.red;
}

void		color_to_img(t_mlx_img *img, int color, int i, int j, int decalage)
{
	int					tmp;
	unsigned char		switch_color[6];
	int					idx;

	idx = 0;
	tmp = ((img->len * j) + i * (img->bpp >> 3));
	switch_color[0] = color % 256;
	switch_color[1] = 255;
	switch_color[2] = 255;
	switch_color[3] = 255 - color % 256;
	switch_color[4] = 0;
	switch_color[5] = 0;

	while (idx < 3)
	{
		img->img[tmp + idx] = switch_color[(color / 256 + 4 * idx + decalage) % 6];
		idx++;
	}
}

void				full_scan(t_params *params)
{
	const t_rgb	no_solve_color = {255, 255, 255, 1};
	const int iteration_max = ITERATION_MAX;

	t_idx	scan;
	t_pos	scale;
	int i;

	scale.x = params->max.i/(params->x2 - params->x1);
	scale.y = params->max.j/(params->y2 - params->y1);

	scan.i = 0;

	while(scan.i < params->max.i)
	{
		scan.j = 0;
		while(scan.j < params->max.j)
		{
			// color_to_img(&params->img, ((float)scan.i / params->max.i) * 1534, scan.i, scan.j, params->decalage);
			if (params->set == JULIA)
			{
				params->z_r = scan.i / scale.x + params->x1;
				params->z_i = scan.j / scale.y + params->y1;
			}
			else if (params->set == MANDELBROT)
			{
				params->c_r = scan.i / scale.x + params->x1;
				params->c_i = scan.j / scale.y + params->y1;	
				params->z_i = 0;
				params->z_r = 0;
			}
			i = 0;
			while (params->z_r*params->z_r + params->z_i*params->z_i < 4 && i < iteration_max)
			{
				float tmp = params->z_r;
				params->z_r = params->z_r * params->z_r - params->z_i * params->z_i + params->c_r;
				params->z_i = 2 * params->z_i * tmp + params->c_i;
				i++;
			}
			if (i == iteration_max)
				rgb_to_img(&params->img, no_solve_color, scan.i, scan.j);
			else
				color_to_img(&params->img, (int)(((float)i / iteration_max) * 1534 * 2) % 1534, scan.i, scan.j, params->decalage);
			scan.j++;
		}
		scan.i++;
	}
}
