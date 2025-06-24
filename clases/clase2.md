---
title: Clase 2
layout: default
nav_order: 3
---

# Clase 2

* Tipos de kernel. Kernel de Linux. Arquitectura.
* Mecanismo de arranque del kernel.
* Procesos.
* Scheduler.
* Gestión de procesos: Estados, visualización.
* Creación de procesos: `fork()`

{: .nota-title }
> Material
>
> * [Presentación](https://docs.google.com/presentation/d/1k4_qzy1bh7mKbOa2QoFThZ_oRMASUCi9I5pEYrxVzu8/edit?usp=drive_link)
>
> * [Material adicional y ejemplos de código](https://github.com/cese-sopg/cese-sopg.github.io/tree/main/material-clases/clase2)

## Prácticas

### Práctica 1

Escribir un programa que al invocarlo como `./es-ascii archivo` informa si el
`archivo` contiene texto ASCII o no (es decir, si todos los caracteres son bytes
entre 0 y 127).

En caso de error, el programa debe informar la causa y finalizar con
código de error.

### Práctica 2

Escribir un programa que al invocarlo como `./rot13 archivo` encripta el
`archivo` mediante el algoritmo de cifrado
[ROT13](https://en.wikipedia.org/wiki/ROT13).

Asumir que el contenido del archivo puede ser más grande que la memoria
disponible. La conversión debe hacerse sobre el mismo archivo abierto en modo
`O_RDWR`, y usando la función `lseek`.

En caso de error, el programa debe informar la causa y finalizar con
código de error.

### Práctica 3

Escribir un programa que cree una instancia hija con la función `fork()`. Luego
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

### Práctica 4

Editar el código del programa anterior e invertir los tiempos utilizados en
`sleep()` entre las instancias padre e hijo. Compilar y ejecutar. ¿Cómo es el
comportamiento en este caso del proceso hijo? ¿Termina el proceso normalmente?
¿Qué ocurre cuando termina su ejecución el proceso padre?

### Práctica 5

Implementar un _shell_ primitivo, que permita ejecutar comandos simples
mediante la sintaxis `<comando> <argumento> <argumento> ...`.

El ciclo principal debe ser algo como:

```
while true {
    Mostrar el prompt ("$ ")
    Leer una línea de la entrada estándar
    En caso de EOF:
        fin
    Dividir la línea en tokens [1] y verificar que haya al menos un token (el
    nombre del comando a ejecutar)
    fork()
    En el padre:
      esperar a que el hijo finalice
    En el hijo:
      usar alguna de las funciones exec() para ejecutar el subcomando
}
```

Verificar el estado de error de todas las funciones de biblioteca invocadas.
¿Qué debería hacer el programa ante un error?

Nota: para `[1]` puede ser útil la función
[`strtok()`](https://man7.org/linux/man-pages/man3/strtok.3.html)
