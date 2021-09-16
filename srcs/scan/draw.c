/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 18:21:54 by mchardin          #+#    #+#             */
/*   Updated: 2021/09/16 17:30:24 by mchardin         ###   ########.fr       */
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

void		color_to_img(t_mlx_img *img, int color, int i, int j)
{
	int		tmp;

	// ft_printf("color : %d - ", color);
	tmp = ((img->len * j) + i * (img->bpp >> 3));
	img->img[tmp + 2] = color >> 16;
	img->img[tmp + 1] = (color - (img->img[tmp + 0] << 16)) >> 8;
	img->img[tmp + 0] = (color - (img->img[tmp + 1] << 8));
	// ft_printf("%d, %d, %d\n ", (unsigned char)img->img[tmp + 0], (unsigned char)img->img[tmp + 1],(unsigned char)img->img[tmp + 2]);
}

void				full_scan(t_params *params)
{
	t_idx	scan;
	t_rgb	color;
	t_pos	scale;

	int iteration_max = 500;

	scale.x = params->max.i/(params->x2 - params->x1);
	scale.y = params->max.j/(params->y2 - params->y1);

	scan.i = 0;

	while(scan.i < params->max.i)
	{
		scan.j = 0;
		while(scan.j < params->max.j)
		{
			params->z_r = scan.i / scale.x + params->x1;
			params->z_i = scan.j / scale.y + params->y1;
			// params->z_r = 0;
			// params->z_i = 0;
			int i = 0;

			while (params->z_r*params->z_r + params->z_i*params->z_i < 4 && i < iteration_max)
			{
				float tmp = params->z_r;
				params->z_r = params->z_r * params->z_r - params->z_i * params->z_i + params->c_r;
				params->z_i = 2 * params->z_i * tmp + params->c_i;
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
				// color.red = (int)(((float)i / iteration_max) * 16777216) % 255;
				// color.green = (int)(((float)i / iteration_max) * 16777216) % (255 * 255);
				// color.blue = (int)(((float)i / iteration_max) * 16777216) % (255 * 255 * 255);
				color_to_img(&params->img, ((float)i / iteration_max) * 16777216, scan.i, scan.j);
			}
			scan.j++;
		}
		scan.i++;
	}
}

// while zx*zx + zy*zy < 4 and i > 1:
//                 tmp = zx*zx - zy*zy + cX
//                 zy,zx = 2.0*zx*zy + cY, tmp