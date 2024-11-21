# include "../include/minitalk.h"

int main(int argc, char **argv) {
	if (argc != 3) {
		ft_printf("Usage: %s <server_pid> <message>\n", argv[0]);
		return 1;
	}
	int server_pid = ft_atoi(argv[1]);
	char *message = argv[2];

	ft_printf("SERVER PID: %d\n", server_pid);
	ft_printf("MESSAGE: %s\n", message);
	// if (kill(server_pid, SIGUSR1) == -1) {
	// 	ft_printf("Failed to send signal");
	// 	return 1;
	// }
	return 0;
}
