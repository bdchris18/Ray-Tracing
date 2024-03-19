OBJS	= WinMain.o Window.o Keyboard.o ExceptionHandler.o
SOURCE	= WinMain.cpp Window.cpp Keyboard.cpp ExceptionHandler.cpp
HEADER	= Window.h Keyboard.h ExceptionHandler.h
OUT	= a.out
CC	 = g++
FLAGS	 = -g -c -Wall
LFLAGS	 = 

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

WinMain.o: WinMain.cpp
	$(CC) $(FLAGS) WinMain.cpp 

Window.o: Window.cpp
	$(CC) $(FLAGS) Window.cpp 

Keyboard.o: Keyboard.cpp
	$(CC) $(FLAGS) Keyboard.cpp 

ExceptionHandler.o: ExceptionHandler.cpp
	$(CC) $(FLAGS) ExceptionHandler.cpp 


clean:
	rm -f $(OBJS) $(OUT)

run: $(OUT)
	./$(OUT)