/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_argv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: penchoivanov <penchoivanov@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 14:31:20 by ipavlov           #+#    #+#             */
/*   Updated: 2025/06/06 14:43:06 by penchoivano      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

int	check_argv(int argc, char *argv[])
{
	int	i;

	i = 1;
	if (argc < 5 || argc > 6)
	{
		printf("incorrect input: time-die, time-eat, time-sleep, \
			(optional)num-meals\n");
		return (0);
	}
	while (argv[i])
	{
		if (!ft_isdigit(argv[i]) || !ft_atol(argv[i]))
		{
			printf("incorrect input: time-die, time-eat, time-sleep, \
					(optional)num-meals\n");
			return (0);
		}
		i++;
	}
	return (1);
}
