/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svereten <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 16:06:16 by svereten          #+#    #+#             */
/*   Updated: 2024/04/17 17:51:00 by svereten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

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

char	*ft_strjoin(char *fd_buf, char *aux)
{
	char	*res;
	size_t	fd_buf_len;
	size_t	i;

	if (!aux)
		return (NULL);
	fd_buf_len = 0;
	if (fd_buf)
		fd_buf_len = ft_strlen(fd_buf);
	res = (char *)malloc((fd_buf_len + ft_strlen(aux) + 1) * sizeof(char));
	if (!res)
		return (free_fd_buf(&fd_buf), NULL);
	i = 0;
	while (fd_buf && fd_buf[i])
	{
		res[i] = fd_buf[i];
		i++;
	}
	while (aux[i - fd_buf_len])
	{
		res[i] = aux[i - fd_buf_len];
		i++;
	}
	res[i] = '\0';
	return (free_fd_buf(&fd_buf), res);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*res;
	unsigned int	new_len;
	unsigned int	i;
	size_t			s_len;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (start >= s_len)
		new_len = 0;
	else if (len > s_len - start)
		new_len = s_len - start;
	else
		new_len = len;
	res = (char *)malloc((new_len + 1) * sizeof(char));
	if (!res)
		return (NULL);
	i = start;
	while ((i < len + start) && s[i] && start < s_len)
	{
		res[i - start] = s[i];
		i++;
	}
	res[i - start] = '\0';
	return (res);
}
