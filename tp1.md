---
title: Trabajo práctico 1
layout: default
nav_order: 9
nav_exclude: false
---

# Trabajo práctico 1

## Objetivo

Escribir un programa que permite almacenar información ASCII en forma de
_clave-valor_, recibiendo los comandos a ejecutar desde `stdin`.

El programa debe:

1. Esperar a que se ingrese un _comando_ por `stdin`. El comando se especifica
   como una secuencia de caracteres ASCII hasta el `\n`.

2. Realizar la operación correspondiente, escribiendo la respuesta en `stdout`.

3. Volver al paso 1.

El programa finaliza cuando se llega al fin de archivo (EOF) en `stdin`.

Los comandos que acepta el programa son:

* `SET <clave> <valor>\n`:
  * Se crea un archivo llamado `<clave>` con el contenido indicado en
    `<valor>` (sin incluir el `\n`).
  * Se responde `OK\n`.
* `GET <clave>`:
  * Si existe el archivo correspondiente, se responde con:
    `OK\n<valor>\n` (es decir, una línea de texto que dice `OK` y otra con el
    contenido del archivo).
  * Si no existe, se responde con `NOTFOUND\n`
* `DEL <clave>`:
  * Si existe el archivo correspondiente, se elimina.
  * Tanto si existe como no, se responde `OK\n`.

### Manejo de errores

Ante cualquier caso excepcional, se debe informar la causa imprimiendo un
mensaje en `stderr`. Además, si se trata de un problema irrecuperable,
el proceso debe finalizar con código de error. Al menos se deben manejar los
siguientes casos:

* Alguna de las llamadas de sistema devuelve un error.
* Se recibe un comando desconocido o con formato incorrecto (por
  ejemplo, `SET` sin argumentos o con solo un argumento).

## Ejemplo

* Se ejecuta el programa: `./tp1`

* El programa queda esperando a recibir entrada de `stdin`. Por cada comando
  ingresado, se imprime la respuesta correspondiente:

```
$ ./tp1
SET manzana apple
OK
SET perro dog
OK
SET hola hello
OK
GET perro
OK
dog
GET casa
NOTFOUND
DEL perro
OK
GET perro
NOTFOUND
```

* Notar que el programa finaliza al llegar al fin de archivo (EOF) en `stdin`.
  En la consola de Linux, esto se puede simular con `Ctrl+D`.

* Dado que la información se almacena en archivos, si se ejecuta el programa nuevamente, los
  archivos creados en la ejecución anterior siguen existiendo y pueden ser
  accedidos con los comandos `GET` o `DEL`:

```
$ ./tp1
GET manzana
OK
apple
```

----

## Entrega


**Fecha límite para la entrega 1:** clase 4

**Fecha límite para la entrega 2:** clase 6 (opcional en caso de haber aprobado
la entrega 1, se puede realizar para mejorar la nota del TP)

* Crear un repositorio **privado** de Github con el código fuente del programa,
  y un archivo `README.md` con el nombre del alumno, una breve descripción de la
  solución implementada e instrucciones para compilar y ejecutar el programa.

* Invitar al repositorio al usuario `dessaya`.

* Crear un *issue* o *pull request* con el título `Entrega TP1` y asignarlo al
  usuario `dessaya`.

## Nota

La nota del TP se determina en base a la correctitud, prolijiidad y elegancia
del código.

La nota final de la materia es un promedio entre la nota de los TPs y la nota del
examen final.
