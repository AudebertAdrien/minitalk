/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaudeber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 13:51:05 by aaudeber          #+#    #+#             */
/*   Updated: 2023/04/15 19:22:50 by aaudeber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <unistd.h>
#include <signal.h>

volatile int	g_unblock_sigquit = 0;

void	block_signal(int signal)
{
	printf("block_signal %d\n", signal);
	sigset_t sigset;

	sigemptyset(&sigset);

	sigaddset(&sigset, signal);

	sigprocmask(SIG_BLOCK, &sigset, NULL);
	if (signal == SIGQUIT)
		printf("\e[36mSIGQUIT (ctrl-\\) blocked.\e[0m\n");
}

void	unblock_signal(int signal)
{
	printf("unblock_signal %d\n", signal);
	sigset_t	sigset;

	sigemptyset(&sigset);

	sigaddset(&sigset, signal);

	sigprocmask(SIG_UNBLOCK, &sigset, NULL);
	if (signal == SIGQUIT)
		printf("\e[36mSIGQUIT (ctrl-\\) unblocked.\e[0m\n");
}

void	sigint_handler(int signal)
{
	printf("handler\n");
	printf("Signal : %d\n", signal);
	if (signal != SIGINT)
		return ;
	block_signal(SIGINT);
	g_unblock_sigquit = 1;
	unblock_signal(SIGINT);
}

void	set_signal_action(void)
{
	struct	sigaction act;
	
	bzero(&act , sizeof(act));
	
	act.sa_handler = &sigint_handler;

	sigaction(SIGINT, &act, NULL);
}

int	main(void)
{
	printf("getpid : %d\n", getpid());

	set_signal_action();

	block_signal(SIGQUIT);

	while (1)
	{
		block_signal(SIGINT);
		printf("g_var : %d\n", g_unblock_sigquit);
			
		if (g_unblock_sigquit == 1)
		{
			printf("\n\e[36mSIGQUIT detected. Unblocking SIGQUIT\e[0m\n");
			unblock_signal(SIGINT);
			unblock_signal(SIGQUIT);
			printf("////\n");
		}
		else
			unblock_signal(SIGINT);
		sleep(1);
	}
	return (0);
}
