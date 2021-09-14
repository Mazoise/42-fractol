/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 18:21:54 by mchardin          #+#    #+#             */
/*   Updated: 2021/09/14 22:39:24 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
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

void				full_scan(t_params *params)
{
	t_idx	scan;
	t_rgb	color;
	t_pos	scale;

	float x1 = -2.1;
	float x2 = 0.6;
	float y1 = -1.2;
	float y2 = 1.2;
	int iteration_max = 200;

	scale.x = params->max.i/(x2 - x1);
	scale.y = params->max.j/(y2 - y1);

	scan.i = 0;

	while(scan.i < params->max.i)
	{
		scan.j = 0;
		while(scan.j < params->max.j)
		{
			float c_r = scan.i / scale.x + x1;
			float c_i = scan.j / scale.y + y1;
			float z_r = 0;
			float z_i = 0;
			int i = 0;

			while (z_r*z_r + z_i*z_i < 4 && i < iteration_max)
			{
				float tmp = z_r;
				z_r = z_r * z_r - z_i * z_i + c_r;
				z_i = 2 * z_i * tmp + c_i;
				i++;
			}
			if (i == iteration_max)
			{
				color.red = 255;
				color.blue = 255;
				color.green = 255;
				rgb_to_img(&params->img, color, scan.i, scan.j);
			}
			else
			{
				color.red = (i / (iteration_max / 2.0)) * 255;
				color.blue = 0;
				color.green = 0;
				rgb_to_img(&params->img, color, scan.i, scan.j);
			}
			scan.j++;
		}
		scan.i++;
	}
}

// while zx*zx + zy*zy < 4 and i > 1:
//                 tmp = zx*zx - zy*zy + cX
//                 zy,zx = 2.0*zx*zy + cY, tmp