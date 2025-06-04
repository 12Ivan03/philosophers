/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: penchoivanov <penchoivanov@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 11:30:15 by ipavlov           #+#    #+#             */
/*   Updated: 2025/06/04 09:33:28 by penchoivano      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

void	printf_error(int i)
{
	if (i == 1)
		printf("Error with initialising the env\n");
	else if (i == 2)
		printf("Error mutext uninitialized\n");
	else if (i == 3)
		printf("Error creating philosopher\nn");

}
