# LAB Operator Overloading. Custom I/O

Este documento detalla el funcionamiento del programa C++ que implementa la clase `Mattrix`, enfocándose en la sobrecarga de los operadores de flujo de entrada y salida para facilitar la manipulación de objetos personalizados.

## Captura de pantalla del código

```cpp
#include <iostream>

class Mattrix
{
private:
	int values[2][2];

public:

	Mattrix() {

		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++) {
				values[i][j] = 0;
			}
		}
	}

	friend std::istream& operator>>(std::istream& is, Mattrix& m)
	{

		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++) {

				is >> m.values[i][j];

			}
		}

		return is;
	}

	friend std::ostream& operator<<(std::ostream& os, const Mattrix& m)
	{
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++) {

				os << m.values[i][j];
				if (j < 1) {
					os << " ";
				}
			}
			os << std::endl;
		}

		return os;
	}
};

int main()
{
	Mattrix matrix;


	std::cin >> matrix;

	std::cout << matrix;

	return 0;

}
````

## Captura de pantalla de la ejecución

**Ejecución 1 (Entrada de 4 valores):**

Entrada:

```
1 2
3 4
```

Salida:

```
1 2
3 4
```

**Ejecución 2 (Entrada en una sola línea):**

Entrada:

```
10 20 30 40
```

Salida:

```
10 20
30 40
```

## Explicación del ejercicio

El objetivo de este ejercicio es demostrar la **sobrecarga de operadores** en C++, específicamente los operadores de inserción (`<<`) y extracción (`>>`) de flujos. Por defecto, `std::cin` y `std::cout` solo saben cómo manejar tipos de datos primitivos (como `int`, `float`, `char`). Para que puedan trabajar directamente con una clase personalizada como `Mattrix` (una matriz de 2x2), es necesario "enseñarles" cómo interpretar estos objetos.

El código logra esto definiendo dos funciones `friend` (amigas). La función `operator>>` toma el flujo de entrada `istream` y el objeto `Mattrix`, e itera sobre el arreglo interno `values` para llenar cada celda con los datos ingresados por el usuario. La función `operator<<` hace lo inverso: toma el flujo de salida `ostream` y el objeto, recorriendo la matriz para imprimirla con el formato deseado (espacios entre columnas y saltos de línea entre filas). Al declarar estas funciones como `friend`, tienen acceso directo a los miembros privados de la clase (`values`). Esto permite que en el `main` se escriba un código extremadamente limpio y abstracto como `std::cin >> matrix;` y `std::cout << matrix;`, tratando a la compleja estructura de la matriz con la misma simplicidad que si fuera un número entero.


