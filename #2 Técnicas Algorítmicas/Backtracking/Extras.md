# Demostración Complejidad (I)

Queremos calcular la complejidad de:

```cpp
void f(int k) {
  for (int i = k; i < n; i++) {
    f(i + 1);
  }
}
```

Sea $T(k)$ la complejidad de el llamado a $f(k)$.
Cuando $k = n$ realizamos 0 llamados. Por lo tanto definimos:

- $T(n) = 1$

Cuando $k \lt n$, iteramos desde $i = k$ hasta $n - 1$, y para cada iteración hacemos $f(i+1)$. Como cada iteración cuesta $T(i + 1)$, podemos escribir a $T(k)$ como:

$$
T(k) =
\begin{cases}
1 & k = n \quad \\
1 + \sum^{n-1}_{i=k}T(i+1) & k < n
\end{cases}
$$

---

Sea $r$ la cantidad de elementos restantes, tal que $r = n - k$, definimos $S(r) = T(k)$. Como $r = n - k$, $k = n - r$, por lo tanto:

$$
S(r) = T(n - r) =
\begin{cases}
1 & r = 0 \quad \\
1 + \sum^{n-1}_{i=n - r}T(i+1) & 0 \lt r \le n
\end{cases}
$$

Desarrollamos $\sum^{n-1}_{i=n - r}T(i+1)$:

$$
T(n-r+1) + T(n-r+2) + \dots + T(n-1) + T(n) \\
$$

Por definición de $S(r) = T(n - r)$
- $T(n-r+1)$ significa que $r = r - 1 \implies T(n-r+1) = S(r-1)$
- $T(n-r+2)$ significa que $r = r - 2 \implies T(n-r+2) = S(r-2)$
- $\dots$
- $T(n-1)$ significa que $r = 1 \implies T(n-1) = S(1)$
- $T(n)$ significa que $r = 0 \implies T(n) = S(0)$

Por lo tanto, $\sum^{n-1}_{i=n - r}T(i+1) = \sum_{j=0}^{r-1} S(j)$. Entonces:

$$
S(r) =
\begin{cases}
1 & r = 0 \quad \\
1 + \sum_{j=0}^{r-1} S(j) & 0 \lt r \le n
\end{cases}
$$

---

Busquemos una conjetura. Primero veamos los valores de distintos $S(r)$ con $r$ *pequeño*.

- $S(0) = 1$
- $S(1) = 1 + \sum_{j=0}^{0} S(j) = 1 + S(0) = 2$
- $S(2) = 1 + \sum_{j=0}^{1} S(j) = 1 + S(0) + S(1) = 4$
- $S(3) = 1 + \sum_{j=0}^{2} S(j) = 1 + S(0) + S(1) + S(2) = 8$
- $S(4) = 1 + \sum_{j=0}^{3} S(j) = 1 + S(0) + S(1) + S(2) + S(3) = 16$
- $S(5) = 1 + \sum_{j=0}^{4} S(j) = 1 + S(0) + S(1) + S(2) + S(3) + S(4) = 32$

Vemos que para $r > 1$, $S(r)$ parece devolver $2^r$. Probémoslo por inducción.

---

Sea:
$$
S(r) =
\begin{cases}
1 & r = 0 \quad \\
1 + \sum_{j=0}^{r-1} S(j) & 0 \lt r \le n
\end{cases}
$$

Quiero demostrar que $\forall \ r \in \mathbb{N} : r \gt 1$: $S(r) = 2^r$. 

Mi hipótesis inductiva es: $P(r) \equiv S(r) = 2^r$.

Quiero ver que $P(r) \implies P(r+1)$.

$P(r+1) \equiv S(r+1) = 2^{r+1}$

$(I): S(r) = 1 + \sum_{j=0}^{r-1} S(j) = 1 + S(0) + S(1) + \dots + S(r - 1)$ 

$S(r+1) = 1 + \sum_{j=0}^{r} S(j) = \underbrace{1 + S(0) + S(1) + \dots + S(r-1)}_{\text{Por} \ (I): \ S(r) \ = \ 2^r} + \underbrace{S(r)}_{HI: \ 2^r}$

Por lo tanto $S(r+1) = 2^r + 2^r = 2^r \cdot (1 + 1) = 2^r \cdot 2 = 2^{r+1}$

En conclusión, la complejidad del algoritmo es de $\Theta(2^n)$