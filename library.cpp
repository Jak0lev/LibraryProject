#include <iostream>
#include <string>
#include <fstream>
#include <filesystem>
#include <vector>

// Reminder to kohu: pls comment what everything does
// make it possible that books can have modifiable statuses, for example: "reserved", "borrowed" and "available"

using namespace std;
namespace fs = std::filesystem;

void callReader(string j);
bool isRunning = true;

string basepath{ "../libraryProject/BOOKS/" };
fstream bookDetails(basepath + "bookDetails.txt", ios::app);
ifstream example(basepath + "example.txt");
fstream required(basepath + "req.txt", ios::app);
// string help = "===== List of commands =====\nShow all the books in a list - E\nShow details about a book - F [name of the book]\nAdd book to archive - W [name of the book]\nRead a book's contents - S [name of the book]\nDelete a book - Q [name of the book]\nHelp - H";
string help = "\n===== List of commands =====\nList of all the books - G\nShow details about a book - F [name of the book]\nAdd book to archive - W [name of the book]\nHelp - H\n=====\n";
class crazy {
private:
	string title{};
	string ISBN{};
	string author{};
	string publisher{};
	string date{};
	string language{};
	string subjMatter{};
	string status{};

public:
	void addBook() {
		cout << "\n=====\n" << "Enter the book's title: ";
		std::getline(std::cin >> std::ws, title);
		cout << "ISBN: ";
		std::getline(std::cin >> std::ws, ISBN);
		cout << "Author: ";
		std::getline(std::cin >> std::ws, author);
		cout << "Publisher: ";
		std::getline(std::cin >> std::ws, publisher);
		cout << "Date: ";
		std::getline(std::cin >> std::ws, date);
		cout << "Language: ";
		std::getline(std::cin >> std::ws, language);
		cout << "Subject matter: ";
		std::getline(std::cin >> std::ws, subjMatter);
		cout << "Status: ";
		std::getline(std::cin >> std::ws, status);
		writeDetails(title, ISBN, author, publisher, date, language, subjMatter, status);
		cout << "Finished! \n";
		cout << "=====\n";
	}
	void inspectBook(string x) {
		callReader(x);
		/*if (x.begin(), x.end()) {
		}*/
		cout << "\n===== \n" << title << '\n';
		cout << ISBN << '\n';
		cout << author << '\n';
		cout << publisher << '\n';
		cout << date << '\n';
		cout << language << '\n';
		cout << subjMatter << '\n';
		cout << status << "\n=====\n";
	}
	void writeDetails(string a, string b, string c, string d, string e, string f, string g, string h) {
		bookDetails << "@\n";
		bookDetails << '"' << title << '"' << '\n';
		bookDetails << "ISBN: " << ISBN << '\n';
		bookDetails << "Author: " << author << '\n';
		bookDetails << "Publisher: " << publisher << '\n';
		bookDetails << "Date: " << date << '\n';
		bookDetails << "Language: " << language << '\n';
		bookDetails << "Subject matter: " << subjMatter << '\n';
		bookDetails << "Status: " << status << '\n';
		bookDetails.seekg(0);
	}
};

int main()
{
	crazy book1;

	while (isRunning) {
		try { 
			cout << "\nLibrary home screen\ntype 'h' for help\n";
			string x{};
			std::getline(std::cin >> std::ws, x);
			transform(x.begin(), x.end(), x.begin(), ::tolower);

			if (x == "w") {
				book1.addBook();
			}
			/*else if (x == "z") {
				book1.inspectBook(x);
			}*/
			else if (x == "h") {
				cout << help;
			}
			else if (x == "q") {
				cout << "\nLeaving library. Shutting down.\n";
				bookDetails.close();
				example.close();
				required.close();
				isRunning = false;
			}
			else if (x == "g") {
				for (const auto& entry : fs::directory_iterator(basepath)) {
					cout << entry.path().filename() << '\n';
				}
			}
			else if (x[0] == 'f') {
				book1.inspectBook(x);
			}
			else if (x == "c") {
				system("cls");
			}

			else {
				throw x;
			}
		}
		catch (string l) {
			cout << "\nEntered: " << l;
			cout << "\nInvalid input, try again.\n";
		}
	}
	required.close();
	example.close();
	bookDetails.close();
	return 0;
}

void callReader(string j) {
	try {
		int num_whitespaces{};
		for (char c : j) {
			if (isspace(c, cin.getloc()))++num_whitespaces;
			cout << c;
		}
		cout << "\nCMON..." << num_whitespaces << '\n';
		size_t pos = j.find(' ') + 1;
		j.erase(0, pos);
		cout << "Debug callreader:\n" << j << '\n';
		if (j[0] != 'f') {
			vector<string> myBox = {};
			myBox.push_back(j);
			cout << myBox[0] << " it reached the box yey!";
			// loop through every text file name in file "BOOKS"
			for (const auto& entry : fs::directory_iterator(basepath)) {
				if (myBox[0] == entry.path().filename()) {
					cout << "\nReached the entry.path(), entering the file\n\n";
					myBox.clear();
					char ch{};
					while (example >> noskipws >> ch) {
						cout << ch;
					}
					example.clear();
					example.seekg(0, example.beg);
				}
			}
			
		}
		else {
			cout << "Error, try again.\n";
		}
	}
	catch (...){
		bookDetails.close();
		exit(0);
	}
}

void addBookToArchive(string box1)
{
	int i = stoi(box1);
}
