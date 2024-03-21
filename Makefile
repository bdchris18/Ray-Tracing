OBJS	= WinMain.o Window.o Keyboard.o ExceptionHandler.o Mouse.o App.o Timer.o
SOURCE	= WinMain.cpp Window.cpp Keyboard.cpp ExceptionHandler.cpp Mouse.cpp App.cpp Timer.cpp
HEADER	= Window.h Keyboard.h ExceptionHandler.h Mouse.h App.h Timer.h
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
	
Mouse.o: Mouse.cpp
	$(CC) $(FLAGS) Mouse.cpp 

ExceptionHandler.o: ExceptionHandler.cpp
	$(CC) $(FLAGS) ExceptionHandler.cpp 

App.o: App.cpp
	$(CC) $(FLAGS) App.cpp

Timer.o: Timer.cpp
	$(CC) $(FLAGS) Timer.cpp

clean:
	rm -f $(OBJS) $(OUT)

run: $(OUT)
	./$(OUT)