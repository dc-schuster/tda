# Compilador y flags
CXX      := g++
CXXFLAGS := -std=c++17 -O2 -Wall -Wextra -Wshadow -pedantic -MMD -MP
LDFLAGS  :=

# Salida
TARGET := solucion

# Fuentes / objetos / dependencias
SRCS := $(wildcard *.cpp)
OBJS := $(SRCS:.cpp=.o)
DEPS := $(OBJS:.o=.d)

# Regla por defecto
all: $(TARGET)

# Link final
$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $@ $(LDFLAGS)

# Compilación por archivo + dependencias automáticas
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

-include $(DEPS)

# Utilidades
.PHONY: clean run debug release

run: $(TARGET)
	./$(TARGET)

clean:
	$(RM) $(OBJS) $(DEPS) $(TARGET)

debug: CXXFLAGS := -std=c++17 -g -O0 -Wall -Wextra -MMD -MP
debug: clean all

release: CXXFLAGS := -std=c++17 -O3 -DNDEBUG -Wall -Wextra -MMD -MP
release: clean all
