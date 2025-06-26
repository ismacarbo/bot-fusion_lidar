CXX       := g++
CXXFLAGS  := -std=c++17 \
              $(shell sdl2-config --cflags) \
              -I../../third_party/imgui \
              -I../../third_party/imgui/backends \
              -I../../third_party/implot \
              -I../../third_party/gl3w/include \
              -I../../sdk/include \
              -I../../sdk/src \
              -DIMGUI_IMPL_OPENGL_LOADER_GL3W
LDFLAGS   := $(shell sdl2-config --libs) -lGL -ldl -lm -lpthread

SOURCES := mainPlot.cpp \
           ../../third_party/imgui/imgui.cpp \
           ../../third_party/imgui/imgui_draw.cpp \
           ../../third_party/imgui/imgui_tables.cpp \
           ../../third_party/imgui/imgui_widgets.cpp \
           ../../third_party/imgui/backends/imgui_impl_sdl2.cpp \
           ../../third_party/imgui/backends/imgui_impl_opengl3.cpp \
           ../../third_party/implot/implot.cpp \
           ../../third_party/implot/implot_items.cpp \
           ../../third_party/gl3w/src/gl3w.c

OBJECTS := $(SOURCES:.cpp=.o)
OBJECTS := $(OBJECTS:.c=.o)

all: ultra_simple

ultra_simple: $(OBJECTS)
	$(CXX) -o $@ $^ $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

%.o: %.c
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) ultra_simple
