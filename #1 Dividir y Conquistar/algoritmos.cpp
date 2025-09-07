#include <vector>
#include <cstdio>
#include <numeric>
#include <bits/stdc++.h>
using namespace std;

// Utilidades


// Ejercicio 3
bool overloadMasALaIzquierda(vector<int> &array, size_t start, size_t end) {
    int length = end - start + 1;
        
    // Caso Base
    if (length == 2) return (array[start] > array[end]);

    // Caso Recursivo
    int mid = (length / 2) - 1 + start;

    int sumLeft  = std::accumulate(array.begin() + start, array.begin() + (mid + 1), 0);
    int sumRight = std::accumulate(array.begin() + (mid + 1), array.begin() + (end + 1), 0);

    return (
        sumLeft > sumRight && 
        overloadMasALaIzquierda(array, start, mid) &&
        overloadMasALaIzquierda(array, mid + 1, end)
    );
}

bool masALaIzquierda(vector<int> &array) {
    return overloadMasALaIzquierda(array, 0, array.size() - 1);
}

// Ejercicio 4
void overloadIndiceEspejo (vector<int> &array, size_t start, size_t end, int &result) {
    // Escribe en result:  i si existe un i tal que array[i] = i
    // Si no existe un i tal que array[i] = i, no modifica el valor de result
    if (result != -1) return;

    int length = end - start + 1;

    // Caso base
    if (length == 1) {
        if (array[start] == start) {
            result = start;
        }
        return;
    }

    // Caso recursivo
    int mid = start + (length + 1) / 2 - 1;  // ceil(length/2) - 1 + start
    if (array[mid] == mid) {
        result = mid;
        return;
    } else if (array[mid] > mid) {
        overloadIndiceEspejo(array, start, mid, result);
    } else if (array[mid] < mid) {
        overloadIndiceEspejo(array, mid + 1, end, result);
    }
}

int indiceEspejo(vector<int> &array) {
    // Devuelve i tal que array[i] = i. Si no existe:
    // Devuelve -1 si no existe un i tal que array[i] = i
    int result = -1;
    overloadIndiceEspejo(array, 0, array.size() - 1, result);
    return result;
}

// Main
int main() {

    // Ejercicio 3
    vector<int> array31 = {8, 6, 7, 4, 5, 1, 3, 2};
    vector<int> array32 = {8, 4, 7, 6, 5, 1, 3, 2};

    bool array31r  = masALaIzquierda(array31);
    bool array32r  = masALaIzquierda(array32);
    const char* result3 = (array31r && !array32r) ? "true" : "false";

    printf("Ejercicio 3: %s\n", result3);

    // Ejercicio 4
    vector<int> array41 = {-4, -1, 2, 4, 7};
    const char* result4 = (indiceEspejo(array41) == 2) ? "true" : "false";
    
    printf("Ejercicio 4: %s\n", result4);
}
