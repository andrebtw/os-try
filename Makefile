.PHONY:        fclean, all, clear, re, run

NAME            =	os

CMP             =   i686-elf-gcc
FLAG            =   -ffreestanding -m32
RM              =   rm -rf
BUILD_DIR       =   build/

HEADER_DIR = include
HEADER_FILE = kernel
INC = $(addsuffix .h, $(addprefix $(HEADER_DIR)/, $(HEADER_FILE)))

SRC_DIR = src
SRC_FILE = kernel
SRC = $(addsuffix .c, $(addprefix $(SRC_DIR)/, $(SRC_FILE)))

OBJS = $(SRC:%.c=$(BUILD_DIR)%.o)

$(BUILD_DIR)%.o: %.c $(INC)
					mkdir -p $(@D)
					$(CMP) $(FLAG) -I$(HEADER_DIR) -c $< -o $@

all: clear $(NAME)

$(NAME): $(INC) $(OBJS)
					i686-elf-ld -o $(BUILD_DIR)kernel.bin -Ttext 0x1000 $(OBJS) --oformat binary
					nasm -f bin src/boot.asm -o $(BUILD_DIR)boot.bin
					cat $(BUILD_DIR)boot.bin $(BUILD_DIR)kernel.bin > $(NAME).img
					@echo "\033[32m 🎉 Compilation successful! 🥳 \033[0m"

clean:
					$(RM) $(BUILD_DIR)

fclean:
					$(RM) $(NAME).img
					$(RM) $(BUILD_DIR)

re:         		fclean all

run:				
					qemu-system-x86_64 $(NAME).img