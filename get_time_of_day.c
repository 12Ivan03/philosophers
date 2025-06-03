/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_time_of_day.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipavlov <ipavlov@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 10:47:15 by ipavlov           #+#    #+#             */
/*   Updated: 2025/02/28 11:54:36 by ipavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philosophers.h"

unsigned int	get_time(void)
{
	struct timeval	get_time;
	unsigned int	time;

	gettimeofday(&get_time, NULL);
	time = get_time.tv_usec / 1000 + get_time.tv_sec * 1000;
	return (time);
}
