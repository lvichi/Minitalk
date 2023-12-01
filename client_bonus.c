/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvichi <lvichi@student.42porto.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 17:31:37 by lvichi            #+#    #+#             */
/*   Updated: 2023/12/01 20:33:13 by lvichi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

char	*g_str;

static void	sig_handler(int signum)
{
	signum = 0;
	write(1, "Done!\n", 6);
	free(g_str);
	exit(0);
}

static void	send_string(int pid, char *str)
{
	int		i;
	int		j;
	char	c;

	i = -1;
	while (str[++i])
	{
		j = -1;
		c = str[i];
		while (++j < 8)
		{
			if (c & 128)
				kill(pid, SIGUSR1);
			else
				kill(pid, SIGUSR2);
			usleep(150);
			c = c << 1;
		}
	}
}

static void	send_int(int pid, int num)
{
	int	i;

	i = -1;
	usleep(500);
	while (++i < 32)
	{
		if (num & 2147483648)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		usleep(500);
		num = num << 1;
	}
}

int	main(int argc, char **argv)
{
	struct sigaction	act;
	int					retry;

	if (argc != 3)
	{
		write (1, "Incorrect arguments.\n", 21);
		return (0);
	}
	act.sa_handler = &sig_handler;
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;
	sigaction(SIGUSR1, &act, NULL);
	print_pid(0);
	g_str = get_formatted_str(argv[2]);
	retry = 3;
	while (retry-- >= 0)
	{
		send_int(ft_atoi(argv[1]), getpid());
		send_int(ft_atoi(argv[1]), ft_strlen(g_str));
		send_int(ft_atoi(argv[1]), check_str(g_str));
		send_string(ft_atoi(argv[1]), g_str);
		sleep(2);
	}
	free(g_str);
}
