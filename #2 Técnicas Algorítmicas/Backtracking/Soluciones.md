# Suma Subconjuntos

## Idea de Algoritmo

Tenemos un multiconjunto $C = \{c_1, \dots, c_n\}$ de numeros naturales y un natural $k$, queremos determinar si existe un subconjunto de $C$ cuya sumatoria sea $k$. En particular, queremos devolver un vector $p = (p_1, \dots, p_n)$ de valores binarios, donde si $p_i = 1$, entonces $c_i$ pertenece a la solución.

Podas:

- Si para un estado dado, la *suma acumulada* excede el valor de k, entonces no tiene sentido seguir desarrollandola, ya que estamos trabajando con valores naturales (mayores a 0), por ende el valor de *suma acumulada* seguirá creciendo y nunca llegaremos a $k$.
- Otra posible poda podría ser tener una matriz dep $i \times k$, donde vamos guardando el valor de verdad de si es posible llegar a una solución válida desde el índice $i$, con una suma restante $k$.

## Implementación

*No se implementa la segunda poda*

```cpp
bool overloadSumaSubconjuntos(vector<int> &multiconjunto, int i, int &k, vector<uint8_t> &parcial) {

    if (k < 0) return false;
    if (i == -1) return (k == 0); // Si recorrimos todo el multiconjunto, hay solución
                                  // si y solo si la suma restante es 0.

    bool sinRestar = overloadSumaSubconjuntos(multiconjunto, i - 1, k, parcial);
    if (sinRestar) return true;
  
    // Restamos
    k -= multiconjunto[i];
    // Como restamos, actualizamos la solución parcial.
    parcial[i] = 1;  
    bool restando = overloadSumaSubconjuntos(multiconjunto, i - 1, k, parcial);

    if (restando) {
        return true;
    } else {
        // No sirvió restar, restauramos tanto k como la solución parcial.
        parcial[i] = 0;
        k += multiconjunto[i];
        return false;
    }
}

vector<uint8_t> sumaSubconjuntos(vector<int> multiconjunto, int k) {
    vector<uint8_t> parcial(multiconjunto.size(), 0);

    bool possible = overloadSumaSubconjuntos(multiconjunto, multiconjunto.size() - 1, k, parcial);

    if (possible) {
        return parcial;     
    } else {
        for (int i = 0; i < parcial.size(); i++) {
            parcial[i] = 0;
        }
        return parcial;
    }
}
```

---

# Magi Cuadrados

Un *cuadrado mágico* de orden $n$ es un cuadrado (matriz de $n \times n$) con los numeros $1, \dots, n^2$ tal que todas sus filas, columnas y las dos diagonales suman lo mismo.

## Inciso A

*¿Cuántos cuadrados habría que generar para encontrar todos los cuadrados mágicos si se utiliza una solución de fuerza bruta?*

Habría que generar todos los posibles cuadrados. Veamos exactamente cómo es que se arma un cuadrado. Pongamos como ejemplo $n = 3$.

Sabemos que el cuadrado tendra los siguiente numeros: $[1, 2, 3, 4, 5, 6, 7, 8, 9]$. Bien, tenemos $9$ posibles elecciones para poner en la primera fila y primera columna. Elegimos (sin sentido) el 1. Bien, ahora tenemos $8$ posibles elecciones. Rapidamente vemos que cada vez que hacemos una elección, las posibles elecciones se reducen a razón de $1$. La operación matemática que representa este comportamiento es el factorial ($!$). Por ende si tenemos $3^2$ numeros, podemos generar $(3^2)!$ cuadrados.

En conclusión, la cantidad de cuadrados a generar para encontrar todos los cuadrados mágicos si se utiliza una solución de fuerza bruta, es $\Theta((n^2)!)$

## Inciso B

