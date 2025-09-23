#include <map>
#include <vector>
#include <cstdint>
#include <bits/stdc++.h>
using namespace std;

// Utils
signed long long int INF = 100000000;

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

// Ejercicio 9
uint64_t kingArmy(uint32_t n) {

    vector<uint64_t> dias(n, 0);

    for (size_t i = 2; i < n; i++) {
        dias[i] = dias[i-1] + dias[i-2];
    }

    return dias[n - 1];
}


// Ejercicio 10
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


// Ejercicio 12
struct optiData {
    int cantBilletes;
    int cantidadPagada;
    bool init;
};

optiData minOpti(optiData opti1, optiData opti2) {
    if (opti1.cantidadPagada < opti2.cantidadPagada) return opti1;
    if (opti1.cantidadPagada > opti2.cantidadPagada) return opti2;
    if (opti1.cantBilletes < opti2.cantBilletes)     return opti1;
    if (opti1.cantBilletes > opti2.cantBilletes)     return opti2;
    return opti1;
}

optiData optiPago(vector<vector<optiData>> &dp, vector<int> &billetes, int costo, int actual) {
    // dp es una matriz inicializada en optiData{INF, INF} para todo indice.

    // Queremos devolver la mejor solución utilizando los billetes de 0 a i (?)

    // Tenemos dos posibilidades:
    //  - usamos el billete b_n, reduciendo el costo
    //  - no usamos el billete b_n, no reducimos el costo

    if (dp[costo][actual].init) return dp[costo][actual];

    optiData base = {0, 0, true};

    if (costo > 0 && actual == billetes.size()) {
        // No hay solución posible, devolvemos INF para que no sea electo luego en el min.
        base.cantBilletes = INF;
        base.cantidadPagada = INF;
        dp[costo][actual] = base;
        return base;
    }

    if (costo == 0) {
        dp[costo][actual] = base;
        return base;
    }

    if (actual >= billetes.size()) {
        printf("Actual: %d\nSize: %d\nCosto: %d\n", actual, billetes.size(), costo);
    }

    // Calculamos el resultado utilizando el billete

    int nuevoCosto = costo - billetes[actual];
    if (nuevoCosto < 0) nuevoCosto = 0;
    optiData resultadoUsando = optiPago(dp, billetes, nuevoCosto, actual + 1);
    resultadoUsando.cantBilletes += 1;
    resultadoUsando.cantidadPagada += billetes[actual];
    resultadoUsando.init = true;

    // Calculamos el resultado sin usar el billete
    optiData resultadoSinUsar = optiPago(dp, billetes, costo, actual + 1);
    resultadoSinUsar.init = true;

    optiData result = minOpti(resultadoUsando, resultadoSinUsar);

    dp[costo][actual] = result;

    return result;
}