/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 14:49:07 by mchardin          #+#    #+#             */
/*   Updated: 2021/09/19 17:47:43 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void		key_events(t_params *params)
{
	float tmp_x = (params->x2 - params->x1) * 0.05;
	float tmp_y = (params->y2 - params->y1) * 0.05;
	if (params->event[ZOOM] == 1)
	{
		params->x1 += tmp_x;
		params->x2 -= tmp_x;
		params->y1 += tmp_y;
		params->y2 -= tmp_y;
	}
	else if (params->event[DEZOOM] == 1)
	{
		params->x1 -= tmp_x;
		params->x2 += tmp_x;
		params->y1 -= tmp_y;
		params->y2 += tmp_y;
	}
	else if (params->event[LEFT] == 1)
	{
		params->x1 -= tmp_x * 2;
		params->x2 -= tmp_x * 2;
	}
	else if (params->event[RGHT] == 1)
	{
		params->x1 += tmp_x * 2;
		params->x2 += tmp_x * 2;
	}
	else if (params->event[UP] == 1)
	{
		params->y1 -= tmp_y * 2;
		params->y2 -= tmp_y * 2;
	}
	else if (params->event[DWN] == 1)
	{
		params->y1 += tmp_y * 2;
		params->y2 += tmp_y * 2;
	}
	else if (params->event[COLOR_SHIFT] == 1)
	{
		params->decalage++;
	}
}

int			press_key(int keycode, t_params *params)
{
	if (keycode == W_KEY)
		params->event[ZOOM] = 1;
	else if (keycode == S_KEY)
		params->event[DEZOOM] = 1;
	else if (keycode == LEFT_KEY)
		params->event[LEFT] = 1;
	else if (keycode == RIGHT_KEY)
		params->event[RGHT] = 1;
	else if (keycode == UP_KEY)
		params->event[UP] = 1;
	else if (keycode == DOWN_KEY)
		params->event[DWN] = 1;
	else if (keycode == Q_KEY)
		params->event[COLOR_SHIFT] = 1;
	return (1);
}

int			release_key(int keycode, t_params *params)
{
	if (keycode == ESC_KEY)
		exit_wdw(params);
	if (keycode == W_KEY)
		params->event[ZOOM] = 0;
	else if (keycode == S_KEY)
		params->event[DEZOOM] = 0;
		else if (keycode == LEFT_KEY)
		params->event[LEFT] = 0;
	else if (keycode == RIGHT_KEY)
		params->event[RGHT] = 0;
	else if (keycode == UP_KEY)
		params->event[UP] = 0;
	else if (keycode == DOWN_KEY)
		params->event[DWN] = 0;
	else if (keycode == Q_KEY)
		params->event[COLOR_SHIFT] = 0;
	return (1);
}
