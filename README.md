# 🏦 Advanced Banking System

**Advanced Banking System** is a robust console-based application built in C++. It simulates real-world banking operations, featuring secure multi-level authentication, comprehensive user administration, and full client account management.

---

## 🚀 What's New (Latest Updates)

- **Secure Login Menu:** Added an authentication layer to restrict system access based on user roles (Admin / Staff).
- **User Management (Manage Users):** A dedicated administrative panel to Add, Update, Delete, and List system users/permissions.
- **Architectural Refactoring:** Re-organized the entire project into a clean, professional folder structure (`src/` and `include/`) for better maintainability.

---

## ✨ Features

### 🔐 Security & Access Control
- **Multi-Level Login:** Prevents unauthorized access to sensitive financial records.
- **User Management:** Complete CRUD operations for system employees/operators.

### 💼 Banking Operations
- **Client Management:** Add, update, delete, and search client profiles.
- **Transactions Panel:** Perform instant, secure deposits and withdrawals.
- **Financial Insights:** View individual balances and calculate total capital pooled across all clients.

### 🛡️ System Robustness
- **Input Validation:** Strict error-handling to completely block illegal inputs or crashing operations.
- **Persistent Storage:** Automated data saving and loading from local text files.
- **Safety Confirmations:** Prompted confirmations prior to executing high-risk data changes (deletions/transfers).

---

## 📂 File Structure

```text
├── 📁 include/           # Head/Interface files (.h)
│   ├── ClientServices.h
│   ├── UserServices.h
│   └── ...
├── 📁 src/               # Implementation files (.cpp)
│   ├── Bank.cpp          # Main Entry point
│   ├── ClientService.cpp
│   ├── UserService.cpp
│   └── ...
├── ClientFile.txt        # Encapsulated data storage
└── .gitignore            # Clean environment config (omits IDE/build junk)