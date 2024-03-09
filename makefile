CFLAGS=-std=c++17 -O2
LDFLAGS=-lglfw -lvulkan -ldl -lpthread -lX11 -lXxf86vm -lXrandr -lXi

.PHONY: test clean

test: *.cpp *.hpp
	g++ $(CFLAGS) -o VulkanTest *.cpp $(LDFLAGS)
	./compile.sh
	./VulkanTest

clean:
	rm -f VulkanTest
