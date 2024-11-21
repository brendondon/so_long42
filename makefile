# Caminho para o diretório da MiniLibX
MLX_PATH = ./minilibx-linux
MLX_FLAGS = -I$(MLX_PATH) -L$(MLX_PATH) -lmlx -lXext -lX11 -lm

# Nome do arquivo de saída
NAME = test

# Fonte principal
SRC = main.c\
	  input_verify.c \
	  get_next_line.c \
	  get_next_line_utils.c \
	  map_img.c \
	  utils.c

# Comando de compilação
all:
	cc -g $(SRC) $(MLX_FLAGS) -o $(NAME)

# Comando de limpeza dos arquivos binários
clean:
	rm -f $(NAME)

# Comando de limpeza total (apagar binários e recompilar)
fclean: clean

re: fclean all
