---
title: Clase 5
layout: default
nav_order: 6
---

# Clase 5
{: .no_toc }

* Comunicación entre procesos: Sockets (parte II)
* Comunicación entre procesos: Named FIFOS
* Multiplexed I/O

{: .nota-title }
> Material
>
> * [Presentación](https://docs.google.com/presentation/d/1H13iBDSK98wg2ABpzAVLls2FFSeEqbFbg_B1RYF7ne8/edit?usp=drive_link)
>
> * [Material adicional y ejemplos de código](https://github.com/cese-sopg/cese-sopg.github.io/tree/main/material-clases/clase5)

## Prácticas

### Práctica 1: calculadora v2

En la práctica 3 de la clase anterior se desarrolló una calculadora con un
protocolo de comunicación ASCII.

Modificar la aplicación para utilizar un protocolo binario. Definir un `struct`
para el mensaje hacia el servidor y otra para el mensaje hacia el cliente con
los campos necesarios. Usar los mismos structs en ambos programas y enviarlos y
recibirlos usando `read` y `write`.

Verificar que el protocolo sea _independiente de la
plataforma_; es decir que el servidor y cliente puedan ejecutarse en
plataformas diferentes.

Discutir qué ventajas y desventajas tiene cada opción de protocolo.

### Práctica 2: chat v2

En la práctica 2 de la clase anterior se desarrolló una aplicación de chat con
un servidor y dos clientes.

Modificar la aplicación usando alguna de las técnicas de entrada/salida multiplexada
para recibir información de ambos clientes en simultáneo.
