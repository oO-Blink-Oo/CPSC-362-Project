#include <iostream>
#include <ctype.h>
#include <iomanip>
#include <string>
#include <stdlib.h>
#include <fstream>
#include <vector>
#include <algorithm>
#include <functional>

//#include <initializer_list>

#define ARGC_ERROR 1

#define FILE_ERROR 2


using namespace std;

void customer_interface();
void admin_interface();
void welcomePrompt();
void signInPrompt();
void featureMenu();
void testlist(int, const char*[]);

//Customer Class
class customer {
public:
	customer(string customerName, double money) : customerName_(customerName), money_(money) {}
	customer() : customerName_("John"), money_(100) {}

	//FUNCTIONS NEEDED:
	
	//1.VIEW SHOPPING CART
	void viewShoppingCart() {

	}
	//2. ADD TO SHOPPING CART
	void addToShoppingCart() {

	}
	//3. REMOVE FROM SHOPPING CART
	void removeFromShoppingCart() {

	}
	//4. SUM THE TOTAL OF THE SHOPPING CART
	double sumShoppingCart() {

	}
	//5. SUBTRACT TOTAL SUM OF SHOPPING CART FROM MONEY
	double totalMoney() {

	}
	
private:
	string customerName_;
	vector <book> shoppingCart_;
	vector <double> totalOfShoppingCart_;
	double money_;
};


struct author {

	author() : author("", "") {}

	author(const string& lname, const string& fname) : lname_(lname), fname_(fname) {}



	friend bool operator<(const author& a, const author& b) {

		return a.lname_ < b.lname_ || (a.lname_ == b.lname_ && a.fname_ < b.fname_);

	}

	friend bool operator==(const author& a, const author& b) {

		return a.lname_ == b.lname_ && a.fname_ == b.fname_;

	}

	friend bool operator>(const author& a, const author& b) {

		return !(a < b) && !(a == b);

	}

	friend std::istream& operator>>(std::istream& is, author& author) {

		return is >> author.fname_ >> author.lname_;

	}

	friend std::ostream& operator<<(std::ostream& os, const author& author) {

		return os << std::setw(12) << author.fname_ << " " << author.lname_ << "\t";

	}

	string lname_;

	string fname_;

};

struct book {

	book() : book(0, "", author(), 0, 0, "", 0.0) {}

	book(size_t isbn, const string& title, const author& author, size_t quantity, size_t edition,

		const string& category, double price) : isbn_(isbn), title_(title), author_(author), quantity_(quantity),

		edition_(edition), category_(category), price_(price) {}



	friend bool operator<(const book& a, const book& b) {

		return a.price_ < b.price_ || (a.price_ == b.price_ && a.title_ < b.title_)

			|| (a.price_ == b.price_ && a.title_ == b.title_ && a.category_ < b.category_);

	}

	friend bool operator==(const book& a, const book& b) {

		return a.price_ == b.price_ && a.title_ == b.title_ && a.category_ == b.category_;

	}

	friend bool operator>(const book& a, const book& b) {

		return !(a < b) && !(a == b);

	}



	friend istream& operator>>(istream& is, book& book) {

		is >> book.isbn_;
		is >> book.title_;
		is >> book.author_;
		is >> book.quantity_;
		is >> book.edition_;
		is >> book.category_;
		is >> book.price_;
		return is;

	}

	friend ostream& operator<<(ostream& os, const book& book) {

		return os << book.isbn_ << setw(100) << book.title_ << setw(20)

			<< book.author_ << setw(10) << book.quantity_ << setw(10) << book.edition_

			<< setw(10) << book.category_ << setw(10) << book.price_;

	}



	size_t isbn_;

	string title_;

	author author_;

	size_t quantity_;

	size_t edition_;

	string category_;

	double price_;



};



template <typename T>

using citerator = typename vector<T>::const_iterator;



template <typename T>    // template aliasing -- see JOSUTTIS

using pair_range = pair<citerator<T>, citerator<T>>;



//------------------------------------------------------

