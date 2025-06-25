#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <ctime>
#include <iomanip>
#include <map>
#include <limits>
#include <sstream>

using namespace std;

// Constants
const string BOOKS_FILE = "books_data.txt";
const string TRANSACTIONS_FILE = "transactions.txt";

// Book Class
class Book {
public:
    int id;
    string title;
    string author;
    string category;
    int publicationYear;
    bool isIssued;

    Book(int id, string title, string author, string category = "General", int year = 0)
        : id(id), title(title), author(author), category(category), 
          publicationYear(year), isIssued(false) {}
};

// Transaction Record Class
class Transaction {
public:
    int bookId;
    string bookTitle;
    string studentName;
    string issueDate;
    string returnDate;
    bool isReturned;

    Transaction(int id, string title, string student, string iDate, 
                string rDate = "", bool returned = false)
        : bookId(id), bookTitle(title), studentName(student), 
          issueDate(iDate), returnDate(rDate), isReturned(returned) {}
};

// Library Class
class Library {
private:
    vector<Book> books;
    vector<Transaction> transactions;
    map<string, int> categoryCount;

    string getCurrentDate() {
        time_t now = time(0);
        tm* ltm = localtime(&now);
        return to_string(1900 + ltm->tm_year) + "-" + 
               to_string(1 + ltm->tm_mon) + "-" + 
               to_string(ltm->tm_mday);
    }

    bool isBookIdUnique(int id) {
        return find_if(books.begin(), books.end(), [id](const Book& b) {
            return b.id == id;
        }) == books.end();
    }

    void saveBooksToFile() {
        ofstream outFile(BOOKS_FILE);
        if (outFile.is_open()) {
            for (const auto& book : books) {
                outFile << book.id << "," << book.title << "," << book.author << ","
                        << book.category << "," << book.publicationYear << ","
                        << book.isIssued << "\n";
            }
            outFile.close();
        }
    }

    void loadBooksFromFile() {
        ifstream inFile(BOOKS_FILE);
        if (inFile.is_open()) {
            books.clear();
            string line;
            while (getline(inFile, line)) {
                stringstream ss(line);
                string token;
                vector<string> tokens;

                while (getline(ss, token, ',')) {
                    tokens.push_back(token);
                }

                if (tokens.size() == 6) {
                    Book book(stoi(tokens[0]), tokens[1], tokens[2], tokens[3], 
                             stoi(tokens[4]));
                    book.isIssued = (tokens[5] == "1");
                    books.push_back(book);
                    categoryCount[tokens[3]]++;
                }
            }
            inFile.close();
        }
    }

    void saveTransactionsToFile() {
        ofstream outFile(TRANSACTIONS_FILE);
        if (outFile.is_open()) {
            for (const auto& trans : transactions) {
                outFile << trans.bookId << "," << trans.bookTitle << "," 
                        << trans.studentName << "," << trans.issueDate << ","
                        << trans.returnDate << "," << trans.isReturned << "\n";
            }
            outFile.close();
        }
    }

    void loadTransactionsFromFile() {
        ifstream inFile(TRANSACTIONS_FILE);
        if (inFile.is_open()) {
            transactions.clear();
            string line;
            while (getline(inFile, line)) {
                stringstream ss(line);
                string token;
                vector<string> tokens;

                while (getline(ss, token, ',')) {
                    tokens.push_back(token);
                }

                if (tokens.size() == 6) {
                    Transaction trans(stoi(tokens[0]), tokens[1], tokens[2], 
                                    tokens[3], tokens[4], tokens[5] == "1");
                    transactions.push_back(trans);
                }
            }
            inFile.close();
        }
    }

