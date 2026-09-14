/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coders.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynascime <yannssouza@outlook.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/12 18:46:24 by ynascime          #+#    #+#             */
/*   Updated: 2026/09/14 01:26:19 by ynascime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	simulation(t_memory *memory)
{
	int	state;

	pthread_mutex_lock(&memory->sim_mutex);
	state = memory->sim_is_active;
	pthread_mutex_unlock(&memory->sim_mutex);
	return (state);
}

static void	task(t_coder *coder, char task)
{
	if (task == 'c')
	{
		pthread_mutex_lock(&coder->burnout_mutex);
		coder->bournout_time = ms_time();
		pthread_mutex_unlock(&coder->burnout_mutex);
		print_task(coder->id, "compiling", coder->memory);
		usleep(coder->memory->time_comp * 1000);
		coder->n_comp += 1;
		if (coder->n_comp >= coder->memory->n_compiles_required)
		{
			pthread_mutex_lock(&coder->finish_mutex);
			coder->finished = 1;
			pthread_mutex_unlock(&coder->finish_mutex);
		}
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
	while (simulation(memory) && !coder->finished)
	{
		if (!manage_dongles(memory, coder))
			break ;
		task(coder, 'c');
		release_dongles(memory, coder);
		if (!simulation(memory))
			break ;
		task(coder, 'd');
		if (!simulation(memory))
			break ;
		task(coder, 'r');
	}
	return (NULL);
}
