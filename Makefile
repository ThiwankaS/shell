TARGET = minishell

CMD = cc

CFLAGS = -Werror -Wall -Wextra -g

LDFLAGS = -lreadline

LIBFT_DIR = ./ft_libft

TARGET_LIBFT = $(LIBFT_DIR)/libft.a

LIBFT_LINK = -L$(LIBFT_DIR) -lft

LIBFT_INC = $(LIBFT_DIR)/libft.h $(LIBFT_DIR)/ft_printf.h $(LIBFT_DIR)/get_next_line.h

SRCS = \
	srcs/built_in/env/env_handling.c\
	srcs/built_in/env/env_ll.c\
	srcs/built_in/env/env_utils.c\
	srcs/parse/cmd_args_utils.c\
	srcs/parse/parser.c\
	srcs/parse/heredoc.c\
	srcs/signals/signal_handlers.c\
	srcs/syntax/pipe_syntax.c\
	srcs/syntax/redirect_syntax.c\
	srcs/syntax/tariling_pipe.c\
	srcs/syntax/syntax_checker.c\
	srcs/utils/cleaners.c\
	srcs/helper.c\
	srcs/main.c\

OBJS = $(SRCS:.c=.o)

all : $(TARGET)

$(TARGET) : $(TARGET_LIBFT) $(OBJS)
	$(CMD) $(CFLAGS) $(OBJS) $(LIBFT_LINK) -o $(TARGET) $(LDFLAGS)
%.o : %.c
	$(CMD) $(CFLAGS) -c $< -o $@

$(TARGET_LIBFT) :
	@make -C $(LIBFT_DIR)

clean :
	rm -f $(OBJS)
	@make -C $(LIBFT_DIR) clean

fclean : clean
	rm -f $(TARGET)
	@make -C $(LIBFT_DIR) fclean

re : fclean all

.PHONY : all clean fclean re
