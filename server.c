/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaudeber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 13:51:05 by aaudeber          #+#    #+#             */
/*   Updated: 2023/04/26 17:31:12 by aaudeber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	get_char(int signal, int *c, int bits_nb)
{
	static int	bit_nb = 0;

	if (signal == SIGUSR1)
		*c |= (1 << bit_nb);
	if (signal == SIGUSR2)
		*c &= ~(1 << bit_nb);
	bit_nb += 1;
	if (bit_nb == bits_nb)
	{
		bit_nb = 0;
		return (1);
	}
	return (0);
}

void	sigint_handler(int signal)
{
	static int c = 0;
	static char *str;

	if (!str)
		str = ft_calloc(100, sizeof(char));
	if(get_char(signal, &c, 8))
	{
		if (c == '\0')
		{
			printf("sizeof(*str) :%ld\n", sizeof(*str));
			printf("sizeof(str) :%ld\n", sizeof(str));
			ft_bzero(str, ft_strlen(str));
			free(str);
		}
		else
		{
			str = ft_free_join(str, c); 
			ft_putstr_fd(str, 1);
			printf("\n");
		}
		c = 0;
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
