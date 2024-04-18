/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svereten <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 13:25:04 by svereten          #+#    #+#             */
/*   Updated: 2024/04/18 10:35:02 by svereten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"

static char	*get_next_output(char *fd_buf)
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

static char	*remove_output(char *fd_buf, char *aux_buf)
{
	char	*res;
	char	*nl_location;
	size_t	nnl_index;

	if (!fd_buf)
		return (NULL);
	if (!aux_buf)
		return (free_fd_buf(&fd_buf), NULL);
	nl_location = ft_strchr(fd_buf, '\n');
	if (!nl_location || !nl_location[1])
		return (free_fd_buf(&fd_buf), NULL);
	nnl_index = nl_location - fd_buf;
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
		return (free_fd_buf(&fd_buf), NULL);
	bytes_read = 1;
	while (!ft_strchr(fd_buf, '\n') && bytes_read)
	{
		bytes_read = read(fd, aux_buf, BUFFER_SIZE);
		if (bytes_read == -1)
			return (free(aux_buf), free_fd_buf(&fd_buf), NULL);
		aux_buf[bytes_read] = '\0';
		fd_buf = ft_strjoin(fd_buf, aux_buf);
	}
	free(aux_buf);
	aux_buf = get_next_output(fd_buf);
	fd_buf = remove_output(fd_buf, aux_buf);
	return (aux_buf);
}

/*#include <fcntl.h>
int main()
{
	char *res;
	int fd = open("./multiple_nl.txt", O_RDONLY);
	res = get_next_line(fd);
	int i = 0;
	while (i < 5)
	{
		while (0)
		{
			printf("%d\n", res[i]);
			i++;
		}
		printf("line is %s\n", res);
		free(res);
		res = get_next_line(fd);
		i++;
	}
	printf("line is %s\n", res);
	free(res);

	//get_next_line(3);
	//get_next_line(3);
}*/
