NAME 	= philo

CC 		= gcc

CFLAGS 	= -Wall -Wextra -Werror -g 

SRCS 	=	main.c check.c threadinit.c utils.c move.c close.c \
			mini_libft/ft_atoi.c mini_libft/ft_isdigit.c mini_libft/ft_calloc.c mini_libft/ft_bzero.c mini_libft/ft_memset.c \

OBJS	= $(SRCS:.c=.o)

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -lpthread

all: $(NAME)


%.o:%.c
	@$(CC) $(CFLAGS) -c $^ -o $@

clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean all