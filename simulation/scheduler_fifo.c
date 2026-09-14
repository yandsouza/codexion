/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scheduler_fifo.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynascime <yannssouza@outlook.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/13 20:44:35 by ynascime          #+#    #+#             */
/*   Updated: 2026/09/13 22:26:04 by ynascime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static int	fifo_append_coder(t_memory *memory, t_coder *coder);
static int	append_list(t_fifo_list *list, t_coder *coder);
static int	pop_list(t_fifo_list *list);

int	scheduler_fifo(t_memory *memory, t_coder *coder)
{
	int	result;

	pthread_mutex_lock(&memory->fifo_list.list_mutex);
	result = fifo_append_coder(memory, coder);
	pthread_mutex_unlock(&memory->fifo_list.list_mutex);
	return (result);
}

static int	fifo_append_coder(t_memory *memory, t_coder *coder)
{
	int	acquired;

	append_list(&memory->fifo_list, coder);
	while (simulation(memory) == 1
		&& (memory->fifo_list.first->coder != coder
			|| take_dongle(coder) == 1))
	{
		if (simulation(memory) == 1
			&& memory->fifo_list.first->coder == coder)
		{
			pthread_mutex_unlock(&memory->fifo_list.list_mutex);
			usleep(1000);
			pthread_mutex_lock(&memory->fifo_list.list_mutex);
		}
		else
			pthread_cond_wait(&memory->fifo_list.cond,
				&memory->fifo_list.list_mutex);
	}
	acquired = 0;
	if (simulation(memory) == 1)
	{
		acquired = 1;
		pop_list(&memory->fifo_list);
		pthread_cond_broadcast(&memory->fifo_list.cond);
	}
	return (acquired);
}

static int	append_list(t_fifo_list *list, t_coder *coder)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	if (node == NULL)
		return (1);
	node->coder = coder;
	node->next = NULL;
	if (list->first == NULL)
	{
		list->first = node;
		list->last = node;
	}
	else
	{
		list->last->next = node;
		list->last = node;
	}
	return (0);
}

static int	pop_list(t_fifo_list *list)
{
	t_node	*temp;

	if (list->first == NULL)
		return (1);
	temp = list->first;
	list->first = temp->next;
	if (list->first == NULL)
		list->last = NULL;
	free (temp);
	return (0);
}
