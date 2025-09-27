#include <vector>
#include <cstdint>
#include <bits/stdc++.h>
using namespace std;

// Utils
signed long long int INF = 100000000;

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


// Ejercicio 13
struct astro {
    bool init;
    int ganancia;
};

int astroTrade(vector<vector<astro>> &dp, vector<int> A, int c, int d) {
    // dp es una matriz de floor(|A| / 2) × |A| (asumiendo que |A| = días)

    // No puedo tener asteroides negativos.
    // No puedo comprar mas de un asteroide por día
    // No puedo estar en un día negativo
    if (c < 0 || c > d || d < 0 || c > A.size() / 2) return -INF;
    
    // No puedo tener asteroides el primer dia
    if (d == 0) return (c == 0 ? 0 : -INF); 

    if (dp[c][d].init) return dp[c][d].ganancia;

    int comprar = astroTrade(dp, A, c - 1, d - 1) - A[d - 1];
    int vender  = astroTrade(dp, A, c + 1, d - 1) + A[d - 1];
    int nada    = astroTrade(dp, A, c, d - 1);

    astro result = {true, max({comprar, vender, nada})}; 
    dp[c][d] = result;

    return result.ganancia;
}



// Ejercicio 14
struct item {
    int id;
    int tarda;
    int expira;
    int valor;
};
 
struct solucionFire {
    int valor;
    vector<item*> items;
    bool init;
};
 
bool itemComparator(const item& a, const item& b) {
    if (a.expira != b.expira) return a.expira < b.expira;
    if (a.tarda  != b.tarda ) return a.tarda  < b.tarda;
    return a.valor > b.valor;
}
 
solucionFire fire(vector<vector<solucionFire>> &dp, uint64_t n, int t_a, int &d_max, vector<item> &items) {
 
    solucionFire base = {0, {}, true};
 
    if (n >= items.size()) return base;
    if (t_a > d_max) return base;
 
    if (dp[n][t_a].init) return dp[n][t_a];
 
    // No salvo elemento
    solucionFire noSalvoElemento = fire(dp, n + 1, t_a, d_max, items);
    dp[n][t_a] = noSalvoElemento;
 
 
    // Salvo elemento.
    if (t_a <= items[n].expira - items[n].tarda - 1) {
        solucionFire salvoElemento = fire(dp, n + 1, t_a + items[n].tarda, d_max, items);
        salvoElemento.init = true;
        salvoElemento.valor += items[n].valor;
        salvoElemento.items.push_back(&items[n]);
 
        dp[n][t_a] = (salvoElemento.valor >= noSalvoElemento.valor ? salvoElemento : noSalvoElemento);
    }
 
    return dp[n][t_a];
}


// Ejercicio 20
#define NINIT (-1)
#define PATO 0
#define DODO 1
#define NINGUNO 2
const int MOD = 100000000;

int caesar(vector<vector<vector<int>>> &dp, const int mp, const int md, int np, int nd, int ut) {

    if ((ut == 1 || ut == 0) && dp[np][nd][ut] != NINIT) return dp[np][nd][ut];

    int soluciones = 0;
    bool addPatos = (ut == DODO && np > 0) || (ut == NINGUNO);
    bool addDodos = (ut == PATO && nd > 0) || (ut == NINGUNO);

    if (np + nd == 0) return 1;             // No hay más que hacer. Solución encontrada.
    if (!addPatos && !addDodos) return 0;   // Quedan tropas pero no las podemos ubicar.

    if (addPatos) {
        // Agregamos Patos
        int maxIterPatos = min(np, mp);
        for (int patoAmount = 1; patoAmount <= maxIterPatos; patoAmount++) {
            soluciones += caesar(dp, mp, md, np - patoAmount, nd, PATO);
        }
    } 
    if (addDodos) {
        // Agregamos Dodos
        int maxIterDodos = min(nd, md);
        for (int dodoAmount = 1; dodoAmount <= maxIterDodos; dodoAmount++) {
            soluciones += caesar(dp, mp, md, np, nd - dodoAmount, DODO);
        }
    }
    dp[np][nd][ut] = soluciones % MOD;
    return dp[np][nd][ut];
}

