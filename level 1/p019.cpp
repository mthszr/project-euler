#include <iostream>

using namespace std;

// Function to determine if a year is a leap year
bool is_leap_year(int year) {
    return (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
}

int main() {
    int sunday_count = 0;
    int day_of_week = 2;  // 1 Jan 1901 was a Tuesday (0 = Sunday, 1 = Monday, ..., 6 = Saturday)

    // Days in each month for non-leap and leap years
    int days_in_month[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    for (int year = 1901; year <= 2000; ++year) {
        for (int month = 0; month < 12; ++month) {
            // If the first day of the month is Sunday
            if (day_of_week == 0) {
                ++sunday_count;
            }

            // Move to the first day of the next month
            day_of_week = (day_of_week + days_in_month[month]) % 7;

            // Adjust for leap year
            if (month == 1 && is_leap_year(year)) {
                day_of_week = (day_of_week + 1) % 7;
            }
        }
    }

    cout << "Number of Sundays on the first of the month during the 20th century: " << sunday_count << endl;

    return 0;
}
