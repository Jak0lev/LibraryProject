#include <iostream>
#include <string>	
#include <fstream>	// for creating, reading and writing files
#include <filesystem>	// for finding file directories
#include <vector>	// for storing two or more strings with a whitespace between them

/*
Reminder to kohu: pls comment what everything does
make it possible that books can have modifiable statuses, for example: "reserved", "borrowed" and "available"
*/


// Setup
using namespace std;
namespace fs = std::filesystem;

void callLooper(string j);
void inspectBook(string myBox);
void contentReader(string myBox);
bool isRunning = true;

string basepath{ "C:/../repos/libraryProject/BOOKS/" };
string help = "\n===== List of commands =====\nQuit the library - Q\nList of all the books - G\nAdd book to archive - W\nShow details about a book - Z [name of the book]\nRead the contents of a book - F [name of the book]\nClear console - C\n=====\n";

// creating a class through which the program writes / reads stuff to files
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
	void readBook(string x) {
		callLooper(x);
	}
	void writeDetails(string a, string b, string c, string d, string e, string f, string g, string h) {
		string filenamer = a;
		remove(filenamer.begin(), filenamer.end(), ' ');
		fstream bookDetails(basepath + filenamer + ".txt", ios::app);
		bookDetails << "@\n";
		bookDetails << '"' << title << '"' << '\n';
		bookDetails << "ISBN: " << ISBN << '\n';
		bookDetails << "Author: " << author << '\n';
		bookDetails << "Publisher: " << publisher << '\n';
		bookDetails << "Date: " << date << '\n';
		bookDetails << "Language: " << language << '\n';
		bookDetails << "Subject matter: " << subjMatter << '\n';
		bookDetails << "Status: " << status << '\n';
		bookDetails << "@\n";
		bookDetails.seekg(0);
		bookDetails.close();
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
			else if (x[0] == 'z') {
				book1.readBook(x);
			}
			else if (x == "h") {
				cout << help;
			}
			else if (x == "q") {
				cout << "\nLeaving library. Shutting down.\n";
				isRunning = false;
			}
			else if (x == "g") {
				for (const auto& entry : fs::directory_iterator(basepath)) {
					cout << entry.path().filename() << '\n';
				}
			}
			else if (x[0] == 'f') {
				book1.readBook(x);
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
	return 0;
}


// Functions that read, write and do stuff with files
void callLooper(string j) {
	try {
		if (j[0] == 'z') {
			size_t pos = j.find(' ') + 1;
			j.erase(0, pos);
			// cout << "Debug callLooper:\n" << j << '\n';
			vector<string> myBox = {};
			myBox.push_back(j);
			// loop through every text file name in file "BOOKS"
			for (const auto &entry : fs::directory_iterator(basepath)) {
				if (myBox[0] == entry.path().filename()) {
					inspectBook(myBox[0]);
				}
				else if (myBox[0] == "") {
					cout << "Bad input.\n";
				}
			}
		}
		else if (j[0] == 'f') {
			size_t pos = j.find(' ') + 1;
			j.erase(0, pos);
			vector<string> myBox = {};
			myBox.push_back(j);
			// loop through every text file name in file "BOOKS"
			for (const auto &entry : fs::directory_iterator(basepath)) {
				if (myBox[0] == entry.path().filename()) {
					contentReader(myBox[0]);
				}
				else if (myBox[0] == "") {
					cout << "Bad input.\n";
				}
			}
			myBox.clear();
			cout << "\n\nmyBox has been cleared()";
		}
	}
	catch (...){
		cout << "Error. Unexpected interruption." << '\n';
		exit(0);
	}
}

void inspectBook(string myBox) {
	int hits{0};
	char ch{};
	fstream textfile(basepath + myBox);	
	cout << '\n';
	while (textfile >> noskipws >> ch && hits != 2) {
		if (ch == '@') {
			textfile.ignore();
			hits += 1;
		}
		else {
			cout << ch;
		}
	}
	textfile.clear();
	textfile.seekg(0, textfile.beg);
	textfile.close();
}

void contentReader(string myBox) {
	int hits{ 0 };
	char ch{};
	fstream textfile(basepath + myBox);	
	while (textfile >> noskipws >> ch) {
		if (ch == '@') {
			hits += 1;
		}
		if (hits == 2) {
			if (ch != '@') {
				cout << ch;
			}
		}
	}
	textfile.clear();
	textfile.seekg(0, textfile.beg);
	textfile.close();
}
