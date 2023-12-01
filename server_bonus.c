/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvichi <lvichi@student.42porto.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 17:48:45 by lvichi            #+#    #+#             */
/*   Updated: 2023/12/01 20:52:20 by lvichi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

int	g_buffer;

static void	sig_handler(int signum)
{
	if (signum == 10)
	{
		g_buffer = g_buffer << 1;
		g_buffer = g_buffer + 1;
	}
	else if (signum == 12)
		g_buffer = g_buffer << 1;
	else
		exit(0);
}

static int	get_int(void)
{
	int	i;

	g_buffer = 0;
	i = -1;
	while (++i < 32)
		sleep(30000);
	return (g_buffer);
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
			if (!usleep(100000))
			{
				free(str);
				return (NULL);
			}
		}
		str[i] = g_buffer;
	}
	str[i] = 0;
	return (str);
}

static void	print(char *str, int s_pid, int check)
{
	int	i;

	i = -1;
	if (check == check_str(str) && ft_strlen(str) != 0)
	{
		while (str[++i])
			write(1, &str[i], 1);
		kill(s_pid, SIGUSR1);
	}
	free(str);
}

int	main(void)
{
	char				*str;
	int					len;
	int					s_pid;
	struct sigaction	act;
	int					check;

	act.sa_handler = &sig_handler;
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;
	sigaction(SIGUSR1, &act, NULL);
	sigaction(SIGUSR2, &act, NULL);
	sigaction(SIGINT, &act, NULL);
	print_pid(1);
	while (1)
	{
		s_pid = get_int();
		len = get_int();
		check = get_int();
		str = get_str(len);
		if (str)
			print(str, s_pid, check);
	}
}
