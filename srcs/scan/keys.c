/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 14:49:07 by mchardin          #+#    #+#             */
/*   Updated: 2021/09/14 21:14:11 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		key_events(t_params *params)
{
	if (params->event[CAM_L] == 1)
		;
}

int			press_key(int keycode, t_params *params)
{
	if (keycode == LEFT_KEY || keycode == Q_KEY)
		params->event[CAM_L] = 1;
	return (1);
}

int			release_key(int keycode, t_params *params)
{
	if (keycode == ESC_KEY)
		exit_wdw(params);
	if (keycode == LEFT_KEY || keycode == Q_KEY)
		params->event[CAM_L] = 0;
	return (1);
}
