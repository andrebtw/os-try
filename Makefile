# Toolchain and flags
CMP             = i686-elf-gcc
NASM            = nasm
LD              = i686-elf-ld
FLAGS           = -ffreestanding -m32 -Wall -Wextra
NASMFLAGS       = -f elf32
LDFLAGS         = -Ttext 0x1000 -e kmain --oformat binary
RM              = rm -rf

# Project structure
NAME            = os
BUILD_DIR       = build/
HEADER_DIR      = include
SRC_DIR         = src

# Source files
HEADER_FILES    = kernel vga_text stdint io keyboard debug stdlib ATA IDT
HEADERS         = $(addsuffix .h, $(addprefix $(HEADER_DIR)/, $(HEADER_FILES)))

C_SRC_FILES     = kernel_entry vga_text io keyboard debug stdlib/strlen ATA IDT
C_SOURCES       = $(addsuffix .c, $(addprefix $(SRC_DIR)/, $(C_SRC_FILES)))

# Assembly files
ASM_SRC_FILES   = isr
ASM_SOURCES     = $(addsuffix .asm, $(addprefix $(SRC_DIR)/, $(ASM_SRC_FILES)))

# Object files
C_OBJS          = $(C_SOURCES:%.c=$(BUILD_DIR)%.o)
ASM_OBJS        = $(ASM_SOURCES:%.asm=$(BUILD_DIR)%.o)
OBJS            = $(C_OBJS) $(ASM_OBJS)

# Default target
all: $(NAME).img

# OS Image
$(NAME).img: $(BUILD_DIR)bootloader.bin $(BUILD_DIR)kernel.bin
	@cat $^ > $@
	@echo "\033[32m 🎉 Compilation successful! 🥳 \033[0m"

# Build the bootloader
$(BUILD_DIR)bootloader.bin: src/bootloader.asm
	@mkdir -p $(@D)
	@$(NASM) -f bin $< -o $@

# Build the kernel
$(BUILD_DIR)kernel.bin: $(OBJS)
	@$(LD) $(LDFLAGS) -o $@ $^

# Compile C files
$(BUILD_DIR)%.o: %.c $(HEADERS)
	@mkdir -p $(@D)
	@$(CMP) $(FLAGS) -I$(HEADER_DIR) -c $< -o $@

# Compile assembly files
$(BUILD_DIR)%.o: %.asm
	@mkdir -p $(@D)
	@$(NASM) $(NASMFLAGS) $< -o $@

# Generate dependency files for C files
DEPFILES = $(C_SOURCES:%.c=$(BUILD_DIR)%.d)
$(BUILD_DIR)%.d: %.c
	@mkdir -p $(@D)
	@$(CMP) $(FLAGS) -I$(HEADER_DIR) -MM -MT $(@:.d=.o) $< > $@

# Include dependency files
ifneq ($(MAKECMDGOALS),clean)
ifneq ($(MAKECMDGOALS),fclean)
-include $(DEPFILES)
endif
endif

# Phony targets
.PHONY: all clean fclean re run

clean:
	@$(RM) $(BUILD_DIR)

fclean: clean
	@$(RM) $(NAME).img

re: fclean all

run: $(NAME).img
	@qemu-system-i386 -hda $(NAME).img