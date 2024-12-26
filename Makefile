NAME = philo
CC = cc
CFLAGS =  -pthread -I./inc -Wall -Werror -Wextra
SRC_DIR = ./src
INC_DIR = ./inc
SRC = $(SRC_DIR)/philo.c \
      $(SRC_DIR)/args_check.c \
	  $(SRC_DIR)/ft_atoi.c \
	  $(SRC_DIR)/monitor.c \
	  $(SRC_DIR)/routine.c \
	  $(SRC_DIR)/initialize.c \
	  $(SRC_DIR)/cleanup.c \
	  $(SRC_DIR)/print_error.c \
	  $(SRC_DIR)/time.c
OBJ = $(SRC:.c=.o)


all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LDFLAGS)

.c.o:		
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

my: all myclean

.PHONY: all clean fclean re