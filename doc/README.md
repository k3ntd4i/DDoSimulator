# Notas

## Ramas

### `puzzle`

El puzzle es lo que sucede al querer atacar una empresa, el usuario debe digital las iniciales (o el carácter correspondiente) de cada palabra. Ejemplo de uso (sin ningún temporizador):

```cpp
#include "../include/puzzle.hpp"
#include "../include/estructuras/cola.hpp"
#include <iostream>
#include <string>

int main()
{
    // La cola es obligatoria para poder verificar si el usuario digito los caracteres correctos
    Cola<std::string> extracted_words{};

    // Aca en vez de imprimirlo podemos guardar el comando completo para asignarle
    // la visualizacion en el SFML
    std::cout << get_command(8, extracted_words, true, true) << '\n';

    std::string input_command{};
    std::cout << "[+] Digite las iniciales de cada palabra: ";
    std::getline(std::cin, input_command);

    std::cout << std::boolalpha << correct_command(input_command, extracted_words);

    return 0;
}
```

Consta de dos banderas: `hard` y `extreme` (por defecto `false` para ambas). La bandera `hard` agrega números a la lista de palabras, y `extreme` agrega caracteres especiales. Tanto números como caracteres, cada uno tiene un 50% de posibilidades de aparecer

## Tareas

Proyecto sobre-simplificado:

- [ ] **HASH MAP**: Asignar una empresa a cada punto/coordenada del mapa 

- [x] **COLA**: En la línea de comandos aparece cierta cantidad de palabras aleatorias y el usuario debe digitar rápidamente las iniciales de cada palabra para poder accionar el ataque.

- [ ] **GRAFO**: Las empresas reciben infecciones indirectas tras un ataque del usuario (porque las empresas estan interconectadas)

- [ ] **ARBOL DE BUSQUEDA BINARIA**: El atacante puede comprar información, herramientas y demás recursos en la darkweb para ganar ventaja (plagiar a plague inc lo de transmision y sintomas)

Posibles otras implementaciones:

- [ ] **MAX/MIN-HEAP**: Se muestra una lista de las empresas mas/menos vulnerables/afectadas
