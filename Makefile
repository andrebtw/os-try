.PHONY:        fclean, all, clean, re, run

NAME            =	os

CMP             =   i686-elf-gcc
FLAG            =   -ffreestanding -m32
RM              =   rm -rf
BUILD_DIR       =   build/

HEADER_DIR = include
HEADER_FILE = kernel vga_text stdint io keyboard debug stdlib/stdlib
INC = $(addsuffix .h, $(addprefix $(HEADER_DIR)/, $(HEADER_FILE)))

SRC_DIR = src
SRC_FILE = kernel_entry vga_text io keyboard debug stdlib/strlen
SRC = $(addsuffix .c, $(addprefix $(SRC_DIR)/, $(SRC_FILE)))

OBJS = $(SRC:%.c=$(BUILD_DIR)%.o)

$(BUILD_DIR)%.o: %.c $(INC)
					mkdir -p $(@D)
					$(CMP) $(FLAG) -I$(HEADER_DIR) -c $< -o $@

all: clean $(NAME)

$(NAME): $(INC) $(OBJS)
					nasm -f bin src/bootloader.asm -o $(BUILD_DIR)bootloader.bin
					i686-elf-ld -o $(BUILD_DIR)kernel.bin -Ttext 0x1000 -e main $(OBJS) --oformat binary
					cat $(BUILD_DIR)bootloader.bin $(BUILD_DIR)kernel.bin > $(NAME).img
					@echo "\033[32m 🎉 Compilation successful! 🥳 \033[0m"

clean:
					$(RM) $(BUILD_DIR)

fclean:
					$(RM) $(NAME).img
					$(RM) $(BUILD_DIR)

re:         		fclean all

run:				
					qemu-system-i386 -drive file=$(NAME).img,format=raw 