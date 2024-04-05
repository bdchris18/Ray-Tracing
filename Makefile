<<<<<<< Updated upstream
OBJS	= WinMain.o Window.o Keyboard.o ExceptionHandler.o Mouse.o App.o Timer.o Graphics.o
SOURCE	= WinMain.cpp Window.cpp Keyboard.cpp ExceptionHandler.cpp Mouse.cpp App.cpp Timer.cpp Graphics.cpp
HEADER	= Window.h Keyboard.h ExceptionHandler.h Mouse.h App.h Timer.h Graphics.h
OUT	= a.out
CC	 = g++
FLAGS	 = -g -c -Wall
LDLIBS	 = -L. -ld3d11 -I"C:\usr\bin\Microsoft DirectX SDK (June 2010)\Include" -mwindows

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS) $(LDLIBS)
=======
OBJS	= WinMain.o Window.o Keyboard.o ExceptionHandler.o
SOURCE	= WinMain.cpp Window.cpp Keyboard.cpp ExceptionHandler.cpp
HEADER	= Window.h Keyboard.h ExceptionHandler.h
OUT	= a.out
CC	 = g++
FLAGS	 = -g -c -Wall
LFLAGS	 = 

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)
>>>>>>> Stashed changes

WinMain.o: WinMain.cpp
	$(CC) $(FLAGS) WinMain.cpp 

Window.o: Window.cpp
	$(CC) $(FLAGS) Window.cpp 

Keyboard.o: Keyboard.cpp
	$(CC) $(FLAGS) Keyboard.cpp 
<<<<<<< Updated upstream
	
Mouse.o: Mouse.cpp
	$(CC) $(FLAGS) Mouse.cpp 
=======
>>>>>>> Stashed changes

ExceptionHandler.o: ExceptionHandler.cpp
	$(CC) $(FLAGS) ExceptionHandler.cpp 

<<<<<<< Updated upstream
App.o: App.cpp
	$(CC) $(FLAGS) App.cpp

Timer.o: Timer.cpp
	$(CC) $(FLAGS) Timer.cpp

Graphics.o: Graphics.cpp
	$(CC) $(FLAGS) Graphics.cpp
=======
>>>>>>> Stashed changes

clean:
	rm -f $(OBJS) $(OUT)

run: $(OUT)
	./$(OUT)