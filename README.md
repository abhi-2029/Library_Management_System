# Library_Management_System
# 📚 Library Management System in C++

This is a **console-based Library Management System** written in **C++**. It allows you to manage a digital library by adding, issuing, returning, and deleting books, while also maintaining a persistent transaction history. The system is designed to be simple yet robust, with features like paginated listings, category-wise statistics, and file-based data storage using plain text files.

---

## ✨ Features

- ✅ Add, delete, search, and view books
- ✅ Issue books to students and return them
- ✅ Maintain transaction history
- ✅ Category-wise and status-based book statistics
- ✅ Paginated book listings (10 books per page)
- ✅ File-based data persistence (`.txt` files)
- ✅ Input validation to handle bad entries
- ✅ Preloaded with 250+ popular books across categories

---

## 📁 File Structure

```bash
.
├── code.cpp              # Main source code
├── books_data.txt        # Auto-generated storage for books
├── transactions.txt      # Auto-generated log for book transactions
└── README.md             # Project documentation
🔧 How to Compile and Run
🧱 Requirements
C++ compiler (g++, clang++, etc.)

Windows/Linux/macOS terminal

💻 Compilation
Open terminal and run:

bash
Copy
Edit
g++ code.cpp -o library

▶️ Run the Program
bash
Copy
Edit
./library        # On Linux/macOS
library.exe      # On Windows

🧪 Functional Overview
📌 Book Management
Add new books with ID, title, author, category, and year

Search books by title, ID, or author

Delete books by ID

Paginated view of all books with ID, title, author, category, year, and status

🔄 Issue/Return System
Issue books to students by entering student name

Return books using their ID

System tracks issue and return dates

📊 Statistics
Shows total books

Number of books issued vs available

Books grouped by category with counts

📜 Transaction History
View complete log of all book issues and returns

Shows issue date, return date, student name, and current status

💾 Data Persistence
books_data.txt: Stores all book records

transactions.txt: Stores all transactions (issued/returned logs)

Automatically read on start and saved on exit

You don’t need to create these files manually—they are created and updated by the program.

🔒 Input Validation
Handles invalid numeric input for IDs and years

Prevents duplicate book IDs

Handles invalid options in the menu

🚀 Initial Dataset
If no books_data.txt exists, the program auto-loads 250+ popular books across genres such as:

📖 Fiction & Classics

🧘 Hinduism & 📿 Islam

💻 Computer Science & Technology

👨‍💻 Programming Books


🧑‍💻 Author
Made with ❤️ by Abhishek Ranjan

Feel free to fork, contribute, or give feedback!


📄 License
You can add a license of your choice here (MIT, GPL, etc.), or state:

