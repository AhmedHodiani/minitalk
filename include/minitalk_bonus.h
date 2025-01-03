/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk_bonus.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataher <ataher@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 21:48:58 by ataher            #+#    #+#             */
/*   Updated: 2025/01/04 02:45:26 by ataher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_BONUS_H
# define MINITALK_BONUS_H

# include "libft.h"
# include "libftprintf.h"
# include <signal.h>
# include <unistd.h>
# include <stdio.h>

void	send_int(int pid, int num);
void	send_char(int pid, char c);
void	send_bit(int pid, char bit, int flag_to_pause);
void	config_signals(struct sigaction *sa);

typedef struct s_protocol
{
	int		bits;
	int		data;
	int		flag;
	char	*message;
}			t_protocol;

#endif
