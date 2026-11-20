# OFLACS

## Contexto y funcionalidad

Este programa es un sistema para consultar y organizar información de una biblioteca musical. Está enfocado en el formato FLAC (Free Lossless Audio Codec); sin embargo, también es compatible con formatos comprimidos (mp3, opus), aunque algunas funcionalidades pueden verse limitadas. El software opera desde una carpeta local en la computadora del usuario y su función principal se basa en extraer los metadatos de los archivos de audio para estructurar y gestionar los datos de toda la colección.

## Descripción del avance 1

En el primer avance, se ha implementado lo siguiente:

- Función `songNames`, que itera sobre todos los archivos de música y extrae el nombre de cada canción para imprimirlo en consola.
- Función `sortQuality`, que itera sobre todos los archivos y guarda en un vector la información sobre la calidad de la música (frecuencia de muestreo y tasa de bits), al igual que el nombre de la canción. Esto permite imprimir en consola una lista de todas las pistas de la carpeta ordenadas por calidad (de mayor a menor), junto con su respectiva información técnica.
- Función `main`, la cual le solicita al usuario la ruta de su carpeta de música para poder utilizar las funciones mencionadas anteriormente.

## Descripción del avance 2

En el segundo avance, se ha implementado lo siguiente:

- Implementación de una estructura de datos lista doblemente ligada `dlist.h` como clase con sus métodos, esta estructura es usada para que el usuario pueda crear una lista con sus canciones favoritas (canción y autor).
- En main se crea la lista doblemente encadenada y se agregaron más opciones para usar los métodos de la estructura (agregar, ver lista, borrar y actualizar).

### Cambios sobre el primer avance

- Se actualizó el análisis de complejidad del algoritmo de ordenamiento usado en el proyecto, ya que el anterior era incorrecto.
- Se actualizó el main para que fuera interactivo y no se acabara el programa solo con una ejecución, esto para mejorar la continuidad del programa.
- Se agregaron mejoras estéticas como una función para imprimir el título en grande al inicio del programa y otra para limpiar la pantalla.
- Se agregó una función complementaria que muestra el artista y álbum de cada canción (sin ordenar).

## Descripción del avance 3

En el tercer avance, se ha implementado lo siguiente:

- Implementación del método `searchString` en la estructura de datos (lista doblemente ligada), el cual se utiliza en el `main` como un buscador de canciones.

### Cambios sobre el segundo avance

Se mejoró la usabilidad del programa mediante los siguientes puntos:

- Se eliminó la opción de ordenar por calidad y la opción de mostrar nombres por separado para unificarlas en una sola función. Ahora, esta función muestra toda la información de cada canción (nombre, artista y datos técnicos) ya ordenada por calidad por defecto.

- Se reemplazó la opción de modificar canciones favoritas manualmente por un sistema más eficiente. Ahora, al iniciar el programa, todo el catálogo de canciones se carga en una lista doblemente ligada. Para agregar una canción a favoritos, el usuario simplemente selecciona el número de la canción en la lista y todos sus datos se copian automáticamente. Así, el programa ya no es susceptible a errores por parte del usuario. Este cambio se complementa con la nueva función de buscar canción (`searchString`), ya que el buscador te muestra los números de las canciones encontradas, permitiéndote usar esos números para agregarlas rápidamente a tu lista de favoritos.

## Dependencias del sistema (IMPORTANTE):

El proyecto requiere tener instalada la biblioteca `TagLib` en el sistema para compilar y funcionar correctamente.

## Instrucciones para compilar el avance de proyecto

Ejecuta el siguiente comando en la terminal:

```
g++ main.cpp $(pkg-config --cflags --libs taglib) -o OFLACS
```

## Instrucciones para ejecutar el avance de proyecto

Ejecuta el siguiente comando en la terminal:
`./OFLACS`

## Descripción de las entradas del avance de proyecto

El programa recibirá como entrada un string de la ruta de la carpeta donde está guardada la biblioteca de música en la computadora.

- Opción 3 `Add favorite song`: Programa recibe número de canción a agregar en la lista de canciones favoritas.

- Opción 5 `Delete favorite`: Recibe número de canción de la lista de canciones favoritas que se quiere eliminar de la lista.

- Opción 6 `Search song`: Recibe string del nombre de la canción que se va a buscar en la lista de canciones que da la opción 1.

## Descripción de las salidas del avance de proyecto

- Opción 1 `Songs`: Lista del nombre, artista e información técnica (frecuencia de muestreo y tasa de bits) de todas las canciones, ordenadas por calidad.

- Opción 2 `Songs albums`: Lista del nombre y álbum de cada canción, de igual manera ordenadas por calidad.

- Opción 4 `See favorite songs`: Imprime la lista de las canciones favoritas del usuario que haya agregado o borrado con las opciones 3 y 5.

