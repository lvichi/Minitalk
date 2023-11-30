/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvichi <lvichi@student.42porto.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 17:48:45 by lvichi            #+#    #+#             */
/*   Updated: 2023/11/23 18:17:37 by lvichi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	g_letter;

static void	sig_handler(int signum)
{
	if (signum == 10)
	{
		g_letter = g_letter << 1;
		g_letter = g_letter + 1;
	}
	else
		g_letter = g_letter << 1;
}

static void	print_pid(void)
{
	char	*pid;

	pid = ft_itoa(getpid());
	write(1, "Server PID: ", 11);
	write(1, pid, ft_strlen(pid));
	write(1, "\n", 1);
	free(pid);
}

static int	get_len(void)
{
	int	i;
	int	len;

	i = -1;
	while (++i < 32)
		sleep(30000);
	len = g_letter;
	g_letter = 0;
	return (len);
}

static char	*get_str(int len)
{
	char	*str;
	int		i;
	int		j;

	str = (char *)malloc(sizeof(char) * len + 1);
	if (!str)
		return (NULL);
	i = -1;
	while (++i < len)
	{
		j = -1;
		while (++j < 8)
		{
			if (!sleep(2))
			{
				free(str);
				return (NULL);
			}
		}
		str[i] = g_letter;
	}
	str[i] = 0;
	return (str);
}

int	main(void)
{
	char	*str;
	int		len;

	print_pid();
	signal(SIGUSR1, sig_handler);
	signal(SIGUSR2, sig_handler);
	while (1)
	{
		g_letter = 0;
		len = get_len();
		str = get_str(len);
		if (str)
		{
			write(1, str, len);
			free(str);
		}
	}
}
