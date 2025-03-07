NAME            =	boot


all:        		$(NAME)

$(NAME):    		
					nasm -f bin boot.asm -o $(NAME).bin
					@echo "\033[32m-- $(NAME) compile and create --\033[0m"
