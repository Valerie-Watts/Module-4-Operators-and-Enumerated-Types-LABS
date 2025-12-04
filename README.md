# Colección de Laboratorios: C++ Avanzado

Este repositorio contiene una serie de ejercicios prácticos diseñados para explorar y dominar características avanzadas del lenguaje C++. Los laboratorios se centran principalmente en la **Sobrecarga de Operadores** (Operator Overloading), el **Manejo de Excepciones** personalizado, el uso de **Enumeraciones** (`enum`) y la implementación de **Estructuras de Datos** orientadas a objetos.

## Contenido del Repositorio

A continuación se describen los 7 ejercicios incluidos en esta colección:

### 1. Sobrecarga de Operadores Básica (I/O)
* **Archivo:** `LAB_OperatorOverloading_CustomIO.cpp`
* **Descripción:** Implementación de una clase `Mattrix` (matriz simple de 2x2).
* **Conceptos Clave:** Sobrecarga de los operadores de flujo de entrada (`>>`) y salida (`<<`) mediante funciones `friend`, permitiendo leer e imprimir objetos complejos directamente con `std::cin` y `std::cout`.

### 2. Estructura de Datos Dinámica con Operadores
* **Archivo:** `LAB_Stack_Implementation.cpp`
* **Descripción:** Creación de una pila (`Stack`) dinámica basada en nodos enlazados.
* **Conceptos Clave:**
    * Uso de operadores para manipular la estructura: `<<` para *push* y `>>` para *pop*.
    * Manejo de excepciones (`EmptyError`) para evitar el desbordamiento inferior (underflow).

### 3. Enumeraciones y Validación Lógica
* **Archivo:** `LAB_Enums_RepresentingValues.cpp`
* **Descripción:** Sistema de calendario que calcula días transcurridos desde la época Unix (1 de enero de 1970).
* **Conceptos Clave:**
    * Uso de `enum` para Meses y Días de la Semana para mejorar la legibilidad.
    * Excepciones (`InvalidDateError`) para validar reglas de negocio (fechas históricas no permitidas).

### 4. Árboles Binarios y Salida Personalizada
* **Archivo:** `LAB_Operators_iostream_BST.cpp`
* **Descripción:** Implementación de un Árbol Binario de Búsqueda (BST) que se ordena automáticamente al imprimirse.
* **Conceptos Clave:** Sobrecarga del operador `<<` para realizar un recorrido *inorder* implícito al enviar el árbol al flujo de salida.

### 5. Máquina de Estados Finitos (FSM)
* **Archivo:** `LAB_Representing_Values_Order.cpp`
* **Descripción:** Simulación de una máquina de estados que transiciona según valores de entrada.
* **Conceptos Clave:**
    * Sobrecarga dual del operador `<<`: como método miembro para inyectar datos y realizar transiciones, y como función amiga para imprimir el historial de estados.
    * Uso de `enum` para definir estados (`Start`, `Stop`, etc.).

### 6. Herencia y Polimorfismo en Recorridos
* **Archivo:** `LAB_Operators_ComplexClasses.cpp`
* **Descripción:** Jerarquía de clases para árboles binarios donde clases derivadas definen el comportamiento de impresión.
* **Conceptos Clave:**
    * **Herencia:** Clases `Inorder`, `Postorder`, `Preorder` heredan de `BinaryTree`.
    * **Sobrecarga:** Cada subclase implementa su propia versión de `operator<<` y `operator[]` para acceder a los datos según su orden de recorrido específico.

### 7. Aritmética Matricial Completa
* **Archivo:** `LAB_Operators_Arithmetic.cpp`
* **Descripción:** Una clase `Matrix` robusta y redimensionable capaz de realizar álgebra lineal.
* **Conceptos Clave:**
    * Sobrecarga de operadores aritméticos: `+`, `-`, `*`.
    * Validación dimensional estricta lanzando excepciones personalizadas (`IncompatibleMatrixException`) si las matrices no coinciden en tamaño para la operación solicitada.

## Requisitos de Compilación

Todos los archivos están escritos en C++ estándar. Se pueden compilar utilizando `g++` o cualquier compilador moderno compatible con C++11 o superior.

Ejemplo de compilación:
```bash
g++ nombre_del_archivo.cpp -o salida.exe
./salida.exe
````