- Opción 6 `Search Song`: Lista del número, nombre, artista e información técnica (frecuencia de muestreo y tasa de bits) de la o las canciones que hayan coincidido con la búsqueda.

## Cumplimiento de sub-competencias

### SICT0301: Evalúa los componentes

#### Análisis de Complejidad - ALGORITMO DE ORDENAMIENTO

En la función `sortQuality` hago uso del sort() default de C++, este con la implementación de una función lambda para cambiar el criterio de ordenación, que por defecto es de menor a mayor. El sort default de C++ usa un algoritmo llamado introsort (Introspective Sort), el cual en realidad es un híbrido entre otros 3: Quicksort, Heapsort e Insertion Sort. Para hacer el análisis de complejidad primero analizaré cómo funciona el algoritmo en sí.

| Algoritmo          | Mejor Caso | Caso Medio | Peor Caso  |
| :----------------- | :--------: | :--------: | :--------: |
| **Quicksort**      | O(N log N) | O(N log N) |   O(N^2)   |
| **Heapsort**       | O(N log N) | O(N log N) | O(N log N) |
| **Insertion Sort** |    O(N)    |   O(N^2)   |   O(N^2)   |

Introsort primero analiza cuántos elementos va a ordenar, si esta cantidad de elementos es mayor a 16, introsort va a entrar con quicksort, el cual como vemos en la tabla anterior tiene un mejor caso y caso medio de O(N log N). Introsort dependiendo el número de elementos a ordenar coloca un límite de profundidad (iteraciones), si el algoritmo que empezó con Quicksort supera este límite de profundidad, para evitar que quicksort pase a su peor caso, el algoritmo pasa a usar Heapsort, el cual asegura como mejor, medio y peor caso O(N log N), y para finalizar, cuando el algoritmo ya sea de Quicksort o Heapsort tiene particiones de 16 elementos aproximadamente, usa Insertion sort para ordenar estas partes.

Ahora, si la cantidad de elementos a ordenar desde un inicio es menor a 16, el algoritmo utiliza exclusivamente Insertion Sort, el cual tiene como peor caso O(N^2).

Así que en general, el tiempo de complejidad en el mejor, medio y peor caso de introsort recae en la cantidad de elementos que vaya a ordenar. Si se están ordenando miles de elementos, introsort asegura siempre un tiempo de complejidad de O(N log N). Si se están ordenando pocos elementos, el tiempo de complejidad de introsort en el mejor, medio y peor caso serán los mismos que Insertion sort, ya que es el algoritmo que se usa.

Por lo que para aislar un solo tiempo de complejidad para cada caso en Introsort, depende de cómo visualicemos el algoritmo, en este caso se asumirá que Introsort no tiene conocimiento de cuántos elementos va a ordenar, así que sus tiempos de complejidad recaen en Insertion Sort, ya que el peor caso sería que tocaran pocos elementos y su tiempo de complejidad proporcional a esos elementos serán los de Insertion Sort:

| Algoritmo     | Mejor Caso | Caso Medio | Peor Caso |
| :------------ | :--------: | :--------: | :-------: |
| **IntroSort** |    O(N)    |   O(N^2)   |  O(N^2)   |

Si se ve desde la perspectiva de que el tiempo de complejidad para tan pocos elementos es insignificante, se pueden tomar el tiempo de complejidad fijo de O(N log N), pero para la visión de este proyecto, aunque 16 elementos son pocos, su peor complejidad teórica usando Insertion Sort seguirá siendo O(N^2), y por lo mismo consideraremos los tiempos de complejidad de Insertion Sort para IntroSort.

Como se mencionó anteriormente, en el proyecto complemento el uso de la función sort() con una función lambda, la cual uso para cambiar el criterio de ordenación ya que hago uso de un vector y tupla para una matriz, donde los primeros dos elementos de cada fila son números y son los elementos a considerar (frecuencia de muestreo y tasa de bits). La función lambda se basa en que si encuentra dos números iguales en el primer elemento de la fila, este pasa a comparar los segundos elementos de la fila. Y de igual manera lo hace de mayor a menor, logrando ordenar la música de mayor calidad a menor calidad. Cabe recalcar que la función lambda no afecta el tiempo de complejidad, ya que los métodos funcionan de la misma manera.

#### Análisis de Complejidad - ESTRUCTURA DE DATOS

En el proyecto implementé la estructura de datos lista doblemente encadenada, donde uso tres métodos principales: inserción, búsqueda y borrado. La inserción para agregar canciones a la lista de canciones favoritas, la búsqueda para buscar un elemento con su posición y el borrado para borrar definitivamente la canción de la lista. Al igual que un método que recorre toda la lista para imprimirla. Los tiempos de complejidad por cada uno de estos métodos según mi implementación son los siguientes:

