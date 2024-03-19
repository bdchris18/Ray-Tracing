CC = g++

RT: WinMain.cpp Window.cpp
	${CC} WinMain.cpp Window.cpp -o WinMain

run: WinMain
	WinMain.exe
