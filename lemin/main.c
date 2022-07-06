/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molesen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 16:11:31 by molesen           #+#    #+#             */
/*   Updated: 2022/07/01 16:11:33 by molesen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/lemin.h"

int	main(int argc, char **argv)
{
	int	total;

	if (argc == 1)
	{
		total = 0;
		if (parsing_phase(&total) == ERROR)
			return (0);
	}
	else if (argv)
		ft_printf("Usage: ./lem-in < maps/subject.map\n");
	return (0);
}
