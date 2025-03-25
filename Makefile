TARGET = shell

CMD = cc

CFLAGS = -Werror -Wall -Wextra -g

LDFLAGS = -lreadline

SRCS = \
	help.c\
	libft.c\
	main.c\

OBJS = $(SRCS:.c=.o)

all : $(OBJS)
	$(CMD) $(CFLAGS) $(OBJS) -o $(TARGET) $(LDFLAGS)

clean :
	rm -f $(OBJS)

fclean : clean
	rm -f $(TARGET)

re : fclean all

.PHONY : all clean fclean re