| Método                      | Mejor Caso | Caso Promedio | Peor Caso |
| :-------------------------- | :--------: | :-----------: | :-------: |
| **Inserción (`insertion`)** |   $O(1)$   |    $O(1)$     |  $O(1)$   |
| **Búsqueda (`searchPos`)**  |   $O(1)$   |    $O(N)$     |  $O(N)$   |
| **Borrado (`deleteAt`)**    |   $O(1)$   |    $O(N)$     |  $O(N)$   |
| **Impresión (`printList`)** |   $O(N)$   |    $O(N)$     |  $O(N)$   |

- `Inserción`: Esto porque el método usa el apuntador tail para poner el nuevo elemento directamente al final de la lista sin tener que recorrer ningún elemento.

- `Búsqueda`: Esto porque hace uso de un ciclo for para poder recorrer desde head hasta la posición del elemento que se quiere buscar, por lo que solo tendría O(1) en lugar de O(N) en el caso de que le tocara el primer elemento.

- `Borrado`: Esto porque hace uso de un ciclo for para poder recorrer desde head hasta la posición del elemento que se quiere eliminar, por lo que solo tendría O(1) en lugar de O(N) en el caso de que le tocara el primer elemento.

- `Impresión`: Esto porque usa un ciclo while el cual siempre recorre absolutamente toda la lista desde head hasta encontrar un puntero null, imprimiendo todos los elementos.

#### Análisis de Complejidad - PROGRAMA COMPLETO

Para el análisis de complejidad del programa completo, tanto en el código de la estructura de datos como en el `main`, fui función por función y línea por línea. En cada línea se calculó el tiempo de ejecución y, tomando el tiempo mayor, se dictaminó una complejidad general para cada función.

Existen funciones con tiempo de complejidad variable (mejor, promedio y peor caso) debido a que internamente invocan algoritmos cuyo rendimiento depende del acomodo de los datos, como por ejemplo el `sort` en la función `sortQuality`. Estos tiempos de complejidad se heredan a la función que los contiene, tomando también en cuenta cómo interactúan con las complejidades del resto del código.

**Nota:** El análisis línea por línea se encuentra en los comentarios del `main` y de la estructura de datos.

##### `dlist.h` (Estructura de Datos)

| Función / Método                              | Complejidad General                        |
| :-------------------------------------------- | :----------------------------------------- |
| `DLink(T val)`                                | $O(1)$ - Constante                         |
| `DLink(T val, DLink<T> *nxt, DLink<T> *prev)` | $O(1)$ - Constante                         |
| `DList()`                                     | $O(1)$ - Constante                         |
| `~DList()`                                    | $O(1)$ - Constante                         |
| `searchString(string val)`                    | Mejor $O(1)$, Promedio $O(N)$, Peor $O(N)$ |
| `insertion(T val)`                            | $O(1)$ - Constante                         |
| `searchPos(int pos)`                          | Mejor $O(1)$, Promedio $O(N)$, Peor $O(N)$ |
| `deleteAt(int pos)`                           | Mejor $O(1)$, Promedio $O(N)$, Peor $O(N)$ |
| `printList()`                                 | $O(N)$ - Lineal                            |
| `saveToFile(string filename) const`           | $O(N)$ - Lineal                            |
| `loadFromFile(string filename)`               | $O(N)$ - Lineal                            |

<br>

##### `main.cpp` (Programa Principal)

| Función                                                  | Complejidad General                            |
| :------------------------------------------------------- | :--------------------------------------------- |
| `sortQuality(string rutacarp, DList<string> &SongsInfo)` | Mejor $O(N)$, Promedio $O(N^2)$, Peor $O(N^2)$ |
| `songAlbums(string rutacarp)`                            | Mejor $O(N)$, Promedio $O(N^2)$, Peor $O(N^2)$ |
| `clearScreen()`                                          | $O(1)$ - Constante                             |
| `printOFLACS()`                                          | $O(1)$ - Constante                             |
| `main()`                                                 | Mejor $O(N)$, Promedio $O(N^2)$, Peor $O(N^2)$ |

Como conclusión, tenemos que el programa en su totalidad (es decir, la función `main`) tiene los siguientes tiempos de complejidad:

| Función                                   | Complejidad General                            |
| :---------------------------------------- | :--------------------------------------------- |
| Complejidad final del programa (`main()`) | Mejor $O(N)$, Promedio $O(N^2)$, Peor $O(N^2)$ |

### SICT0302: Toma decisiones

#### Algoritmo de ordenamiento

Para el ordenamiento de las canciones por calidad de audio, tomé la decisión de implementar la función `std::sort()` de la librería estándar de C++ basándome en lo siguiente:

