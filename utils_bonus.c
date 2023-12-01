/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvichi <lvichi@student.42porto.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 20:26:49 by lvichi            #+#    #+#             */
/*   Updated: 2023/12/01 20:25:51 by lvichi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

int	check_str(char *str)
{
	int	check;
	int	i;

	check = 0;
	i = -1;
	if (!str)
		return (0);
	while (str[++i])
	{
		if (i % 2 == 0)
			check += str[i];
		else
			check -= str[i];
	}
	return (check);
}

void	print_pid(int op)
{
	char	*pid;

	pid = ft_itoa(getpid());
	if (op == 1)
		write(1, "Server PID: ", 11);
	else
		write(1, "Client PID: ", 11);
	write(1, pid, ft_strlen(pid));
	write(1, "\n", 1);
	free(pid);
}

static char	format_char(char c)
{
	if (c == 'n')
		return (10);
	if (c == 'a')
		return (7);
	if (c == 'b')
		return (8);
	if (c == 't')
		return (9);
	if (c == 'v')
		return (11);
	if (c == 'f')
		return (12);
	if (c == 'r')
		return (13);
	if (c == 92)
		return (92);
	else
		return (c);
}

char	*get_formatted_str(char *str)
{
	char	*formatted_str;
	int		i;
	int		j;
	int		size;

	size = 0;
	i = -1;
	while (str[++i])
		if (str[i] != 92)
			size++;
	formatted_str = (char *)malloc(sizeof(char) * size + 1);
	if (!formatted_str)
		return (NULL);
	i = -1;
	j = 0;
	while (str[++i])
	{
		if (str[i] != 92)
			formatted_str[j++] = str[i];
		else
			formatted_str[j++] = format_char(str[++i]);
	}
	formatted_str[j] = 0;
	return (formatted_str);
}
