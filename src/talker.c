/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   talker.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataher <ataher@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 18:51:32 by ataher            #+#    #+#             */
/*   Updated: 2024/11/26 22:05:51 by ataher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"

void	config_signals(struct sigaction *sa)
{
	if (sigaction(SIGUSR1, sa, NULL) < 0)
	{
		bugger_error("Could not setup SIGUSR1");
		exit(EXIT_FAILURE);
	}
	if (sigaction(SIGUSR2, sa, NULL) < 0)
	{
		bugger_error("Could not setup SIGUSR2");
		exit(EXIT_FAILURE);
	}
}

void	send_int(int pid, int num)
{
	int		shift;
	char	bit;

	shift = (sizeof(int) * 8) - 1;
	while (shift >= 0)
	{
		bit = (num >> shift) & 1;
		send_bit(pid, bit, 1);
		shift--;
	}
}

void	send_char(int pid, char c)
{
	int		shift;
	char	bit;

	shift = (sizeof(char) * 8) - 1;
	while (shift >= 0)
	{
		bit = (c >> shift) & 1;
		send_bit(pid, bit, 1);
		shift--;
	}
}

void	send_bit(int pid, char bit, int flag_to_pause)
{
	if (bit == 0)
	{
		if (kill(pid, SIGUSR1) < 0)
		{
			bugger_error("Sending SIGUSR1");
			exit(EXIT_FAILURE);
		}
	}
	else if (bit == 1)
	{
		if (kill(pid, SIGUSR2) < 0)
		{
			bugger_error("Sending SIGUSR2");
			exit(EXIT_FAILURE);
		}
	}
	if (flag_to_pause != 0)
		pause();
}