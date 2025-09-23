# Имя финальной библиотеки
NAME = get_next_line.a

# Компилятор и флаги
CC = gcc
CFLAGS = -Wall -Wextra -Werror

# Исходники и объектные файлы
SRCS = get_next_line.c get_next_line_utils.c
OBJS = $(SRCS:.c=.o)

# Заголовочные файлы
INCLUDES = get_next_line.h

# Правило по умолчанию
all: $(NAME)

# Создание статической библиотеки
$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)
	echo "Library $(NAME) created"

# Компиляция объектных файлов
%.o: %.c $(INCLUDES)
	$(CC) $(CFLAGS) -c $< -o $@

# Очистка объектных файлов
clean:
	rm -f $(OBJS)
	echo "Object files removed"

# Полная очистка (объекты и библиотека)
fclean: clean
	rm -f $(NAME)
	echo "Library $(NAME) removed"

# Пересборка
re: fclean all

