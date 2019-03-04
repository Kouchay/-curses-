CFLAF= 	-L/usr/local/lib/ -lcurl \
        -L/lib32 -lncursesw -lm

all:
	gcc -c -g asciiarttable.c -o asciiarttable.o $(CFLAF)
	gcc -c -g cJSON.c -o cJSON.o $(CFLAF)

	gcc -c -g curlapi.c -o curlapi.o $(CFLAF)

	gcc -c -g main.c -o main.o $(CFLAF)
	gcc -c -g drawui.c -o drawui.o $(CFLAF)
	gcc -o  wearther asciiarttable.o cJSON.o curlapi.o main.o drawui.o $(CFLAF) 
