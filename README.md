Markdown
# 🏦 Bank Management System (V2.5.0)

A secure, performance-optimized, console-based Banking Management System built from the ground up using modern **C++** structural concepts. This release features a complete architecture refactoring to separate logical components and interfaces, making the code highly maintainable and clean.

## 🚀 Key Features
* **User Management & Login Menu:** Secure access separation with dedicated panels for Admins and regular Users.
* **Client Management:** Comprehensive operations to create, update, delete, and view bank clients.
* **Robust File-Based Database:** Persistent data storage using optimized system structures.
* **Refactored Architecture:** Full modularization of headers and source definitions.

---

## 📁 Repository Structure
The project follows a flat, modern C++ directory layout to maximize clarity for open-source contributors and reviewers:

* 📁 **`Include/`** — Houses all header files (`.h`) organized by logical layer:
  * 📁 `Model/` : Data blueprints (`Client.h`, `User.h`)
  * 📁 `Services/` : Business logic definitions
  * 📁 `Utils/` : Helper mechanisms and system wrappers
* 📁 **`Src/`** — Contains the implementation source files (`.cpp`) that drive the application's core logic.
* 📄 **`Bank Program.vcxproj`** — The native Visual Studio project configuration mapping for local compilation.

---

## 🔑 Default Credentials for Testing
To comply with security best practices, the production user-database files are omitted from source control. A default testing file with an administrative user is included for immediate environment validation:

* **Username:** `Admin`
* **Password:** `1111`

---

## 🛠️ How to Run & Build Local Instance

### Prerequisites
* **Windows OS**
* **Microsoft Visual Studio IDE** (configured with the *Desktop development with C++* workload).

### Steps:
1. Clone this repository to your local machine:
   ```bash
   git clone [https://github.com/FaresAlsallal/BankProgram.git](https://github.com/FaresAlsallal/BankProgram.git)
Open Visual Studio.

Choose Open a project or solution and select the Bank Program.vcxproj file from the root directory. (Visual Studio will automatically generate a localized .sln file matching your system architecture).

Set your build target configuration to Debug | x64 or Release | x64.

Press Ctrl + Shift + B to compile, then press F5 to run the application safely.

👤 Author
Fares Alsallal — Lead Software Engineer

GitHub Profile: FaresAlsallal