Queremos escribir un algoritmo que use backtracking y solucione el problema. Como queremos que todas las filas, columnas y diagonales tengan el mismo valor de sumatoria, podemos mantener una variable que tenga el valor de sumatoria de una fila (podría ser columna o diagonal, pero como vamos a resolver fila por fila, mantengo el valor de sumatoria de la primera completada), luego si al terminar una columna, fila o diagonal, la sumatoria no coincide con el valor de esta variable, entonces la solución parcial no es valida.

```cpp
void incrementIndexes(size_t max, uint16_t &i, uint16_t &j) {
    if (j + 1 > max) {
        j = 0;
        i++;
    } else {
        j++;
    }
    return;
}

void decrementIndexes(size_t max, uint16_t &i, uint16_t &j) {
    if (j == 0) {
        i--;
        j = max;
    } else {
        j--;
    }
}

bool matchColumnSum(vector<vector<uint64_t>> &cuadrado, uint64_t &expectedSum) {
    uint64_t columnSum = 0;
    bool result = true; 
    for (uint16_t column = 0; column < cuadrado.size(); column++) {
        for (uint16_t row = 0; row < cuadrado.size(); row++) {
            columnSum += cuadrado[row][column];  
        }
        result = result && (columnSum == expectedSum);
        columnSum = 0;
    }
    return result;
}

bool matchDiagonalSum(vector<vector<uint64_t>> &cuadrado, uint64_t &expectedSum) {

    uint16_t index = 0;
    uint64_t diagonalSum = 0;
    bool result = true;

    // First Diagonal
    for (index = 0; index < cuadrado.size(); index ++) {
        diagonalSum += cuadrado[index][index];
    }
    result = result && (diagonalSum == expectedSum);

    // Reset index & diagonalSum
    index = 0;
    diagonalSum = 0;

    // Second Diagonal
    for (size_t i = 0; i < cuadrado.size(); ++i) {
        diagonalSum += cuadrado[i][cuadrado.size() - 1 - i];
    }
  
    return (result && diagonalSum == expectedSum);
}

bool overloadMagiCuadrados(vector<vector<uint64_t>> &cuadrado, vector<uint16_t> &disponibles, uint16_t i, uint16_t j, uint64_t currentSum) {
  
    // Cuadrado 100% completo
    if (i == cuadrado.size()) {
        // Chequeo columnas y diagonales. Las filas ya se asumen chequeadas.
        bool matchedColumnSum = matchColumnSum(cuadrado, currentSum);
        bool matchedDiagonalSum = matchDiagonalSum(cuadrado, currentSum);
        return (matchedColumnSum && matchedDiagonalSum);
    }

    if (i == 1 && j == 0) {
        // Ya completé toda la primera fila. Calculamos la suma de la misma.
        currentSum = 0;
        for (int index = 0; index < cuadrado.size(); index++) {
            currentSum += cuadrado[0][index];
        }
    }

    // Completé 2 filas o más, quiero ver que la sumatoria de la última fila completada == currentSum
    // Me fijo solo de la última ya que si complete la fila i, asumo que la fila i-1 cumple que su sumatoria == currentSum 
    if (i >= 2 && i < cuadrado.size() && j == 0) {
        uint64_t rowSum = 0;
        for (int index = 0; index < cuadrado.size(); index++) {
            rowSum += cuadrado[i - 1][index];
        }
        if (rowSum != currentSum) return false;
    }

    // Tenemos dos posibles decisiones:
    //     1 - Ponemos en (i, j) el valor de de disponibles[0]
    //     2 - Mandamos disponibles[0] al final de disponibles, y ponemos en (i, j) el valor de disponibles[1]
    for (size_t k = 0; k < disponibles.size(); ++k) {
        uint16_t disponible = disponibles[k];

        // Colocar v en la celda y quitarlo de disponibles (swap+pop)
        cuadrado[i][j] = disponible;
        swap(disponibles[k], disponibles.back());
        uint16_t sacado = disponibles.back();
        disponibles.pop_back();

        // Actualizamos indices
        uint16_t ni = i, nj = j;
        incrementIndexes(cuadrado.size() - 1, ni, nj);

        if (overloadMagiCuadrados(cuadrado, disponibles, ni, nj, currentSum))
            return true;

        // Hacemos backtrack
        disponibles.push_back(sacado);
        std::swap(disponibles[k], disponibles.back()); 
        cuadrado[i][j] = 0; 
    }
    return false;
}

vector<vector<uint64_t>> magiCuadrados(uint16_t n) {
  
    vector<vector<uint64_t>> cuadrado(n, vector<uint64_t>(n, 0));

    vector<uint16_t> disponibles(n * n, 0);
    for (int index = 0; index < n * n; index++) {
        disponibles[index] = index + 1;
    }

    uint16_t i = 0;
    uint16_t j = 0;
    uint64_t currentSum = 0;

    overloadMagiCuadrados(cuadrado, disponibles, i, j, currentSum);
    return cuadrado;
}
```

