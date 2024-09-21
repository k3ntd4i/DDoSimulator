SRCDIR = src
BUILDDIR = build
OUTDIR = bin

SOURCES = $(wildcard $(SRCDIR)/*.cpp)
OBJECTS = $(patsubst src/%,build/%,$(SOURCES:.cpp=.o))

# Aca es opcional cambiar el nombre del ejecutable (.exe generado)
EXECUTABLE = main

# Poner la ruta completa de donde tengan ubicado cada directorio
SFML_INCLUDE = C:\\build-SFML\\SFML-2.6.1\\include
SFML_LIB = C:\\build-SFML\\SFML-2.6.1\\lib

INC = -I"$(SFML_INCLUDE)"
CFLAGS = -std=c++20 -DSFML_STATIC

# Antes de cada modulo o dependencia poner '-l' seguido del nombre
# Al agregar nuevos modulos o dependencias poner un '\' al final
# No poner '\' en la ultima linea
# Las dependencias se deben poner en cierto orden:
#	Si X depende de Y, entonces X debe ponerse antes de Y
#	Consultar mas en: https://www.sfml-dev.org/tutorials/2.6/start-cb.php
LIB = -L"$(SFML_LIB)" -static \
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

$(OUTDIR)/$(EXECUTABLE): $(OBJECTS)
	@echo "Linkeando: "
	@echo "g++ $^ -o $(OUTDIR)/$(EXECUTABLE) $(LIB)"; \
	g++ $^ -o $(OUTDIR)/$(EXECUTABLE) $(LIB)

$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(BUILDDIR)
	g++ $(CFLAGS) $(INC) -c $< -o $@

clean:
	rm -f $(BUILDDIR)/*.o

tester:
	g++ $(CFLAGS) $(SOURCE_TEST) $(INC) $(LIB) -o $(OUTDIR)/$(FILE_TEST)
	./$(OUTDIR)/$(FILE_TEST)
