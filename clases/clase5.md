---
title: Clase 5
layout: default
nav_order: 6
---

# Clase 5
{: .no_toc }

* Comunicación entre procesos: Sockets

{: .nota-title }
> Material
>
> * [Presentación](https://docs.google.com/presentation/d/1H13iBDSK98wg2ABpzAVLls2FFSeEqbFbg_B1RYF7ne8/edit?usp=drive_link)
>
> * [Material adicional y ejemplos de código](https://github.com/cese-sopg/cese-sopg.github.io/tree/main/material-clases/clase5)

## Práctica: Creación de un cliente-servidor TCP
{: .no_toc }

Desarrollar una calculadora distribuida.

* Cliente: Permite al usuario ingresar un número, luego elegir
una operación (`+`, `-`, `*`, `/`) de un menú y luego ingresar otro número. La
operación no la realizará este programa sino que será solicitada en forma
remota al servidor.
* Servidor: Recibirá una petición de una operación de suma, resta,
  multiplicación o división y devolverá el resultado. Todas las operaciones se
  harán con tipos de datos `float` y se utilizarán sockets TCP.

1. Con un protocolo ASCII:

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

1. Con un protocolo binario. Definir un `struct` para el mensaje hacia el
   servidor y otra para el mensaje hacia el cliente con los campos necesarios.
   Usar los mismos structs en ambos programas y enviarlos y recibirlos usando
   `read` y `write`.

Discutir qué ventajas y desventajas tiene cada opción de protocolo.