template <typename T>   // wrapper class (ADAPTER Design Pattern)

class prwrapper {

public:

	prwrapper(pair_range<T>& pr) : wrap_(pr) {}



	citerator<T> begin() const { return wrap_.first; }

	citerator<T> end()   const { return wrap_.second; }



private:

	pair_range<T> wrap_;

};



//------------------------------------------------------

template <typename T>

void printrange(const string& msg, pair_range<T>& pr, T val) {

	cout << msg;

	prwrapper<T> wrap(pr);



	for (auto el : wrap) { cout << el << "\n"; }

	cout << "\n";

}



class book_sorting {

public:

	void add(const book& bk) {
		bk_.push_back(bk);

	}


	void sort_by_selection(const string& msg, function<bool(const book& a, const book& b)> predicate) {

		cout << "sorting by: " << msg;

		sort(bk_.begin(), bk_.end(), predicate);

	}

	void print_by_selection(const std::string& msg, std::function<bool(const book& a, const book& b)> predicate) {

		sort_by_selection(msg, predicate);

		cout << *this << "\n";

	}

	void sort_analyze() {

		cout << "List of books: \n" << *this << "\n";



		int sort_choice;

		cout << "\tSort by\n";

		cout << "\t1. Price" << endl;

		cout << "\t2. Title" << endl;

		cout << "\t3. Category" << endl;

		cin >> sort_choice;

		while (sort_choice != 1 && sort_choice != 2 && sort_choice != 3) {

			cout << "Please input a valid number: ";

			cin >> sort_choice;

		}

		switch (sort_choice) {

		case 1:

			print_by_selection("price: \n",

				[](const book& a, const book&b) {return a.price_ < b.price_; });

			break;



		case 2:

			print_by_selection("title: \n",

				[](const book& a, const book& b) {return a.title_ < b.title_; });

			break;



		case 3:

			print_by_selection("category: \n",

				[](const book& a, const book& b) {return a.category_ < b.category_; });

			break;



		default:

			break;

		}



	}



	friend ostream& operator<<(ostream& os, const book_sorting& bs) {

		if (bs.bk_.empty()) { return os << "empty\n"; }



		for (auto el : bs.bk_) { os << el << "\n"; }

		return os;

	}



private:

	vector<book> bk_;



};

//-----------------------------------------

//

class filewrapper {

public:

	filewrapper(const string& filename)

		: filename_(filename) {

		ifs_.open(filename_);

		if (!ifs_.is_open()) { cerr << "could not find file: " << filename_ << "\n";  exit(FILE_ERROR); }



		cout << "file: " << filename_ << " is open...\n";

	}

	~filewrapper() {

		ifs_.close();

		cout << "file: " << filename_ << " is closed...\n";

	}



	friend istream& operator>>(filewrapper& fw, book& bk) { return fw.ifs_ >> bk; }



private:

	string filename_;

	fstream ifs_;

};





int main(int argc, const char * argv[]) {
	testlist(argc, argv);
	// welcomePrompt();




	cout << "\nTHANK YOU. SEE YOU AGAIN\n";

	return 0;

}

//WELCOM PROMPT
void welcomePrompt()
{
	//variables used for menu selection
	int signInChoice;
	char choice;

	cout << "\t\t\tWelcome to Phoenix Book Store!\n";
	cout << "\t\t1. Sign in" << endl;
	cout << "\t\t2. Guest\n\t\t";
	cin >> signInChoice;
	while (signInChoice != 1 && signInChoice != 2) {
		cout << "\t\tPlease input a valid choice: ";
		cin >> signInChoice;
	}

	switch (signInChoice) {
	case 1://choose whether to sign in as admin or a user
		cout << "\t\t\tSing in. . .\n"
			<< "\t\tA. As admin\n"
			<< "\t\tB. As user\n\t\t";
		cin >> choice;

		tolower(choice);

		while (choice != 'a' && choice != 'b') {
			cout << "\t\tPlease input a valid choice: ";
			cin >> choice;
		}

		switch (choice) {
		case 'a': admin_interface();
			break;

		case 'b': customer_interface();
			break;

		default:
			break;
		}
	case 2:
		cout << "\t\tContinuing as guest. . .\n\n";
		customer_interface();//show features menu
		break;
	}
}

