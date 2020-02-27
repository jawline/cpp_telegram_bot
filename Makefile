BIN_DIR=./bin/
BIN_FILE=${BIN_DIR}/test

CFLAGS=-O2 -pthread --std=c++17 -DBOT_TOKEN=\"${DBOT_TOKEN}\"
LDFLAGS=-I /usr/local/ssl/include -L /usr/local/ssl/lib -lboost_system -lTgBot -lssl -lcrypto  
SOURCES=./src/csv_loader.cpp ./src/main.cpp

all:
	mkdir -p ${BIN_DIR}
	g++ -o ${BIN_FILE} ${CFLAGS} ${SOURCES}  ${LDFLAGS}

test: all
	${BIN_FILE} test.csv
