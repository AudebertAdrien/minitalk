/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaudeber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 13:51:05 by aaudeber          #+#    #+#             */
/*   Updated: 2023/05/05 17:44:49 by aaudeber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	g_received = 1;

void send_bits(int pid, unsigned int c, int byte)
{
	int	i;
	int	res;
	int	mask;
	int	err;

	i = 0;
	res = 0;
	mask = 1;
	while (i < byte)
	{
		res = (c >> i) & mask;	
		if (res)
			err = kill(pid, SIGUSR1);
		else
			err = kill(pid, SIGUSR2);
		if (err == -1)
			exit(0);
		while(g_received)
			continue ;
		g_received = 1;
		i++;
	}
}

void	siginfo_handler(int	signal, siginfo_t *info, void *ucontext)
{
	(void)info;
	(void)ucontext;
	if (signal == SIGUSR1)
		g_received = 0;
	if (signal == SIGUSR2)
		ft_putstr_fd("Message sent\n", 1);
}

int	main(int argc, char **argv)
{
	int		pid;
	int		i;
	char	*str;
	struct	sigaction act;

	ft_bzero(&act, sizeof(act));
	act.sa_flags = SA_SIGINFO;
	act.sa_sigaction = &siginfo_handler;
	sigaction(SIGUSR1, &act, NULL);
	sigaction(SIGUSR2, &act, NULL);

	i = 0;
	if (argc == 3)
	{
		ft_putstr_fd("Client Stated:", 1);
		write(1, "\n", 1);
		pid = ft_atoi(argv[1]);
		str = argv[2];
		while (str[i])
		{
			send_bits(pid, str[i], 8);
			usleep(100);
			i++;
		}
		send_bits(pid, '\0', 8);
	}
	else
	{
		ft_putstr_fd("error : number of args", 2);
		write(1, "\n", 1);
	}
	return (0);
}