    void initializeSampleBooks() {
        // Fiction/Literature
        addBook(101, "To Kill a Mockingbird", "Harper Lee", "Fiction", 1960);
        addBook(102, "1984", "George Orwell", "Fiction", 1949);
        addBook(103, "Pride and Prejudice", "Jane Austen", "Fiction", 1813);
        addBook(104, "The Great Gatsby", "F. Scott Fitzgerald", "Fiction", 1925);
        addBook(105, "Moby Dick", "Herman Melville", "Fiction", 1851);
        addBook(106, "The Catcher in the Rye", "J.D. Salinger", "Fiction", 1951);
        addBook(107, "Brave New World", "Aldous Huxley", "Fiction", 1932);
        addBook(108, "The Grapes of Wrath", "John Steinbeck", "Fiction", 1939);
        addBook(109, "The Hobbit", "J.R.R. Tolkien", "Fantasy", 1937);
        addBook(110, "One Hundred Years of Solitude", "Gabriel Garcia Marquez", "Fiction", 1967);
        addBook(111, "The Lord of the Rings", "J.R.R. Tolkien", "Fantasy", 1954);
        addBook(112, "Crime and Punishment", "Fyodor Dostoevsky", "Fiction", 1866);
        addBook(113, "The Picture of Dorian Gray", "Oscar Wilde", "Fiction", 1890);
        addBook(114, "Jane Eyre", "Charlotte Bronte", "Fiction", 1847);
        addBook(115, "War and Peace", "Leo Tolstoy", "Fiction", 1869);
        addBook(116, "Anna Karenina", "Leo Tolstoy", "Fiction", 1877);
        addBook(117, "Frankenstein", "Mary Shelley", "Fiction", 1818);
        addBook(118, "Wuthering Heights", "Emily Bronte", "Fiction", 1847);
        addBook(119, "The Odyssey", "Homer", "Classics", -800);
        addBook(120, "The Adventures of Huckleberry Finn", "Mark Twain", "Fiction", 1884);

        // Hinduism
        addBook(121, "Bhagavad Gita", "Various", "Hinduism");
        addBook(122, "The Upanishads", "Various", "Hinduism");
        addBook(123, "Ramayana", "Valmiki", "Hinduism");
        addBook(124, "Mahabharata", "Vyasa", "Hinduism");
        addBook(125, "The Vedas", "Various", "Hinduism");

        // Islam
        addBook(126, "The Quran", "Various", "Islam");
        addBook(127, "Hadith Collections", "Various", "Islam");
        addBook(128, "In the Footsteps of the Prophet", "Tariq Ramadan", "Islam");
        addBook(129, "No god but God", "Reza Aslan", "Islam");
        addBook(130, "Islam: A Short History", "Karen Armstrong", "Islam");

        // Additional books
        addBook(131, "Madame Bovary", "Gustave Flaubert", "Fiction", 1856);
        addBook(132, "The Divine Comedy", "Dante Alighieri", "Classics", 1320);
        addBook(133, "Don Quixote", "Miguel de Cervantes", "Fiction", 1605);
        addBook(134, "Les Misérables", "Victor Hugo", "Fiction", 1862);
        addBook(135, "The Brothers Karamazov", "Fyodor Dostoevsky", "Fiction", 1880);
        addBook(136, "Ulysses", "James Joyce", "Fiction", 1922);
        addBook(137, "Catch-22", "Joseph Heller", "Fiction", 1961);
        addBook(138, "Lolita", "Vladimir Nabokov", "Fiction", 1955);
        addBook(139, "One Flew Over the Cuckoo's Nest", "Ken Kesey", "Fiction", 1962);
        addBook(140, "The Iliad", "Homer", "Classics", -750);
        addBook(141, "A Tale of Two Cities", "Charles Dickens", "Fiction", 1859);
        addBook(142, "Emma", "Jane Austen", "Fiction", 1815);
        addBook(143, "The Stranger", "Albert Camus", "Fiction", 1942);
        addBook(144, "Fahrenheit 451", "Ray Bradbury", "Fiction", 1953);
        addBook(145, "Invisible Man", "Ralph Ellison", "Fiction", 1952);
        addBook(146, "Beloved", "Toni Morrison", "Fiction", 1987);
        addBook(147, "The Sun Also Rises", "Ernest Hemingway", "Fiction", 1926);
        addBook(148, "Mrs Dalloway", "Virginia Woolf", "Fiction", 1925);
        addBook(149, "The Sound and the Fury", "William Faulkner", "Fiction", 1929);
        addBook(150, "Heart of Darkness", "Joseph Conrad", "Fiction", 1899);
        addBook(151, "Clean Code", "Robert C. Martin", "Technology", 2008);
        addBook(152, "The Pragmatic Programmer", "Andrew Hunt", "Technology", 1999);
        addBook(153, "Design Patterns", "Erich Gamma", "Technology", 1994);
        addBook(154, "Code Complete", "Steve McConnell", "Technology", 2004);
        addBook(155, "Structure and Interpretation of Computer Programs", "Harold Abelson", "Technology", 1996);
        addBook(156, "The Mythical Man-Month", "Frederick P. Brooks", "Technology", 1975);
        addBook(157, "Introduction to Algorithms", "Thomas H. Cormen", "Technology", 2009);
        addBook(158, "Artificial Intelligence: A Modern Approach", "Stuart Russell", "Technology", 2021);
        addBook(159, "Deep Learning", "Ian Goodfellow", "Technology", 2016);
        addBook(160, "The Art of Computer Programming", "Donald E. Knuth", "Technology", 1968);
        addBook(161, "Refactoring", "Martin Fowler", "Technology", 1999);
        addBook(162, "Effective Java", "Joshua Bloch", "Technology", 2001);
        addBook(163, "Don't Make Me Think", "Steve Krug", "Technology", 2000);
        addBook(164, "The Clean Coder", "Robert C. Martin", "Technology", 2011);
        addBook(165, "Continuous Delivery", "Jez Humble", "Technology", 2010);
        addBook(166, "You Don't Know JS", "Kyle Simpson", "Technology", 2015);
        addBook(167, "Python Crash Course", "Eric Matthes", "Technology", 2015);
        addBook(168, "Grokking Algorithms", "Aditya Bhargava", "Technology", 2016);
        addBook(169, "Cracking the Coding Interview", "Gayle Laakmann McDowell", "Technology", 2015);
        addBook(170, "Introduction to the Theory of Computation", "Michael Sipser", "Technology", 1997);
        addBook(171, "Linux Pocket Guide", "Daniel J. Barrett", "Technology", 2004);
        addBook(172, "The Phoenix Project", "Gene Kim", "Technology", 2013);
        addBook(173, "The DevOps Handbook", "Gene Kim", "Technology", 2016);
        addBook(174, "Site Reliability Engineering", "Betsy Beyer", "Technology", 2016);
        addBook(175, "Algorithms to Live By", "Brian Christian", "Technology", 2016);
        addBook(176, "Compilers: Principles, Techniques, and Tools", "Alfred V. Aho", "Technology", 2006);
        addBook(177, "The Elements of Computing Systems", "Noam Nisan", "Technology", 2005);
        addBook(178, "Automate the Boring Stuff with Python", "Al Sweigart", "Technology", 2015);
        addBook(179, "How Linux Works", "Brian Ward", "Technology", 2004);
        addBook(180, "Hands-On Machine Learning with Scikit-Learn and TensorFlow", "Aurélien Géron", "Technology", 2017);
        addBook(181, "The Soul of a New Machine", "Tracy Kidder", "Technology", 1981);
        addBook(182, "Hackers: Heroes of the Computer Revolution", "Steven Levy", "Technology", 1984);
        addBook(183, "The Innovators", "Walter Isaacson", "Technology", 2014);
        addBook(184, "Steve Jobs", "Walter Isaacson", "Technology", 2011);
        addBook(185, "Elon Musk", "Ashlee Vance", "Technology", 2015);
        addBook(186, "Masters of Doom", "David Kushner", "Technology", 2003);
        addBook(187, "Zero to One", "Peter Thiel", "Technology", 2014);
        addBook(188, "The Lean Startup", "Eric Ries", "Technology", 2011);
        addBook(189, "The Hard Thing About Hard Things", "Ben Horowitz", "Technology", 2014);
        addBook(190, "Rework", "Jason Fried", "Technology", 2010);
        addBook(191, "Lean Software Development", "Mary Poppendieck", "Technology", 2003);
        addBook(192, "Peopleware", "Tom DeMarco", "Technology", 1987);
        addBook(193, "The Cathedral and the Bazaar", "Eric S. Raymond", "Technology", 1999);
        addBook(194, "Algorithms Unlocked", "Thomas H. Cormen", "Technology", 2013);
        addBook(195, "Understanding the Linux Kernel", "Daniel P. Bovet", "Technology", 2005);
        addBook(196, "Kubernetes Up and Running", "Kelsey Hightower", "Technology", 2017);
        addBook(197, "The Docker Book", "James Turnbull", "Technology", 2014);
        addBook(198, "Agile Estimating and Planning", "Mike Cohn", "Technology", 2005);
        addBook(199, "Programming Pearls", "Jon Bentley", "Technology", 1986);
        addBook(200, "Software Engineering at Google", "Titus Winters", "Technology", 2020);
        addBook(201, "Superintelligence", "Nick Bostrom", "Technology", 2014);
        addBook(202, "AI 2041", "Kai-Fu Lee", "Technology", 2021);
        addBook(203, "Life 3.0", "Max Tegmark", "Technology", 2017);
        addBook(204, "Architecting for Scale", "Lee Atchison", "Technology", 2016);
        addBook(205, "Designing Data-Intensive Applications", "Martin Kleppmann", "Technology", 2017);
        addBook(206, "The Art of Scalability", "Martin L. Abbott", "Technology", 2009);
        addBook(207, "Cloud Native DevOps with Kubernetes", "John Arundel", "Technology", 2019);
        addBook(208, "Cloud Computing: Concepts, Technology & Architecture", "Thomas Erl", "Technology", 2013);
        addBook(209, "Blockchain Basics", "Daniel Drescher", "Technology", 2017);
        addBook(210, "Mastering Blockchain", "Imran Bashir", "Technology", 2017);
        addBook(211, "Blockchain Revolution", "Don Tapscott", "Technology", 2016);
        addBook(212, "Cybersecurity for Beginners", "Raef Meeuwisse", "Technology", 2016);
        addBook(213, "Hacking: The Art of Exploitation", "Jon Erickson", "Technology", 2003);
        addBook(214, "The Web Application Hacker's Handbook", "Dafydd Stuttard", "Technology", 2011);
        addBook(215, "Metasploit: The Penetration Tester's Guide", "David Kennedy", "Technology", 2011);
        addBook(216, "Social Engineering: The Science of Human Hacking", "Christopher Hadnagy", "Technology", 2010);
        addBook(217, "Network Security Essentials", "William Stallings", "Technology", 2000);
        addBook(218, "Modern Operating Systems", "Andrew S. Tanenbaum", "Technology", 1992);
        addBook(219, "Computer Networking: A Top-Down Approach", "James F. Kurose", "Technology", 2000);
        addBook(220, "CompTIA Security+ Study Guide", "Mike Chapple", "Technology", 2020);
        addBook(221, "Computer Organization and Design", "David A. Patterson", "Technology", 2013);
        addBook(222, "Programming Language Pragmatics", "Michael L. Scott", "Technology", 2005);
        addBook(223, "Effective Modern C++", "Scott Meyers", "Technology", 2014);
        addBook(224, "Head First Design Patterns", "Eric Freeman", "Technology", 2004);
        addBook(225, "Game Programming Patterns", "Robert Nystrom", "Technology", 2014);
        addBook(226, "Head First Object-Oriented Analysis and Design", "Brett McLaughlin", "Technology", 2006);
        addBook(227, "Domain-Driven Design", "Eric Evans", "Technology", 2003);
        addBook(228, "The Art of UNIX Programming", "Eric S. Raymond", "Technology", 2003);
        addBook(229, "Build Your Own Database From Scratch", "James Smith", "Technology", 2020);
        addBook(230, "Programming Rust", "Jim Blandy", "Technology", 2017);
        addBook(231, "Programming TypeScript", "Boris Cherny", "Technology", 2019);
        addBook(232, "C Programming Language", "Brian Kernighan", "Technology", 1978);
        addBook(233, "Learn You a Haskell for Great Good!", "Miran Lipovača", "Technology", 2011);
        addBook(234, "Eloquent JavaScript", "Marijn Haverbeke", "Technology", 2011);
        addBook(235, "The Go Programming Language", "Alan Donovan", "Technology", 2015);
        addBook(236, "Fluent Python", "Luciano Ramalho", "Technology", 2015);
        addBook(237, "High Performance Python", "Micha Gorelick", "Technology", 2014);
        addBook(238, "Web Performance in Action", "Jeremy Wagner", "Technology", 2016);
        addBook(239, "Real-Time Rendering", "Tomas Akenine-Möller", "Technology", 1998);
        addBook(240, "The Art of Electronics", "Paul Horowitz", "Technology", 1980);
        addBook(241, "Code: The Hidden Language of Computer Hardware and Software", "Charles Petzold", "Technology", 2000);
        addBook(242, "The Chip: How Two Americans Invented the Microchip", "T. R. Reid", "Technology", 2001);
        addBook(243, "Quantum Computing for Everyone", "Chris Bernhardt", "Technology", 2019);
        addBook(244, "AI Superpowers", "Kai-Fu Lee", "Technology", 2018);
        addBook(245, "The Master Algorithm", "Pedro Domingos", "Technology", 2015);
        addBook(246, "Deep Work", "Cal Newport", "Technology", 2016);
        addBook(247, "Tools of Titans", "Tim Ferriss", "Technology", 2016);
        addBook(248, "Hooked: How to Build Habit-Forming Products", "Nir Eyal", "Technology", 2014);
        addBook(249, "The Startup Owner's Manual", "Steve Blank", "Technology", 2012);
        addBook(250, "The Art of Start 2.0", "Guy Kawasaki", "Technology", 2015);


    }

