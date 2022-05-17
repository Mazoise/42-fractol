/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 15:41:19 by mchardin          #+#    #+#             */
/*   Updated: 2022/05/17 20:55:07 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void
	init_struct(t_params *params)
{
	if (params->set == JULIA)
	{
		params->x1 = -2;
		params->x2 = 2;
		params->y1 = -2;
		params->y2 = 2;
	}
	else if (params->set == MANDELBROT)
	{
		params->x1 = -2.1;
		params->x2 = 0.6;
		params->y1 = -1.2;
		params->y2 = 1.2;
	}
	params->max.i = WINDOW_H * (params->x2 - params->x1)
		/ (params->y2 - params->y1);
	params->max.j = WINDOW_H;
	params->decalage = 0;
}

void
	print_arg_error(void)
{
	ft_dprintf(2, "Error\nNo argument, please enter either");
	ft_dprintf(2, " \"Mandelbrot\" or \"Julia\" ");
	ft_dprintf(2, "(for Julia you must also add 2 floats)\n");
}

int
	parse_julia(t_params *params, char **argv, int argc)
{
	params->set = JULIA;
	if (argc < 4)
	{
		ft_dprintf(2, "Error\n\"Julia\" requires 2 floats as arguments\n");
		return (1);
	}
	params->c_r = atof(argv[2]);  //
	params->c_i = atof(argv[3]);  //
	return (0);
}

int
	check_args(int argc, char **argv, t_params *params)
{
	if (argc < 2)
	{
		print_arg_error();
		return (1);
	}
	if (!ft_strncmp(argv[1], "Julia", 6) || !ft_strncmp(argv[1], "julia", 6))
	{
		if (parse_julia(params, argv, argc))
			return (1);
	}
	else if (!ft_strncmp(argv[1], "Mandelbrot", 11)
		|| !ft_strncmp(argv[1], "mandelbrot", 11))
		params->set = MANDELBROT;
	else
	{
		print_arg_error();
		return (1);
	}
	if (!ft_strncmp(argv[argc - 1], "-save", 6)
		|| !ft_strncmp(argv[argc - 1], "--save", 7))
		params->screenshot = 1;
	else
		params->screenshot = 0;
	return (0);
}
