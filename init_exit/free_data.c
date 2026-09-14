/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynascime <yannssouza@outlook.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/14 02:40:38 by ynascime          #+#    #+#             */
/*   Updated: 2026/09/14 03:00:23 by ynascime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	destroy_mutex(t_memory *memory)
{
	int	i;

	i = 0;
	while (i != memory->n_coders)
	{
		pthread_mutex_destroy(&memory->dongle[i].dongle_mutex);
		pthread_mutex_destroy(&memory->coder[i].burnout_mutex);
		pthread_mutex_destroy(&memory->coder[i].finish_mutex);
		i++;
	}
	pthread_mutex_destroy(&memory->print_mutex);
	pthread_mutex_destroy(&memory->sim_mutex);
	pthread_mutex_destroy(&memory->fifo_list.list_mutex);
	pthread_mutex_destroy(&memory->heap.lock);
	pthread_cond_destroy(&memory->fifo_list.cond);
	pthread_cond_destroy(&memory->heap.cond);
}

void	free_data(t_memory *memory)
{
	t_node	*node;
	t_node	*next;

	node = memory->fifo_list.first;
	if (memory->coder != NULL)
		free(memory->coder);
	if (memory->dongle != NULL)
		free(memory->dongle);
	while (node != NULL)
	{
		next = node->next;
		free(node);
		node = next;
	}
}
