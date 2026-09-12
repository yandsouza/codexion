/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynascime <yannssouza@outlook.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/12 12:25:56 by ynascime          #+#    #+#             */
/*   Updated: 2026/09/12 14:57:16 by ynascime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	main(int argc, char **argv)
{
	t_memory	memory;

	if (argc != 9)
		return (1);
	memset(&memory, 0, sizeof(t_memory));
	if (!parser(&memory, argv))
		return (1);
	printf("ok");
	return (0);
}
