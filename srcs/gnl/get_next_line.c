/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marudlof <marudlof@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 20:20:45 by marudlof          #+#    #+#             */
/*   Updated: 2026/07/27 18:01:01 by marudlof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/**
 * @brief Extract the next line (up to and including '\n') from the buffer.
 * @param start Accumulated read buffer.
 * @return A newly allocated line, or NULL if the buffer is empty or on
 * allocation failure.
 */
static char	*ft_readed_line(char *start)
{
	int		i;
	char	*line;

	if (!start || !start[0])
		return (NULL);
	i = 0;
	while (start[i] && start[i] != '\n')
		i++;
	if (start[i] == '\n')
		i++;
	line = malloc((1 + i) * sizeof(char));
	if (!line)
		return (NULL);
	i = 0;
	while (start[i] && start[i] != '\n')
	{
		line[i] = start[i];
		i++;
	}
	if (start[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

/**
 * @brief Drop the first line from the buffer and keep the remainder.
 * @param start Accumulated read buffer (freed by this call).
 * @return A newly allocated buffer with the leftover content, or NULL when
 * nothing remains.
 */
static char	*ft_move_start(char	*start)
{
	char	*new_buff;
	int		i;
	int		j;

	i = 0;
	while (start && start[i] && start[i] != '\n')
		i++;
	if (!start || start[i] == '\0')
	{
		free(start);
		return (NULL);
	}
	i += (start[i] == '\n');
	new_buff = malloc((1 + ft_strlen(start) - i) * sizeof(char));
	j = 0;
	while (new_buff && start[i + j])
	{
		new_buff[j] = start[i + j];
		j++;
	}
	if (new_buff)
		new_buff[j] = '\0';
	free(start);
	return (new_buff);
}

/**
 * @brief Append a freshly read chunk to the accumulated buffer.
 * @param start Current buffer (freed by this call).
 * @param tmp Chunk to append.
 * @return The joined buffer, or NULL on allocation failure.
 */
static char	*ft_gnl_append(char *start, char *tmp)
{
	char	*joined;

	if (!start)
		joined = ft_strdup(tmp);
	else
		joined = ft_strjoin(start, tmp);
	free(start);
	return (joined);
}

/**
 * @brief Read from the fd until a newline is buffered or EOF is reached.
 * @param start_str Current accumulated buffer.
 * @param fd File descriptor to read from.
 * @return The buffer containing at least one line, or NULL on read/alloc
 * failure.
 */
static char	*ft_gnl_rl(char *start_str, int fd)
{
	char	*tmp;
	int		fd_read;

	tmp = malloc((1 + BUFFER_SIZE) * sizeof(char));
	if (!tmp)
	{
		free(start_str);
		return (NULL);
	}
	fd_read = 1;
	while (!(start_str && ft_strchr(start_str, '\n')) && fd_read != 0)
	{
		fd_read = read(fd, tmp, BUFFER_SIZE);
		if (fd_read == -1)
		{
			free(start_str);
			start_str = NULL;
			break ;
		}
		tmp[fd_read] = '\0';
		start_str = ft_gnl_append(start_str, tmp);
	}
	free(tmp);
	return (start_str);
}

/**
 * @brief Read and return the next line from a file descriptor.
 *
 * State is kept in a static buffer between calls. Passing an invalid fd (or
 * a non-positive BUFFER_SIZE) frees that buffer and returns NULL.
 * @param fd File descriptor to read from.
 * @return The next line including its trailing '\n', or NULL at EOF/on error.
 */
char	*get_next_line(int fd)
{
	char		*tmp;
	static char	*start_str;

	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		free(start_str);
		start_str = NULL;
		return (NULL);
	}
	start_str = ft_gnl_rl(start_str, fd);
	tmp = ft_readed_line(start_str);
	start_str = ft_move_start(start_str);
	return (tmp);
}
