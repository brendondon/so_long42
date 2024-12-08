# Caminho para o diretório da MiniLibX
MLX_PATH = ./minilibx-linux
MLX_FLAGS = -I$(MLX_PATH) -L$(MLX_PATH) -lmlx -lXext -lX11 -lm

# Nome do arquivo de saída
NAME = so_long

# Fonte principal
SRCS = main.c\
	  input_verify.c \
	  get_next_line.c \
	  get_next_line_utils.c \
	  map_img.c \
	  utils.c \
	  verify_path.c \
	  utils2.c \

OBJS = $(SRCS:.c=.o)

# Comando de compilação
MLX_DIR = minilibx-linux/
MLX = $(MLX_DIR)libmlx.a

# Link against required libraries
MLXFLAGS = -L$(MLX_DIR) -lmlx -lX11 -lXext -lm

CC = @cc
# Build the executable
all: $(NAME)

$(NAME): $(SRCS) $(MLX) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(MLXFLAGS) -o $(NAME)
	@echo "\033[1;32m[ ✔ ] $(NAME) ready!\033[0m"

# Build minilibx-linux library
$(MLX): $(MLX_DIR)
	@rm -rf minilibx-linux/.git
	@make -C $^ > /dev/null 2>&1

$(MLX_DIR):
	@echo "\033[1;35m[ ✔ ] Preparing minilibx...\033[0m"
	@git clone https://github.com/42Paris/minilibx-linux.git > /dev/null 2>&1

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
	@echo "\033[1;36m[ ✔ ] Compiling objects...\033[0m"

# Comando de limpeza dos arquivos binários
clean:
	@rm -f $(OBJS)

# Comando de limpeza total (apagar binários e recompilar)
fclean: clean
	@rm -f $(NAME)
	@rm -rf $(MLX_DIR)
	@echo "\033[1;31m[ ✔ ] $(NAME) removed!\033[0m"

re: fclean all
