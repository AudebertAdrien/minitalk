/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaudeber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 13:51:05 by aaudeber          #+#    #+#             */
/*   Updated: 2023/04/25 19:28:34 by aaudeber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

volatile int	sys_call = 0;

int	get_str_len(int signal)
{
	static int	x = 0;
	static int	bit_nb = 0;

	if (signal == SIGUSR1)
		x |= (1 << bit_nb);
	if (signal == SIGUSR2)
		x &= ~(1 << bit_nb);
	bit_nb += 1;
	if (bit_nb == 32)
	{
		ft_putnbr_fd(x, 1);
		printf("\n");
		bit_nb = 0;
	}
	sys_call += 1;
	return (x);
}

char	get_char(int signal)
{
	static char	c = 0;
	static int	bit_nb = 0;

	if (signal == SIGUSR1)
		c |= (1 << bit_nb);
	if (signal == SIGUSR2)
		c &= ~(1 << bit_nb);
	bit_nb += 1;
	if (bit_nb == 8)
	{
		bit_nb = 0;
		c = 0;
		return (c);
	}
}

void	sigint_handler(int signal)
{
	static char	*str;
	static int	len = 0;
	char	c;

	if (sys_call == 32)
	{
		str = malloc(sizeof(char) * len + 1);
		ft_bzero(str, len);
	}	
	if (sys_call < 32)
		len = get_str_len(signal);
	else
	{
		c = get_char(signal);
		if (c)
		{
			printf("\nccc = %c\n", c);
			str[sys_call - 32] = c;
		}
		sys_call += 1;

		if (sys_call == 32 + len)
		{
			printf("=>\n");
			ft_putstr_fd(str, 1);
			printf("\n");
		}
	}
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
