/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynascime <yannssouza@outlook.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/12 12:57:21 by ynascime          #+#    #+#             */
/*   Updated: 2026/09/12 17:15:50 by ynascime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static int	store_memory(t_memory *memory, int *argv)
{
	memory->coder = malloc(sizeof(t_coder) * argv[0]);
	memory->dongle = malloc(sizeof(t_dongle) * argv[0]);
	if (!memory->coder || !memory->dongle)
	{
		fprintf(stderr, "MALLOC ERROR\n");
		return (1);
	}
	memory->n_coders = argv[0];
	memory->n_dongle = argv[0];
	memory->time_to_burnout = argv[1];
	memory->time_comp = argv[2];
	memory->time_debug = argv[3];
	memory->time_refactor = argv[4];
	memory->n_compiles_required = argv[5];
	memory->dongle_cooldown = argv[6];
	return (1);
}

int	parser(t_memory *memory, char **argv)
{
	int	converted_argv[8];
	int	i;

	i = 0;
	while (i <= 6)
	{
		converted_argv[i] = atoi(argv[i + 1]);
		if (converted_argv[i] <= 0)
		{
			fprintf(stderr, "INPUT ERROR: argument must be a unsigned int\n");
			return (0);
		}
		i++;
	}
	memset(memory, 0, sizeof(t_memory));
	if (!store_memory(memory, converted_argv))
		return (0);
	if (strcmp(argv[8], "fifo") != 0 && strcmp(argv[8], "edf") != 0)
	{
		fprintf(stderr, "INPUT ERROR: scheduler must be fifo or edf\n");
		return (0);
	}
	else
		memory->scheduler = argv[8];
	return (1);
}

int argc_msg_error(void)
{
		fprintf(stderr, "Valid usage: ./codexion" 
			" <number_of_coders>"
			" <time_to_burnout> <time_to_compile>"
			" <time_to_debug> <time_to_refactor>"
			" <number_of_compiles_required>"
			" <dongle_cooldown> <scheduler>\n");
		return (1);
}
