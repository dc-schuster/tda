

# [Convertibilidad](https://codeforces.com/group/yuAAIJ8c1R/contest/631549/problem/B)

Tenemos un numero $x$ y lo queremos convertir en un número $y$.

Para esto, podemos realizar dos operaciones:
- $x = x \times 2$
- $x = x \times 10 + 1$

Queremos primero, encontrar si podemos convertir $x$ en $y$. Pensemos en qué casos NO es posible convertir $x$ en $y$.

Elijamos un $x$ y un $y$ arbitrarios y simulemos los distintos pasos.

```mermaid
graph TD
    A["x = 4, y = 10"]

    %% Nivel 1
    A -- "×2"        --> L1L["x = 8"]
    A -- "×10 + 1"   --> L1R["x = 41"]

    %% Nivel 2
    L1L -- "×2"        --> L2LL["x = 16"]
    L1L -- "×10 + 1"   --> L2LR["x = 81"]
    L1R -- "×2"        --> L2RL["x = 82"]
    L1R -- "×10 + 1"   --> L2RR["x = 411"]

    %% Nivel 3
    L2LL -- "×2"        --> L3LLL["x = 32"]
    L2LL -- "×10 + 1"   --> L3LLR["x = 161"]

    L2LR -- "×2"        --> L3LRL["x = 162"]
    L2LR -- "×10 + 1"   --> L3LRR["x = 811"]

    L2RL -- "×2"        --> L3RLL["x = 164"]
    L2RL -- "×10 + 1"   --> L3RLR["x = 821"]

    L2RR -- "×2"        --> L3RRL["x = 822"]
    L2RR -- "×10 + 1"   --> L3RRR["x = 4111"]
```

Como vemos, $x$ es estrictamente creciente. Esto se debe a que el input de $x$ es mayor o igual a 1 y las operaciones son productos con numeros positivos y sumas con positivos. Sabiendo esto, una vez que recibamos un $x$ mayor a $y$, podemos dejar de buscar.
