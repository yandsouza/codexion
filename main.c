/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynascime <yannssouza@outlook.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/12 12:25:56 by ynascime          #+#    #+#             */
/*   Updated: 2026/09/14 02:52:00 by ynascime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	main(int argc, char **argv)
{
	t_memory	memory;

	if (argc != 9)
	{
		free_data(&memory);
		return (argc_msg_error());
	}
	if (!parser(&memory, argv))
	{
		free_data(&memory);
		return (1);
	}
	init_data(&memory);
	start_threads(&memory);
	join_threads(&memory);
	free_data(&memory);
	return (0);
}
