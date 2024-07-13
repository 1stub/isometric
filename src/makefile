CC = g++
CFLAGS = -I/home/stub/repos/SFML/include -g
LDFLAGS = -L/home/stub/repos/SFML/build/lib
LIBS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

# List your source files here
IMGUI_DIR = ../include/imgui/imgui-master
SOURCES =  chunk.cpp chunkManager.cpp main.cpp $(IMGUI_DIR)/imgui.cpp $(IMGUI_DIR)/imgui_demo.cpp $(IMGUI_DIR)/imgui_draw.cpp $(IMGUI_DIR)/imgui_tables.cpp $(IMGUI_DIR)/imgui_widgets.cpp
# Generate a list of object files from the source files
OBJECTS = $(SOURCES:.cpp=.o)

all: sfml-app

sfml-app: $(OBJECTS)
	$(CC) $(OBJECTS) -o isometric $(LDFLAGS) $(LIBS)

%.o: %.cpp
	$(CC) -c $< -o $@ $(CFLAGS)

clean:
	rm -f isometric $(OBJECTS)
