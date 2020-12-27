NAME	= xp2ocr
CFLAGS	= -lm

build/$(NAME): src/$(NAME).c
	$(CC) $(CFLAGS) -o build/$(NAME) src/$(NAME).c

.PHONY: clean
clean:
	rm -f build/$(NAME)
