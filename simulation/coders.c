/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coders.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynascime <yannssouza@outlook.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/12 18:46:24 by ynascime          #+#    #+#             */
/*   Updated: 2026/09/12 22:55:32 by ynascime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	*coder_thread(void *arg)
{
	t_coder	*coder;
	long	time;

	coder = (t_coder *)arg;
	while (!coder->finished)
	{
		usleep(coder->memory->time_comp * 1000);
		coder->n_comp += 1;
		time = ms_time() - coder->memory->start_time;
		printf("Coder %i compiled the %i time in %li\n",
			coder->id, coder->n_comp, time);
		if (coder->n_comp == coder->memory->n_compiles_required)
			coder->finished = 1;
	}
	return (NULL);
}
