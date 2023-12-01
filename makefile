CXX = g++
TARGET = CalculatorVerFinal
SRCS = CalculatorVerFinal.cpp
all: $(TARGET)
$(TARGET): $(SRCS)
	$(CXX) -o $@ $(SRCS)
clean:
	rm -f $(TARGET)