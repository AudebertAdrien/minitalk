/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaudeber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 13:51:05 by aaudeber          #+#    #+#             */
/*   Updated: 2023/04/18 17:44:57 by aaudeber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

volatile int	bit_nb = 0;

int	print_bits(unsigned char c) {
	printf("print_bits\n");
	int	mask;
	int	i;
	int	res;

	i = 0;
	res = 0;
	mask = 128;
	while (i < 8)
	{
		res = (c << i) & mask;	
		if (res)
			printf("1");
		else
			printf("0");	
		i++;
	}
	printf("\n/////////\n");	
}

void	sigint_handler(int signal)
{
	static char	c;
	
	if (!c)
		c = 0;	

	printf("bit_nb : %d", bit_nb);
	if (signal == SIGUSR1)
	{
		c = c | (128 >> bit_nb);
		printf("1");
	}
	if (signal == SIGUSR2)
	{
		//c = c & ~(1 << bit_nb);
		printf("0");
	} 
	printf("\n");
	bit_nb += 1;

	if (bit_nb == 8)
	{
		printf("\n////////\n");
		print_bits(c);
		printf("c = %c\n", c);
		bit_nb = 0;
		c = 0;
	}
}

void	set_signal_action(void)
{
	printf("set_signal_action\n"); 

	struct	sigaction act;
	int	res;
	
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
