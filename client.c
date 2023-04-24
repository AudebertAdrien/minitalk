/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaudeber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 13:51:05 by aaudeber          #+#    #+#             */
/*   Updated: 2023/04/24 18:39:36 by aaudeber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	send_len_bits(int pid, unsigned int c)
{
	int	mask;
	int	i;
	int	res;

	i = 0;
	res = 0;
	mask = 1;
	printf("len : %d\n", c);
	while (i < 32)
	{
		res = (c >> i) & mask;	
		printf("%d", res);
		if (res)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		usleep(2000);
		i++;
	}
	printf("\n");
}

/*
void	send_str_bits(int pid, unsigned int c)
{
	int	mask;
	int	i;
	int	res;

	i = 0;
	res = 0;
	mask = 1;
	printf("c = %c\n", c);
	while (i < 8)
	{
		res = (c >> i) & mask;	
		printf("%d\n", res);
		if (res)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		usleep(1000);
		i++;
	}
}
*/

int	main(int argc, char **argv)
{
	int		pid;
	char	*str;
	char	*str_len;
	int		i;
	int		len;

	i = 0;
	if (argc == 3)
	{
		printf("start\n");
		pid = ft_atoi(argv[1]);
		str = argv[2];
		len = ft_strlen(str);
		/*
		str_len = ft_itoa(len);
		while (str_len[i])
		{
			send_bits(pid, str[i]);
			i++;
		}
		*/
		send_len_bits(pid, len);
		/*
		while (str[i])
		{
			send_str_bits(pid, str[i]);
			i++;
		}
		*/
	}
	else
		printf("error : number of args\n");
	return (0);
}
