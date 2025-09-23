# King Army
$$
D(i) =
\begin{cases}
1 & i = 0 \quad \\
1 & i = 1 \quad \\
d_{i-1} + d_{i-2} & i \gt 1
\end{cases}
$$

La solución de programación dinámica sería algo como: Dado un dia $N$, queremos devolver el número de personas de su ejército. Se pide un algoritmo $O(N)$ para resolver el problema. Vamos a hacer un *for loop* de $N$ iteraciones, vamos a guardar en un vector de longitud $N-1$ los resultados para cada día. Cuando completamos el índice $N-1$ ya encontramos la solución.

*Optimización: Como para un día i necesitamos únicamente los dos días previos, podemos encontrar la solución en $O(n)$ con complejidad espacial $O(1)$, guardando en variables los resultados de los dias $d_{i-1}$ y $d_{i-2}$*.

```cpp
uint64_t kingArmy(uint32_t n) {

    vector<uint64_t> dias(n, 0);

    for (size_t i = 2; i < n; i++) {
        dias[i] = dias[i-1] + dias[i-2];
    }

    return dias[n - 1];
}
```

La complejidad es de $O(n)$ ya que hacemos un for loop de $O(n)$, el loop realiza operaciones $O(1)$.

---

# Vacations

Tenemos $N$ días de vacaciones, tenemos $2$ actividades disponibles, cada día puede tener disponible *ninguna*, *alguna* o *ambas*.

Para un día dado, podemos:
- Hacer una actividad que este disponible, si no la hicimos el día anterior.
- Descansar.

## Inciso A

La idea del algoritmo es la siguiente:

Armamos una matriz de $N \times 3$, donde vamos guardando la mínima cantidad de descansos posibles para un día dado, si ese día descansamos, competimos (en caso de ser posible) o vamos al gimnasio (en caso de ser posible). Si no es posible realizar una determinada actividad, entonces ponemos el valor en $INF$, de esta forma al elegir el mínimo en la próxima *iteración*, no vamos a tener en cuenta este caso, ya que sabemos que siempre habrá una opción más barata (la de descansar).

Usando el ejemplo del enunciado:
- $N = 3$
- $G = [F, T, T, F]$
- $C = [T, T, F, F]$

|    Matriz $M$ |               Descanso ("D")                | Gimnasio ("G")                 | Competir ("C")              |  Comentario                                                                                                                       |
|      :-:      |                   :-:                       |  :-:                           |   :-:                       |   :-:                                                                                                                             | 
| N = 0         | `1`                                         |   `INF`                        | `0`                         |  Inicializamos los valores nosotros. Gimnasio está en $INF$ ya que $G[0] = F$                                                     |
| N = 1         | `1 + min(M[0]["D"], M[0]["G"], M[0]["C"])`  |  `min(M[0]["D"], M[0]["C"])`   | `min(M[0]["D"], M[0]["G"])` |  Cuando una actividad está disponible, al no descansar, <br> elegimos el minimo entre no haber hecho la actividad el día anterior |
| N = 2         | `1 + min(M[1]["D"], M[1]["G"], M[1]["C"])`  |  `min(M[1]["D"], M[1]["C"])`   | `INF`                       |                                                                                                                                   |
| N = 3         | `1 + min(M[2]["D"], M[2]["G"], M[2]["C"])`  |  `INF`                         | `INF`                       |                                                                                                                                   |

Entonces lo que vamos a devolver es `min(M[N]["D"], M[N]["G"], M[N]["C"])`. Usando esta misma idea, creamos una función que toma un día ($N$) y una actividad (*"D"*, *"G"* o *"C"*) y nos devuelve la cantidad (mínima) de descansos hasta ese día, si en el mismo realizamos la actividad dada. Luego, devolvemos `min(f(N, "D"), f(N, "G"), f(N, "C"))`


```cpp
enum Actividad {
    Descansar, 
    Gimnasio, 
    Competir
};

int minDescansos(vector<vector<int>> &dp, int n, Actividad actividad, const vector<bool> &gimnasio, const vector<bool> &competir) {
   
    if (dp[n][actividad] != -1) return dp[n][actividad];

    if (actividad == Descansar) {
        dp[n][Descansar] = 1 + min({
            minDescansos(dp, n - 1, Descansar, gimnasio, competir),
            minDescansos(dp, n - 1, Gimnasio,  gimnasio, competir),
            minDescansos(dp, n - 1, Competir,  gimnasio, competir)
        });
    } else if (actividad == Gimnasio) {
        if (!gimnasio[n]) {
            dp[n][Gimnasio] = INF;
        } else {
            dp[n][Gimnasio] = min({
                minDescansos(dp, n - 1, Descansar, gimnasio, competir),
                minDescansos(dp, n - 1, Competir,  gimnasio, competir),
            });
        }
    } else if (actividad == Competir) {
        if (!competir[n]) {
            dp[n][Competir] = INF;
            return dp[n][Competir];
        }
        dp[n][Competir] = min({
            minDescansos(dp, n - 1, Descansar, gimnasio, competir),
            minDescansos(dp, n - 1, Gimnasio,  gimnasio, competir),
        }); 
    }

    return dp[n][actividad];
}

int vacaciones(uint64_t n, const vector<bool> &gimnasio, const vector<bool> &competir) {

    vector<vector<int>> dp(gimnasio.size(), vector<int>(3, -1));

    dp[0][Descansar] = 1;
    dp[0][Gimnasio]  = gimnasio[0] ? 0 : INF;
    dp[0][Competir]  = competir[0] ? 0 : INF;

    return min({
        minDescansos(dp, n, Descansar, gimnasio, competir),
        minDescansos(dp, n, Gimnasio,  gimnasio, competir),
        minDescansos(dp, n, Competir,  gimnasio, competir)
    });
}
```

