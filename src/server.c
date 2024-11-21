# include "../include/minitalk.h"

void handle_signal(int sig) {
	if (sig == SIGUSR1)
		ft_printf("Received SIGUSR1\n");
	else if (sig == SIGUSR2)
		ft_printf("Received SIGUSR2\n");
}

int main() {
	ft_printf("Server PID: %d\n", getpid());

	signal(SIGUSR1, handle_signal);
	signal(SIGUSR2, handle_signal);

	while (1)
		pause();

	return 0;
}