## Inciso D

Sea $k$ el numero mágico. Tenemos los numeros del $1$ al $n^2$. Por lo tanto la suma total de todos los valores en el arreglo $[1, \dots, n^2]$ es de $\sum^{n^2}_{i = 1}i$. Sabemos que podemos reescribir una sumatoria de la forma $\sum^{m}_{i = 1}i$ como $\frac{m \ (m \ + \ 1)}{2}$. Por lo tanto si tomamos $m = n^2$, obtenemos:

- $\sum^{n^2}_{i = 1}i = \frac{n^2 \ (n^2 \ + \ 1)}{2}$

Bien, entonces para un cuadrado mágico de $n \times n$, sabemos que la sumatoria de todos sus valores es $\frac{n^2 \ (n^2 \ + \ 1)}{2}$, que en particular equivale a $n \cdot k$ (ya que tenemos $n$ filas y cada fila suma $k$).

El desarrollo queda:

- $\sum^{n^2}_{i = 1}i = \frac{n^2 \ (n^2 \ + \ 1)}{2} = n \cdot k$
- $k = \frac{n^2 \ (n^2 \ + \ 1)}{2n} = \frac{n^3 + \ n}{2}$

---

# Maxi Subconjunto

Tenemos una matriz simétrica M de $n \times n$ números naturales, y un nuḿero $k$, queremos encontrar un subconjunto $I$ de ${1, \dots, n}$ con $|I| = k$ que maximice $\sum_{i, j \in I} M_{ij}$.

Por ejemplo, si tenemos $k = 3$ y la siguiente matriz:

$$
M=\begin{pmatrix}
0 & 10 & 10 & 1 \\
10 & 0 & 5 & 2 \\
10 & 5 & 0 & 1 \\
1 & 2 & 1 & 0
\end{pmatrix}
$$

entonces $I = [1, 2, 3]$.

## Inciso A

