/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlinarez <jlinarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 11:10:19 by jlinarez          #+#    #+#             */
/*   Updated: 2024/08/12 12:45:06 by jlinarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen12(char *s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strchr12(char *s, int c)
{
	unsigned int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
			return ((char *)&s[i]);
		i++;
	}
	if ((char)c == s[i])
		return ((char *)&s[i]);
	return (NULL);
}

void	*ft_calloc12(size_t count, size_t size)
{
	char	*mem;
	size_t	i;

	i = 0;
	mem = malloc(count * size);
	if (!mem)
		return (0);
	while (i < size * count)
	{
		mem[i] = 0;
		i++;
	}
	return (mem);
}

char	*ft_strjoin12(char *s1, char *s2)
{
	char	*new;
	size_t	i;
	size_t	j;
	size_t	len_s1;
	size_t	len_s2;

	len_s1 = ft_strlen12(s1);
	len_s2 = ft_strlen12(s2);
	new = ft_calloc12((len_s1 + len_s2 + 1), sizeof(char));
	i = 0;
	j = 0;
	if (new == NULL)
		return (NULL);
	while (i < len_s1)
	{
		new[i] = s1[i];
		i++;
	}
	while (j < len_s2)
	{
		new[i + j] = s2[j];
		j++;
	}
	free(s1);
	return (new);
}
