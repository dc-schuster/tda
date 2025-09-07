
#include <bits/stdc++.h>
#include <cstdint>
#include <vector>
#include <cstdio>
#include <cmath>
using namespace std;

bool habraOverflow(uint32_t a, uint32_t b) {
    if (a > std::numeric_limits<uint32_t>::max() / b) {
        return true;
    }
    return false;
}

bool convertibilidad(uint32_t x, uint32_t y, vector<uint32_t>& secuencia) {
    if (x == y) {
        return 1;
    } else if (x > y) {
        return 0;
    } else {
        int times2;
        int add1;

        if (habraOverflow(x, 2)) {
            times2 = 0;
        } else {
            secuencia.push_back(x * 2);
            times2 = convertibilidad(x * 2, y, secuencia);

            if (not times2) {
                secuencia.pop_back();
            }
        }

        if (habraOverflow(x, 10)) {
            add1 = 0;
        } else {
            if (x * 10 == pow(x, 10)) {
                add1 = 0;
            } else {
                secuencia.push_back(x * 10 + 1);
                add1 = convertibilidad(x * 10 + 1, y, secuencia);

                if (not add1) {
                    secuencia.pop_back();
                }
            }
        }

        return times2 || add1;
    }
}

int main() {
    vector<uint32_t> secuencia;

    uint32_t x, y;
    cin >> x >> y;

    secuencia.push_back(x);

    int posibilidad = convertibilidad(x, y, secuencia);   

    if (posibilidad) {
        printf("YES\n");
        printf("%lu\n", secuencia.size());
        printf("%u ", secuencia[0]);
        for (size_t i = 0; i < secuencia.size(); i++) {
            if (i != 0) {
                printf("%u ", secuencia[i]);
            }            
        }
    } else {
        printf("NO\n");
    }
    printf("\n");

    return 0;
}