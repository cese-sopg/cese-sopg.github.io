---
title: Trabajo práctico
layout: default
nav_order: 9
---

# Trabajo práctico

**Tiempo de entrega:** hasta clase 6

**Fecha límite de aprobación:** hasta clase 8

Una vez recibida la corrección se permiten hasta 2 reentregas, siempre que sea antes
de la fecha límite de aprobación.

## Nota

La nota del TP se determina en base a la correctitud, prolijiidad y elegancia
del código.

La nota final de la materia es un promedio entre la nota del TP y la nota del
examen final.

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
`SIGN:2` y contnuar con su ejecución normal. Las signals se pueden recibir
más de una vez.

En cualquier momento, además, el proceso writer puede detectar el EOF en la
entrada estándar (indicada presionando `CTRL+D` en la consola). En este caso el
writer debe finalizar la ejecución.

### Proceso Reader

Este proceso leerá los datos del named FIFO y según el encabezado `DATA` o
`SIGN` los escribirá en el archivo `log.txt` o `signals.txt`.

## Manejo de errores

Ante cualquier caso excepcional, ambos programas deben mostrar un mensaje de
error apropiado y finalizar con un código de error.

Casos a tener en cuenta como mínimo:

* Error al crear y/o abrir el named FIFO.
* Writer escribe en el pipe pero el reader está muerto.
* Reader lee del pipe pero el writer está muerto.
* Cualquier otro error al escribir o leer el FIFO.

