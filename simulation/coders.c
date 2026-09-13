/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coders.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynascime <yannssouza@outlook.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/12 18:46:24 by ynascime          #+#    #+#             */
/*   Updated: 2026/09/13 16:25:55 by ynascime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static void	print_task(int id, char *task, t_memory *memory)
{
	long	time;

	time = ms_time() - memory->start_time;
	printf("%li %i is %s\n", time, id, task);
	return ;
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
	return ;
}

void	*coder_thread(void *arg)
{
	t_coder	*coder;

	coder = (t_coder *)arg;
	while (!coder->finished)
	{
//		take_dongle(coder);
		task(coder, 'c');
//		release_dongle(coder);
		task(coder, 'd');
		task(coder, 'r');
	}
	return (NULL);
}
