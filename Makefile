SERVER = $(BUILD_PATH)/server
CLIENT = $(BUILD_PATH)/client

CC				= cc
CFLAGS			= -Wall -Wextra -Werror -Iinclude
BUILD_PATH		?= ./build

DEPENDENCIES		= libft libftprintf
DEPENDENCIES_DIR	= ./dependencies
DEPENDENCIES_FLAGS	= $(foreach lib,$(DEPENDENCIES),-L$(BUILD_PATH)/$(lib)) \
						$(foreach lib,$(patsubst lib%,%, $(DEPENDENCIES)),-l$(lib))

SERVER_SRCS			= src/server.c src/talker.c
CLIENT_SRCS			= src/client.c src/talker.c
SERVER_OBJS			= $(SERVER_SRCS:src/%.c=$(BUILD_PATH)/obj/%.o)
CLIENT_OBJS			= $(CLIENT_SRCS:src/%.c=$(BUILD_PATH)/obj/%.o)

all: $(SERVER) $(CLIENT)

$(SERVER): $(SERVER_OBJS) $(foreach lib,$(DEPENDENCIES),$(BUILD_PATH)/$(lib)/$(lib).a)
	$(CC) $(CFLAGS) $(SERVER_OBJS) $(DEPENDENCIES_FLAGS) -o $(SERVER)

$(CLIENT): $(CLIENT_OBJS) $(foreach lib,$(DEPENDENCIES),$(BUILD_PATH)/$(lib)/$(lib).a)
	$(CC) $(CFLAGS) $(CLIENT_OBJS) $(DEPENDENCIES_FLAGS) -o $(CLIENT)

$(foreach lib,$(DEPENDENCIES),$(BUILD_PATH)/$(lib)/$(lib).a):
	$(MAKE) -C $(DEPENDENCIES_DIR)/$(basename $(@F)) BUILD_PATH=../../$(BUILD_PATH)/$(basename $(@F)) all

$(BUILD_PATH)/obj/%.o: src/%.c
	@mkdir -p $(BUILD_PATH)/obj
	$(CC) $(CFLAGS) $(DEPENDENCIES_FLAGS) -c $< -o $@

clean:
	@rm -rf $(BUILD_PATH)/obj
	@rm -rf $(BUILD_PATH)/lib*/obj

copy_include:
	@for lib in $(DEPENDENCIES); do \
		rm -rf include/$$lib; \
		mkdir -p include/$$lib; \
		cp $(DEPENDENCIES_DIR)/$$lib/include/* include/; \
		echo "#include \"$$lib/$$lib.h\"" >> include/minitalk.h; \
	done

fclean: clean
	@rm -rf $(BUILD_PATH)

re: fclean all

.PHONY: all clean re fclean copy_include
