# [Borrar](https://codeforces.com/group/yuAAIJ8c1R/contest/629197/problem/B)

Tenemos un string $s$ de $n$ caracteres. Queremos borrar el string por completo, pero para esto, solo contamos con la siguiente operación:

- Borramos un substring (contiguo) de caracteres **iguales**, luego concatenamos las partes restantes.

Queremos calcular cuál es la mínima cantidad de operaciones necesarias para eliminar todo el string.

Por ejemplo, si tenemos el string $acccad$:

1. Delete [1, 3] $acccad$
2. Delete [0, 1] $aad$
3. Delete [0, 0] $d$

Entonces la mínima cantidad de operaciones es 3.

- La longitud del string es: $1 \leq n \leq 500$

# Idea del Algoritmo

Tomamos $l$, $r$ arbitrarios, tales que $0 \leq l \leq r \lt |s|$.

1. Borramos el substring de caracteres $s[l]$.
2. Buscamos algun $j$ tal que $l \lt j \lt r$ y $s[l] = s[j]$. Y borramos lo que hay entre $s[l]$ y $s[j]$. Luego, nos ahorramos una operación, ya que $s[l]$ y $s[j]$ se juntan, y la próxima vez que borremos, lo haremos en mayor cantidad.

Para esto, usaremos una matriz de $|s|-1 \times |s|-1$.

- $\forall \ i \in \mathbb{Z} : 0 \leq i \leq |s|-1 \implies M[i][i] = 1$. Esto es así porque para borrar desde $i$ hasta $i$, necesitamos una operación. Por otro lado, en todo momento pedimos que $l \leq r$, ya que nos interesa borrar desde principio a fin, no de fin a principio.

Notemos que queremos devolver el valor de $M[0][|s|-1]$.
