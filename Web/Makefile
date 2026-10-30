# A modifié pour pouvoir etre utilisé également sur linux et ajouter des règles de compilation

all:
	g++ -std=c++17 main.cpp ../Back/*.cpp -o prog -I../Back -Wall -Wextra -Wno-conversion-null -lssl -lcrypto -lsodium -lsqlite3 -lws2_32 -lcrypt32