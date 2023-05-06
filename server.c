/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaudeber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 13:51:05 by aaudeber          #+#    #+#             */
/*   Updated: 2023/05/06 17:42:52 by aaudeber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	send_signal_back(int signal, siginfo_t *info)
{
	if (signal == SIGUSR1)
		kill(info->si_pid, SIGUSR1);
	if (signal == SIGUSR2)
		kill(info->si_pid, SIGUSR2);
}

int	get_char(siginfo_t *info, int signal, int *c, int bits_nb)
{
	static int	bit_nb = 0;

	if (signal == SIGUSR1)
		*c |= (1 << bit_nb);
	bit_nb += 1;
	send_signal_back(SIGUSR1, info);
	if (bit_nb == bits_nb)
	{
		bit_nb = 0;
		c = 0;
		return (1);
	}
	return (0);
}

void	end_communication(char **str, siginfo_t *info)
{
	send_signal_back(SIGUSR2, info);
	ft_putstr_fd("\nFrom : ", 1);
	ft_putnbr_fd(info->si_pid, 1);
	ft_putstr_fd("\n============\n", 1);
	ft_putstr_fd(*str, 1);
	ft_putstr_fd("\n============\n", 1);
	ft_bzero(*str, ft_strlen(*str));
	free(*str);
	*str = NULL;
}

void	sigint_handler(int signal, siginfo_t *info, void *ucontext)
{
	static int		c = 0;
	static char		*str;
	int				process_signal;

	(void)ucontext;
	if (!str)
		str = ft_calloc(1, sizeof(char));
	process_signal = get_char(info, signal, &c, 8);
	if (process_signal)
	{
		if (c == '\0')
			end_communication(&str, info);
		else
			str = ft_free_join(str, c);
		c = 0;
	}
}

int	main(void)
{
	struct sigaction	act;

	ft_putnbr_fd(getpid(), 1);
	ft_putstr_fd("\nServer started :\n", 1);
	ft_bzero(&act, sizeof(act));
	act.sa_flags = SA_SIGINFO;
	act.sa_sigaction = &sigint_handler;
	sigaction(SIGUSR1, &act, NULL);
	sigaction(SIGUSR2, &act, NULL);
	sleep(1);
	while (1)
		sleep(1);
	return (0);
}
