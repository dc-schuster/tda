#include <cstdint>
#include <vector>
#include <string>
#include <iomanip>
#include <iostream>
#include <functional>
#include <type_traits>
#include <bits/stdc++.h>
using namespace std;

// Utils
signed long long int INF = numeric_limits<double>::infinity() / 2;

template <class T>
void printVector(const std::vector<T>& v, std::ostream& os = std::cout) {
    os << '[';
    const char* sep = "";
    for (const auto& x : v) { os << sep << x; sep = ", "; }
    os << ']';
}

void printMatrix(const std::vector<std::vector<uint64_t>>& M) {
    if (M.empty()) { std::cout << '\n'; return; }

    std::size_t w = 1;
    for (const auto& fila : M)
        for (uint64_t x : fila) {
            std::size_t len = std::to_string(x).size();
            if (len > w) w = len;
        }

    for (const auto& fila : M) {
        for (std::size_t j = 0; j < fila.size(); ++j) {
            std::cout << std::setw(w) << fila[j];
            if (j + 1 < fila.size()) std::cout << ' ';
        }
        std::cout << '\n';
    }
}

// Ejercicio 1 (Suma Subconjuntos)
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



// Ejercicio 2 (Magi Cuadrados)
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

    bool result = overloadMagiCuadrados(cuadrado, disponibles, i, j, currentSum);

    printf("MagiCuadrado (%d):\n", n);
    printMatrix(cuadrado);

    return cuadrado;
}


// Ejercicio 3 (Maxi Subconjunto)
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


// Ejercicio 4 (Ruta Mínima)
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


// Ejercicio 8 (Cadenas De Adición)
bool valida(vector<int>) {
}

bool cadenasDeAdicionOverload(vector<int> &result, vector<int> &current, const vector<int> numeros, const int n, int i) {
    
    // Poda por optimalidad
    if (current.size() >= result.size() && !result.empty()) {
        return false;
    }

    // Poda por factibilidad
    // Para cada paso habría que ir verificando que para cada 2 <= j <=, existe k_1, k_2 tal que x_k_1 + x_k_2 = x_j
    // Basicamente llamar a valida
    
    if (i == numeros.size() - 1) {
        // Si o si tengo que agregar n (pedimos que numeros sea un arreglo [2, ..., n])
        current.push_back(n);
        if (valida(current) && (result.empty() || result.size() > current.size())) {
            result = current;
            current.pop_back();
            return true;
        } else {
            current.pop_back();
            return false;
        }
    }

    // Agregamos el siguiente numero
    current.push_back(numeros[i]);
    bool agregando = cadenasDeAdicionOverload(result, current, numeros, n, i + 1);
    current.pop_back();

    // No agregamos el siguiente numero
    bool noAgregando = cadenasDeAdicionOverload(result, current, numeros, n, i + 1);

    return (agregando || noAgregando);
}

vector<int> cadenasDeAdicion(int n) {
    vector<int> numeros;
    for (int i = 2; i <= n; i++) {
        numeros.push_back(i);
    }

    vector<int> result;
    vector<int> current;
    current.push_back(1);

    bool possible = cadenasDeAdicionOverload(result, current, numeros, n, 0);

    if (possible) {
        printf("Hay solución, y es:");
        printVector(result);
    } else {
        printf("No existe solución");
    }
}


int main() {
    // Ejercicio 1 (Suma Subconjuntos)
    vector<int> C1 = {6,12,6}; int k1 = 12;
    auto M1 = sumaSubconjuntos(C1, k1);
    int s1 = 0; for (size_t i=0;i<C1.size() && i<M1.size();++i) if (M1[i]) s1 += C1[i];
    const bool r1 = (s1 == k1);

    vector<int> C2 = {3,34,4,12,5,2}; int k2 = 9;
    auto M2 = sumaSubconjuntos(C2, k2);
    int s2 = 0; for (size_t i=0;i<C2.size() && i<M2.size();++i) if (M2[i]) s2 += C2[i];
    const bool r2 = (s2 == k2);

    vector<int> C3 = {2,4,6}; int k3 = 5;
    auto M3 = sumaSubconjuntos(C3, k3);
    int s3 = 0; for (size_t i=0;i<C3.size() && i<M3.size();++i) if (M3[i]) s3 += C3[i];
    const int r3 = (s3 != k3);

    printf("(Ejercicio 1):  %s\n", (r1 && r2 && r3) ? "true" : "false");

    // Ejercicio 2 (Magi Cuadrados)
    // magiCuadrados(3);
    // magiCuadrados(4);

    // Ejercicio 4 (Ruta Mínima)
    vector<vector<uint64_t>> matriz4 = {
        {0, 1, 10, 10},
        {10, 0, 3, 15},
        {21, 17, 0, 2},
        {3, 22, 30, 0}
    };
    vector<signed long long> result4 = rutaMinima(matriz4);
    
    return 0;
}