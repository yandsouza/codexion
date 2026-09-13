/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynascime <yannssouza@outlook.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/12 12:29:16 by ynascime          #+#    #+#             */
/*   Updated: 2026/09/12 22:43:24 by ynascime         ###   ########.fr       */
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

typedef struct s_memory	t_memory;

typedef struct s_dongle
{
	long			cooldown;
}					t_dongle;

typedef struct s_coder
{
	pthread_t		thread_id;
	t_dongle		*dongle_a;
	t_dongle		*dongle_b;
	t_memory		*memory;
	int				id;
	int				n_comp;
	int				finished;
	long			bournout_time;
}					t_coder;

typedef struct s_memory
{
	t_coder			*coder;
	t_dongle		*dongle;
	char			*scheduler;
	int				n_coders;
	int				n_dongle;
	int				n_compiles_required;
	long			time_to_burnout;
	long			time_comp;
	long			time_debug;
	long			time_refactor;
	long			dongle_cooldown;
	long			start_time;
}					t_memory;

int		parser(t_memory *memory, char **argv);
int		argc_msg_error(void);
long	ms_time(void);
void	init_data(t_memory *memory);
void	start_threads(t_memory *memory);
void	join_threads(t_memory *memory);
void	*coder_thread(void *arg);

#endif
