/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_dongles.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynascime <yannssouza@outlook.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/13 18:11:00 by ynascime          #+#    #+#             */
/*   Updated: 2026/09/13 20:22:28 by ynascime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static void	print_task(int id, t_memory *memory)
{
	long	time;

	time = ms_time() - memory->start_time;
	printf("%li %i has taken a dongle\n", time, id);
	return ;
}

int	try_take_dongle(t_dongle *dongle, t_memory *memory)
{
	long	time;

	time = ms_time() - memory->start_time;
	pthread_mutex_lock(&dongle->dongle_mutex);
	if (time >= dongle->cooldown)
		return (0);
	pthread_mutex_unlock(&dongle->dongle_mutex);
	return (1);
}

int	take_dongle(t_coder *coder)
{
	if (try_take_dongle(coder->dongle_a, coder->memory) == 0)
	{
		if (coder->dongle_b == NULL)
		{
			pthread_mutex_unlock(&coder->dongle_a->dongle_mutex);
			return (1);
		}
		if (try_take_dongle(coder->dongle_b, coder->memory) == 0)
		{
			print_task(coder->id, coder->memory);
			return (0);
		}
		else
		{
			pthread_mutex_unlock(&coder->dongle_a->dongle_mutex);
			return (1);
		}
	}
	return (1);
}

int	manage_dongles(t_memory *memory, t_coder *coder)
{
//	if (strcmp("fifo", memory->scheduler))
//		scheduler_fifo();
//	else
//		scheduler_edf();
//
//	temp line above for gcc:
	if (memory && coder)
		return (0);
	return (0);
}
