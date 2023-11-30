/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvichi <lvichi@student.42porto.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 17:31:37 by lvichi            #+#    #+#             */
/*   Updated: 2023/11/23 18:23:11 by lvichi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

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

static char	*get_formatted_str(char *str)
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

static void	send_string(int pid, char *str)
{
	int	i;
	int	j;

	i = -1;
	while (str[++i])
	{
		j = -1;
		while (++j < 8)
		{
			if (str[i] & 128)
				kill(pid, SIGUSR1);
			else
				kill(pid, SIGUSR2);
			usleep(200);
			str[i] = str[i] << 1;
		}
	}
}

static void	send_len(int pid, int len)
{
	int	i;

	i = -1;
	while (++i < (32))
	{
		if (len & 2147483648)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		usleep(250);
		len = len << 1;
	}
}

int	main(int argc, char **argv)
{
	char	*str;

	if (argc != 3)
	{
		write (1, "Incorrect arguments.\n", 21);
		return (0);
	}
	str = get_formatted_str(argv[2]);
	send_len(ft_atoi(argv[1]), ft_strlen(str));
	send_string(ft_atoi(argv[1]), str);
	free(str);
}
