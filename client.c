/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaudeber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 13:51:05 by aaudeber          #+#    #+#             */
/*   Updated: 2023/04/23 19:22:05 by aaudeber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	send_bits(int pid, unsigned char c)
{
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
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		usleep(1000);
		i++;
	}
}

int	main(int argc, char **argv)
{
	int		pid;
	char	*str;
	int		i;

	i = 0;
	if (argc == 3)
	{
		printf("start\n");
		pid = atoi(argv[1]);
		str = argv[2];
		while (str[i])
		{
			send_bits(pid, str[i]);
			//usleep(500);
			i++;
		}
	}
	else
		printf("error : number of args\n");
	return (0);
}
