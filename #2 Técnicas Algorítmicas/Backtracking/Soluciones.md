





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