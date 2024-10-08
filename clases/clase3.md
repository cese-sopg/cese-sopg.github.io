---
title: Clase 3
layout: default
nav_order: 4
---

# Clase 3

* Comunicación entre procesos: Signals
* Comunicación entre procesos: Pipes

{: .nota-title }
> Material
>
> * [Presentación](https://docs.google.com/presentation/d/13HXhRGgIfv4r_xldMbmNpNrVGebx7PCnlXhL4BLv86g/edit?usp=drive_link)
>
> * [Material adicional y ejemplos de código](https://github.com/cese-sopg/cese-sopg.github.io/tree/main/material-clases/clase3)

## Prácticas

### Signals - Práctica 1

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

Escribir un programa que cree una instancia hija con `fork()`. El
proceso padre deberá registrar el handler para `SIGCHLD`, y dentro del mismo
ejecutar la función `wait()`. El proceso hijo deberá ejecutar un `sleep` de 5
segundos y luego terminar. Asegurarse mediante el comando `ps` que el proceso
hijo no quede en estado zombie.

Investigar cómo reacciona el proceso padre (con y sin `SA_RESTART`) si recibe
la señal `SIGCHLD` mientras está ejecutando las funciones:

* `read(STDIN_FILENO, ...)`
* `sleep(...)`
* `pause()`

## Pipes - Práctica 1

Tomar el ejercicio de la práctica 2 de signals y comunicar el proceso hijo con
el padre mediante pipes. El proceso hijo deberá enviar un mensaje luego de
esperar 5 segundos, luego esperará 10 segundos y terminará. El proceso padre
deberá imprimir el mensaje por pantalla.

Implementar correctamente las llamadas a `read` y `write` de forma tal que los
procesos reaccionen mostrando un mensaje de error apropiado en los siguientes
casos:

* `read` en el pipe cuando el hijo termina prematuramente.
* `write` en el pipe cuando el padre termina prematuramente.
