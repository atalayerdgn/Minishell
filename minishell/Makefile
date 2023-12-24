NAME = minishell

CC = gcc
CFLAGS = -Wall -Wextra -Werror

SRC_DIR = srcs/executer
EXPANDER_DIR = srcs/expander
LEXER_DIR = srcs/lexer
PARSER_DIR = srcs/parser
UTILS_DIR = srcs/utils
SRCS = srcs/main.c \
       $(SRC_DIR)/builtin.c \
       $(SRC_DIR)/cd.c \
       $(SRC_DIR)/childprocess.c \
       $(SRC_DIR)/env.c \
       $(SRC_DIR)/errors.c \
       $(SRC_DIR)/executer.c \
       $(SRC_DIR)/export_append.c \
       $(SRC_DIR)/export_builtin.c \
       $(SRC_DIR)/export_utils.c \
       $(SRC_DIR)/fds.c \
       $(SRC_DIR)/heredoc.c \
       $(SRC_DIR)/path_finder.c \
       $(SRC_DIR)/pipes.c \
       $(SRC_DIR)/pwd_utils.c \
       $(SRC_DIR)/signals.c \
       $(SRC_DIR)/unset.c \
       $(EXPANDER_DIR)/expander_utils.c \
       $(EXPANDER_DIR)/expander.c \
       $(LEXER_DIR)/lexer_split.c \
       $(LEXER_DIR)/lexer_utils.c \
       $(LEXER_DIR)/lexer.c \
       $(PARSER_DIR)/parser.c \
       $(PARSER_DIR)/parser_utils.c \
       $(PARSER_DIR)/prelim_parser_utils.c \
       $(PARSER_DIR)/prelim_parser.c \
       $(UTILS_DIR)/atollong.c \
       $(UTILS_DIR)/bubble_sort.c \
       $(UTILS_DIR)/exec_utils.c \
       $(UTILS_DIR)/free.c \
       $(UTILS_DIR)/free2.c \
       $(UTILS_DIR)/list_utils.c \
       $(UTILS_DIR)/string_utils.c \
       $(UTILS_DIR)/node_mem.c \

OBJ = $(SRCS:.c=.o)

LIBFT_DIR = srcs/42lib/libft

LIBS = -L$(LIBFT_DIR) -lft -lreadline -lhistory

INCLUDES = -I$(LIBFT_DIR) -I$(SRC_DIR) -I$(EXPANDER_DIR) -I$(LEXER_DIR) -I$(PARSER_DIR) -I$(UTILS_DIR)

all: $(NAME)

$(NAME): $(OBJ)
	@make -C $(LIBFT_DIR)
	@$(CC) $(CFLAGS) $(OBJ) $(LIBS) -o $(NAME)

$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(EXPANDER_DIR)/%.o: $(EXPANDER_DIR)/%.c
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LEXER_DIR)/%.o: $(LEXER_DIR)/%.c
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(PARSER_DIR)/%.o: $(PARSER_DIR)/%.c
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(UTILS_DIR)/%.o: $(UTILS_DIR)/%.c
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@make -C $(LIBFT_DIR) clean
	@rm -f $(OBJ)
	@find srcs -name "*.o" -type f -delete

fclean: clean
	@make -C $(LIBFT_DIR) fclean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