    void printBookDetails(const Book& book) {
        cout << "\nID: " << book.id << "\nTitle: " << book.title 
             << "\nAuthor: " << book.author << "\nCategory: " << book.category
             << "\nPublication Year: " << (book.publicationYear > 0 ? to_string(book.publicationYear) : "Unknown")
             << "\nStatus: " << (book.isIssued ? "Issued" : "Available") << "\n";
    }

    string calculateDueDate(const string& issueDate) {
        // Simple 14-day due date calculation
        return issueDate + " (Due in 14 days)";
    }

public:
    Library() {
        loadBooksFromFile();
        loadTransactionsFromFile();
        
        // If no books loaded (first run), initialize with sample books
        if (books.empty()) {
            initializeSampleBooks();
        }
    }

    ~Library() {
        saveBooksToFile();
        saveTransactionsToFile();
    }

    void addBook(int id, string title, string author, string category = "General", int year = 0) {
        if (!isBookIdUnique(id)) {
            cout << "Error: Book ID already exists.\n";
            return;
        }

        books.push_back(Book(id, title, author, category, year));
        categoryCount[category]++;
        saveBooksToFile();
        cout << "Book added successfully.\n";
    }

    void searchBookByTitle(const string& title) {
        vector<Book> results;
        copy_if(books.begin(), books.end(), back_inserter(results), 
            [&title](const Book& b) {
                return b.title.find(title) != string::npos;
            });

        if (!results.empty()) {
            cout << "\nSearch Results (" << results.size() << " found):\n";
            for (const auto& book : results) {
                printBookDetails(book);
            }
        } else {
            cout << "No books found with title containing: " << title << "\n";
        }
    }

