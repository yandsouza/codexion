/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coders.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynascime <yannssouza@outlook.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/12 18:46:24 by ynascime          #+#    #+#             */
/*   Updated: 2026/09/13 22:46:24 by ynascime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	simulation(t_memory *memory)
{
	int	state;

	state = 0;
	pthread_mutex_lock(&memory->sim_mutex);
	state = memory->sim_is_active;
	pthread_mutex_unlock(&memory->sim_mutex);
	return (state);
}

static void	print_task(int id, char *task, t_memory *memory)
{
	long	time;

	pthread_mutex_lock(&memory->print_mutex);
	time = ms_time() - memory->start_time;
	printf("%li %i is %s\n", time, id, task);
	pthread_mutex_unlock(&memory->print_mutex);
}

static void	task(t_coder *coder, char task)
{
	if (task == 'c')
	{
		print_task(coder->id, "compiling", coder->memory);
		usleep(coder->memory->time_comp * 1000);
		coder->n_comp += 1;
		if (coder->n_comp >= coder->memory->n_compiles_required)
			coder->finished = 1;
	}
	if (task == 'd')
	{
		print_task(coder->id, "debugging", coder->memory);
		usleep(coder->memory->time_debug * 1000);
	}
	if (task == 'r')
	{
		print_task(coder->id, "refactoring", coder->memory);
		usleep(coder->memory->time_refactor * 1000);
	}
}

void	*coder_thread(void *arg)
{
	t_coder		*coder;
	t_memory	*memory;

	coder = (t_coder *)arg;
	memory = coder->memory;
	while (!coder->finished)
	{
		manage_dongles(memory, coder);
		task(coder, 'c');
		release_dongles(memory, coder);
		task(coder, 'd');
		task(coder, 'r');
	}
	return (NULL);
}
