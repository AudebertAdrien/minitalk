/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaudeber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 17:11:59 by aaudeber          #+#    #+#             */
/*   Updated: 2023/05/06 17:46:58 by aaudeber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

char	*ft_join_char(char const *s1, char const c)
{
	int		i;
	char	*ptr;

	i = 0;
	if (!s1 || !c)
		return (NULL);
	ptr = (char *)ft_calloc((ft_strlen(s1) + 2), sizeof(char));
	if (!ptr)
		return (NULL);
	while (s1[i])
	{
		ptr[i] = s1[i];
		i++;
	}
	if (c)
	{
		ptr[i] = c;
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

char	*ft_free_join(char *str, char c)
{
	char	*tmp;

	tmp = ft_join_char(str, c);
	free(str);
	return (tmp);
}
