/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaudeber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 16:25:04 by aaudeber          #+#    #+#             */
/*   Updated: 2023/02/12 17:41:15 by aaudeber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
	The  bzero()  function  erases the data in the n bytes of the memory 
	starting at the location pointed to by s,
	by writing zeros (bytes containing '\0') to that area.	
*/

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*src_cpy;

	src_cpy = (unsigned char *)s;
	while (n--)
		*src_cpy++ = '\0';
}
