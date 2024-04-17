#include <iostream>
using namespace std;

class Date {
private:
    int day;
    int month;
    int year;

public:
    Date(int d, int m, int y) : day(d), month(m), year(y) {}

    int operator-(const Date& other) const {
        int days = countDaysFromDate(*this) - countDaysFromDate(other);
        return days < 0 ? -days : days;
    }

    Date operator+(int days) const {
        Date result = *this;
        result.day += days;
        while (result.day > daysInMonth(result.month, result.year)) {
            result.day -= daysInMonth(result.month, result.year);
            if (++result.month > 12) {
                result.month = 1;
                result.year++;
            }
        }
        return result;
    }

    bool operator==(const Date& other) const {
        return day == other.day && month == other.month && year == other.year;
    }

    bool operator!=(const Date& other) const {
        return !(*this == other);
    }

    void display() const {
        cout << day << "/" << month << "/" << year << endl;
    }

private:
    int daysInMonth(int m, int y) const {
        const int days[] = { 0, 31, 28 + isLeapYear(y), 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
        return days[m];
    }

    bool isLeapYear(int y) const {
        return (y % 4 == 0);
    }

    int countDaysFromDate(const Date& date) const {
        int days = date.day - 1;
        for (int m = 1; m < date.month; m++) {
            days += daysInMonth(m, date.year);
        }
        for (int y = 1; y < date.year; y++) {
            days += isLeapYear(y) ? 366 : 365;
        }
        return days;
    }
};

int main() {
    Date date1(31, 12, 2022);
    Date date2(10, 1, 2022);

    int difference = date2 - date1;
    cout << "Difference between dates: " << difference << " days" << endl;

    Date date3 = date1 + 5;
    cout << "Updated date 1 after adding 5 days: ";
    date3.display();

    if (date1 == date2)
        cout << "Dates are equal" << endl;
    else if (date1 != date2)
        cout << "Dates are not equal" << endl;

    return 0;
}