La complejidad del algoritmo es $\Theta(n)$.

## Inciso B
Queremos probar la correctitud de nuestro algoritmo. Vamos a hacerlo por inducción

Sea:
- `INF` un número que representa el infinito.
- `G` una lista de booleanos, que indica si para un día $0 \le i \lt |G|$ la actividad *gimnasio* está disponible.
- `C` una lista de booleanos, que indica si para un día $0 \le i \lt |C|$ la actividad *competir* está disponible.
- `a` una actividad arbitraria.
- $P(n): \forall \ n \ge 0$ `vacaciones(n, G, C)` devuelve la mínima cantidad de días de descansos hasta el día n.

### Caso Base

$P(0):$ `vacaciones(0, G, C)` devuelve la mínima cantidad de días de descansos para el día 0.

Queremos saber la cantidad de días de descanso si `n = 0`. Para nuestras 3 posibles elecciones (*Descansar*, *Gimnasio* o *Competir*), inicializamos nuestra matriz `dp[N = 0]` de la siguiente manera: 
- `dp[0][Descansar] = 1`: Cada vez que elegimos descansar, se incrementa en uno la cantidad de días de descansos. Como estamos en el primer día, no pudimos haber descansado antes, por lo tanto estamos en el primer descanso, razón por la cual `dp[0][Descansar] = 1`.
- `dp[0][Gimnasio] = gimnasio[0] ? 0 : INF`: Si `gimnasio[0] = true` significa que podemos realizar dicha actividad el día 0, por lo tanto no habremos descansado, y la cantidad de descansos hasta dicho día es 0. Por la otra parte, si la actividad no está disponible dicho día, entonces escribimos `INF`.
- `dp[0][Competir] = competir[0] ? 0 : INF`: Si `competir[0] = true` significa que podemos realizar dicha actividad el día 0, por lo tanto no habremos descansado, y la cantidad de descansos hasta dicho día es 0. Por la otra parte, si la actividad no está disponible dicho día, entonces escribimos `INF`.

Luego:
```cpp
return min({
    minDescansos(dp, n, Descansar, gimnasio, competir),
    minDescansos(dp, n, Gimnasio,  gimnasio, competir),
    minDescansos(dp, n, Competir,  gimnasio, competir)
});
```
devolvemos el mínimo entre estos tres llamados. Si vemos cómo está escrita `minDescansos()` vemos:
```cpp
if (dp[n][actividad] != -1) return dp[n][actividad];
```

Como `n = 0`, da igual cuál sea la actividad, sabemos que está inicializada, por lo tanto `dp[n][actividad] != -1` es `true` y se devuelve `dp[n][actividad]`, que es justamente lo que queremos.


### Paso Inductivo

Sea $P(n+1):$ `vacaciones(n + 1, G, C)` devuelve la mínima cantidad de días de descansos hasta el día n + 1.

Vamos a asumir que $P(n)$ vale, queremos mostrar que vale $P(n + 1)$. En particular, que $P(n) \implies P(n + 1)$.

- $(I)$ `vacaciones(n, G, C)` devuelve el resultado correcto, sabemos en particular que `dp[k][actividad]` tiene los valores correctos para toda actividad y para todo $0 \le k \le n$. 

Sabemos que `vacaciones(n, G, C)` devuelve el resultado correcto, esto significa que `minDescansos(dp, k, a, G, C)` también devuelve el resultado correcto (la mínima cantidad de días de descanso si el día `n` realizo la actividad `a`) $\forall \ 0 \le k \le n$.

Se ejecuta: 
$(II)$
```cpp
return min({
    minDescansos(dp, n + 1, Descansar, gimnasio, competir),
    minDescansos(dp, n + 1, Gimnasio,  gimnasio, competir),
    minDescansos(dp, n + 1, Competir,  gimnasio, competir)
});
```
es decir, llamamos a `minDescansos(dp, n + 1, Descansar, G, C)`, `minDescansos(dp, n + 1, Gimnasio, G, C)`, `minDescansos(dp, n + 1, Competir, G, C)` y devolvemos el menor número. Veamos qué pasa en cada llamado.

