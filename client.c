/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaudeber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 13:51:05 by aaudeber          #+#    #+#             */
/*   Updated: 2023/04/26 17:27:23 by aaudeber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void send_bits(int pid, unsigned int c, int byte)
{
	int	i;
	int	res;
	int	mask;

	i = 0;
	res = 0;
	mask = 1;
	while (i < byte)
	{
		res = (c >> i) & mask;	
		printf("%d", res);
		if (res)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		usleep(1000);
		i++;
	}
	printf("\n");
}

int	main(int argc, char **argv)
{
	int		pid;
	int		i;
	int		len;
	char	*str;

	i = 0;
	if (argc == 3)
	{
		printf("start\n");
		pid = ft_atoi(argv[1]);
		str = argv[2];
		len = ft_strlen(str);
		//send_bits(pid, len, 32);
		while (str[i])
		{
			send_bits(pid, str[i], 8);
			i++;
		}
		send_bits(pid, '\0', 8);
	}
	else
		printf("error : number of args\n");
	return (0);
}
