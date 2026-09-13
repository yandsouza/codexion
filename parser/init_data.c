/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynascime <yannssouza@outlook.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/12 20:06:25 by ynascime          #+#    #+#             */
/*   Updated: 2026/09/12 21:27:12 by ynascime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	sys_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	init_data(t_memory *memory)
{
	int	i;

	memory->start_time = sys_time();
	i = 0;
	while (i != memory->n_coders)
	{
		memory->coder[i].bournout_time = sys_time();
		memory->coder[i].n_comp = 0;
		memory->coder[i].finished = 0;
		memory->coder[i].dongle_a = NULL;
		memory->coder[i].dongle_b = NULL;
		i++;
	}
}
