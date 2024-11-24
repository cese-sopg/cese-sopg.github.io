---
title: Clase 7
layout: default
nav_order: 8
---

# Clase 7
{: .no_toc }

* POSIX semaphores
* POSIX message queues
* POSIX shared memory

{: .nota-title }
> Material
>
> * [Presentación](https://docs.google.com/presentation/d/1rd-NpcEUBVdj_cLzd8fHogAV4GBr8CIXp6vzqeRi8NE/edit?usp=drive_link)
>
> * [Material adicional y ejemplos de código](https://github.com/cese-sopg/cese-sopg.github.io/tree/main/material-clases/clase7)

## Prácticas

### Práctica 1: Semáforos

1. Escribir 3 programas que realizan las siguientes operaciones:
   * P1
        * `Print(R)`
        * `Print(OK)`
   * P2
        * `Print(I)`
        * `Print(OK)`
   * P3
        * `Print(O)`
        * `Print(OK)`

   Sincronizar los programas utilizando semáforos de forma tal que:
   * El resultado impreso es `R I O OK OK OK`
   * El valor final del/los semáforos es igual al valor inicial.


1. Escribir 2 programas que realizan las siguientes operaciones:
   * P1
        * `Print(A)`
        * `Print(B)`
        * `Print(C)`
   * P2
        * `Print(E)`
        * `Print(F)`
        * `Print(G)`

   Sincronizar los programas utilizando semáforos de forma tal que:
   * A se imprime antes que F
   * F se imprime antes que C

### Práctica 2: Servidor multihilo v2

Modificar el servidor multihilo realizado en la práctica 1 de la clase anterior, de
forma tal que utilice un Message Queue en lugar de un arreglo estático para
la comunicación entre hilos.

Al aceptar una conexión de un cliente, el hilo principal debe encolar el file
descriptor del socket, y lanzar un hilo para atender al cliente. El hilo del
cliente debe desencolar un file descriptor y comunicarse mediante ese socket
con el cliente correspondiente.

### Práctica 3: `mmap`

Modificar el programa realizado en la práctica 3 de la clase 1 (ROT13) de forma
tal que el archivo se cargue y manipule en memoria utilizando `mmap` en lugar
de `read` y `write`.

### Práctica 3: Shared memory

Escribir 2 programas, _writer_ y _reader_, que comparten un segmento de memoria.

* El writer debe escribir una cadena de texto en el segmento en un ciclo
  infinito (por ejemplo la hora actual actualizada una vez por segundo).

* El reader debe imprimir la cadena de texto, luego dormir hasta que la misma
  haya sido modificada, e imprimirla de nuevo, en un ciclo infinito.

El writer y reader deben sincronizarse mediante alguno de los métodos vistos en
clase. El writer debe, además, permitir la existencia de múltiples readers.
