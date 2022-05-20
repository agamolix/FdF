/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atrilles <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 19:35:18 by atrilles          #+#    #+#             */
/*   Updated: 2022/02/08 16:14:27 by atrilles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int str_len(char const *str)
{
    int len;

    len = 0;
    while (str[len])
        len++;
    return len;
}

char    *line(char const *str, char c)
{
    char *temp;
    int len; 
    int i; 

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

char    *forward(char const *str, char c)
{
    while (str[0] && str[0] == c)
        str++;
    return ((char *)str);
}

int     count(char const *str, char c)
{
    char *temp;
    char *freetemp;
    int i;

    i = 0;    
    temp = malloc((str_len(str) + 1) * sizeof(char));
    freetemp = temp;
    temp = forward(str, c);

    while (temp[0])
    {
        i++;
        temp = temp + str_len(line(temp, c));
        temp = forward(temp, c);
    }   
    free (freetemp);
    return i;
}

char	**my_split(char const *s, char c)
{
    char const   **res;
    int i; 
    char *temp;
    
    res = malloc((count(s, c) + 1) * sizeof(char *));
    i = 0;
    temp = malloc((str_len(s) + 1) * sizeof(char));
    temp = forward(s, c);

    while (temp[0])
    {
        res[i] = malloc((str_len(line(temp, c)) + 1) * sizeof(char));
        res[i] = line(temp, c);
        temp = temp + str_len(res[i]);
        temp = forward(temp, c);
        i++;
    }
    res[i] = 0;
    return (char **)res;
}