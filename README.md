# DDoSimulator

## Organización de directorios

- `assets`: Almacena los recursos del juego (imágenes, texturas, audio, etc.)
- `bin`: Almacena los `.exe` que se generan al compilar
- `build`: Almacena los archivos `.o` que se generan durante la compilación, los cuales se utilizan como archivos precompilados para mejorar la eficiencia
- `doc`: Almacena notas de desarrollo para guiarnos entre nosotros
- `include`: Almacena todos los encabezados `.hpp` (los archivos que se se incluyen usando `#include`)
- `src`: Almacena todos los archivos `.cpp` del juego
- `test`: Almacena códigos de prueba y experimentos

El directorio `test` es opcional y se utiliza para poder almacenar las pruebas que quieran hacer sin afectar el proyecto, ya sea de SFML o de C++ en general. Su uso es personal, por lo que también se ignora en Git. Al realizar pruebas de SFML, es necesario agrupar todo el código en un solo archivo, y el `MakeFile` brinda el comando `tester` para compilar dichos archivos con todas las dependencias necesarias:

```ps1
make tester
```

## Configuración

Tener en las variables de entorno _'path'_ las rutas `mingw64\bin` (el compilador de SFML) y `msys64\usr\bin` (ahí está `make`)

Poner en `c_cpp_properties.json` el compilador y el directorio `include` de SFML

Buscar en la configuración de vscode _"cppStandard"_ y seleccionar c++20

## Compilación

### Makefile

Se debe crear un archivo llamado `Makefile` en la raiz del proyecto, luego pegar el siguiente codigo y cambiar las variables necesarias (en los comentarios esta la explicacion detallada)

```make
SRCDIR = src
BUILDDIR = build
OUTDIR = bin

SOURCES = $(wildcard $(SRCDIR)/*.cpp)
OBJECTS = $(patsubst src/%,build/%,$(SOURCES:.cpp=.o))

# Aca es opcional cambiar el nombre del ejecutable (.exe generado)
EXECUTABLE = main

# Poner la ruta completa de donde tengan ubicado cada directorio
SFML_INCLUDE = C:\\SFML-2.6.1\\include
SFML_LIB = C:\\SFML-2.6.1\\lib

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
# Si el archivo de prueba no implica SFML, entonces compilarlo a mano desde la terminal
#	g++ .\test\prueba.cpp -o .\test\prueba.exe 
FILE_TEST = prueba
SOURCE_TEST = test/$(FILE_TEST).cpp

$(OUTDIR)/$(EXECUTABLE): $(OBJECTS)
	@mkdir -p $(OUTDIR)
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
```

- Antes de compilar tener en cuenta:
  - Usar **PowerShell** en vez de Git Bash
  - Cada que se quiera compilar luego de hacer cambios, se deben guardar dichos cambios
  - Todos los comandos se deben ejecutar estando en el directorio donde se encuentra el archivo `Makefile`

Para compilar se debe ejecutar en la terminal el comando `make`

```ps1
make
```

Para abrir el programa se ejecuta el `.exe` generado

```ps1
.\bin\main.exe
```

También está el comando `make clean` para eliminar los archivos generados en la compilación anterior. Esto es util cuando se quiere compilar todo desde cero, mas que todo si parece haber algún conflicto o error entre los archivos precompilados (los `.o` del directorio `build`)

```ps1
make clean
```

Si solo se realizan pequeñas modificaciones, se recomienda simplemente ejecutar `make`. El compilador detectará automáticamente qué archivo ha sido modificado, sin necesidad de recompilar el resto.

### Script

Como da pereza ejecutar a cada rato esos tres comandos, se ha creado un script en PowerShell que automatiza todo de forma segura. Solo hay que ejecutar en la terminal el archivo `construir.ps1` (por defecto no se ejecuta `make clean`)

```ps1
.\construir.ps1
```

Para que el script ejecute `make clean` se le debe pasar la opción `-c`

```ps1
.\construir.ps1 -c
```

Sin embargo, dado que el script no fue creado por el usuario en su sistema, Windows no lo ejecuta por razones de seguridad. En este caso, se puede copiar el contenido del script y crear un nuevo archivo `construir.ps1`. De esta manera, Windows considerará que el usuario ha escrito el script y, por lo tanto, podrá ejecutarlo.
