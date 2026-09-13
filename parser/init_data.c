/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynascime <yannssouza@outlook.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/12 20:06:25 by ynascime          #+#    #+#             */
/*   Updated: 2026/09/13 20:23:43 by ynascime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

long	ms_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	init_mutex_and_cond(t_memory *memory)
{
	int	i;

	pthread_mutex_init(&memory->sim_mutex, NULL);
	i = 0;
	while (i != memory->n_coders)
		pthread_mutex_init(&memory->dongle[i++].dongle_mutex, NULL);
}

static void	assign_dongles(t_memory *memory, t_coder *coder, int i)
{
	int	next;

	if (memory->n_coders > 1)
	{
		next = (i + 1) % memory->n_coders;
		if (i < next)
		{
			coder->dongle_a = &memory->dongle[i];
			coder->dongle_b = &memory->dongle[next];
		}
		else
		{
			coder->dongle_a = &memory->dongle[next];
			coder->dongle_b = &memory->dongle[i];
		}
	}
	else
		coder->dongle_a = &memory->dongle[i];
}

void	init_data(t_memory *memory)
{
	int	i;

	memory->start_time = ms_time();
	memory->sim_is_active = 1;
	i = 0;
	while (i != memory->n_coders)
	{
		memory->coder[i].bournout_time = ms_time();
		memory->coder[i].id = i + 1;
		memory->coder[i].n_comp = 0;
		memory->coder[i].finished = 0;
		memory->coder[i].memory = memory;
		memory->dongle[i].cooldown = 0;
		memory->coder->dongle_a = NULL;
		memory->coder->dongle_b = NULL;
		assign_dongles(memory, &memory->coder[i], i);
		i++;
	}
	init_mutex_and_cond(memory);
}
