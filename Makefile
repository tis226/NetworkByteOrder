all: add-nbo

add-nbo: add-nbo.c
	gcc -o add-nbo add-nbo.c -lnsl

clean:
	rm -f add-nbo
