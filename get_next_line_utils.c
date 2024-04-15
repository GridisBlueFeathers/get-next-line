/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svereten <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 16:06:16 by svereten          #+#    #+#             */
/*   Updated: 2024/04/15 19:33:46 by svereten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strchr(const char *s, int c)
{
	int		i;

	i = 0;
	if (!s)
		return (NULL);
	while (s[i] && s[i] != (unsigned char)c)
		i++;
	if (!s[i] && (unsigned char)c)
		return (NULL);
	return (&((char *)s)[i]);
}

char	*ft_strjoin(char *buf, char const *aux)
{
	char	*res;
	size_t	len;
	size_t	buf_len;
	size_t	i;

	if (!buf && !aux)
		return (NULL);
	buf_len = ft_strlen(buf);
	len = buf_len + ft_strlen(aux);
	res = (char *)malloc(len + 1);
	if (!res)
		return (NULL);
	i = 0;
	while (buf && buf[i])
	{
		res[i] = buf[i];
		i++;
	}
	while (aux[i - buf_len])
	{
		res[i] = aux[i - buf_len];
		i++;
	}
	res[i] = '\0';
	return (res);
}
