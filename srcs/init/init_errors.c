/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_errors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 19:12:35 by mchardin          #+#    #+#             */
/*   Updated: 2021/09/14 21:05:40 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		check_format(char *str)
{
	int	i;

	i = ft_strlen(str);
	if (!ft_strncmp(str, "-save", 6))
	{
		ft_dprintf(2, "Error\nMissing map reference before save request\n");
		exit(0);
	}
	else if (i < 5 || ft_strncmp(&str[i - 4], ".cub", 5))
	{
		ft_dprintf(2, "Error\nMap file should end in \".cub\"\n");
		exit(0);
	}
}

void		check_args(int argc, char **argv, t_params *params)
{
	if (argc < 2)
	{
		ft_dprintf(2, "Error\nNo map specified\n");
		exit(0);
	}
	else if (argc > 2 && (!ft_strncmp(argv[2], "-save", 6)
		|| !ft_strncmp(argv[2], "--save", 7)))
		params->screenshot = 1;
	else
		params->screenshot = 0;
}
