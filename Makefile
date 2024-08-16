SRCDIR = src
BUILDDIR = build
OUTDIR = bin

# Cambiar 'main.cpp' por el archivo que se quiera compilar
# Si se trabajan con multiples archivos incluirlos asi:
# $(SRCDIR)/archivo1.cpp $(SRCDIR)/archivo2.cpp ...
SOURCES = $(SRCDIR)/main.cpp
OBJECTS = $(patsubst src/%,build/%,$(SOURCES:.cpp=.o))

# Aca es opcional cambiar el nombre del ejecutable (.exe generado)
EXECUTABLE = main

INC = -I"C:\build-SFML\SFML-2.6.1\include"
CFLAGS = -std=c++20 -DSFML_STATIC

# Antes de cada modulo o dependencia poner '-l' seguido del nombre
# Al agregar nuevos modulos o dependencias poner un '\' al final
# No poner '\' en la ultima linea
LIB = -L"C:\build-SFML\SFML-2.6.1\lib" \
	-lsfml-graphics-s \
	-lsfml-window-s \
	-lsfml-system-s \
	-lopengl32 \
	-lfreetype \
	-lwinmm \
	-lgdi32

# Cambiar 'prueba' por el nombre del archivo (sin .cpp) que se quiera compilar
FILE_TEST = prueba
SOURCE_TEST = test/$(FILE_TEST).cpp

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	g++ $(OBJECTS) -o $(OUTDIR)/$(EXECUTABLE) $(LIB)

$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(BUILDDIR)
	g++ $(CFLAGS) -c $< -o $@ $(INC)

clean:
	rm -f $(BUILDDIR)/*.o

tester:
	g++ $(CFLAGS) $(SOURCE_TEST) $(INC) $(LIB) -o $(OUTDIR)/$(FILE_TEST)
	./$(OUTDIR)/$(FILE_TEST)
