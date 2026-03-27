---
title: Trabajo práctico
layout: default
nav_order: 9
nav_exclude: false
---

# Trabajo práctico

## Objetivo

Escribir un servidor TCP que permite almacenar información ASCII en forma de
_clave-valor_.

El servidor debe:

1. Esperar a que un cliente se conecte mediante el protocolo TCP, puerto 5000.

2. Esperar a que el cliente envíe un _comando_ a ejecutar. El comando se
   especifica como una secuencia de caracteres ASCII hasta el `\n`.

3. Realizar la operación correspondiente.

4. Cortar la conexión con el cliente y volver al paso 1.

Los comandos que acepta el servidor son:

* `SET <clave> <valor>\n`:
  * Se crea en el servidor un archivo llamado `<clave>` con el contenido
    indicado en `<valor>` (sin incluir el `\n`).
  * Se responde al cliente `OK\n`.
* `GET <clave>`:
  * Si existe el archivo correspondiente, se responde al cliente con:
    `OK\n<valor>\n` (es decir, una línea de texto que dice `OK` y otra que
    contiene el contenido del archivo).
  * Si no existe, se responde con `NOTFOUND\n`
* `DEL <clave>`:
  * Si existe la el archivo correspondiente, se elimina.
  * Tanto si existe como no, se responde `OK\n`.

### SIGUSR1

El servidor debe además escuchar la señal `SIGUSR1`, y al recibirla, si hay un
cliente conectado, debe desconectarlo inmediatamente y pasar a esperar a que se
conecte otro cliente. Si no hay ningún cliente conectado, el servidor debe
ignorar la señal.

### Mensajes en `stdout`

Al iniciar, el servidor debe imprimir su PID en `stdout` para que pueda ser
utilizado posteriormente para enviarle señales.

Cuando se conecta un cliente, el servidor debe imprimir en `stdout` el mensaje
`cliente conectado: <IP del cliente>`, y cuando se desconecta, debe imprimir
`cliente desconectado: <IP del cliente>`.

### Manejo de errores

Ante cualquier caso excepcional, se debe informar la causa imprimiendo un
mensaje en `stderr`. Además, si se trata de un problema irrecuperable,
el proceso debe finalizar con código de error. Al menos se deben manejar los
siguientes casos:

* Alguna de las llamadas de sistema devuelve un error.
* El cliente se desconecta inesperadamente.
* El cliente envía un comando desconocido o con formato incorrecto (por
  ejemplo, `SET` sin argumentos o con solo un argumento).

## Cliente

Dado que el protocolo de comunicación es ASCII, no es necesario programar un
cliente sino que se pueden utilizar herramientas como `nc` (netcat) o `telnet`.

En ubuntu se pueden instalar con: `apt install netcat` o `apt install telnet`.

## Ejemplo

* En la consola #1 (server): `./server`

* En la consola #2 (client): `nc localhost 5000`. Si la conexión es exitosa, el proceso
  se queda esperando a recibir entrada de `stdin`.

```
$ nc localhost 5000
SET manzana apple
OK
$ nc localhost 5000
SET perro dog
OK
$ nc localhost 5000
SET hola hello
OK
$ nc localhost 5000
GET perro
OK
dog
$ nc localhost 5000
GET casa
NOTFOUND
$ nc localhost 5000
DEL perro
OK
$ nc localhost 5000
GET perro
NOTFOUND
$
```

----

## Entrega

Entregar por mail, adjuntando el código fuente o (preferentemente) un link a un
repositorio de Github.

* **Fecha límite para la primera entrega:** hasta clase 6
* **Fecha límite de aprobación:** hasta clase 8

Una vez recibida la corrección se permiten hasta 2 reentregas, siempre que sea antes
de la fecha límite de aprobación.

## Nota

La nota del TP se determina en base a la correctitud, prolijiidad y elegancia
del código.

La nota final de la materia es un promedio entre la nota del TP y la nota del
examen final.
