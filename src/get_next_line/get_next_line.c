/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandreev <nandreev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 14:49:22 by nandreev          #+#    #+#             */
/*   Updated: 2024/06/04 13:55:30 by nandreev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*split_buf(char *big_buf)
{
	char	*read_line;
	int		i;

	i = 0;
	while (big_buf[i] != '\n' && big_buf[i] != '\0')
		i ++;
	if (big_buf[i] == '\n')
	{
		read_line = malloc (sizeof(char) * (i + 2));
		if (read_line == NULL)
			return (NULL);
		ft_strlcpy (read_line, big_buf, (i + 2));
		ft_strlcpy(big_buf, (big_buf + i + 1), (ft_strlen(big_buf) - i));
	}
	else
	{
		read_line = malloc (sizeof(char) * (i + 1));
		if (read_line == NULL)
			return (NULL);
		ft_strlcpy (read_line, big_buf, (i + 1));
		*big_buf = '\0';
	}
	return (read_line);
}

char	*join_bufs(char *big_buf, char *read_buf)
{
	char	*big_buf_dub;

	big_buf_dub = ft_strjoin(big_buf, read_buf);
	free (big_buf);
	big_buf = malloc (sizeof(char) * (ft_strlen(big_buf_dub) + 1));
	if (big_buf == NULL)
	{
		free (big_buf_dub);
		free (read_buf);
		return (NULL);
	}
	ft_strlcpy(big_buf, big_buf_dub, (ft_strlen(big_buf_dub)+1));
	free (big_buf_dub);
	return (big_buf);
}

char	*read_file(int fd, char *big_buf)
{
	char	*read_buf;
	int		bytes_read;

	bytes_read = -1;
	read_buf = malloc (sizeof(char) * (BUFFER_SIZE + 1));
	if (read_buf == NULL)
		return (NULL);
	read_buf[0] = '\0';
	while (ft_strchr(read_buf, '\n') == NULL && bytes_read != 0)
	{
		bytes_read = read (fd, read_buf, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			free (read_buf);
			free (big_buf);
			return (NULL);
		}
		if (bytes_read == 0)
			break ;
		read_buf[bytes_read] = '\0';
		big_buf = join_bufs(big_buf, read_buf);
	}
	free (read_buf);
	return (big_buf);
}

char	*get_next_line(int fd)
{
	static char	*big_buf;
	char		*read_line;

	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		free (big_buf);
		return (NULL);
	}
	big_buf = read_file (fd, big_buf);
	if (big_buf == NULL || *big_buf == '\0')
	{
		free (big_buf);
		return (NULL);
	}
	read_line = split_buf(big_buf);
	if (ft_strlen(big_buf) == 0)
	{
		free(big_buf);
		big_buf = NULL;
	}
	return (read_line);
}

/* #include <fcntl.h>
#include <stdio.h>

int	main()
{

	int		fd;
	char	*line;

	fd = open ("file.txt", O_RDWR);
	//fd = open ("empty_file.txt", O_RDWR);
	//fd = open ("41_with_nl.txt", O_RDWR);
	
	//read from stdin;
	//fd = 0; 
	
	line = get_next_line(fd);
	printf("%s", line);
	free(line);
	line = get_next_line(fd);
	printf("%s", line);
	free(line);
	line = get_next_line(fd);
	printf("%s", line);
	free(line);
	line = get_next_line(fd);
	printf("%s", line);
	free(line);
	line = get_next_line(fd);
	printf("%s", line);
	free(line);
	line = get_next_line(fd);
	printf("%s", line);
	free(line);
	line = get_next_line(fd);
	printf("%s", line);
	free(line);
	// line = get_next_line(fd);
	// printf("%s", line);
	// free(line);
	// line = get_next_line(fd);
	// printf("%s", line);
	// free(line);
	
	
	close(fd);
	get_next_line(-1); // freeing big_buf

	return (0);
}  */
