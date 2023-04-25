CLIENT		= client
SERVER		= server

CC			= gcc -g
CFLAGS		= -Wall -Wextra 

INC			= -I ./include -I ./libft 
CLIENT_SRCS		= client.c 
SERVER_SRCS		= server.c 

CLIENT_OBJ			= $(CLIENT_SRCS:%.c=%.o)
SERVER_OBJ			= $(SERVER_SRCS:%.c=%.o)

%.o: %.c 
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@

all: $(CLIENT) $(SERVER)

make_libft:
	@echo ✅ "Compile libft\n"
	@make re -s -C ./libft

$(CLIENT): $(CLIENT_OBJ)
	@echo ✅ "Compile client\n"
	@$(CC) $^ -o $@ -Llibft -lft 

$(SERVER): $(SERVER_OBJ) 
	@echo ✅ "Compile server\n"
	@$(CC) $^ -o $@ -Llibft -lft 

clean_lft:
	@echo ✅ "Clean libft\n"
	@make fclean -s -C ./libft

clean:
	@rm -rf $(CLIENT_OBJ)
	@rm -rf $(SERVER_OBJ)

fclean: clean 
	@echo ✅ "Clean minitalk\n"
	@rm -f $(CLIENT) $(SERVER)

re: fclean all

.PHONY: all clean fclean re clean_lft