    void searchBookById(int id) {
        auto it = find_if(books.begin(), books.end(), [id](const Book& b) {
            return b.id == id;
        });

        if (it != books.end()) {
            printBookDetails(*it);
        } else {
            cout << "Book not found.\n";
        }
    }

    void searchBooksByAuthor(const string& author) {
        vector<Book> results;
        copy_if(books.begin(), books.end(), back_inserter(results), 
            [&author](const Book& b) {
                return b.author.find(author) != string::npos;
            });

        if (!results.empty()) {
            cout << "\nBooks by " << author << " (" << results.size() << " found):\n";
            for (const auto& book : results) {
                printBookDetails(book);
            }
        } else {
            cout << "No books found by author: " << author << "\n";
        }
    }

    void issueBook(int id, const string& studentName) {
        auto it = find_if(books.begin(), books.end(), [id](const Book& b) {
            return b.id == id;
        });

        if (it != books.end()) {
            if (!it->isIssued) {
                it->isIssued = true;
                string currentDate = getCurrentDate();
                transactions.push_back(Transaction(id, it->title, studentName, currentDate));
                saveBooksToFile();
                saveTransactionsToFile();
                cout << "Book issued successfully. Due date is " 
                     << calculateDueDate(currentDate) << "\n";
            } else {
                cout << "Book is already issued.\n";
            }
        } else {
            cout << "Book not found.\n";
        }
    }

