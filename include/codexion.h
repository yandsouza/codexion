/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynascime <yannssouza@outlook.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/12 12:29:16 by ynascime          #+#    #+#             */
/*   Updated: 2026/09/13 22:43:34 by ynascime         ###   ########.fr       */
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

typedef struct s_memory		t_memory;
typedef struct s_coder		t_coder;

typedef struct s_node
{
	t_coder			*coder;
	struct s_node	*next;
}					t_node;

typedef struct s_fifo_list
{
	t_node			*first;
	t_node			*last;
	pthread_mutex_t	list_mutex;
	pthread_cond_t	cond;
}					t_fifo_list;

typedef struct s_dongle
{
	long			cooldown;
	pthread_mutex_t	dongle_mutex;
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
	t_fifo_list		fifo_list;
	char			*scheduler;
	int				sim_is_active;
	int				n_coders;
	int				n_dongle;
	int				n_compiles_required;
	long			time_to_burnout;
	long			time_comp;
	long			time_debug;
	long			time_refactor;
	long			dongle_cooldown;
	long			start_time;
	pthread_mutex_t	sim_mutex;
	pthread_mutex_t	print_mutex;
}					t_memory;

int		parser(t_memory *memory, char **argv);
int		argc_msg_error(void);
long	ms_time(void);
void	init_data(t_memory *memory);
void	start_threads(t_memory *memory);
void	join_threads(t_memory *memory);
void	*coder_thread(void *arg);
int		manage_dongles(t_memory *memory, t_coder *coder);
int		take_dongle(t_coder *coder);
void	release_dongles(t_memory *memory, t_coder *coder);
int		simulation(t_memory *memory);
int		scheduler_fifo(t_memory *memory, t_coder *coder);

#endif
