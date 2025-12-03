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
