# DDoSimulator

## Organización de directorios

- `assets`: Almacena los recursos del juego (imágenes, texturas, audio, etc.)
- `bin`: Almacena los `.exe` que se generan al compilar
- `build`: Almacena los archivos `.o` que se generan en el pre-compilado
- `doc`: Almacena notas de desarrollo para guiarnos entre nosotros
- `include`: Almacena todos los encabezados `.hpp` (códigos que se utilizan con `#include`)
- `src`: Almacena el código como tal del juego
- `test`: Almacena códigos de testeo

## Configuración

Tener en las variables de entorno las rutas `mingw64\bin` (el compilador de SFML) y `msys64\usr\bin` (ahi esta el `make` de MSYS2) en el _path_

Poner en `c_cpp_properties.json` el compilador y el directorio `include` de SFML

## Compilación

En el archivo `Makefile` esta todo configurado, solo es cambiar variables cuando sea necesario (dentro del mismo archivo hay comentarios explicativos)

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

Para volver a compilar algo se recomienda ejecutar `make clean` para limpiar lo de la compilación anterior

```ps1
make clean
```

Al ejecutar `make clean` se aumenta el tiempo de compilación, puesto que, se debe compilar todo de nuevo. En caso de solo hacer pequeñas modificaciones se recomienda simplemente ejecutar `make`, y el compilador sabrá automáticamente que archivo fue modificado sin necesidad de compilar todo lo demás

### Script

Como da pereza ejecutar a cada rato esos tres comandos hay un script en PowerShell que automatiza todo de forma segura, solo es ejecutar en la terminal el archivo `construir.ps1`

```ps1
.\construir.ps1
```

Sin embargo, debido a que el script no fue escrito por el usuario de su sistema, Windows no lo ejecuta por seguridad. En dicha situación, copiar el contenido del script y crear un nuevo archivo `construir.ps1`, de esta forma Windows cree que el usuario escribió el script y por ende ya lo puede ejecutar

### Tests

Para ejecutar alguna prueba (los códigos del directorio `test`) simplemente se debe ejecutar en la terminal `make tester` (automáticamente se ejecuta el `.exe` generado)

```ps1
make tester
```