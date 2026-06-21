---
title: Trabajo práctico 2
layout: default
nav_order: 10
nav_exclude: true
---

# Trabajo práctico 2

## Objetivo

Tomar el código del [Trabajo práctico 1](tp1.md) y adaptarlo para que, en lugar
de recibir los comandos desde `stdin`, funcione como un servidor TCP que recibe
los comandos a través de la red.

El servidor debe:

1. Esperar a que un cliente se conecte mediante el protocolo TCP, puerto 5000.

2. Esperar a que el cliente envíe un _comando_ a ejecutar. El comando se
   especifica como una secuencia de caracteres ASCII hasta el `\n`.

3. Realizar la operación correspondiente, enviando la respuesta al cliente.

4. Volver al paso 2 para atender el siguiente comando del mismo cliente.

5. Cuando el cliente cierra la conexión, volver al paso 1 para esperar a que se
   conecte un nuevo cliente.

Es decir, mientras la conexión permanezca abierta, el servidor atiende todos los
comandos que envíe el cliente (de la misma manera en que el TP1 atiende los
comandos recibidos por `stdin`).

Los comandos que acepta el servidor son los mismos que en el TP1.

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
* El cliente envía un comando desconocido o con formato incorrecto (por
  ejemplo, `SET` sin argumentos o con solo un argumento).

## Cliente

Dado que el protocolo de comunicación es ASCII, no es necesario programar un
cliente sino que se pueden utilizar herramientas como `nc` (netcat) o `telnet`.

En ubuntu se pueden instalar con: `apt install netcat` o `apt install telnet`.

## Ejemplo

* En la consola #1 (server):

```
$ ./server
PID: 12345
```

* En la consola #2 (client): `nc localhost 5000`. Si la conexión es exitosa, el proceso
  se queda esperando a recibir entrada de `stdin`.

```
$ nc localhost 5000
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
$
```

* Mientras no se cierre la conexión, el servidor sigue atendiendo comandos sobre
  la misma sesión. La conexión se cierra desde el cliente (por ejemplo, con
  `Ctrl+C` o `Ctrl+D` en `nc`).

----

## Entrega

**Fecha límite para la entrega 1:** clase 7

**Fecha límite para la entrega 2:** una semana luego de la clase 8 (opcional en
caso de haber aprobado la entrega 1, se puede realizar para mejorar la nota del
TP)

* Realizar los cambios sobre el mismo repositorio del TP1.

* Crear un *issue* o *pull request* con el título `Entrega TP2` y asignarlo al
  usuario `dessaya`.


## Nota

La nota del TP se determina en base a la correctitud, prolijiidad y elegancia
del código.

La nota final de la materia es un promedio entre la nota de los TPs y la nota del
examen final.