```cpp
int sumatoriaConIndices(vector<vector<int>> &matriz, vector<uint64_t> &indices) {
    size_t i = 0;
    size_t j = 0;
    int sumatoria = 0;

    for (int indiceI = 0; indiceI < indices.size(); indiceI++) {
        for (int indiceJ = 0; indiceJ < indices.size(); indiceJ++) {
            sumatoria += matriz[indices[indiceI]][indices[indiceJ]];
        }
    }
    return sumatoria;
}

void overloadMaxiSubconjunto(
    vector<vector<int>> &matriz,
    vector<size_t> &solucionParcial,
    vector<size_t> &mejorSolucion,
    int &mejorSumatoria,
    size_t indiceStart,
    size_t &k
) {

    // Si indiceStart es igual a n pero la solucionParcial no tiene k elementos, no es una solución válida.
    if (indiceStart == matriz.size() && solucionParcial.size() != k) return;

    // Si ya elegimos k elementos, calculamos la sumatoria.
    if (solucionParcial.size() == k) {
        int sumatoria = sumatoriaConIndices(matriz, solucionParcial);
        if (sumatoria > mejorSumatoria) {
            mejorSumatoria = sumatoria;
            mejorSolucion = solucionParcial;
        }
        return;
    }

    // Para cada posible indice, pruebo usarlo o no usarlo.
    for (size_t indice = indiceStart; indice < matriz.size(); indice++) {
        // Uso el indice
        solucionParcial.push_back(indice);
        // Hacemos recursion
        overloadMaxiSubconjunto(matriz, solucionParcial, mejorSolucion, mejorSumatoria, indice + 1, k);

        // Lo más intuitivo es hacer ahora, algo como:
        // No lo uso
        // solucionParcial.pop_back();
        // overloadMaxiSubconjunto(matriz, solucionParcial, mejorSolucion, mejorSumatoria, indice + 1, k);

        // Sin embargo, en la siguiente iteración vamos a llamar a overloadMaxiSubconjunto con indice = indice + 1, sin haber usado el indice actual.
        // Entonces para evitar estados repetidos que hagan que nuestra función tarde más, dejamos comentado ese caso 'No lo uso'.

        solucionParcial.pop_back();
    }  
}

vector<uint64_t> maxiSubconjunto(vector<vector<int>> &matriz, size_t &k) {

    vector<size_t> solucionParcial;
    vector<size_t> mejorSolucion;
    int mejorSumatoria = 0;

    overloadMaxiSubconjunto(matriz, solucionParcial, mejorSolucion, mejorSumatoria, 0, k);

    return mejorSolucion;
}
```

# Inciso B

```cpp
int sumatoriaConIndices(vector<vector<int>> &matriz, vector<uint64_t> &indices) {
    for (int indiceI = 0; indiceI < indices.size(); indiceI++) {
        for (int indiceJ = 0; indiceJ < indices.size(); indiceJ++) {
            sumatoria += matriz[indices[indiceI]][indices[indiceJ]];
        }
    }
    return sumatoria;
}
```
La complejidad de `sumatoriaConIndices()` es de $\Theta(k^2)$, ya que solo la llamamos cuando $|indices| = k$, y hacemos dos *nested for loops* de $k$ iteraciones cada uno.

---

```cpp
void overloadMaxiSubconjunto(...) {
    // Si ya elegimos k elementos, calculamos la sumatoria.
    if (solucionParcial.size() == k) {
        int sumatoria = sumatoriaConIndices(matriz, solucionParcial);
    }
```
$\Theta(k^2)$

