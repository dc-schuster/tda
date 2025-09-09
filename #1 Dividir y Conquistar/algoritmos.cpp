#include <vector>
#include <cstdio>
#include <numeric>
#include <bits/stdc++.h>
using namespace std;

// Utilidades
using Matriz4x4 = std::array<std::array<long long, 4>, 4>;

static inline Matriz4x4 prod(const Matriz4x4& A, const Matriz4x4& B) {
    Matriz4x4 C{};
    for (int i = 0; i < 4; ++i)
        for (int k = 0; k < 4; ++k) {
            long long aik = A[i][k];
            for (int j = 0; j < 4; ++j)
                C[i][j] += aik * B[k][j];
        }
    return C;
}

static inline Matriz4x4 identidad4() {
    Matriz4x4 I{}; 
    for (int i = 0; i < 4; ++i) I[i][i] = 1;
    return I;
}

Matriz4x4 potencia(Matriz4x4 A, long long n) {
    Matriz4x4 res = identidad4();
    while (n > 0) {
        if (n & 1) res = prod(res, A);
        A = prod(A, A);
        n >>= 1;
    }
    return res;
}

inline Matriz4x4 add(const Matriz4x4& X, const Matriz4x4& Y) {
    Matriz4x4 Z{};
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            Z[i][j] = X[i][j] + Y[i][j];
    return Z;
}

bool matrixEq(const Matriz4x4& A, const Matriz4x4& B) {
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            if (A[i][j] != B[i][j]) return false;
    return true;
}

template <class Matrix>
void printMatrix(const Matrix& A) {
    if (A.size() == 0) { std::cout << "[]\n"; return; }
    const size_t rows = A.size();
    const size_t cols = A[0].size();

    // calcular anchos por columna
    std::vector<size_t> w(cols, 0);
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            std::ostringstream oss;
            oss << A[i][j];
            w[j] = std::max(w[j], oss.str().size());
        }
    }

    std::cout << "[";
    for (size_t i = 0; i < rows; ++i) {
        std::cout << (i == 0 ? "[" : "\n [");
        for (size_t j = 0; j < cols; ++j) {
            std::ostringstream oss; oss << A[i][j];
            std::cout << std::setw((int)w[j]) << oss.str();
            if (j + 1 < cols) std::cout << ", ";
        }
        std::cout << "]";
        if (i + 1 < rows) std::cout << ",";
    }
    std::cout << "]\n";
}

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


// Ejercicio 5
int potenciaLogaritmica(int base, int potencia) {
    // Casos Base
    if (potencia == 1) return base;
    if (potencia == 0) return 1;

    // Caso Recursivo
    if (potencia % 2 == 0) {
        int rec = potenciaLogaritmica(base, potencia / 2);
        return rec * rec;
    } else {
        int rec = potenciaLogaritmica(base, floor(potencia / 2));
        return rec * (rec * base);
    }
}


// Ejercicio 6
int overloadMaximoMontaña(vector<int> &array, int start, int end) {

    int length = end - start + 1;

    // Caso Base
    if (length == 1) return array[start];
    if (length == 2) {
        if (array[start] < array[end]) return array[end];
        return array[start];
    }
    
    // Caso Recursivo
    int mid = (length / 2) - 1 + start;

    if (array[mid - 1] < array[mid]) {
        return overloadMaximoMontaña(array, mid, end);
    } else {
        return overloadMaximoMontaña(array, start, mid - 1);
    }
}

int maximoMontaña(vector<int> &array) {
    return overloadMaximoMontaña(array, 0, array.size() - 1);
}


// Ejercicio 8
int overloadMaximaSubsecuencia(vector<int> &array, int start, int end) {

    size_t length = end - start + 1;
    size_t mid = floor((length / 2)) + start - 1;

    if (length == 1) return array[start];

    int leftMax  = overloadMaximaSubsecuencia(array, start, mid);
    int rightMax = overloadMaximaSubsecuencia(array, mid + 1, end);

    int midLeft = INT_MIN, acc = 0;
    for (int i = mid; i >= start; --i) {
        acc += array[i];
        midLeft = max(midLeft, acc);
    }

    int midRight = INT_MIN; acc = 0;
    for (int i = mid + 1; i <= end; ++i) {
        acc += array[i];
        midRight = max(midRight, acc);
    }

    return std::max({leftMax, rightMax, midLeft + midRight});
}

int maximaSubsecuencia(vector<int> &array) {
    return overloadMaximaSubsecuencia(array, 0, array.size() - 1);
}


// Ejercicio 9
Matriz4x4 potenciaSum(Matriz4x4 &A, int n) {
    if (n == 1) return A;
    
    Matriz4x4 half = potenciaSum(A, n / 2);
    Matriz4x4 halfPower = potencia(A, n / 2);
    return add(half, prod(halfPower, half));
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

    // Ejercicio 5
    int result51 = potenciaLogaritmica(-100, 0);
    int result52 = potenciaLogaritmica(-5, 3);
    int result53 = potenciaLogaritmica(2, 7); 
    int works5   = (result51 == 1) && (result52 == -125) && (result53 == 128);
    printf("Ejercicio 5: %s\n", works5 ? "true" : "false"); 

    // Ejercicio 6
    vector<int> array61 = {-1, 3, 8, 22, 30, 22, 8, 4, 2, 1};
    int result6 = maximoMontaña(array61);
    printf("Ejercicio 6: %s\n", (result6 == 30) ? "true" : "false"); 

    // Ejercicio 8
    vector<int> array81 = {3, -1, 4, 8, -2, 2, -7, 5};
    vector<int> array82 = {3, -1, 4, 8, 5, 2, -7, 5, 2};
    int result81 = maximaSubsecuencia(array81);
    int result82 = maximaSubsecuencia(array82);
    printf("Ejercicio 8: %s\n", (result81 == 14 && result82 == 21) ? "true" : "false"); 

    // Ejercicio 9
    Matriz4x4 matriz9 = {{
        {2, 3, 4, 1},
        {3, 1, 5, 7},
        {6, 6, 1, 2},
        {4, 7, 3, 4}
    }};
    Matriz4x4 matriz9expected = {{
        {400201842, 447098367, 364633941, 395350809},
        {680277669, 760374819, 618974952, 671242023},
        {579481236, 647017926, 528814818, 573235302},
        {751744032, 839570307, 685533561, 743192634}
    }};
    Matriz4x4 matriz9result = potenciaSum(matriz9, 8);
    printf("Ejercicio 9: %s\n", (matrixEq(matriz9result, matriz9expected)) ? "true" : "false");
}
