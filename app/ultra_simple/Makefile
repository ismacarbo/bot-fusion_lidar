
CXX      := g++
CXXFLAGS := -std=c++17 \
            $(shell sdl2-config --cflags) \
            -I../../third_party/imgui \
            -I../../third_party/imgui/backends \
            -I../../third_party/implot \
            -I../../third_party/gl3w/include \
            -I../../sdk/include \
            -I../../sdk/src \
            -DIMGUI_IMPL_OPENGL_LOADER_GL3W
SDK_SRC_ROOT := ../../sdk/src

SDK_SOURCES := \
    $(wildcard $(SDK_SRC_ROOT)/*.cpp) \
    $(wildcard $(SDK_SRC_ROOT)/arch/linux/*.cpp) \
    $(wildcard $(SDK_SRC_ROOT)/hal/*.cpp) \
    $(wildcard $(SDK_SRC_ROOT)/dataunpacker/*.cpp) \
    $(wildcard $(SDK_SRC_ROOT)/dataunpacker/*/*.cpp)

SOURCES := \
    mainPlot.cpp \
    ../../third_party/imgui/imgui.cpp \
    ../../third_party/imgui/imgui_draw.cpp \
    ../../third_party/imgui/imgui_tables.cpp \
    ../../third_party/imgui/imgui_widgets.cpp \
    ../../third_party/imgui/backends/imgui_impl_sdl2.cpp \
    ../../third_party/imgui/backends/imgui_impl_opengl3.cpp \
    ../../third_party/implot/implot.cpp \
    ../../third_party/implot/implot_items.cpp \
    ../../third_party/gl3w/src/gl3w.c \
    $(SDK_SOURCES)

OBJECTS := $(SOURCES:.cpp=.o)
OBJECTS := $(OBJECTS:.c=.o)

LDFLAGS := \
    $(shell sdl2-config --libs) \
    -lGL -ldl -lm -lpthread


all: ultra_simple

ultra_simple: $(OBJECTS)
	$(CXX) -o $@ $^ $(LDFLAGS)


%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@


%.o: %.c
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) ultra_simple
