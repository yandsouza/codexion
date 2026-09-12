/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_threads.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynascime <yannssouza@outlook.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/12 18:32:21 by ynascime          #+#    #+#             */
/*   Updated: 2026/09/12 19:16:39 by ynascime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	start_threads(t_memory *memory)
{
	int	i;

	i = 0;
	while (i != memory->n_coders)
	{
		pthread_create(&memory->coder[i].thread_id,
			NULL, coder_thread, &memory->coder[i]);
		i++;
	}
}

void	join_threads(t_memory *memory)
{
	int	i;

	i = 0;
	while (i != memory->n_coders)
		pthread_join(memory->coder[i++].thread_id, NULL);
}
