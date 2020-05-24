rm -rf FileWriter.o GenomeMixer.o Random.o Position.o Bot.o Population.o main.o program outputs/*
/usr/bin/g++ --std=c++11 -c FileWriter.cpp GenomeMixer.cpp Random.cpp Position.cpp Bot.cpp Population.cpp main.cpp 
/usr/bin/g++ --std=c++11 FileWriter.o GenomeMixer.o Random.o Position.o Bot.o Population.o main.o -o program
rm FileWriter.o GenomeMixer.o Random.o Position.o Bot.o Population.o main.o
./program