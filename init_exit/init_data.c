/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynascime <yannssouza@outlook.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/12 20:06:25 by ynascime          #+#    #+#             */
/*   Updated: 2026/09/14 02:09:39 by ynascime         ###   ########.fr       */
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
	pthread_mutex_init(&memory->print_mutex, NULL);
	pthread_mutex_init(&memory->fifo_list.list_mutex, NULL);
	pthread_mutex_init(&memory->heap.lock, NULL);
	pthread_cond_init(&memory->fifo_list.cond, NULL);
	pthread_cond_init(&memory->heap.cond, NULL);
	i = 0;
	while (i != memory->n_coders)
	{
		pthread_mutex_init(&memory->dongle[i].dongle_mutex, NULL);
		pthread_mutex_init(&memory->coder[i].finish_mutex, NULL);
		pthread_mutex_init(&memory->coder[i].burnout_mutex, NULL);
		i++;
	}
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

static void	init_heap(t_memory *memory)
{
	int	i;

	memory->heap.size = 0;
	i = 0;
	while (i < 500)
	{
		memory->heap.tree[i] = NULL;
		i++;
	}
}

void	init_data(t_memory *memory)
{
	int	i;

	memory->start_time = ms_time();
	memory->sim_is_active = 1;
	memory->fifo_list.first = NULL;
	memory->fifo_list.last = NULL;
	init_heap(memory);
	i = 0;
	while (i != memory->n_coders)
	{
		memory->coder[i].bournout_time = ms_time();
		memory->coder[i].id = i + 1;
		memory->coder[i].n_comp = 0;
		memory->coder[i].finished = 0;
		memory->coder[i].memory = memory;
		memory->dongle[i].cooldown = 0;
		memory->coder[i].dongle_a = NULL;
		memory->coder[i].dongle_b = NULL;
		assign_dongles(memory, &memory->coder[i], i);
		i++;
	}
	init_mutex_and_cond(memory);
}
