# 4.1.4 LAB Enums. representing values

Este documento detalla el funcionamiento del programa C++ que utiliza enumeraciones (`enum`) para representar meses y días de la semana, combinándolas con el manejo de excepciones para calcular días transcurridos desde una fecha específica.

## Captura de pantalla del código

```cpp
#include <iostream>

enum Month {
	JANUARY = 1, FEBRUARY, MARCH, APRIL, MAY, JUNE,
	JULY, AUGUST, SEPTEMBER, OCTOBER, NOVEMBER, DECEMBER
};

enum dayWeek {
	THURSDAY = 0, FRIDAY, SATURDAY, SUNDAY, MONDAY, TUESDAY, WEDNESDAY
};

const std::string monthNames[] = {
	"", "January", "February", "March", "April", "May", "June",
	"July", "August", "September", "October", "November", "December"
};

const std::string dayNames[] = {
	"Thursday", "Friday", "Saturday", "Sunday", "Monday", "Tuesday", "Wednesday"
};

class InvalidDateError : public std::exception {
public: 
	const char* what() const noexcept override {
		return "Error: Date is before January 1st 1970";
	}
};

bool LeapYear(int year) {
	return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0); 
}

int daysMonth(int month, int year) {
	
	int days[] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };
	if (month == FEBRUARY && LeapYear(year)) {
		return 29;
	}
	return days[month];
}

class calendar {
private:

	int day, month, year; 

public: 

	calendar(int d, int m, int y) {
		
		if (y < 1970 || (y == 1970 && m == 1 && d < 1)) {
			throw InvalidDateError();
		}

		day = d;
		month = m;
		year = y;
	}

	int daysSince1970() {
		int totalDays = 0; 

		for (int y = 1970; y < year; y++) {
			if (LeapYear(y)) {
				totalDays += 366;
			}
			else {
				totalDays += 365;
			}
		}

		for (int m = 1; m < month; m++) {
			totalDays += daysMonth(m, year);
		}

		totalDays += day;
		return totalDays - 1;
	}

	void print()
	{
		int totalDays = daysSince1970();
		int dayOfWeek = totalDays% 7;
		std::cout << day << " " << monthNames[month] << " " << year << " - " << dayNames[dayOfWeek] << " - " << totalDays << " days since 1st Jan";
	}
};

int main()
{

	try
	{
		int d, m, y; 

		std::cin >> d >> m >> y;

		calendar date(d, m, y);	

		date.print(); 

	}
	catch (const InvalidDateError& e)
	{
		std::cout << e.what() << std::endl;
	}
	
	return 0; 
}
````

## Captura de pantalla de la ejecución

**Ejecución 1 (Fecha válida):**

Entrada:

```
2 1 1970
```

*(El 1 de enero de 1970 fue Jueves -Thursday-, por lo tanto, el 2 de enero es Viernes)*

Salida:

```
2 January 1970 - Friday - 1 days since 1st Jan
```

**Ejecución 2 (Fecha inválida - Previa a 1970):**

Entrada:

```
31 12 1969
```

Salida:

```
Error: Date is before January 1st 1970
```

## Explicación del ejercicio

El objetivo de este ejercicio es aplicar el uso de `enum` (enumeraciones) para mejorar la legibilidad del código al trabajar con conjuntos de valores constantes, como los meses del año (`Month`) y los días de la semana (`dayWeek`). Además, se integra el manejo de excepciones para validar la lógica del calendario.

La clase `calendar` utiliza estas enumeraciones internamente para gestionar las fechas. El constructor implementa una validación crítica: comprueba si la fecha ingresada es anterior al 1 de enero de 1970 (la época Unix). Si lo es, lanza una excepción personalizada `InvalidDateError`. En el `main`, un bloque `try` envuelve la creación del objeto `calendar`. Si el constructor detecta una fecha inválida y lanza la excepción, el bloque `catch` la intercepta e imprime el mensaje de error definido en `what()`. Esto demuestra cómo combinar estructuras de datos enumeradas con un manejo robusto de errores para crear programas más seguros y fáciles de entender.
