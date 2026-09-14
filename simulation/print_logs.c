/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_logs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynascime <yannssouza@outlook.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/14 01:22:20 by ynascime          #+#    #+#             */
/*   Updated: 2026/09/14 01:28:08 by ynascime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	print_task(int id, char *task, t_memory *memory)
{
	long	time;

	pthread_mutex_lock(&memory->print_mutex);
	time = ms_time() - memory->start_time;
	printf("%li %i is %s\n", time, id, task);
	pthread_mutex_unlock(&memory->print_mutex);
}

void	print_dongle(int id, t_memory *memory)
{
	long	time;

	pthread_mutex_lock(&memory->print_mutex);
	time = ms_time() - memory->start_time;
	printf("%li %i has taken a dongle\n", time, id);
	pthread_mutex_unlock(&memory->print_mutex);
}

void	print_burnout(int id, t_memory *memory)
{
	long	time;

	pthread_mutex_lock(&memory->print_mutex);
	time = ms_time() - memory->start_time;
	printf("%li %i burned out\n", time, id);
	pthread_mutex_unlock(&memory->print_mutex);
}
