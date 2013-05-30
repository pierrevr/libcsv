CPP=g++
CPPFLAGS=-Wall -Wextra -pedantic
OBJ=CsvFile.o
BIN=libcsv.a

all: $(BIN)

libcsv.a: $(OBJ)
	ar -r $(BIN) $(OBJ)

CsvFile.o: CsvFile.cpp
	$(CPP) $(CPPFLAGS) -c CsvFile.cpp

clean:
	rm -f $(OBJ)
	rm -f $(BIN)

.PHONY: clean
