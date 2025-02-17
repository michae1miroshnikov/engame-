CC = clang
FLAGS = -std=c11 -Wall -Wextra -Werror -Wpedantic
CFLAGS := $(CFLAGS) `pkg-config --cflags sdl2 SDL2_image SDL2_ttf`
LDFLAGS := $(LDFLAGS) `pkg-config --libs sdl2 SDL2_image SDL2_ttf`
# CFLAGS := -Iinc -Iresource/inc
# LDFLAGS := -Lresource/lib \
# 			-Wl,-Bstatic -lSDL2 -lSDL2_image -lSDL2_ttf \
# 			-Wl,-Bdynamic -lm 
#-ldl -lpthread -lrt
NAME = endgame
SRC = $(wildcard ./src/*.c)
OBJ = $(patsubst ./src/%.c, ./obj/%.o, $(SRC))

all: $(NAME)

$(NAME): $(OBJ)
	@ar rcs $(NAME).a $(OBJ);
	@$(CC) -o $(NAME) $(OBJ) $(FLAGS) $(LDFLAGS) -Iinc -Linc -lm $(NAME).a

./obj/%.o: ./src/%.c
	@mkdir -p ./obj
	@$(CC) -c $< -o $@ $(FLAGS) $(CFLAGS) -Iinc

clean:
	@rm -rf ./obj/*

uninstall: clean
	@rm -f $(NAME)
	@rm -f $(NAME).a
	@rm -rf ./obj/

reinstall: uninstall all
