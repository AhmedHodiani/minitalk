# include "../include/minitalk.h"

void send_char(int server_pid, char c) {
    unsigned char ascii_value = (unsigned char)c;

	int i = 6;
	while (i >= 0) {
		int sig = (ascii_value >> i) & 1;
		if (sig == 1) {
			if (kill(server_pid, SIGUSR1) == -1) {
				ft_printf("Failed to send signal");
				return;
			}
		} else {
			if (kill(server_pid, SIGUSR2) == -1) {
				ft_printf("Failed to send signal");
				return;
			}
		}
        printf("%d", sig);
		i--;
	}
	printf("\n");
}

int main(int argc, char **argv) {
	if (argc != 3) {
		ft_printf("Usage: %s <server_pid> <message>\n", argv[0]);
		return 1;
	}
	int server_pid = ft_atoi(argv[1]);
	char *message = argv[2];

	ft_printf("SERVER PID: %d\n", server_pid);
	// ft_printf("MESSAGE: %s\n", message);

	int i = 0;
	while (message[i]) {
		printf("sending %c\n", message[i]);
		send_char(server_pid, message[i]);
		i++;
	}
	// send_char(server_pid, message[i]);
	// if (kill(server_pid, SIGUSR1) == -1) {
	// 	ft_printf("Failed to send signal");
	// 	return 1;
	// }
	return 0;
}