#### `minDescansos(dp, n + 1, Descansar, G, C)`

Como `dp[n+1][Descansar]` no está inicializada, entonces está en `-1`, por lo tanto `dp[n+1][Descansar] != -1` evalúa a `false`.

Como la actividad es `Descansar`, `if (actividad == Descansar)` evalúa a `true` y el código a ejecutar ahora es:

```cpp
dp[n+1][actividad] = 1 + min({
    minDescansos(dp, (n + 1) - 1, Descansar, gimnasio, competir),
    minDescansos(dp, (n + 1) - 1, Gimnasio,  gimnasio, competir),
    minDescansos(dp, (n + 1) - 1, Competir,  gimnasio, competir)
});
```

Como elegimos descansar, la cantidad de días de descanso se incrementa en 1. Como $P(n)$ es verdadera, entonces sabemos que 
```cpp
min({
    minDescansos(dp, (n + 1) - 1, Descansar, gimnasio, competir),
    minDescansos(dp, (n + 1) - 1, Gimnasio,  gimnasio, competir),
    minDescansos(dp, (n + 1) - 1, Competir,  gimnasio, competir)
})
```
devuelve el valor correcto, por lo tanto incrementamos en uno la cantidad correcta de días descansados. Entonces tenemos en `dp[n+1][Descansar]` tenemos el valor correcto.

#### `minDescansos(dp, n + 1, Gimnasio, G, C)`

Como `dp[n+1][Gimnasio]` no está inicializada, entonces está en `-1`, por lo tanto `dp[n+1][Gimnasio] != -1` evalúa a `false`.

Como la actividad es `Gimnasio`, `if (actividad == Gimnasio)` evalúa a `true` y el código a ejecutar ahora es:

```cpp
if (actividad == Gimnasio) {
    if (!gimnasio[n+1]) {
        dp[n+1][Gimnasio] = INF;
    } else {
        dp[n+1][Gimnasio] = min({
            minDescansos(dp, (n + 1) - 1, Descansar, gimnasio, competir),
            minDescansos(dp, (n + 1) - 1, Competir,  gimnasio, competir),
        });
    }
}
```
Hay dos opciones para `gimnasio[n+1]`, o es `true` o es `false`. 

- Si fuese `false`, significa que no podemos realizar la actividad el día n+1, por lo tanto al ser imposible, ponemos `dp[n+1][actividad] = INF`, cuando se compute el mínimo ($II$), *no se tendrá en cuenta* el INF, al ser el elemento neutro de la función `min()`.
- Si fuese `true`, luego no se incrementan los días de descanso, y guardamos en `dp[n+1][Gimnasio]` el mínimo de días de descanso entre `minDescansos(dp, n, Descansar, G, C)` y `minDescansos(dp, n, Competir,  G, C)`, que por $HI$ sabemos que devuelve el valor correcto.

Luego `dp[n+1][Gimnasio]` almacena el valor correcto.

#### `minDescansos(dp, n + 1, Competir, G, C)`

Como `dp[n+1][Competir]` no está inicializada, entonces está en `-1`, por lo tanto `dp[n+1][Competir] != -1` evalúa a `false`.

Como la actividad es `Competir`, `if (actividad == Competir)` evalúa a `true` y el código a ejecutar ahora es:

```cpp
if (actividad == Competir) {
    if (!competir[n+1]) {
        dp[n+1][Competir] = INF;
    } else {
        dp[n+1][Competir] = min({
            minDescansos(dp, (n + 1) - 1, Descansar, gimnasio, competir),
            minDescansos(dp, (n + 1) - 1, Gimnasio,  gimnasio, competir),
        });
    }
}
```
Hay dos opciones para `gimnasio[n+1]`, o es `true` o es `false`. 

- Si fuese `false`, significa que no podemos realizar la actividad el día n+1, por lo tanto al ser imposible, ponemos `dp[n+1][actividad] = INF`, cuando se compute el mínimo ($II$), *no se tendrá en cuenta* el INF, al ser el elemento neutro de la función `min()`.
- Si fuese `true`, luego no se incrementan los días de descanso, y guardamos en `dp[n+1][Competir]` el mínimo de días de descanso entre `minDescansos(dp, n, Descansar, G, C)` y `minDescansos(dp, n, Competir,  G, C)`, que por $HI$ sabemos que devuelve el valor correcto.

Luego `dp[n+1][Competir]` almacena el valor correcto.


#### Conclusión

Demostramos que `dp[n+1][a]` almacena el valor correcto para toda actividad. Luego, como `vacaciones()` devuelve el mínimo entre `dp[n+1][Descansar]`, `dp[n+1][Gimnasio]` y `dp[n+1][Competir]`, entonces estamos devolviendo el mínimo entre 3 valores correctos. Por lo tanto nuestro algoritmo es correcto.

