/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scheduler_edf.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynascime <yannssouza@outlook.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/14 00:27:08 by ynascime          #+#    #+#             */
/*   Updated: 2026/09/14 02:36:38 by ynascime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static int	is_priority(t_memory *memory, t_coder *coder);

int	scheduler_edf(t_memory *memory, t_coder *coder)
{
	t_heap	*controler;

	controler = &memory->heap;
	pthread_mutex_lock(&controler->lock);
	heap_push(controler, coder);
	pthread_cond_broadcast(&controler->cond);
	pthread_mutex_unlock(&controler->lock);
	while (simulation(memory) == 1)
	{
		if (is_priority(memory, coder))
		{
			if (take_dongle(coder) == 0)
				break ;
		}
		usleep(500);
	}
	pthread_mutex_lock(&controler->lock);
	heap_pop(controler, coder);
	pthread_cond_broadcast(&controler->cond);
	pthread_mutex_unlock(&controler->lock);
	return (1);
}

static int	is_priority(t_memory *memory, t_coder *coder)
{
	int			i;
	int			e;
	long		time;

	i = (coder->id - 2 + memory->n_coders) % memory->n_coders;
	e = coder->id % memory->n_coders;
	time = check_burnout(coder);
	if (check_burnout(&memory->coder[i]) < time)
		return (0);
	if (check_burnout(&memory->coder[e]) < time)
		return (0);
	return (1);
}
