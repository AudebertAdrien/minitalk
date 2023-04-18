/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaudeber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 13:51:05 by aaudeber          #+#    #+#             */
/*   Updated: 2023/04/18 17:44:41 by aaudeber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	send_bits(int pid, unsigned char c)
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
		printf("res %d\n", res);
		printf("i %d:\n", i);
		
		if (res)
		{
			printf("1");
			kill(pid, SIGUSR1);
		}
		else
		{
			printf("0");	
			kill(pid, SIGUSR2);
		}
		usleep(1000);
		printf("\n////////\n");	
		i++;
	}
}

int	main(int argc, char **argv)
{
	int	pid;

	if (argc == 2)
	{
		pid = atoi(argv[1]);
		printf("pid : %d\n", pid);
		send_bits(pid, 'a');
		usleep(1000);
		send_bits(pid, 8);
	}
	return (0);
}

/*
void	test_bits(unsigned char c)
{
	printf("test_bits :\n");	
	int n = 0;
	int a = 128;
	int b = 0;

	b = a | (1 << 0); 
	// a = 10000000 | 00001000 (= 10001000)
	//b |= (1 << 2);
	//b |= 16;
	send_bits(1, b);
}
*/
