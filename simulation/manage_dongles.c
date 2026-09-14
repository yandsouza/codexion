/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_dongles.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynascime <yannssouza@outlook.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/13 18:11:00 by ynascime          #+#    #+#             */
/*   Updated: 2026/09/14 01:29:06 by ynascime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	release_dongles(t_memory *memory, t_coder *coder)
{
	long	time;

	time = ms_time() - memory->start_time;
	coder->dongle_a->cooldown = time + memory->dongle_cooldown;
	if (coder->dongle_b != NULL)
		coder->dongle_b->cooldown = time + memory->dongle_cooldown;
	pthread_mutex_unlock(&coder->dongle_a->dongle_mutex);
	if (coder->dongle_b != NULL)
		pthread_mutex_unlock(&coder->dongle_b->dongle_mutex);
	pthread_mutex_lock(&memory->fifo_list.list_mutex);
	pthread_cond_broadcast(&memory->fifo_list.cond);
	pthread_mutex_unlock(&memory->fifo_list.list_mutex);
}

static int	try_take_dongle(t_dongle *dongle, t_memory *memory)
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
			print_dongle(coder->id, coder->memory);
			return (0);
		}
		if (try_take_dongle(coder->dongle_b, coder->memory) == 0)
		{
			print_dongle(coder->id, coder->memory);
			print_dongle(coder->id, coder->memory);
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
	if (strcmp("fifo", memory->scheduler) == 0)
		return (scheduler_fifo(memory, coder));
//	else
//		return (scheduler_edf());
	return (0);
}
