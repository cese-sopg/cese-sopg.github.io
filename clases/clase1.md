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

Crear una carpeta llamada `prueba_ln` y dentro de ella un archivo de texto
llamado `datos.txt` con contenido simple. Luego, crear un enlace duro a
`datos.txt` llamado `copia_dura.txt` y un enlace simbólico llamado
`copia_simbolica.txt`. Verificar que los tres archivos existen y sus respectivos
números de inodo. Probar qué ocurre al modificar el contenido de uno de ellos.

Finalmente, eliminar el archivo original `datos.txt` y verificar qué enlaces
siguen funcionando. Explicar por qué el comportamiento de cada uno fue
diferente.

### Práctica 2

Crear un archivo llamado `notas.txt` que contenga algún texto.
Luego, realizar las siguientes tareas, determinando comando apropiado a ejecutar
para cada una, y verificando qué ocurre al intentar leer y/o escribir el
contenido del archivo:

  * Eliminar todos los permisos del archivo `notas.txt` para todos los usuarios.
  * Dar permisos de lectura solamente al propietario del archivo.
  * Cambiar los permisos para que todos los usuarios puedan leer y escribir el
    archivo.
  * Finalmente, establecer los permisos para que solo el propietario pueda leer
    y escribir, y el grupo y otros usuarios no tengan ningún permiso.

### Práctica 3

Escribir un programa en C que al invocarlo como `./tam archivo` imprime el tamaño en
bytes del `archivo`.

1. Usando las funciones
   [`open`](https://man7.org/linux/man-pages/man2/open.2.html) y
   [`lseek`](https://man7.org/linux/man-pages/man2/lseek.2.html).
2. Usando la función
   [`stat`](https://man7.org/linux/man-pages/man2/stat.2.html).

En caso de error, el programa debe informar la causa y finalizar con
código de error.