    void returnBook(int id) {
        auto bookIt = find_if(books.begin(), books.end(), [id](const Book& b) {
            return b.id == id;
        });

        if (bookIt != books.end()) {
            if (bookIt->isIssued) {
                bookIt->isIssued = false;
                string currentDate = getCurrentDate();

                auto transIt = find_if(transactions.begin(), transactions.end(), 
                    [id](const Transaction& t) {
                        return t.bookId == id && !t.isReturned;
                    });

                if (transIt != transactions.end()) {
                    transIt->returnDate = currentDate;
                    transIt->isReturned = true;
                }

                saveBooksToFile();
                saveTransactionsToFile();
                cout << "Book returned successfully.\n";
            } else {
                cout << "This book is not currently issued.\n";
            }
        } else {
            cout << "Book not found.\n";
        }
    }


//     void listAllBooks() {
//     sort(books.begin(), books.end(), [](const Book& a, const Book& b) {
//         return a.id < b.id;
//     });

//     const int pageSize = 10;
//     int totalBooks = books.size();
//     int page = 0;

//     while (page * pageSize < totalBooks) {
//         system("cls"); // Or system("clear"); for Linux/Mac

//         cout << "\nLibrary Catalog (" << totalBooks << " books)\n";
//         cout << left << setw(8) << "ID" << setw(30) << "Title" 
//              << setw(25) << "Author" << setw(15) << "Category" 
//              << setw(10) << "Year" << "Status\n";
//         cout << string(100, '-') << "\n";

//         for (int i = page * pageSize; i < min((page + 1) * pageSize, totalBooks); ++i) {
//             const Book& book = books[i];
//             cout << left << setw(8) << book.id << setw(30) 
//                  << (book.title.length() > 28 ? book.title.substr(0, 27) + "." : book.title)
//                  << setw(25) 
//                  << (book.author.length() > 23 ? book.author.substr(0, 22) + "." : book.author)
//                  << setw(15) << book.category << setw(10) 
//                  << (book.publicationYear > 0 ? to_string(book.publicationYear) : "Unknown")
//                  << (book.isIssued ? "Issued" : "Available") << "\n";
//         }

//         cout << "\nPage " << (page + 1) << " of " << ((totalBooks + pageSize - 1) / pageSize) << "\n";
//         if ((page + 1) * pageSize >= totalBooks) break;

//         cout << "Press Enter to view next page...";
//         cin.ignore();
//         cin.get();
//         ++page;
//     }
// }

