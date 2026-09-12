/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynascime <yannssouza@outlook.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/12 12:29:16 by ynascime          #+#    #+#             */
/*   Updated: 2026/09/12 20:05:01 by ynascime         ###   ########.fr       */
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
	pthread_t		thread_id;
}					t_coder;

typedef struct s_dongle
{
	int				cooldown;
}					t_dongle;

typedef struct s_memory
{
	t_coder			*coder;
	t_dongle		*dongle;
	int				n_coders;
	int				n_dongle;
	int				time_to_burnout;
	int				time_comp;
	int				time_debug;
	int				time_refactor;
	int				n_compiles_required;
	int				dongle_cooldown;
	char			*scheduler;
}					t_memory;

int		parser(t_memory *memory, char **argv);
int		argc_msg_error(void);
void	init_data(t_memory *memory);
void	start_threads(t_memory *memory);
void	join_threads(t_memory *memory);
void	*coder_thread(void *arg);

#endif
