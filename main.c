/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynascime <yannssouza@outlook.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/12 12:25:56 by ynascime          #+#    #+#             */
/*   Updated: 2026/09/12 15:28:53 by ynascime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	main(int argc, char **argv)
{
	t_memory	memory;

	if (argc != 9)
	{
		fprintf(stderr, "Valid usage: ./codexion <number_of_coders>"
			" <time_to_burnout> <time_to_compile>"
			" <time_to_debug> <time_to_refactor>"
			" <number_of_compiles_required>"
			" <dongle_cooldown> <scheduler>\n");
		return (1);
	}
	if (!parser(&memory, argv))
		return (1);
	printf("ok\n");
	return (0);
}
