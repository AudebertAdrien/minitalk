/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaudeber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 13:51:05 by aaudeber          #+#    #+#             */
/*   Updated: 2023/04/13 13:59:24 by aaudeber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void	handler(int theSignal)
{
	printf("signal %d\n", theSignal);
	fflush(stdout);
}

int	main(void)
{
	struct	sigaction prepaSignal;
	
	printf("getpid : %d\n", getpid());
	prepaSignal.sa_handler = &handler;
	prepaSignal.sa_flags = 0;
	sigemptyset(&prepaSignal.sa_mask);
	sigaction(SIGINT, &prepaSignal, 0);
	sigaction(SIGQUIT, &prepaSignal, 0);
	sigaction(SIGTERM, &prepaSignal, 0);

	while (1) ;

	return (0);
}
