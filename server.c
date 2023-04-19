/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaudeber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 13:51:05 by aaudeber          #+#    #+#             */
/*   Updated: 2023/04/19 15:43:02 by aaudeber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

volatile int	bit_nb = 0;

void	sigint_handler(int signal)
{
	static char	c;
	
	if (!c)
		c = 0;	
	if (signal == SIGUSR1)
		c = c | (128 >> bit_nb);
	if (signal == SIGUSR2)
		c = c & ~(128 >> bit_nb);
	bit_nb += 1;
	printf("\n");
	if (bit_nb == 8)
	{
		printf("%c", c);
		bit_nb = 0;
		c = 0;
	}
}

void	set_signal_action(void)
{
	struct	sigaction act;
	
	bzero(&act , sizeof(act));
	act.sa_handler = &sigint_handler;
	sigaction(SIGUSR1, &act, NULL);
	sigaction(SIGUSR2, &act, NULL);
}

int	main(void)
{
	printf("getpid : %d\n", getpid());
	set_signal_action();
	while (1)
	{
		sleep(1);
	}
	return (0);
}