Como mencioné en el análisis de complejidad, a pequeña escala, aproximadamente en menos de 16 elementos, el sort común de C++ tiene la misma complejidad de Insertion Sort, pero esto cambia bastante si hablamos a gran escala, ya que si sorteamos cientos o miles de elementos se asegura siempre un tiempo de complejidad de $O(N \log N)$. En cambio, si hubiera implementado algoritmos como Bubble Sort, Selection Sort o un Insertion Sort puro, a gran escala estos seguirían con peor y promedio caso de $O(N^2)$. Si el usuario intenta cargar una biblioteca con 10,000 canciones, resultaría en tiempos de carga demasiado largos.

Usando el sort de C++, estoy cubriendo a los usuarios con la escalabilidad de un tiempo de complejidad $O(N \log N)$ si cargan miles de archivos de música, la naturaleza del algoritmo híbrido de introsort ofrece el rendimiento necesario para todos los casos.

#### Estructura de datos

La razón principal del uso de una lista doblemente encadenada es que, al querer implementar la opción de que el usuario pueda tener una lista de sus canciones favoritas guardada y poder consultarla, esta lista de canciones favoritas tiene un orden lineal y cronológico perfecto para usar justamente una lista, donde el método de inserción tiene un tiempo de complejidad de O(1), y el uso de una lista doblemente encadenada en lugar de una simple está enfocado a tener la mejor opción posible por si en un futuro decido implementar navegación o algún otro método.

**Comparándolo a un árbol:**
Usé la lista por la conveniencia lineal que mencioné anteriormente, una estructura de datos de naturaleza no lineal no tiene sentido en el uso que le quiero dar a la estructura, el cual es una lista lineal de canciones favoritas.

**Comparándolo a una fila:**
La abstracción de _first in first out_ no tiene sentido en el uso que le quiero dar a la estructura porque no se está buscando que la primera canción en entrar a la lista sea la primera en salir, se está buscando poder eliminar posiciones no específicas.

### SICT0303: Implementa acciones científicas

#### Método de consulta

Para consultar la información de la estructura de datos, uso dos funciones en la implementación de la estructura de datos:

- `printList`: El cual funciona para consultar toda la estructura de datos y la imprime.

- `searchString`: El cual con la función find de string, compara el elemento de cada nodo a un string dado para ver si existen coincidencias, si existen se imprime el valor completo del nodo (string con información de la canción) y su número en la lista de canciones. Este se usa en el programa como buscador y es útil para encontrar canciones en la lista y saber qué número tienen para agregarla a la lista de favoritos o solo ver si existe la canción en la lista.

#### Lectura y escritura de archivos para cargar y guardar datos

Para que la estructura de datos se mantenga aunque se cierre el programa, estoy haciendo uso de un archivo txt `favoritos.txt`, esto mediante el uso de dos métodos clave de la implementación de la estructura de datos:

- `saveToFile`: Este método recibe el nombre del archivo de texto en un string, donde con el uso de `fstream`, se usa ofstream para abrir el archivo en modo de escritura, una vez hecho esto, con el uso de un nodo prueba se recorre la lista completa, guardando los datos en el archivo con saltos de línea.

- `loadFromFile`: Este método recibe el nombre del archivo de texto en un string, y de igual manera, con el uso de `fstream` se usa ifstream para abrir el archivo en modo lectura, después con el uso de un ciclo while y getline, la función itera sobre cada línea del archivo, guardando cada línea en un valor temporal y guardando esa línea en cada iteración con el método de `insertion`, y de esta manera guarda toda la información del archivo en la estructura de datos.

Cabe recalcar que en `saveToFile`, si no existe el archivo antes de ejecutar el método, el sistema crea uno por defecto, donde en otra ejecución `loadFromFile` obtendrá los datos obtenidos durante la anterior ejecución del programa.
Estos dos métodos se integran en el main de manera que al iniciar el programa, se ejecuta la función `loadFromFile`, de esta manera se cargan todos los datos en la lista doblemente encadenada para poder usarse durante la ejecución, donde antes de finalizar el programa se ejecuta `saveToFile`, donde se guardan los datos nuevos, actualizados o borrados.

## [Video del funcionamiento del programa.](https://youtu.be/E0_LPOpYvKI)

### Evidencia 2: Problemas

[Video 1: Algoritmo de ordenamiento](https://youtu.be/HO7V56X3ZbY?si=UyTw0Do7O_lMyYYb)
[Video 2: Estructura de datos lineal](https://youtu.be/5safSQHYHkI?si=_h0YoEwVxPJ1xjop)
[Video 3: Estructura de datos no lineal](https://youtu.be/z6HpMtYnWpw?si=Mi93O9p9VGKDzaz7)
