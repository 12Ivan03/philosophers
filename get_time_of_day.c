/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_time_of_day.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: penchoivanov <penchoivanov@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 10:47:15 by ipavlov           #+#    #+#             */
/*   Updated: 2025/06/06 14:38:34 by penchoivano      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

time_t	get_time(void)
{
	struct timeval	get_time;
	time_t			time;

	gettimeofday(&get_time, NULL);
	time = get_time.tv_usec / 1000 + get_time.tv_sec * 1000;
	return (time);
}
