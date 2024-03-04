---
title: Clases
layout: default
nav_order: 3
---

# Clases
{: .no_toc}

* [Filminas](https://drive.google.com/drive/folders/17CBqHsCZWHfci5L5EOHmm5Ffxgdr0feF)

* [Grabaciones de las clases](#)

* [Material adicional y ejemplos de código](https://github.com/cese-sopg/cese-sopg.github.io/tree/main/material-clases)

## Índice
{: .no_toc .text-delta }

- Índice
{:toc}

## Clase 1: GNU/Linux - Archivos

* Breve historia de UNIX. Introducción a GNU/Linux.
* Capas del sistema operativo. Separación entre userland y kernel space.
* Estándares: POSIX, SUS.
* Archivos. Inodos. Jerarquía de archivos estándar.
* Comandos básicos de Linux.
* Sistema de permisos.
* API de manejo de archivos.

## Clase 2: Kernel - Procesos

* Tipos de kernel. Kernel de Linux. Arquitectura.
* Proceso de arranque.
* Procesos y threads.
* Scheduler de Linux
* Gestión de procesos: Estados, visualización.
* Creación de procesos: `fork()`

<details markdown="1">
<summary>Prácticas</summary>

### Práctica 1
{: .no_toc }

Escribir un programa que cree una instancia hija con el syscall `fork()`. Luego
de `fork()`, la instancia padre ejecuta un sleep de 20 segundos y luego termina.
La instancia hija ejecuta un sleep de 40 segundos y luego termina.

Para compilar y probar, trabajar con dos instancias de consolas, una en cada
mitad horizontal de la pantalla. En una consola lanzar el programa y en la otra
visualizar el estado de los procesos (usar `ps -elf | grep [proceso]`) y observar
el estado de cada instancia.

¿Qué pasa con el proceso hijo cuando termina el proceso padre? ¿Terminan
normalmente?

{: .nota }
Incluir `<unistd.h>` para utilizar la función `sleep()`.

{: .nota }
Puede utilizarse el comando `watch` para ejecutar periódicamente el comando
`ps`. Ejemplo: `watch -n 1 “ps -elf | grep [proceso]”`

{: .nota }
Usar el nombre del proceso `“proceso”` y no `“./proceso”`, ya que al ser zombie
el comando `ps` lo muestra sin el `“./”`.

### Práctica 2
{: .no_toc }

Editar el código del programa anterior e invertir los tiempos utilizados en
`sleep()` entre las instancias padre e hijo. Compilar y ejecutar. ¿Cómo es el
comportamiento en este caso del proceso hijo? ¿Termina el proceso normalmente?
¿Qué ocurre cuando termina su ejecución el proceso padre?

</details>

## Clase 3: Signals - Pipes

* Comunicación entre procesos: Signals
* Comunicación entre procesos: Pipes

<details markdown="1">
<summary>Prácticas</summary>

### Signals - Práctica 1
{: .no_toc }

1. Crear el archivo `loop.py`. Escribir en su interior:

    ```python
    import time
    while True:
        time.sleep(1)
        print("tick")
    ```

2. Ejecutar el script.

    ```bash
    python loop.py
    ```

    Se deberá observar en la consola los mensajes `“tick”` cada un segundo.

3. Ejecutar la lista de procesos activos para ver el estado del mismo y obtener
   el PID.

    ```bash
    ps -elf
    ```

    Aparecerá el proceso con una `S` (Interruptable) debido a la función `sleep()`.
    Obtener el PID.

4. Presionar `Ctrl+Z` para enviar la signal `SIGSTP` al proceso.

5. Ejecutar la lista de procesos activos para ver el estado.

    ```bash
    ps -elf
    ```

    Aparecerá el proceso con una `T` (stopped).

6. Reanudar el proceso enviando la señal de continuar:

    ```bash
    kill -SIGCONT pid
    ```

7. Se deberá ver el `"tick"` nuevamente.

### Signals - Práctica 2
{: .no_toc }

Escribir un programa que cree una instancia hija con `fork()`. El
proceso padre deberá registrar el handler para `SIGCHLD`, y dentro del mismo
ejecutar la función `wait()`. El proceso hijo deberá ejecutar un `sleep` de 5
segundos y luego terminar. Asegurarse mediante el comando `ps` que el proceso
hijo no quede en estado zombie.

### Pipes - Práctica 1
{: .no_toc }

Tomar el ejercicio de la práctica 2 de signals y comunicar el proceso hijo con
el padre mediante pipes. El proceso hijo deberá enviar un mensaje luego de
esperar 5 segundos, luego esperará 10 segundos y terminará. El proceso padre
deberá imprimir el mensaje por pantalla.

</details>

## Clase 4: Named FIFOs - Networking | Presentación TP

## Clase 5: Sockets

## Clase 6: Threads

## Clase 7: Semaphores - Message queues - Shared memory

## Clase 8: Examen final
