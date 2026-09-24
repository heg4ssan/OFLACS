# OFLACS
## Contexto y funcionalidad 
Este programa es un sistema para consultar y organizar información de una biblioteca musical. Está enfocado en el formato FLAC (Free Lossless Audio Codec); sin embargo, también es compatible con formatos comprimidos (mp3, opus), aunque algunas funcionalidades pueden verse limitadas. El software opera desde una carpeta local en la computadora del usuario y su función principal se basa en extraer los metadatos de los archivos de audio para estructurar y gestionar los datos de toda la colección.

## Descripción del avance 1
En el primer avance, se ha implementado lo siguiente:
- Función `songNames`, que itera sobre todos los archivos de música y extrae el nombre de cada canción para imprimirlo en consola.
- Función `sortQuality`, que itera sobre todos los archivos y guarda en un vector la información sobre la calidad de la música (frecuencia de muestreo y tasa de bits), al igual que el nombre de la canción. Esto permite imprimir en consola una lista de todas las pistas de la carpeta ordenadas por calidad (de mayor a menor), junto con su respectiva información técnica.
- Función `main`, la cual le solicita al usuario la ruta de su carpeta de música para poder utilizar las funciones mencionadas anteriormente.

## Dependencias del sistema: 
El proyecto requiere tener instalada la biblioteca `TagLib` en el sistema para compilar y funcionar correctamente. 

## Cumplimiento de sub-competencias
### SICT0301: Evalúa los componentes
** Anlaisis de Complejidad ** 
En la función `sortQuality` hago uso del sort() default de C++, este con la implementación de una función lambda para cambiar el criterio de ordenación, que por defecto es de menor a mayor. El sort default de C++ usa un algoritmo llamado introsort (Introspective Sort), el cual en realidad es un tipo de algoritmo híbrido entre otros 3. Primero usa Quicksort, el cual en un caso promedio es uno de los algoritmos más rápidos, su problema radica en que si los datos están puestos de la peor manera posible, su tiempo de complejidad se vuelve `O(N²)`. El introsort se encarga de detectar si durante el quicksort hay demasiadas ejecuciones, cambie a Heapsort, el cual tiene garantizado un tiempo de ejecución `O(N log N)` en su peor caso. Para finalizar, introsort usa Insertion Sort cuando ya se dividió la lista original en partes muy pequeñas por su eficiencia. Todo esto se resume a que introsort tendrá como peor caso un tiempo de ejecución `O(N log N)`, y como consecuencia también la función por defecto de sort() en C++. 

Como se mencionó anteriormente, en el proyecto complemento el uso de la función sort() con una función lambda, la cual uso para cambiar el criterio de ordenación ya que hago uso de un vector y tupla para una matriz, donde los primeros dos elementos de cada fila son números y son los elementos a considerar (frecuencia de muestreo y tasa de bits). La función lambda se basa en que si encuentra dos números iguales en el primer elemento de la fila, este pasa a comparar los segundos elementos de la fila. Y de igual manera lo hace de mayor a menor, logrando ordenar la música de mayor calidad a menor calidad. Cabe recalcar que la función lambda no afecta el tiempo de complejidad, ya que los métodos funcionan de la misma manera.

### SICT0302: Toma decisiones
Hago uso del `sort()` default de C++ por dos razones principales:
- Facilidad de implementación: por ser una función nativa del lenguaje, se implementa de manera sencilla y evita la necesidad de programar un algoritmo propio.
- Eficiencia y rapidez: como mencioné anteriormente, la función `sort()` trabaja híbridamente. Al usar el algoritmo Quicksort como principal y Heapsort como secundario, asegura un tiempo de ejecución en el peor de los casos de `O(N log N)`.
