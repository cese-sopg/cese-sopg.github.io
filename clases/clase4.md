---
title: Clase 4
layout: default
nav_order: 5
---

# Clase 4
{: .no_toc }

* Introducción a networking
* Comunicación entre procesos: Sockets (parte I)
* Presentación del Trabajo práctico. Entrega antes de clase 6.

{: .nota-title }
> Material
>
> * [Presentación](https://docs.google.com/presentation/d/1KrrIcEJh-uxxZBW8TLOqi0KmhC9CVBlrEaAkjp_BxQ0/edit?usp=drive_link)
>
> * [Material adicional y ejemplos de código](https://github.com/cese-sopg/cese-sopg.github.io/tree/main/material-clases/clase4)

## Prácticas

### Práctica 1: proxy

Implementar un simple servidor _proxy_ que reenvía datos de un cliente a otro:

```
A (client) ---> S (server) ---> B (client)
```

En este ejemplo, los clientes A y B se conectan al servidor S en dos puertos
diferentes (para poder diferenciarlos).

Una vez establecidas ambas conexiones, S recibe datos de A y los reenvía a B.
S finaliza su ejecución cuando cualquiera de los dos clientes se
desconecta.

### Práctica 2: chat

Implementar una aplicación simple de chat con un servidor y dos clientes:

```
A (client) <---> S (server) <---> B (client)
```

En este ejemplo, los clientes A y B se conectan al servidor S (en este caso
puede ser al mismo puerto ya que los clientes son simétricos).
Una vez establecidas ambas conexiones, S recibe datos de A y los reenvía a B **y
viceversa**. S finaliza su ejecución cuando cualquiera de los dos clientes se
desconecta.

Para que el servidor pueda leer datos de dos conexiones en forma simultánea,
una forma posible es utilizar la función `recv` con el flag `MSG_PEEK` (dado
que por defecto `read` y `recv` son bloqueantes). En las próximas clases
estudiaremos formas más sofisticadas de resolver este problema.

### Práctica 3: calculadora

Desarrollar una calculadora distribuida.

* Cliente: Permite al usuario ingresar un número, luego elegir
una operación (`+`, `-`, `*`, `/`) de un menú y luego ingresar otro número. La
operación no la realizará este programa sino que será solicitada en forma
remota al servidor.
* Servidor: Recibirá una petición de una operación de suma, resta,
  multiplicación o división y devolverá el resultado. Todas las operaciones se
  harán con tipos de datos `float` y se utilizarán sockets TCP.

El protocolo de comunicación es ASCII:

Petición de cálculo al servidor: `>CMD:%c,%f,%f\n` donde:
1. Comienza con `>`
2. `%c` se reemplaza por un caracter que indica el comando: `+`, `-`, `*` y `/`
3. `%f` se reemplaza por el número `float` ingresado
4. Finaliza con `\n`

Respuesta de petición hacia el cliente: `>CMD:%c,r:%f\n` (ej:
`>CMD:+,r:3.14\n`), donde:
1. Comienza con `>`
2. `%c` se reemplaza por un caracter que indica el comando: `+`, `-`, `*` y `/`
3. `%f` se reemplaza por el número float resultado de la operación

Respuesta en caso de error: `>ERR:%s\n` (ej: `>ERR:Division por cero\n`),
donde:
1. Comienza con `>`
2. `%s` se reemplaza por el mensaje de error

