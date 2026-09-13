/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynascime <yannssouza@outlook.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/12 20:06:25 by ynascime          #+#    #+#             */
/*   Updated: 2026/09/12 22:46:37 by ynascime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

long	ms_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	init_data(t_memory *memory)
{
	int	i;

	memory->start_time = ms_time();
	i = 0;
	while (i != memory->n_coders)
	{
		memory->coder[i].bournout_time = ms_time();
		memory->coder[i].id = i + 1;
		memory->coder[i].n_comp = 0;
		memory->coder[i].finished = 0;
		memory->coder[i].dongle_a = NULL;
		memory->coder[i].dongle_b = NULL;
		memory->coder[i].memory = memory;
		i++;
	}
}
