/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaudeber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 16:35:22 by aaudeber          #+#    #+#             */
/*   Updated: 2023/02/17 16:11:22 by aaudeber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
	The calloc() function allocates memory for an array of nmemb elements of
	size bytes each and returns a pointer to the allocated memory.  
	The memory is set to zero.  If nmemb or size is 0, then calloc() returns
	either NULL, or a unique  pointer  value  that can later be successfully 
	passed to free().  If the multiplication of nmemb and size
       	would result in integer overflow, then calloc() returns an error.	
*/

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;

	if (!nmemb || !size)
		return (malloc(0));
	if (nmemb * size / size != nmemb)
		return (NULL);
	ptr = (void *)malloc(nmemb * size);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, nmemb * size);
	return (ptr);
}
