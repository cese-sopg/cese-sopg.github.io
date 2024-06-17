---
title: Clase 6
layout: default
nav_order: 7
---

# Clase 6
{: .no_toc }

* Threads.
* Sincronización: mutexes.

{: .nota-title }
> Material
>
> * [Presentación](https://docs.google.com/presentation/d/1zK8A3vaE5x-q-_17fUuqt3788Kfsgz1IQk-D54c0M80/edit?usp=drive_link)
>
> * [Material adicional y ejemplos de código](https://github.com/cese-sopg/cese-sopg.github.io/tree/main/material-clases/clase6)

## Práctica
{: .no_toc }

1. Tomar el [ejemplo](https://github.com/cese-sopg/cese-sopg.github.io/tree/main/material-clases/clase6/practica)
   y modificar `server_tcp.c` para que
   pueda aceptar múltiples conexiones. Para ello se lanzará un thread
   cada vez que se acepte una nueva conexión. Cada thread se encargará de
   recibir datos del cliente y enviar como respuesta lo mismo que recibió.

    Se deberá utilizar la biblioteca `clientdata.c` provista para el ejercicio,
    que representa un cliente que se conecta al servidor. En `clientdata.h`
    se define la siguiente estructura:

    ```c
    typedef struct {
        int fd;
        pthread_t thread;
        int free;
    } clientdata;
    ```

    Se deberá definir una lista (array) del tipo `clientdata` de 100 posiciones.
    Los campos se deberán cargar luego de aceptar la conexión, de la siguiente manera:

    * `fd`: File descriptor devuelto por la función `accept()`
    * `thread`: variable `pthread_t` utilizada para crear el thread
    * `free`: En `true` para indicar que la posición del array está libre (se
      utilizará una lista de ítems del tipo `clientdata`)

    Cuando se acepta una conexión, se utilizará la función `cd_getfreeindex()`
    para obtener el índice de la lista del primer elemento libre (sin datos de ningún
    cliente). Éste se utilizará para cargar los datos y luego lanzar el
    thread.

    El thread deberá recibir como argumentos un puntero al `clientdata`,
    que posee en uno de sus campos el file descriptor de la conexión aceptada.

    La biblioteca `clientdata` también posee la función `cd_init()`, que
    debe ejecutarse al comienzo del programa para inicializar la lista vacía.

2. Capturar la signal `SIGINT` (ctrl+c) y finalizar todos los threads y sockets
   abiertos antes de finalizar el proceso.
