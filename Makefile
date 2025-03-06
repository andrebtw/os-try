NAME            =	os


all:        		$(NAME)

$(NAME):    		
					nasm boot.asm -f bin -o $(NAME).bin
					@echo "\033[32m-- $(NAME) compile and create --\033[0m"
