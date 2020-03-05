CFLAGS =  -Wall -Wextra -Werror
CC = gcc -I /usr/local/include  
DPN = -L /usr/local/lib -lmlx -framework OpenGL -framework AppKit
NAME = Cub3d
SRC = main.c

all : $(NAME)

$(NAME) :
	@$(CC) $(CFLAGS) -o $(NAME) $(SRC) $(DPN)
run :
	@./$(NAME)
debug : 
	@$(CC) $(CFLAGS) -o $(NAME) $(SRC) $(DPN) -g
	@lldb $(NAME)
clean :
	@rm -rf $(NAME) 

re : clean all