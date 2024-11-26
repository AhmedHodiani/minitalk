/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataher <ataher@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 21:48:58 by ataher            #+#    #+#             */
/*   Updated: 2024/11/26 22:04:31 by ataher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <signal.h>
# include <unistd.h>
# include "libft.h"
# include <stdio.h>
# include "ft_printf.h"

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
