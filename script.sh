rm -rf dist
mkdir dist
cd dist
g++ --std=c++11 -pthread -c ./../FileWriter.cpp ./../GenomeMixer.cpp ./../Random.cpp ./../Position.cpp ./../Bot.cpp ./../Population.cpp ./../main.cpp 
g++ --std=c++11 -pthread FileWriter.o GenomeMixer.o Random.o Position.o Bot.o Population.o main.o -o program
mv ./program ./../
cd ..
cd ./outputs
rm -rf *.json
cd ..
./program