```cpp
    for (size_t indice = indiceStart; indice < matriz.size(); indice++) {
        overloadMaxiSubconjunto(matriz, solucionParcial, mejorSolucion, mejorSumatoria, indice + 1, k);
    }  
}
```
Justificación idéntica a [esta](./Extras.md#demostración-complejidad-i).
$\Theta(2^n)$

---

*Nota: $\Theta(k^2)$ es despreciable frente a $\Theta(2^n)$*.

En conclusión, la complejidad de nuestro algoritmo es $\Theta(2^n)$.


---

# Ruta Mínima

Dada una matriz $D$ de $n \times n$ números naturales, queremos encontrar una permutación de $\{1, \dots, n\}$ que minimice $D_{\pi(n), \pi(0)} + \sum_{i=0}^{n-2}D_{\pi(i), \pi(i+1)}$.

Por ejemplo, para esta matriz:
$$
M=\begin{pmatrix}
0 & 1 & 10 & 10 \\
10 & 0 & 3 & 15 \\
21 & 17 & 0 & 2 \\
3 & 22 & 30 & 0
\end{pmatrix}
$$

la mejor permutación es $\pi(i)$. Esto es así porque la forma más barata de ir desde 0 hasta n, y luego volver, es:
- $D[0][1] = 1$ (Vamos desde 0 hasta 1)
- $D[1][2] = 3$ (Vamos desde 1 hasta 2)
- $D[2][3] = 2$ (Vamos desde 2 hasta 3)
- $D[3][0] = 3$ (Vamos desde 3 hasta 0)

El costo total termina siendo $9$, y en particular es el mínimo que podemos conseguir.

# Inciso A
Arranco en la posición 0, tengo que ir de la forma más barata posible hasta $|D| - 1$. Por ejemplo, para una matriz de $4 \times 4$, si arranco desde la posición 0, tengo 3 opciones.
- Voy de 0 a 1.
- Voy de 0 a 2.
- Voy de 0 a 3.

Supongamos que elegimos ir al 2. Ahora tenemos 2 opciones. La opción de ir del 2 al 0 la descartamos, ya que si volvemos al 0, ¿vamos a volver al 2 de nuevo?
Entonces nuestras opciones son:
- Voy de 2 a 1.
- Voy de 2 a 3. 

Supongamos que elegimos ir al 1. Ahora tenemos una última opcion, que es la de ir de 1 a 3.

*Nota: Se pide que la permutación sea una función biyectiva, por ende tenemos que realizar $n$ pasos, y en el último indice de la permutación, debe estar el valor $n-1$*.

```cpp
void overloadRutaMinima(
    vector<vector<uint64_t>> &matriz, 
    vector<size_t> disponibles,
    vector<signed long long> &solucionParcial,
    signed long long &sumatoriaParcial,
    vector<signed long long> &mejorSolucion,
    signed long long &minimaSumatoria
) {
    
    // Poda. Si la sumatoria actual es mayor o igual a la sumatoria de la mejor solución,
    // no vale la pena seguir por esta rama. Cortamos.
    if (sumatoriaParcial >= minimaSumatoria) {return;}

    // Calculamos la sumatoria de la solucion parcial
    if (disponibles.empty()) {
        uint64_t total = sumatoriaParcial + matriz[solucionParcial.back()][matriz.size() - 1];

        if (total < minimaSumatoria) {
            mejorSolucion = solucionParcial;
            mejorSolucion.push_back(matriz.size() - 1);
            minimaSumatoria = total;
        }
        return;
    }

    // Probamos "todas" las combinaciones
    for (size_t index = 0; index < disponibles.size(); index++) {
        size_t disponible = disponibles[index];
        uint64_t costo = matriz[solucionParcial.back()][disponible];

        sumatoriaParcial += costo;
        solucionParcial.push_back(disponible);

        size_t last = disponibles.size() - 1;
        swap(disponibles[index], disponibles[last]);
        disponibles.pop_back();

        overloadRutaMinima(
            matriz, 
            disponibles,
            solucionParcial, 
            sumatoriaParcial, 
            mejorSolucion, 
            minimaSumatoria
        );

        disponibles.push_back(disponible);
        swap(disponibles[index], disponibles[last]);

        solucionParcial.pop_back();
        sumatoriaParcial -= costo;    
    }

    // Ya la mejor solución fue calculada y está en mejorSolucion
    return;
}

vector<signed long long> rutaMinima(vector<vector<uint64_t>> &matriz) {
    vector<size_t> disponibles = {};
    for (size_t disponible = 1; disponible < matriz.size() - 1; disponible++) {
        disponibles.push_back(disponible);
    }

    signed long long sumatoriaParcial = 0;
    vector<signed long long> solucionParcial = {0};

    vector<signed long long> mejorSolucion;
    signed long long minimaSumatoria = INF;

    overloadRutaMinima(
        matriz, 
        disponibles,
        solucionParcial, 
        sumatoriaParcial,
        mejorSolucion, 
        minimaSumatoria
    );

    return mejorSolucion;
}
```

# Inciso B
Justificación idéntica a [esta](./Extras.md#demostración-complejidad-ii).
En conclusión, la complejidad de nuestro algoritmo es $\Theta(n!)$.

*En cuanto a la complejidad espacial, no lo calculamos ya que se ve claramente que es despreciable. No realizamos copias de las variables por cada llamado.*

# Inciso C

Ya tenemos implementadas la poda:
- Si la sumatoria actual es mayor o igual a la sumatoria de la mejor solución, no vale la pena seguir por esta rama, ya que no hay valores en la matriz negativos, que puedan reducir el costo de la ruta.
