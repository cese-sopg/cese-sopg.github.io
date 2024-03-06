---
title: Clase 3
layout: default
parent: Inicio
nav_order: 3
nav_exclude: true
---

# Clase 3
{: .no_toc }

* Comunicación entre procesos: Signals
* Comunicación entre procesos: Pipes

## Prácticas
{: .no_toc .text-delta }

* Prácticas
{:toc}

## Signals - Práctica 1
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

## Signals - Práctica 2
{: .no_toc }

Escribir un programa que cree una instancia hija con `fork()`. El
proceso padre deberá registrar el handler para `SIGCHLD`, y dentro del mismo
ejecutar la función `wait()`. El proceso hijo deberá ejecutar un `sleep` de 5
segundos y luego terminar. Asegurarse mediante el comando `ps` que el proceso
hijo no quede en estado zombie.

## Pipes - Práctica 1
{: .no_toc }

Tomar el ejercicio de la práctica 2 de signals y comunicar el proceso hijo con
el padre mediante pipes. El proceso hijo deberá enviar un mensaje luego de
esperar 5 segundos, luego esperará 10 segundos y terminará. El proceso padre
deberá imprimir el mensaje por pantalla.
