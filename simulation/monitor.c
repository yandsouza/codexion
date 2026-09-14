/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynascime <yannssouza@outlook.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/13 23:14:59 by ynascime          #+#    #+#             */
/*   Updated: 2026/09/14 00:22:53 by ynascime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static void	finish_simulation(t_memory *memory);

void print_log(t_memory *memory)
{
	pthread_mutex_lock(&memory->print_mutex);
	printf("ok monitor is working DELETE THIS LINE LATER\n");
	pthread_mutex_unlock(&memory->print_mutex);
}

static void	print_task(int id, t_memory *memory)
{
	long	time;

	pthread_mutex_lock(&memory->print_mutex);
	time = ms_time() - memory->start_time;
	printf("%li %i burned out\n", time, id);
	pthread_mutex_unlock(&memory->print_mutex);
}

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
	int		i;
	int		finish;
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
			else if ((ms_time() - check_burnout(&memory->coder[i])) > memory->time_to_burnout)
			{
				finish_simulation(memory);
				print_task(memory->coder[i].id, memory);
				return (NULL);
			}
			i++;
		}
		if (finish == memory->n_coders)
		{
			finish_simulation(memory);
			// line below be deleted
			print_log(memory);
			return (NULL);
		}
		usleep(100);
	}
	return (NULL);
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
