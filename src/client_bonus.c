/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataher <ataher@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 19:05:12 by ataher            #+#    #+#             */
/*   Updated: 2025/01/04 02:36:07 by ataher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk_bonus.h"

static void	client_handler(int sig)
{
	if (sig == SIGUSR2)
	{
		bugger_box("Server affirmed reception of the full message");
		exit(EXIT_SUCCESS);
	}
}

static void	client_send_message(int server_pid, char *str)
{
	int	i;

	bugger_cmd("Sending message length (int): %d", ft_strlen(str));
	send_int(server_pid, ft_strlen(str));
	bugger_cmd("Sending message...");
	i = 0;
	while (str[i] != '\0')
		send_char(server_pid, str[i++]);
	bugger_cmd("Sending null terminator...");
	send_char(server_pid, '\0');
}

int	main(int argc, char **argv)
{
	struct sigaction	s_client;

	if (argc != 3)
	{
		bugger_info("Usage: %s <server_pid> <message>", argv[0]);
		return (EXIT_FAILURE);
	}
	else if (kill(ft_atoi(argv[1]), 0) < 0)
	{
		bugger_error("PID is invalid");
		return (EXIT_FAILURE);
	}
	sigemptyset(&s_client.sa_mask);
	s_client.sa_flags = SA_RESTART;
	s_client.sa_handler = client_handler;
	config_signals(&s_client);
	client_send_message(ft_atoi(argv[1]), argv[2]);
	return (EXIT_SUCCESS);
}
