
SRC		= julia.c main.c mandelbrot.c main_utils.c mand_utils.c julia_utils.c
CC		= cc
OBJS	= $(SRC:.c=.o)
CFLAGS	= -Wall -Wextra -Werror -g
NAME	= fractol
L_CRT	= ar rcs
MK		= make

FT_PRINTF_DIR	= ./ft_printf
FT_PRINTF_LIB	= $(FT_PRINTF_DIR)/libftprintf.a



all: $(NAME)


$(NAME): $(OBJS) $(FT_PRINTF_LIB) $(LIBFT_LIB)
	$(CC) $(CFLAGS) $(OBJS) $(FT_PRINTF_LIB) -Lmlx_linux -lmlx_Linux -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME)

$(FT_PRINTF_LIB):
	$(MK) -C $(FT_PRINTF_DIR)

$(LIBFT_LIB):
	$(MK) -C $(LIBFT_DIR)

clean:
	rm -f $(OBJS)
	$(MK) -C $(FT_PRINTF_DIR) clean
	# $(MK) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MK) -C $(FT_PRINTF_DIR) fclean
	# $(MK) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
.SECONDARY: