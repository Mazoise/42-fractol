/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 14:49:07 by mchardin          #+#    #+#             */
/*   Updated: 2021/09/16 16:51:26 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		key_events(t_params *params)
{
	if (params->event[ZOOM] == 1)
	{
		float tmp = (params->x2 - params->x1) * 0.05;
		params->x1 += tmp;
		params->x2 -= tmp;
		tmp = (params->y2 - params->y1) * 0.05;
		params->y1 += tmp;
		params->y2 -= tmp;
	}
	else if (params->event[DEZOOM] == 1)
	{
		float tmp = (params->x2 - params->x1) * 0.05;
		params->x1 -= tmp;
		params->x2 += tmp;
		tmp = (params->y2 - params->y1) * 0.05;
		params->y1 -= tmp;
		params->y2 += tmp;
	}
}

int			press_key(int keycode, t_params *params)
{
	if (keycode == UP_KEY || keycode == W_KEY)
		params->event[ZOOM] = 1;
	else if (keycode == DOWN_KEY || keycode == S_KEY)
		params->event[DEZOOM] = 1;
	return (1);
}

int			release_key(int keycode, t_params *params)
{
	if (keycode == ESC_KEY)
		exit_wdw(params);
	if (keycode == UP_KEY || keycode == W_KEY)
		params->event[ZOOM] = 0;
	else if (keycode == DOWN_KEY || keycode == S_KEY)
		params->event[DEZOOM] = 0;
	return (1);
}