    void listAllBooks() {
    sort(books.begin(), books.end(), [](const Book& a, const Book& b) {
        return a.id < b.id;
    });

    const int pageSize = 10;
    int totalBooks = books.size();
    int page = 0;

    while (page * pageSize < totalBooks) {
        system("cls"); // Use "clear" on Linux/Mac

        cout << "\nLibrary Catalog (" << totalBooks << " books)\n";
        cout << left << setw(8) << "ID" << setw(30) << "Title" 
             << setw(25) << "Author" << setw(15) << "Category" 
             << setw(10) << "Year" << "Status\n";
        cout << string(100, '-') << "\n";

        for (int i = page * pageSize; i < min((page + 1) * pageSize, totalBooks); ++i) {
            const Book& book = books[i];
            cout << left << setw(8) << book.id << setw(30) 
                 << (book.title.length() > 28 ? book.title.substr(0, 27) + "." : book.title)
                 << setw(25) 
                 << (book.author.length() > 23 ? book.author.substr(0, 22) + "." : book.author)
                 << setw(15) << book.category << setw(10) 
                 << (book.publicationYear > 0 ? to_string(book.publicationYear) : "Unknown")
                 << (book.isIssued ? "Issued" : "Available") << "\n";
        }

        cout << "\nPage " << (page + 1) << " of " << ((totalBooks + pageSize - 1) / pageSize) << "\n";
        if ((page + 1) * pageSize >= totalBooks) break;

        cout << "Press Enter to view next page...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Flush leftover input
        cin.get();
        ++page;
    }
}



    void deleteBook(int id) {
        auto it = find_if(books.begin(), books.end(), [id](const Book& b) {
            return b.id == id;
        });

        if (it != books.end()) {
            string category = it->category;
            books.erase(it);
            categoryCount[category]--;
            saveBooksToFile();
            cout << "Book deleted successfully.\n";
        } else {
            cout << "Book not found.\n";
        }
    }