//SIGN IN PROMPT
void signInPrompt() {
	char signInAnswer, accountAnswer;

	cout << "Returning user? (y/n): ";
	cin >> signInAnswer;
	while ((signInAnswer != 'Y') && (signInAnswer != 'y') && (signInAnswer != 'N') && (signInAnswer != 'n')) {
		cout << "Please input a valid choice: ";
		cin >> signInAnswer;
	}

	tolower(signInAnswer);//forces singInAnswer to be lower case


	if (signInAnswer == 'y') {//if returning user, then this means that this user is already in our textfile of users

							  //insert login function, if this is a returning user there will be a saved payment method that will be used for checkout
	}
	else {

		cout << "Would you like to create a user account? (y/n): ";
		cin >> accountAnswer;
		tolower(accountAnswer);//forces singInAnswer to be lower case

		while (accountAnswer != 'y' && accountAnswer != 'n') {
			cout << "Please input a valid choice: ";
			cin >> accountAnswer;
		}



		if (accountAnswer == 'n') {

			cout << "Continuing as guest. . .\n";
			featureMenu();//show features menu

		}
		else {

			cout << "Creating user account. . .\n";
			//create user account

		}

	}

}

//FEATURE MENU
void featureMenu() {
	cout << setw(50) << "Please select from the menu:\n";
	cout << setw(50) << "1. Search and pick a book\n" //searching for book should ask user if they want to search through ISBN, Title or Author, once found user is asked if what to do next; order, view more

		<< setw(63) << "2. Display ALL of the books available.\n"//prompt user what to do next; search and pick frmo the displayed selection

		<< setw(52) << "3. Contact Customer Support\n"//outputs customer support email and number
		<< setw(32) << "4. Exit\n";

}

void admin_interface() {
	int ch;
	do {
		cout << "\t\t\tWHICH OPERATION DO YOU WANT TO PERFORM ?" << endl << endl;
		cout << " \t\t1.     Manage books" << endl;
		cout << " \t\t2.     Manage orders" << endl;
		cout << " \t\t3.     Manage customers" << endl;
		cout << " \t\t4.     Exit" << endl;
		cout << "\t\tEnter your choice" << endl;
		cin >> ch;
		while (ch != 1 && ch != 2 && ch != 3 && ch != 4 && ch != 4)
		{
			cout << "\t\tPlease input a valid answer: ";
			cin >> ch;
		}
		switch (ch) {

			//manage books
		case 1:

			break;
		case 2:

			break;
		case 3:

			break;
		case 4:
			break;
		}
	} while (ch != 4);
}

//CUSTOMER INTERFACE
void customer_interface() {
	int ch;
	do {
		cout << "\t\t\tWHICH OPERATION DO YOU WANT TO PERFORM ?" << endl << endl;
		cout << " \t\t1.     Search books" << endl;
		cout << " \t\t2.     List books by category" << endl;
		cout << " \t\t3.     Creat an account" << endl;
		cout << " \t\t4.     Login" << endl;
		cout << " \t\t5.     Exit" << endl;
		cout << "\t\tEnter your choice: ";
		cin >> ch;
		while (ch != 1 && ch != 2 && ch != 3 && ch != 4 && ch != 5)
		{
			cout << "\t\tPlease input a valid answer: ";
			cin >> ch;
		}
		switch (ch) {

		case 1:

			break;
		case 2:

			break;
		case 3:

			break;
		case 4:

			break;
		case 5:
			break;
		}
	} while (ch != 5);
}



void testlist(int argc, const char* argv[]) {

	if (argc != 2) { cerr << "Usage: filename\n";  exit(ARGC_ERROR); }



	filewrapper fw(argv[1]);

	book bk;

	book_sorting bs;



	while (fw >> bk) {

		bs.add(bk);

	}

	bs.sort_analyze();

}

