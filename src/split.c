/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atrilles <atrilles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 17:38:41 by atrilles          #+#    #+#             */
/*   Updated: 2022/05/27 10:12:20 by atrilles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

int	str_len(char const *str)
{
	int	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

char	*line(char const *str, char c)
{
	char	*temp;
	int		len;
	int		i;

	len = 0;
	while (str[len] && str[len] != c)
		len++;
	temp = malloc((len + 1) * sizeof(char));
	i = 0;
	while (i < len)
	{
		temp[i] = str[i];
		i++;
	}
	temp[i] = 0;
	return (temp);
}

char	*forward(char const *str, char c)
{
	while (str[0] && str[0] == c)
		str++;
	return ((char *)str);
}

int	count(char const *str, char c)
{
	int		i;

	i = 0;
	str = forward(str, c);
	while (str[0])
	{
		i++;
		while (str[0] && str[0] != c)
			str++;
		str = forward(str, c);
	}
	return (i);
}

char	**my_split(char const *s, char c)
{
	char const	**res;
	int			i;

	res = malloc((count(s, c) + 1) * sizeof(char *));
	i = 0;
	s = forward(s, c);
	while (s[0])
	{
		res[i] = line(s, c);
		s = s + str_len(res[i]);
		s = forward(s, c);
		i++;
	}
	res[i] = 0;
	return ((char **)res);
}
