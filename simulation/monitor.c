/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynascime <yannssouza@outlook.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/13 23:14:59 by ynascime          #+#    #+#             */
/*   Updated: 2026/09/14 01:23:00 by ynascime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void		finish_cond(t_memory *memory, int finish);
static void	finish_simulation(t_memory *memory);

long	check_burnout(t_coder *coder)
{
	long	burnout;

	burnout = 0;
	pthread_mutex_lock(&coder->burnout_mutex);
	burnout = coder->bournout_time;
	pthread_mutex_unlock(&coder->burnout_mutex);
	return (burnout);
}

int	check_finished(t_coder *coder)
{
	int	finished;

	finished = 0;
	pthread_mutex_lock(&coder->finish_mutex);
	finished = coder->finished;
	pthread_mutex_unlock(&coder->finish_mutex);
	return (finished);
}

void	*monitor(void *arg)
{
	int			i;
	int			finish;
	t_memory	*memory;

	memory = (t_memory *)arg;
	while (simulation(memory))
	{
		i = 0;
		finish = 0;
		while (i != memory->n_coders)
		{
			if (check_finished(&memory->coder[i]) == 1)
				finish++;
			else if ((ms_time() - check_burnout(&memory->coder[i]))
				> memory->time_to_burnout)
			{
				finish_simulation(memory);
				print_burnout(memory->coder[i].id, memory);
				return (NULL);
			}
			i++;
		}
		finish_cond(memory, finish);
	}
	return (NULL);
}

void	finish_cond(t_memory *memory, int finish)
{
	if (finish == memory->n_coders)
	{
		finish_simulation(memory);
		return ;
	}
	usleep(100);
}

static void	finish_simulation(t_memory *memory)
{
	pthread_mutex_lock(&memory->sim_mutex);
	memory->sim_is_active = 0;
	pthread_mutex_unlock(&memory->sim_mutex);
	pthread_mutex_lock(&memory->fifo_list.list_mutex);
	pthread_cond_broadcast(&memory->fifo_list.cond);
	pthread_mutex_unlock(&memory->fifo_list.list_mutex);
}
