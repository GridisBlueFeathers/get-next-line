/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svereten <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 13:25:04 by svereten          #+#    #+#             */
/*   Updated: 2024/04/15 20:08:32 by svereten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"

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
	res = (char *)malloc(new_len + 1);
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

char	*get_next_line_from_fd_buf(char *buf)
{
	size_t	len;
	char	*res;

	if (!buf)
		return (NULL);
	len = 0;
	while (buf[len] && buf[len] != '\n')
		len++;
	if (!buf[len])
		return (NULL);
	res = ft_substr(buf, 0, len);
	return (res);
}

char	*trim_fd_buf(char *buf)
{
	size_t	len;
	size_t	start;
	char	*res;

	if (!buf)
		return (NULL);
	len = 0;
	while (buf[len] && buf[len] != '\n')
		len++;
	if (buf[len])
		len++;
	start = len;
	while (buf[len])
		len++;
	res = ft_substr(buf, start, len - start + 1);
	return (res);
}

char	*get_next_line(int fd)
{
	static char	*fd_buf;
	char		*aux_buf;
	int			bytes_read;

	if (fd < 0 || BUFFER_SIZE < 0)
		return (NULL);
	aux_buf = (char *)malloc(BUFFER_SIZE + 1);
	if (!aux_buf)
		return (NULL);
	bytes_read = 1;
	while (!ft_strchr(fd_buf, '\n') && bytes_read)
	{
		bytes_read = read(fd, aux_buf, BUFFER_SIZE);
		if (bytes_read == -1)
			return (free(aux_buf), NULL);
		aux_buf[BUFFER_SIZE] = '\0';
		fd_buf = ft_strjoin(fd_buf, aux_buf);
	}
	free(aux_buf);
	aux_buf = get_next_line_from_fd_buf(fd_buf);
	if (!aux_buf)
		return (NULL);
	//printf("yo %s", fd_buf);
	fd_buf = trim_fd_buf(fd_buf);
	if (!fd_buf)
		return (NULL);
	return (aux_buf);
}

/*#include <fcntl.h>
int main()
{
	char *res;
	int fd = open("./file_to_read", O_RDONLY);
	res = get_next_line(fd);
	while (res)
	{
		printf("%s\n", res);
		res = get_next_line(fd);
	}
	//get_next_line(3);
	//get_next_line(3);
}*/
