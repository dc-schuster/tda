
#include <stdlib.h>
#include <cstring>
#include <algorithm>

#include <bits/stdc++.h>
using namespace std;

int stringIgual(char *string, int start, int end, char caracter) {
    // Devuelve la cantidad de movimientos necesarios para convertir un segmento de un string en caracteres character..
    
    int indice = start;
    int movimientos = 0;

    while (indice <= end) {
        if (string[indice] != caracter) {
            movimientos++;
        }
        indice++;
    }

    return movimientos;
}

int lLindo(char *string, int start, int end, char l) {
    
    if (start == end) {
        if (string[start] == l) {
            return 0;
        } else {
            return 1;
        }
    }

    // Si llegamos hasta acá, sabemos que tenemos un string de longitud mayor que 1. Por lo que tenemos que analizar los 2 siguientes casos:

    // La longitud de *s* es mayor que 1, la primera mitad del string consta unicamente del caracter *l*, y la segunda mitad del string es un string *(l+1)-lindo*.
    // Para este caso, queremos calcular la suma de movimientos para que:
    //      - La primera mitad del string esté compuesto únicamente de caracteres l.
    //      - La segunda mitad del string es (l+1)-lindo. 

    // La longitud de *s* es mayor que 1, la segunda mitad del string consta unicamente del caracter *l* y la primera mitad de la cadena es un string *(l+1)-lindo*.
    // Para este caso, queremos calcular la suma de movimientos para que:
    //      - La primera mitad del string es (l+1)-lindo.  
    //      - La segunda mitad del string esté compuesto únicamente de caracteres l.

    int length = end - start + 1;
    int mid = start + length / 2;

    int primeraMitadIgual = stringIgual(string, start, mid - 1, l);
    int segundaMitadLMas1Linda = lLindo(string, mid, end, l + 1);

    int primeraMitadLMas1Linda = lLindo(string, start, mid - 1, l + 1);
    int segundaMitadIgual = stringIgual(string, mid, end, l);

    return std::min(primeraMitadIgual + segundaMitadLMas1Linda, primeraMitadLMas1Linda + segundaMitadIgual);    
}

int main() {

    int t;
    if (!(cin >> t)) return 0;

    while (t--) {
        int length;
        string s;
        cin >> length;
        cin >> s;

        vector<char> arrayChars(length + 1);
        memcpy(arrayChars.data(), s.data(), length);
        arrayChars[length] = '\0';

        int ans = lLindo(arrayChars.data(), 0, length - 1, 'a');

        cout << ans << '\n';
    }
    return 0;
}