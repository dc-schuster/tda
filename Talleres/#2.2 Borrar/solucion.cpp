#include <iostream>
#include <string>
#include <vector>
using namespace std;

int borrar(string str) {
    int longitud = str.size();
    vector<vector<int>> dp(longitud, vector<int>(longitud, 0));
    
    // Llenamos la diagonal en 1
    for (int i = 0; i < longitud; i++) {
        dp[i][i] = 1;
    }

    // Armamos el resto de la matriz
    // Queremos ir analizando bloques de mayor y mayor longitud. Arrancamos en 2, ya que el caso 1
    // está ya contemplado en el for loop anterior.
    for (int subStrLen = 2; subStrLen < longitud + 1; subStrLen++) {
        for (int l = 0; l + subStrLen - 1 < longitud; l++) {
            int r = l + subStrLen - 1;

            // Borramos desde l, el substring que caracteres s[l]
            dp[l][r] = 1 + dp[l + 1][r];

            // Intentamos buscar un j tal que s[l] = s[j]. Luego borramos lo que está en el medio (l+1 hasta j-1)
            for (int j = l + 1; j <= r; ++j) {
                if (str[j] == str[l]) {
                    int operaciones;
                    if (j - 1 >= l + 1) {
                        operaciones = dp[l + 1][j - 1];
                    } else {
                        operaciones = 0;
                    };
                    dp[l][r] = min(dp[l][r], operaciones + dp[j][r]);
                }
            }
        }
    }
    return dp[0][longitud - 1];

}

int main() {
    int n;
    string s;
    if (!(cin >> n)) return 0;
    cin >> s;

    cout << borrar(s) << "\n";
    return 0;
}