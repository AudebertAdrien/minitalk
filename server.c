/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaudeber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 13:51:05 by aaudeber          #+#    #+#             */
/*   Updated: 2023/04/26 14:45:23 by aaudeber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	bits_to_int(int signal, int *x, int byte)
{
	static int	bit_nb = 0;

	if (signal == SIGUSR1)
		*x |= (1 << bit_nb);
	if (signal == SIGUSR2)
		*x &= ~(1 << bit_nb);
	bit_nb += 1;
	if (bit_nb == byte)
	{
		if (byte == 32)
			printf("byte 32 : %d\n", *x);
		if (byte == 8)
			printf("byte 8 : %d\n", *x);

		bit_nb = 0;
	}
}

void	sigint_handler(int signal)
{
	static char	*str;
	static int	len = 0;
	static int	sys_call = 0;
	static int	i = 0;
	static int	c = 0;

	if (sys_call < 32)
		bits_to_int(signal, &len, 32);

	if (sys_call == 32)
	{
		str = ft_calloc((len + 1),sizeof(char));
		printf("len : %d\n",len);
		printf("sizeof : %ld\n", sizeof(str));
	}
	
	if (sys_call > 32)
	{
		bits_to_int(signal, &c, 8);
		if (sys_call == (32 + len))
		{
			printf("END!!!! %d\n", 32 + len);
			sys_call = 0;
			len = 0;
			c = 0;
			len = 0;
			str = NULL;
			free(str);
		}
	}

	sys_call += 1;
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
