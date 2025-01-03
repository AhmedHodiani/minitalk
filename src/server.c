/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataher <ataher@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 22:01:54 by ataher            #+#    #+#             */
/*   Updated: 2025/01/04 01:27:51 by ataher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"

static void	server_is_message_finished(
	t_protocol *t_server, int *i, int client_pid)
{
	if (t_server->bits == 8 && t_server->flag == 1)
	{
		t_server->message[*i] = t_server->data;
		(*i)++;
		if (t_server->data == '\0')
		{
			ft_printf("%s\n", t_server->message);
			free(t_server->message);
			t_server->message = NULL;
			t_server->flag = 0;
			*i = 0;
			send_bit(client_pid, 1, 0);
		}
		t_server->bits = 0;
	}
}

static void	server_is_str_length_finished(t_protocol *t_server)
{
	if (t_server->bits == sizeof(int) * 8 && t_server->flag == 0)
	{
		t_server->flag = 1;
		t_server->message = malloc(sizeof(char) * (t_server->data + 1));
		if (t_server->message == NULL)
		{
			bugger_error("String length allocation failed");
			exit(EXIT_FAILURE);
		}
		t_server->message[t_server->data] = '\0';
		t_server->bits = 0;
	}
}

static void	handle_signal(int num, siginfo_t *info, void *context)
{
	static t_protocol	t_server;
	static int			i;

	usleep(100);
	(void)context;
	(void)info;
	if (t_server.bits == 0)
		t_server.data = 0;
	if (num == SIGUSR2 && t_server.flag == 0)
		t_server.data |= 1 << (((sizeof(int) * 8) - 1) - t_server.bits);
	else if (num == SIGUSR2 && t_server.flag == 1)
		t_server.data |= 1 << (((sizeof(char) * 8) - 1) - t_server.bits);
	t_server.bits++;
	server_is_str_length_finished(&t_server);
	server_is_message_finished(&t_server, &i, info->si_pid);
	send_bit(info->si_pid, 0, 0);
}

int	main(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_sigaction = handle_signal;
	sa.sa_flags = SA_SIGINFO | SA_RESTART;
	config_signals(&sa);
	bugger_cmd("Server PID: %d\n", getpid());
	while (1)
		pause();
	return (EXIT_SUCCESS);
}
