/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynascime <yannssouza@outlook.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/12 12:25:56 by ynascime          #+#    #+#             */
/*   Updated: 2026/09/12 12:44:56 by ynascime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	main(int argc, char **argv)
{
	t_memory	memory;

	if (argc != 9)
		return (1);
	if (argv)
		return (0);
	memset(&memory, 0, sizeof(t_memory));
	return (0);
}
