TARGET = winoptimizer.exe
SRC_DIR = src
SRCS = $(wildcard $(SRC_DIR)/*.cpp)

CXXFLAGS = -O2 -std=c++20 -Iinclude

ifeq ($(OS),Windows_NT)
    CXX = g++
    EXE =
    SYSTEMCXXFLAGS = -static
else
    CXX = x86_64-w64-mingw32-g++
    EXE = .exe
    SYSTEMCXXFLAGS = -static -static-libgcc -static-libstdc++
endif

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) $(SYSTEMCXXFLAGS) $(SRCS) -o $(TARGET)

clean:
	rm -f $(TARGET)