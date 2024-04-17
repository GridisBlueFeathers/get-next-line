/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svereten <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 13:25:04 by svereten          #+#    #+#             */
/*   Updated: 2024/04/17 17:31:54 by svereten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"

void	free_fd_buf(char **fd_buf)
{
	free(*fd_buf);
	*fd_buf = NULL;
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
	size_t	len;
	size_t	fd_buf_len;
	size_t	i;

	if (!aux)
		return (NULL);
	fd_buf_len = 0;
	if (fd_buf)
		fd_buf_len = ft_strlen(fd_buf);
	len = fd_buf_len + ft_strlen(aux);
	res = (char *)malloc((len + 1) * sizeof(char));
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

char	*get_next_output(char *fd_buf)
{
	char	*res;
	char	*nl_location;
	size_t	len;

	if (!fd_buf)
		return (NULL);
	nl_location = ft_strchr(fd_buf, '\n');
	if (!nl_location)
	{
		res = ft_substr(fd_buf, 0, ft_strlen(fd_buf));
		if (!res || !ft_strlen(res))
			return (free(res), NULL);
		return (res);
	}
	len = nl_location - fd_buf + 1;
	res = ft_substr(fd_buf, 0, len);
	return (res);
}

char	*remove_output(char *fd_buf)
{
	char	*res;
	char	*nl_location;
	size_t	nnl_index;

	if (!fd_buf)
		return (NULL);
	nl_location = ft_strchr(fd_buf, '\n');
	if (!nl_location)
		return (free_fd_buf(&fd_buf), NULL);
	nnl_index = nl_location - fd_buf;
	if (!fd_buf[nnl_index + 1])
		return (free_fd_buf(&fd_buf), NULL);
	res = ft_substr(fd_buf, nnl_index + 1, ft_strlen(fd_buf) - nnl_index - 1);
	return (free_fd_buf(&fd_buf), res);
}

char	*get_next_line(int fd)
{
	static char	*fd_buf;
	char		*aux_buf;
	int			bytes_read;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	aux_buf = (char *)malloc(BUFFER_SIZE + 1);
	if (!aux_buf)
		return (NULL);
	bytes_read = 1;
	while (!ft_strchr(fd_buf, '\n') && bytes_read)
	{
		bytes_read = read(fd, aux_buf, BUFFER_SIZE);
		printf("fd_buf %s\n", fd_buf);
		if (bytes_read == -1)
			return (free(aux_buf), free_fd_buf(&fd_buf), NULL);
		aux_buf[bytes_read] = '\0';
		fd_buf = ft_strjoin(fd_buf, aux_buf);
	}
	free(aux_buf);
	aux_buf = get_next_output(fd_buf);
	fd_buf = remove_output(fd_buf);
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
		int i = 0;
		while (0)
		{
			printf("%d\n", res[i]);
			i++;
		}
		printf("line is %s\n", res);
		free(res);
		res = get_next_line(fd);
	}
	printf("line is %s\n", res);
	free(res);
	close(fd);
	fd = open("./test-files/41_no_nl", O_RDONLY);
	res = get_next_line(fd);
	while (res)
	{
		int i = 0;
		while (0)
		{
			printf("%d\n", res[i]);
			i++;
		}
		printf("line is %s\n", res);
		free(res);
		res = get_next_line(fd);
	}
	printf("line is %s\n", res);
	free(res);

	//get_next_line(3);
	//get_next_line(3);
}*/
