# Bank Program

**Bank Program** is a simple console-based banking management system built in C++.  
It allows users to manage clients’ accounts securely and efficiently, including adding new clients, updating client information, performing deposits and withdrawals, and viewing balances.

---

## Features

- Add, update, delete, and search clients
- Perform transactions: deposit and withdraw money
- View all clients and their account balances
- Input validation and error handling to prevent incorrect operations
- Persistent storage of client data in `ClientFile.txt`
- Transaction confirmations to avoid accidental changes
- Total balance calculation across all clients

---

## File Structure

- `Bank.cpp` - Main program with all functionalities
- `ClientFile.txt` - Stores client data (used as persistent storage)
- `.gitignore` - Ignores unnecessary Visual Studio and temporary files

---

## How to Use

1. Compile and run `Bank.cpp` in a C++ IDE (Visual Studio recommended)
2. Use the main menu to navigate between options:
   - Show all clients
   - Add new client
   - Delete a client
   - Update client information
   - Find a client
   - Transactions (Deposit, Withdraw, Show total balances)
   - Exit
3. Follow on-screen instructions for each operation.

---

## Notes

- Deposits have a maximum limit of **10,000** per transaction.
- Withdrawals have a maximum limit of **3,000** per transaction.
- All data is stored in `ClientFile.txt` and will persist between program runs.

---

## Author

Fares Alsallal  
[GitHub Profile](https://github.com/FaresAlsallal)

