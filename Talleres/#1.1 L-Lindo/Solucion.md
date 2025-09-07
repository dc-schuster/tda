# [L-Lindo](https://codeforces.com/group/yuAAIJ8c1R/contest/631549/problem/A)

Un string es *l-lindo* si cumple al menos una de las siguientes condiciones:
- El string es nada más y nada menos que *"l"*.
- La longitud de *s* es mayor que 1, la primera mitad del string consta unicamente del caracter *l*, y la segunda mitad del string es un string *(l+1)-lindo*.
- La longitud de *s* es mayor que 1, la segunda mitad del string consta unicamente del caracter *l* y la primera imtad de la cadena es un string *(l+1)-lindo*.

Sabemos que la longitud del string es $2^k$ para algún $k \geq 0$.

En un solo movimiento, podemos elegir un indice $i$ y reemplazar $s_i$ con cualquier letra minúscula.

Nuestro objetivo es encontrar el numero minimo de movimientos necesarios para obtener un string *'a'-lindo* a partir de s.

# Idea de Algoritmo

En un principio, queremos obtener la minima cantidad de movimientos necesarios para convertir nuestro string, en *'a'-lindo*. Lo primero que se me viene a la cabeza es un algoritmo donde analizamos las distintas posibilidades de convertir nuestro string en uno *'a'-lindo*, y luego vamos eligiendo el minimo de cada resultado recursivo. 
