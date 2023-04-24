/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaudeber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 13:51:05 by aaudeber          #+#    #+#             */
/*   Updated: 2023/04/24 18:34:59 by aaudeber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

volatile int	bit_nb = 0;
volatile int	sys_call = 0;

int	get_str_len(int signal)
{
	static int	c = 0;

	if (signal == SIGUSR1)
		c |= (1 << bit_nb);
	if (signal == SIGUSR2)
		c &= ~(1 << bit_nb);
	bit_nb += 1;
	if (bit_nb == 32)
	{
		printf("\n====\n");
		ft_putnbr_fd(c, 1);
		printf("\n====\n");
		bit_nb = 0;
		//c = 0;
		sys_call = 0;
		return (0);
	}
	sys_call += 1;
	return (0);
}

void	sigint_handler(int signal)
{
	static char	c = 0;

	if (sys_call < 32)
	{
		printf("sys_call :%d\n", sys_call);
		get_str_len(signal);
	}
	/*
	else
	{
		printf("else");
		if (signal == SIGUSR1)
			c |= (1 << bit_nb);
		if (signal == SIGUSR2)
			c &= ~(1 << bit_nb);
		bit_nb += 1;
		if (bit_nb == 8)
		{
			printf("\n====\n");
			write(1, &c, 1);
			printf("\n====\n");
			bit_nb = 0;
			c = 0;
		}
	}
	*/
}

void	set_signal_action()
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
