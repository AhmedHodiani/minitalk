SERVER = server
CLIENT = client

INCLUDE		= include
CC			= cc
CFLAGS		= -Wall -Wextra -Werror -I$(INCLUDE)

LIBFT			= ft
LIBFT_ARCHIVE	= libft.a
LIBFT_DIR		= libft

SERVER_SRC = src/server.c src/talker.c
CLIENT_SRC = src/client.c src/talker.c

all: $(LIBFT_ARCHIVE) $(SERVER) $(CLIENT)

$(SERVER): $(LIBFT_ARCHIVE) $(SERVER_SRC)
	$(CC) $(CFLAGS) $(SERVER_SRC) -L$(LIBFT_DIR) -l$(LIBFT) -o $(SERVER)

$(CLIENT): $(LIBFT_ARCHIVE) $(CLIENT_SRC)
	$(CC) $(CFLAGS) $(CLIENT_SRC) -L$(LIBFT_DIR) -l$(LIBFT) -o $(CLIENT)

$(LIBFT_ARCHIVE):
	make -C $(LIBFT_DIR)

clean:
	make -C $(LIBFT_DIR) clean

fclean:
	make -C $(LIBFT_DIR) fclean
	rm -rf $(SERVER) $(CLIENT)

re: fclean all

.PHONY: all clean fclean re
