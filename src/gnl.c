/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atrilles <atrilles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 16:40:25 by atrilles          #+#    #+#             */
/*   Updated: 2022/05/24 14:05:22 by atrilles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../gnl.h"

char	*part1(char *s, int index)
{
	char	*res;
	int		i;

	if (s[0] == 0)
		return (0);
	if (index < 0)
	{
		res = malloc((ft_strlen(s) + 1) * sizeof(char));
		i = -1;
		while (s[++i])
			res[i] = s[i];
		res[i] = 0;
		return (res);
	}
	res = malloc((index + 2) * sizeof(char));
	if (res == 0)
		return (0);
	res[index + 1] = 0;
	while (index >= 0)
	{
		res[index] = s[index];
		index--;
	}
	return (res);
}

char	*part2(char *s, int index)
{
	char	*res;
	int		i;

	if (index < 0)
	{
		free(s);
		return (0);
	}
	i = 0;
	if (s[index + 1] == 0)
	{
		free(s);
		return (0);
	}
	res = malloc((ft_strlen(s) - index) * sizeof(char));
	while (s[index + i + 1])
	{
		res[i] = s[index + i + 1];
		i++;
	}
	res[i] = 0;
	free(s);
	return (res);
}

char	*read_temp(int fd, char *temp)
{
	char	*buf;
	int		nb_read;

	buf = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (buf == 0)
		return (0);
	nb_read = 1;
	while (nb_read > 0 && index_nl(temp) == -1)
	{
		nb_read = read(fd, buf, BUFFER_SIZE);
		if (nb_read == -1 || (temp == 0 && nb_read == 0))
		{
			free(buf);
			return (0);
		}
		buf[nb_read] = 0;
		temp = ft_strjoin(temp, buf);
	}
	free(buf);
	return (temp);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*temp = 0;

	if (BUFFER_SIZE == 0 || fd < 0)
		return (0);
	temp = read_temp(fd, temp);
	if (temp == 0)
		return (0);
	line = part1(temp, index_nl(temp));
	temp = part2(temp, index_nl(temp));
	return (line);
}
