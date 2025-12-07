CXX = g++
CXXFLAGS = -std=c++20 -Wall -Wextra -O2

TARGET = main.bin
SRC = main.cc
TARGETBIS = mainbis.bin
SRCBIS = mainbis.cc

all: $(TARGET) $(TARGETBIS)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o bin/$(TARGET) $(SRC)
	./bin/$(TARGET)

$(TARGETBIS): $(SRCBIS)
	$(CXX) $(CXXFLAGS) -o bin/$(TARGETBIS) $(SRCBIS)
	./bin/$(TARGETBIS)

clean:
	rm -f $(TARGET) $(TARGETBIS)