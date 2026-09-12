/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynascime <yannssouza@outlook.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/12 12:25:56 by ynascime          #+#    #+#             */
/*   Updated: 2026/09/12 17:12:43 by ynascime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	main(int argc, char **argv)
{
	t_memory	memory;

	if (argc != 9)
		return (argc_msg_error());
	if (!parser(&memory, argv))
		return (1);
	printf("Numbers of coders: %i\n", memory.n_coders);
	printf("Number of dongles: %i\n", memory.n_dongle);
	printf("Time to burnout: %is\n", memory.time_to_burnout);
	printf("Time to compile: %is\n", memory.time_comp);
	printf("Time to debug: %ims\n", memory.time_debug);
	printf("Time to refactor: %ims\n", memory.time_refactor);
	printf("Number of compiles required: %i\n", memory.n_compiles_required);
	printf("Dongle cooldown: %ims\n", memory.dongle_cooldown);
	printf("Scheduler: %s\n", memory.scheduler);
	return (0);
}
