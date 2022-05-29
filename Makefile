# compiler setup
CC=gcc
CFLAGS=-Wall -Wextra -lm

# define targets
TARGETS=image_editor

build: $(TARGETS)

image_editor: image_editor.c utils.h load_command.h select_command.h rotate_command.h crop_command.h apply_command.h save_command.h
	$(CC) image_editor.c -o image_editor utils.c load_command.c select_command.c rotate_command.c crop_command.c apply_command.c save_command.c $(CFLAGS) 


clean:
	rm -f $(TARGETS)

.PHONY: pack clean