CLIENT			= client
SERVER			= server

CC				= gcc
CFLAGS			= -Wall -Wextra -Werror  

INC				= -I ./include -I ./libft 
CLIENT_SRCS		= client.c 
SERVER_SRCS		= server.c minitalk_utils.c 

CLIENT_OBJ		= $(CLIENT_SRCS:%.c=%.o)
SERVER_OBJ		= $(SERVER_SRCS:%.c=%.o)

%.o: %.c 
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@

make_libft:
	@echo ✅ "Compile libft\n"
	@make re -s -C ./libft

all: make_libft $(CLIENT) $(SERVER)

$(CLIENT): $(CLIENT_OBJ)
	@echo ✅ "Compile client\n"
	@$(CC) $^ -o $@ -Llibft -lft 

$(SERVER): $(SERVER_OBJ) 
	@echo ✅ "Compile server\n"
	@$(CC) $^ -o $@ -Llibft -lft 

clean_lft:
	@echo ✅ "Clean libft\n"
	@make fclean -s -C ./libft

clean: clean_lft
	@echo ✅ "Clean minitalk\n"
	@rm -rf $(CLIENT_OBJ)
	@rm -rf $(SERVER_OBJ)

fclean: clean 
	@rm -f $(CLIENT) $(SERVER)

re: fclean all

.PHONY: all clean fclean re clean_lft
