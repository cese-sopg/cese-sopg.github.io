---
title: Clase 2
layout: default
parent: Inicio
nav_order: 2
nav_exclude: true
---

# Clase 2
{: .no_toc }

* Tipos de kernel. Kernel de Linux. Arquitectura.
* Proceso de arranque.
* Procesos y threads.
* Scheduler de Linux
* Gestión de procesos: Estados, visualización.
* Creación de procesos: `fork()`

## Prácticas
{: .no_toc .text-delta }

* Prácticas
{:toc}

## Práctica 1

Escribir un programa que cree una instancia hija con el syscall `fork()`. Luego
de `fork()`, la instancia padre ejecuta un sleep de 20 segundos y luego termina.
La instancia hija ejecuta un sleep de 40 segundos y luego termina.

Para compilar y probar, trabajar con dos instancias de consolas, una en cada
mitad horizontal de la pantalla. En una consola lanzar el programa y en la otra
visualizar el estado de los procesos (usar `ps -elf | grep [proceso]`) y observar
el estado de cada instancia.

¿Qué pasa con el proceso hijo cuando termina el proceso padre? ¿Terminan
normalmente?

{: .nota }
Incluir `<unistd.h>` para utilizar la función `sleep()`.

{: .nota }
Puede utilizarse el comando `watch` para ejecutar periódicamente el comando
`ps`. Ejemplo: `watch -n 1 “ps -elf | grep [proceso]”`

{: .nota }
Usar el nombre del proceso `“proceso”` y no `“./proceso”`, ya que al ser zombie
el comando `ps` lo muestra sin el `“./”`.

## Práctica 2

Editar el código del programa anterior e invertir los tiempos utilizados en
`sleep()` entre las instancias padre e hijo. Compilar y ejecutar. ¿Cómo es el
comportamiento en este caso del proceso hijo? ¿Termina el proceso normalmente?
¿Qué ocurre cuando termina su ejecución el proceso padre?
