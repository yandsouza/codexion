/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynascime <yannssouza@outlook.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/12 12:29:16 by ynascime          #+#    #+#             */
/*   Updated: 2026/09/12 12:36:51 by ynascime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_H
# define CODEXION_H

# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_coder
{
	int				id;
}					t_coder;

typedef struct s_dongle
{
	int				cooldown;
}					t_dongle;

typedef struct s_memory
{
	t_coder			*coder;
	t_dongle		*dongle;
}					t_memory;

#endif
