/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynascime <yannssouza@outlook.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/12 12:25:56 by ynascime          #+#    #+#             */
/*   Updated: 2026/09/12 22:45:43 by ynascime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	print_memory(t_memory *memory)
{
	int	i;

	printf("Numbers of coders: %i\n", memory->n_coders);
	printf("Number of dongles: %i\n", memory->n_dongle);
	printf("Time to burnout: %lis\n", memory->time_to_burnout);
	printf("Time to compile: %lis\n", memory->time_comp);
	printf("Time to debug: %lims\n", memory->time_debug);
	printf("Time to refactor: %lims\n", memory->time_refactor);
	printf("Number of compiles required: %i\n", memory->n_compiles_required);
	printf("Dongle cooldown: %lims\n", memory->dongle_cooldown);
	printf("Scheduler: %s\n", memory->scheduler);
	printf("\n===Coders===\n");
	i = 0;
	while (memory->n_coders != i)
	{
		printf("Coder: %ld\n", memory->coder[i].thread_id);
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_memory	memory;

	if (argc != 9)
		return (argc_msg_error());
	if (!parser(&memory, argv))
		return (1);
	init_data(&memory);
	start_threads(&memory);
	print_memory(&memory);
	join_threads(&memory);
	return (0);
}