    void showStatistics() {
        cout << "\nLibrary Statistics:\n";
        cout << "Total Books: " << books.size() << "\n";
        cout << "Issued Books: " << count_if(books.begin(), books.end(), 
            [](const Book& b) { return b.isIssued; }) << "\n";
        
        cout << "\nBooks by Category:\n";
        for (const auto& pair : categoryCount) {
            cout << setw(20) << left << pair.first << ": " << pair.second << "\n";
        }
    }

    void showTransactionHistory() {
        cout << "\nTransaction History:\n";
        cout << left << setw(8) << "Book ID" << setw(30) << "Title" 
             << setw(20) << "Student" << setw(15) << "Issue Date" 
             << setw(15) << "Return Date" << "Status\n";
        cout << string(100, '-') << "\n";

        for (const auto& trans : transactions) {
            cout << left << setw(8) << trans.bookId << setw(30) 
                 << (trans.bookTitle.length() > 28 ? trans.bookTitle.substr(0, 27) + "." : trans.bookTitle)
                 << setw(20) 
                 << (trans.studentName.length() > 18 ? trans.studentName.substr(0, 17) + "." : trans.studentName)
                 << setw(15) << trans.issueDate << setw(15) 
                 << (trans.isReturned ? trans.returnDate : "Not returned")
                 << (trans.isReturned ? "Returned" : "Active") << "\n";
        }
    }

    void clearScreen() {
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif
    }
};

// Main Function
int main() {
    Library library;
    int choice, id, year;
    string title, author, studentName, category;

    while (true) {
        library.clearScreen();
        cout << "\nLibrary Management System\n";
        cout << "1. Add Book\n2. Search Book by Title\n3. Search Book by ID\n";
        cout << "4. Search Books by Author\n5. Issue Book\n6. Return Book\n";
        cout << "7. List All Books\n8. Delete Book\n9. View Statistics\n";
        cout << "10. View Transaction History\n11. Exit\n";
        cout << "Enter your choice: ";
        
        // Input validation
        while (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number: ";
        }

        switch (choice) {
            case 1: // Add Book
                cout << "Enter Book ID: ";
                while (!(cin >> id)) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid input. Please enter a number: ";
                }
                cin.ignore();
                cout << "Enter Title: ";
                getline(cin, title);
                cout << "Enter Author: ";
                getline(cin, author);
                cout << "Enter Category (optional, press enter for General): ";
                getline(cin, category);
                if (category.empty()) category = "General";
                cout << "Enter Publication Year (optional, 0 for unknown): ";
                while (!(cin >> year)) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid input. Please enter a number: ";
                }
                library.addBook(id, title, author, category, year);
                break;
            case 2: // Search by Title
                cout << "Enter Title (or part of title): ";
                cin.ignore();
                getline(cin, title);
                library.searchBookByTitle(title);
                break;
            case 3: // Search by ID
                cout << "Enter Book ID: ";
                while (!(cin >> id)) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid input. Please enter a number: ";
                }
                library.searchBookById(id);
                break;
            case 4: // Search by Author
                cout << "Enter Author Name (or part of name): ";
                cin.ignore();
                getline(cin, author);
                library.searchBooksByAuthor(author);
                break;
            case 5: // Issue Book
                cout << "Enter Book ID: ";
                while (!(cin >> id)) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid input. Please enter a number: ";
                }
                cin.ignore();
                cout << "Enter Student Name: ";
                getline(cin, studentName);
                library.issueBook(id, studentName);
                break;
            case 6: // Return Book
                cout << "Enter Book ID: ";
                while (!(cin >> id)) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid input. Please enter a number: ";
                }
                library.returnBook(id);
                break;
            case 7: // List All Books
                library.listAllBooks();
                break;
            case 8: // Delete Book
                cout << "Enter Book ID: ";
                while (!(cin >> id)) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid input. Please enter a number: ";
                }
                library.deleteBook(id);
                break;
            case 9: // Statistics
                library.showStatistics();
                break;
            case 10: // Transaction History
                library.showTransactionHistory();
                break;
            case 11: // Exit
                cout << "Exiting program.\n";
                return 0;
            default:
                cout << "Invalid choice. Please try again.\n";
        }

        cout << "\nPress Enter to continue...";
        cin.ignore();
        cin.get();
    }

    return 0;
}