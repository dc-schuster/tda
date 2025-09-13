# [Alfabéticamente](https://codeforces.com/group/yuAAIJ8c1R/contest/629197/problem/A)

- Tengo $n$ strings de letras minúsculas.
- Quiero ordenar los strings alfabéticamente.
- No tengo permitido cambiarlos de lugar, solo darlos vuelta (leer de atras hacia adelante).
- Dos palabras iguales consecutivas se consideran ordenadas.
- Para dar vuelta el string $i$, se gasta $c_i$ de energía.
- Queremos minimizar la cantidad de energía que se necesita gastar para que las palabras queden en orden alfabético.

# Idea de Algoritmo

Para cada string tenemos dos opciones:

1. Damos vuelta el string, pagando $c_i$.
2. Dejamos el string tal cual, pagando $0$.

Entonces la idea sería armar una matriz de $n \times 2$. Donde en $M[i][0]$ guardo el costo minimo parcial sin dar vuelta el string $i$ y en $M[i][1]$ guardo el costo minimo parcial dando vuelta el string $i$. En cada paso, nos aseguramos de que el string actual esté ordenado con respecto al anterior. Si no lo está, ponemos el costo en +-1.

Por ejemplo:

- $n$: 3
- $c$: [100, 200, 300]
- ["za", "yb", "xc"]

$$
\begin{bmatrix}
-1 & 100 \\
-1 & 300 \\
300 & 600
\end{bmatrix}
$$

Como vemos, devolvemos $min\{M[n-1][0], M[n-1][1]\}$. Si pasase que tenemos -1 tanto en $M[n-1][0]$ como en $M[n-1][1]$, devolvemos $-1$.

# Reducción de Memoria

Es probable que nos quedemos sin memoria para casos extremadamente grandes. Si pensamos un poco más, no es necesario guardar toda la matriz.
Si para algún estado cualquiera, conocemos los costos actuales, nos da igual todo lo anterior. Además, esto nos permite podar casos en donde llegamos a filas de la forma $[-1, -1]$. Llegar a una fila de la forma $[-1, -1]$ significa que no es posible cumplir con la consigna.

Dicho esto, replanteamos nuestra matriz de $n \times 2$ y nos quedamos con algunas variables que vayan guardando los costos de invertir el string y el costo de no hacerlo.