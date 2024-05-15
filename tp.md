---
title: Trabajo práctico
layout: default
nav_order: 6
---

# Trabajo práctico

**Tiempo de entrega:** hasta clase 6.

## Objetivo

Comunicar dos procesos por medio de un named FIFO. El proceso Writer podrá
recibir texto por la consola y signals. El proceso Reader deberá escribir en un
archivo el texto que recibe del proceso Writer y en otro archivo las signals
que recibe del proceso Writer.

## Partes del sistema

![](/assets/tp-diagrama.png)

### Proceso Writer

Este proceso debe imprimir su propio PID y luego entrar en un bucle esperando a
que el usuario ingrese texto hasta que presione ENTER. En ese momento escribirá
en una named FIFO los datos con el siguiente formato:

```
DATA:XXXXXXXXX
```

En cualquier momento el proceso podrá recibir las signals `SIGUSR1` y
`SIGUSR2`. En dicho caso deberá escribir en el named FIFO el mensaje `SIGN:1` o
`SIGN:2` y contnuar con su ejecución normal.

### Proceso Reader

Este proceso leerá los datos del named FIFO y según el encabezado `DATA` o
`SIGN` los escribirá en el archivo `log.txt` o `signals.txt`.

## Manejo de errores

Ante cualquier caso excepcional, ambos programas deben mostrar un mensaje de
error y finalizar con un código de error.
