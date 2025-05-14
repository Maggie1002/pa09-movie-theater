// @file: pa09.cpp
// @author: Maggie White
// @date: May 14th, 2025
// @note I pledge my word of honor that I have complied with the
// CSN Academic Integrty Policy while completeing this assignment.
// Brief Program Description: Starter code for Movie Theater Booking System
// using 2D arrays and structs.
// @note I spent about 6ish hours completing this assignment. I recieved help
// from tri tran to help me out with github

#include <iostream>
#include <iomanip>
using namespace std;

// Global constants
const int MAX_ROWS = 4;     ///< maximum number of rows
const int MAX_SEATS = 12;   ///< maximum number of seats per row
const double SEAT_PRICE = 10;    ///<price per seat

/**
* Struct to represent a seat
* contains booking status, row number, seat number, and price.
*/

struct Seat
{
    bool isBooked;      // true if booked, false if available
    int rowNumber;      // 1-based row number
    int seatNumber;     // 1-based seat number
    double price;       // price of the seat
};

// Function Prototypes
void displaySeatingChart(const Seat seats[][MAX_SEATS]);
bool bookSeat(Seat seats[][MAX_SEATS], double& totalSales);
bool cancelSeat(Seat seats[][MAX_SEATS], double& totalSales);
void displaySalesSummary(const Seat seats[][MAX_SEATS], double totalSales);
int displayMenu();

int main() {
    Seat seats[MAX_ROWS][MAX_SEATS];    //2D array of Seat structs
    double totalSales = 0.0;            //Total sales accumulator
    int row;
    int col;
    int menuChoice;

    // Initialize seating chart
    for (row = 0; row < MAX_ROWS; row++)
    {
        for (col = 0; col < MAX_SEATS; col++) {
            seats[row][col].isBooked = false;
            seats[row][col].rowNumber = row + 1;
            seats[row][col].seatNumber = col + 1;
            seats[row][col].price = SEAT_PRICE;
        }
    }

    cout << "Welcome to the C++ Theater Booking System!\n";

    do {
        menuChoice = displayMenu();

        switch (menuChoice) {
            case 1:
                displaySeatingChart(seats);     //Show seating layout
                break;
            case 2:
                bookSeat(seats, totalSales);    //book a seat
                break;
            case 3:
                cancelSeat(seats, totalSales);  // Cancel a seat
                break;
            case 4:
                displaySalesSummary(seats, totalSales); //Show sales info
                break;
            case 5:
                cout << "Thank you for using the C++ Theater Booking System!" << endl;
                break;
            default:
                cout << "Invalid selection. Please try again.\n";
        }

    } while (menuChoice != 5); //repeat until user chooses to exit

    return 0;
}

/**
 * Displays the current seating chart.
 * O represents an open seat, X represents a booked seat.
 */
void displaySeatingChart(const Seat seats[][MAX_SEATS]) {
    cout << "\n     Seating Chart (O = Open, X = Booked)\n";
    cout << "     "; //5
    for (int i = 1; i <= MAX_SEATS; i++)
        cout << setw(3) << i;
    cout << endl;
    for (int row = 0; row < MAX_ROWS; row++) {
        cout<< "Row" << setw(1) << row +1 << ":";
        for (int col = 0; col < MAX_SEATS; col++) {
            cout << setw(3) << (seats[row][col].isBooked ? "X" : "O");
        }
        cout << endl;
    }
}

/**
 * Books a seat for a customer if available.
 *
 * @param seats The 2D array of Seat structs
 * @param totalSales Reference to total ticket sales amount
 * @return true if booking succeeded, false otherwise
 */
bool bookSeat(Seat seats[][MAX_SEATS], double& totalSales)
 {
    int row, seat;
    cout << "Enter row number(1-" << MAX_ROWS << "):";
    cin >> row;
    cout << "Enter seat number(1-" << MAX_SEATS << "):";
    cin >> seat;

    if (row < 1 || row > MAX_ROWS || seat < 1 || seat > MAX_SEATS) {
        cout << "Invalid seat selection.\n";
        return false;
    }

    if(seats[row - 1][seat - 1].isBooked) {
        cout << "Seat already booked.\n";
        return false;
    }

    seats [row -1][seat - 1].isBooked = true;
    totalSales += seats[row - 1][seat - 1].price;
    cout << "Seat booked successfully.\n";
    return true;
}

/**
 * @brief Cancels a seat booking if it exists and updates total sales.
 *
 * @param seats the 2D array of Seat structs
 * @param totalSales Reference to total ticket sales amount.
 * @return true if cancellation succeeded, false otherwise.
 */
bool cancelSeat(Seat seats[][MAX_SEATS], double& totalSales)
{
    int row, seat;
    cout << "Enter row number (1-" << MAX_ROWS << "): ";
    cin >> row;
    cout << "Enter seat number (1-" << MAX_SEATS << "): ";
    cin >> seat;

    if (row < 1 || row > MAX_ROWS || seat < 1 || seat > MAX_SEATS) {
        cout << "invalid seat selection.\n";
        return false;
    }

    if (!seats[row - 1][seat - 1].isBooked) {
        cout << "Seat is not booked.\n";
        return false;
    }

    seats[row - 1][seat - 1].isBooked = false;
    totalSales -= seats[row - 1][seat - 1].price;
    cout << "Booking cancelled.\n";
    return true;
}

/**
 * @brief Displays sales summary report.
 *
 * Shows seats sold, available, and total sales amount.
 *
 * @param seats the 2D array of Seat structs.
 * @param totalSales The current total sales amount.
 * @return None
 */
void displaySalesSummary(const Seat seats[][MAX_SEATS], double totalSales)
{
    int sold = 0, available = 0;
    for (int row = 0; row < MAX_ROWS; row++) {
        for ( int col = 0; col < MAX_SEATS; col++) {
            if (seats[row][col].isBooked) {
                sold++;
            } else {
                available++;
            }
        }
    }
    cout << fixed << setprecision(2);
    cout << "\nSales Summary: \n";
    cout << "seats Sold: " << sold << endl;
    cout << "Seats Available: " << available << endl;
    cout << "Total Sales: $" << totalSales << endl;
}

/**
 * @brief Displays the main menu and gets the user's choice.
 *
 * @return An integer representing the user's menu choicd
 */
int displayMenu()
{
    int menuChoice;
    cout << "\n1. Display Seating Chart\n";
    cout << "2. Book a Seat\n";
    cout << "3. Cancel a Booking\n";
    cout << "4. View Sales Summary\n";
    cout << "5. Exit\n";
    cout << "Enter your choice: ";
    cin >> menuChoice;

    return menuChoice;
}
