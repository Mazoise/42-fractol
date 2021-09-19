/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 14:45:55 by mchardin          #+#    #+#             */
/*   Updated: 2021/09/16 16:15:02 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <math.h>

int				draw_in_wdw(t_params *params)
{
	full_scan(params);
	mlx_put_image_to_window(params->ptr, params->wdw, params->fullscreen, 0, 0);
	key_events(params);
	return (1);
}

void			loop_mlx(t_params *params)
{
	mlx_hook(params->wdw, 17, 0, exit_wdw, params);
	mlx_do_key_autorepeatoff(params->ptr);
	mlx_loop_hook(params->ptr, draw_in_wdw, params);
	mlx_hook(params->wdw, 2, 1L << 0, press_key, params);
	mlx_hook(params->wdw, 3, 1L << 1, release_key, params);
	mlx_loop(params->ptr);
}

int				main(int argc, char **argv)
{
	t_params	params;

	if (check_args(argc, argv, &params))
		return (0);
	if (!(params.ptr = mlx_init()))
	{
		ft_dprintf(2, "Error\nMlx error : %s (init.)\n", strerror(errno));
		return (0);
	}
	init_struct(&params);
	if (params.screenshot == 1)
		screenshot_bmp(&params);
	if (!(window_mlx(&params, "--- FRACTOL ---")))
		return (0);
	loop_mlx(&params);
}
