# Cálculo de Complejidad.

## 1 - Identificar los parámetros de la recurrencia.

- $a$: Número de subproblemas en los que se divide el problema.
- $c$: Factor de reducción de tamaño. Notamos que cada subproblema tiene como tamaño máximo, $\frac{n}{c}$.
- $f(n)$: Costo de dividir y combinar resultados. Por ejemplo, en Merge Sort, $f(n) = O(n)$. Esto es así porque una vez que ya tenemos los resultados recursivos y queremos combinar los resultados, usamos la funcion *merge*, que combina los dos arreglos. En el peor caso, vamos a tener que recorrer ambos arreglos completamente, costando $O(n)$.
- $n_0$: Tamaño base del problema a partir del cual se resuelve directamente en tiempo constante. Por ejemplo, en Merge Sort, el tamaño base es cuando la lista tiene tamaño 1 o 0. Claramente una lista de tamaño 1 o 0, ya está ordenada.

## 2 - Escribir la recurrencia.

$$
T(n) =
\begin{cases}
\Theta(1) & n \le n_0 \quad \\
a\,T\!\left(\dfrac{n}{c}\right) + f(n) & n > n_0
\end{cases}
$$

## 3 - Aplicar el Teorema Maestro

Comparar $f(n)$ con $n^{\log_{c}a}$.

- **Caso 1:**
  Si $f(n) = O(n^{\log_c a - \varepsilon})$ para algún $\varepsilon > 0$,entonces la complejidad es:
  $T(n) = \Theta(n^{\log_c a})$
- **Caso 2:**
  Si $f(n) = \Theta(n^{\log_c a})$, entonces la complejidad es:
  $T(n) = \Theta(n^{\log_c a} \cdot \log \ n)$.
- **Caso 3:**
  Si $f(n) = \Omega(n^{\log_c a + \varepsilon})$ para algún $\varepsilon > 0$, y además $a \cdot f(\frac{n}{c}) \le k \cdot f(n)$ para algún $k \lt 1$, entonces la complejidad es:
  $T(n) = \Theta(f(n))$
