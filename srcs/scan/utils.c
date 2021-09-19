/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 15:59:17 by mchardin          #+#    #+#             */
/*   Updated: 2021/09/19 16:09:43 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

double		rsqrt(double number)
{
	const double	x2 = number * 0.5;
	const double	threehalfs = 1.5;
	t_squ			conv;

	conv.i = number;
	conv.f = number;
	conv.i = 0x5f3759df - (conv.i >> 1);
	conv.f *= (threehalfs - (x2 * conv.f * conv.f));
	return (1 / conv.f);
}

void		put_cut_nb_fd(int nb, int fd, int len)
{
	int		k;

	k = 0;
	while (k < len)
	{
		ft_putchar_fd(nb / (int)pow(256, k), fd);
		k++;
	}
}

void		free_all(t_params *params)
{
	if (params->fullscreen)
		mlx_destroy_image(params->ptr, params->fullscreen);
}
