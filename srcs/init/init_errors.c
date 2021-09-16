/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_errors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 19:12:35 by mchardin          #+#    #+#             */
/*   Updated: 2021/09/16 17:19:10 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// void
// 	check_format(char *str)
// {
// 	int	i;

// 	i = ft_strlen(str);
// 	if (!ft_strncmp(str, "-save", 6))
// 	{
// 		ft_dprintf(2, "Error\nMissing map reference before save request\n");
// 		exit(0);
// 	}
// 	else if (i < 5 || ft_strncmp(&str[i - 4], ".cub", 5))
// 	{
// 		ft_dprintf(2, "Error\nMap file should end in \".cub\"\n");
// 		exit(0);
// 	}
// }

int
	check_args(int argc, char **argv, t_params *params)
{
	if (argc < 2)
	{
		ft_dprintf(2, "Error\nNo argument, please enter either \"Mandelbrot\" or \"Julia\" (for Julia you must also add 2 floats)\n");
		return(1);
	}
	if (!ft_strncmp(argv[1], "Julia", 6) || !ft_strncmp(argv[1], "julia", 6))
	{
		params->set = JULIA;
		if (argc < 4) // check if floats for parameters
		{
			ft_dprintf(2, "Error\n\"Julia\" requires 2 floats as arguments\n");
			return(1);
		}
		params->x1 = -2;
		params->x2 = 2;
		params->y1 = -2;
		params->y2 = 2;
		params->c_r = atof(argv[2]);
		params->c_i = atof(argv[3]);
		params->z_r = 0;
		params->z_i = 0;
	}
	else if (!ft_strncmp(argv[1], "Mandelbrot", 11) || !ft_strncmp(argv[1], "mandelbrot", 11))
	{
		params->set = MANDELBROT;
		params->x1 = -2.1;
		params->x2 = 0.6;
		params->y1 = -1.2;
		params->y2 = 1.2;
		params->c_r = 0;
		params->c_i = 0;
	}
	else
	{
			ft_dprintf(2, "Error\nWrong argument, please enter either \"Mandelbrot\" or \"Julia\" (for Julia you must also add 2 floats)\n");
			return(1);
	}
	// if (!ft_strncmp(argv[argc - 1], "-save", 6)
	// 	|| !ft_strncmp(argv[2], "--save", 7))
	// 	params->screenshot = 1;
	// else
	// 	params->screenshot = 0;
	return (0);
}
