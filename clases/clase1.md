---
title: Clase 1
layout: default
nav_order: 2
---

# Clase 1

* Breve historia de UNIX. Introducción a GNU/Linux.
* Capas del sistema operativo. Separación entre userland y kernel space.
* Estándares: POSIX, SUS.
* Archivos. Inodos. Jerarquía de archivos estándar.
* Comandos básicos de Linux.
* Sistema de permisos.
* API de manejo de archivos.

{: .nota-title }
> Material
>
> * [Presentación](https://docs.google.com/presentation/d/1X9mGN_c7PF5vkQKUb5nhHEvSXe1Tsg_JFjBdcDmGyF4/edit?usp=drive_link)

## Prácticas

### Práctica 1

Escribir un programa que al invocarlo como `./tam archivo` imprime el tamaño en
bytes del `archivo`.

1. Usando las funciones
   [`open`](https://man7.org/linux/man-pages/man2/open.2.html) y
   [`lseek`](https://man7.org/linux/man-pages/man2/lseek.2.html).
2. Usando la función
   [`stat`](https://man7.org/linux/man-pages/man2/stat.2.html).

En caso de error, el programa debe informar la causa y finalizar con
código de error.

### Práctica 2

Escribir un programa que al invocarlo como `./es-ascii archivo` informa si el
`archivo` contiene texto ASCII o no (es decir, si todos los caracteres son bytes
entre 0 y 127).

En caso de error, el programa debe informar la causa y finalizar con
código de error.

### Práctica 3

Escribir un programa que al invocarlo como `./rot13 archivo` encripta el
`archivo` mediante el algoritmo de cifrado
[ROT13](https://en.wikipedia.org/wiki/ROT13).

Asumir que el contenido del archivo puede ser más grande que la memoria
disponible. La conversión debe hacerse sobre el mismo archivo abierto en modo
`O_RDWR`, y usando la función `lseek`.

En caso de error, el programa debe informar la causa y finalizar con
código de error.

