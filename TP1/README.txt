Introduccion:

El programa simula un torneo pokemon desde el heap. Se crea un puntero a un toreno en el heap el cual apunta a un vector de entrenadores y cada entrenador apunta a tres pokemones. Se listan los entrenadores por pantalla y los hace jugar rondas, a medida que pierden se los eliminan los espacios de memoria donde están ellos y sus pokemones. Y asi sucesivamente hasta que quede un entrendor el cual será el gandor. Una vez finalizado el torneo este se elimina. En el caso de que haya un error con el archivo por emergecia se destruirá.

Linea de compilacion:

La línea de compilación es gcc *.c -Wall -Werror -Wconversion -std=c99 -o torneo_pokemon.

GCC es nuestro compilador (GNU Compiler Collection).

*.c seria el programa que queremos compilar, en este caso como tenemos bibliotecas tenemos que compilarlo con * ya que com0cpila todos los programas dentro del directorio. En el caso de que si quisiera compilar un solo programa seria programa.c

-Wall abilita la advertencias de errores que no evitan que el código corra pero que pueden ser evitados facilmente.

-Werror le avisa al programa que tiene que conisderar todas las advertencias como errores.

-Wconversion avisa las conversiones las cuales pueden alterar un valor.

-std=99 le avisa al compiador que versión de C estoy usando. En este caso es la versión de 1999.

-o le indica al compilador el nombre por el cual se va a llamar al programa. En el caso de de que no se le asigne un nombre el compilador le asignara a.out.

Ejecucion:

La línea de ejecución del archivo seria ./torneo_pokemon ruta_ ejemplo.txt. Consta de dos argumentos. El primero, ./torneo_pokemon, hace que se ejecute el programa y el segundo, ejemplo.txt, seria el archivo de entrenadores el cual hay que pasar. Este archivo tiene que estar escrito con el formato pedido por el enunciado.



Punteros y aritmetica de punteros:

Los punteros son variables los cuales apuntan a un lugar de la memoria el cual es del mismo tipo que ellos, estos pueden apuntar al stack o al heap. También pueden apuntar a otros punteros. Los punteros se definen con * y los punteros de punteros de punteros ** y asi sucesivamente. Estos tienen acceso a lo que apuntan, en el caso de tener un puntero int** ptr que apunta a un puntero *ptr_2 que apunta a un vector, el primero podrá acceder al vector ya que al final apuntan al mismo espacio de la memoria. Ej: (*((*ptr)+k)=n).

Punteros a funcion:

Son funciones las cuales son recibidas como parámetros para otra funcion, la cual las ejecuta. Sirven para los casos en los cuales tenes muchas funciones de firmas similares, un ejemplo es torneo_jugar_ronda, ya que en este tenemos 5 funciones las cuales funcionan de manera identica  pero usando distintas condiciones, en vez de modificar la funcion de torneo_jugar_ronda simplemente le mando el puntero a funcion.

Malloc y Realloc:

Malloc y Realloc son dos funciones que tienen un funcionamiento similar, las cuales reservan memoria en el heap. Lo que hace Malloc, como explique antes, es reservar un espacio en la memoria del tamanio de lo que le pidas, el cual hay que pasárselo por parámetro (malloc(tamanio)). Realloc lo que hace es agrandar la memoria de un puntero y en el caso de que al puntero no se le haya asignado memoria en el Heap este le asignara una, por eso digo que son similares. El puntero y el nuevo tamanio se lo pasas por parámetro (realloc(puntero, nuevo_tamanio).
