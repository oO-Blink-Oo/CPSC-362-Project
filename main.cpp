#include <iostream>
#include <ctype.h>
#include <iomanip>
#include <string>
#include <stdlib.h>
#include <fstream>
#include <vector>
#include <algorithm>
#include <functional>
#include <iterator>
//#include <initializer_list>
#define ARGC_ERROR 1
#define FILE_ERROR 2
using namespace std;
//test functions:
void testlist(int, const char*[]);
void testCustomer();
//functions:
void customer_interface();
void admin_interface();
void welcomePrompt();
void signInPrompt();
void support();
void featureMenu();//not used
void search_interface();

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

//Customer Class
class customer {
public:
	customer(string customerName, double money) : customerName_(customerName), money_(money) {}
	customer() : customerName_("John"), money_(1000) {}
	customer(string customerName) : customerName_(customerName), money_(1000) {}
	//FUNCTIONS NEEDED:
	friend class book_sorting;
	//1.VIEW SHOPPING CART
	void viewShoppingCart() {
		vector <book>::iterator it = shoppingCart_.begin();
		cout << "\n\n" << this->customerName_ << ", your shopping cart has: \n";
		int index = 0;
		for (it; it != shoppingCart_.end(); it++) {
			cout << index << ".) " << *it << "\n";
			index++;
		}
		cout << "\n\n";
	}
	//2. ADD TO SHOPPING CART
	void addToShoppingCart(book item) {//parameter should be the item to be added in the vector
		cout << endl;
		shoppingCart_.push_back(item);
		viewShoppingCart();
	}
	//3. REMOVE FROM SHOPPING CART
	void removeFromShoppingCart(int n) {
		shoppingCart_.erase(shoppingCart_.begin() + n);
	}
	//	//4. SUM THE TOTAL OF THE SHOPPING CART  //NEEDS TO BE IMPLEMENTED STILL
	double sumShoppingCart() {
		double subTotal = 0;
		double tax = 1.09;
		for (int i = 0; i < shoppingCart_.size(); i++)
		{
			subTotal += shoppingCart_[i].price_;
		}
		return subTotal;
	}
	//	
	////	//5. SUBTRACT TOTAL SUM OF SHOPPING CART + TAX FROM(-) MONEY //NEEDS TO BE IMPLEMENTED STILL
	//	double totalMoney() {
	//    	//tax
	//  double tax = 1.09;
	//  
	//	}
	double balance() {
		return money_ -= sumShoppingCart() * 1.09;
	}
	double getMoney() {
		return money_;
	}
private:
	string customerName_;
	vector <size_t> trackingNumbers;
	vector <book> orderHistory;
	vector <book> shoppingCart_;
	vector <double> totalOfShoppingCart_;
	double money_;
};

class admin {
public:
	admin() : admin(0) {}
	admin(double totalSales) : totalSales_(totalSales) {}

	//functions
	double addToSales(double n) {
		return totalSales_ += n;
	}

	void printSales() {
		cout << "\t\t\tTOTAL SALES: $" << totalSales_ << "\n\n";
	}
private:
	double totalSales_;
};

template <typename T>
using citerator = typename vector<T>::const_iterator;

template <typename T>	// template aliasing -- see JOSUTTIS
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
	book pick_book(size_t n) {//function for picking a book from vector of books
		return searchedList_[n];
	}
	void print_by_selection(const std::string& msg, std::function<bool(const book& a, const book& b)> predicate) {//how do we use this? (Chloe)
		sort_by_selection(msg, predicate);
		cout << *this << "\n";
	}
	void sort_analyze() {//SORT THE BOOKS
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

		for (int i = 0; i < bs.bk_.size(); i++) {
			os << i << " " << bs.bk_[i] << "\n";
		}
		//for (auto el : bs.bk_) { os << el << "\n"; }//index here
		return os;
	}
	void printBooks() {
		vector <book>::iterator it = searchedList_.begin();
		int counter = 0;
		for (it; it != searchedList_.end(); it++) {
			cout << counter << ".) " << *it << "\n";
			counter++;
		}
	}

	void printSales() {
		admin_.printSales();
	}
	//ORDER INTERFACE//
	void order_interface() {
		int user_choice;
		cout << "\nPlease select book to order: ";
		cin >> user_choice;
		guest_customer.addToShoppingCart(searchedList_[user_choice]);
	}
	void makePayment() {
		cout << "Your subtotal is: $" << setprecision(2) << fixed << guest_customer.sumShoppingCart() << endl;
		admin_.addToSales(guest_customer.sumShoppingCart());//adds the customer subtotal to the stores total sales
		cout << "Your total is: $" << setprecision(2) << fixed << guest_customer.sumShoppingCart() * 1.09 << endl;
		guest_customer.balance();//payed has been subtracted from total money
		cout << "Transaction has been completed. Thank you!\n";
		cout << "Your current balance is: $" << setprecision(2) << fixed << guest_customer.getMoney();
		for (int i = 0; i < guest_customer.shoppingCart_.size(); i++)
		{
			size_t tempISBN = guest_customer.shoppingCart_[i].isbn_;
			for (int j = 0; j < bk_.size(); j++)
			{
				if (tempISBN == bk_[j].isbn_) {
					bk_[j].quantity_--;
				}
			}
		}
		guest_customer.shoppingCart_.clear();
	}

	void viewShoppingCart() {
		int user_choice;
		int remove_selection;
		guest_customer.viewShoppingCart();
		cout << "\t\t\t1.) Make payment\n"
			<< "\t\t\t2.) Remove book from shopping cart\n"
			<< "\t\t\t3.) Search for more book(s)\n";
		cin >> user_choice;
		switch (user_choice)
		{
		case 1:
			makePayment();
			break;
		case 2:
			cout << "Please select the book you want to remove: ";
			cin >> remove_selection;
			guest_customer.removeFromShoppingCart(remove_selection);
			break;
		case 3:
			search_interface();
			break;
		default:
			break;
		}
	}
	void search_interface()
	{
		int user_choice;
		string firstName, lastName;
		string category, title;
		size_t ISBN;
		author temp(firstName, lastName);
		cout << "\n\n\t\t\t\t\t\tSearch by:\n"
			<< "\t\t\t\t\t\t	1. ISBN\n"//chloe
			<< "\t\t\t\t\t\t	2. Title\n"//xiaomei
			<< "\t\t\t\t\t\t	3. Author\n"//ian
			<< "\t\t\t\t\t\t	4. Category\n"
			<< "\t\t\t\t\t\t	5. Exit\n\t\t\t\t\t\t";
		cin >> user_choice;
		//do {
		switch (user_choice) {
		case 1://ISBN
			cout << "Input ISBN: ";
			cin >> ISBN;
			cout << "\nBook by this ISBN is: \n";
			searchedList_.clear();
			for (int i = 0; i < bk_.size(); i++) {
				if (bk_[i].isbn_ == ISBN) {
					searchedList_.push_back(bk_[i]);
				}
			}
			printBooks();
			order_interface();
			break;
		case 2://TITLE
			cout << "Input Title: ";
			cin >> title;
			cout << "\nBooks by this title is(are): \n";
			searchedList_.clear();
			for (int i = 0; i < bk_.size(); i++) {
				if (bk_[i].title_ == title) {
					searchedList_.push_back(bk_[i]);
				}
			}
			printBooks();
			order_interface();
			break;
		case 3://AUTHOR
			cout << "\t\tInput author's firstName and last name <firstName>_<lastName>: ";
			cin >> firstName;
			cin >> lastName;
			cout << "\nBooks by this author is(are): \n";
			//clear vector first
			searchedList_.clear();
			//used to populate vector used for the searched books
			for (int i = 0; i < bk_.size(); i++) {
				if (bk_[i].author_.lname_ == lastName && bk_[i].author_.fname_ == firstName) {
					searchedList_.push_back(bk_[i]);
				}
			}
			printBooks();
			order_interface();
			break;
		case 4://CATEGORY
			cout << "Input Category: ";
			cin >> category;
			cout << "\nBooks by this category is(are): \n";
			searchedList_.clear();
			for (int i = 0; i < bk_.size(); i++) {
				if (bk_[i].category_ == category) {
					searchedList_.push_back(bk_[i]);
				}
			}
			printBooks();
			order_interface();
			break;
		case 5:
			break;
		};
		//} while (user_choice != 5);
	}
	vector<book> getBook() {
		return bk_;
	}
private:
	double subTotal;
	double total;
	customer guest_customer;
	admin admin_;
	vector<book> searchedList_;
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

		cout << "file: " << filename_ << " is open...\n\n";
	}
	~filewrapper() {
		ifs_.close();
		cout << "\nfile: " << filename_ << " is closed...\n\n";
	}

	friend istream& operator>>(filewrapper& fw, book& bk) { return fw.ifs_ >> bk; }

private:
	string filename_;
	fstream ifs_;
};
/////////////////////////////////////////////////////////////////////////////////////////GLOBAL VARIABLE/////////////////////////////////////////////////////////////////////////
book_sorting bs;//This class object has the vector of books and functions to sort it

				/*********************************///MAIN FUNCTION///***********************************************************/
int main(int argc, const char * argv[]) {
	if (argc != 2) { cerr << "Usage: filename\n";  exit(ARGC_ERROR); }
	filewrapper fw(argv[1]);
	book bk;
	int counter = 0;
	while (fw >> bk) {
		bs.add(bk);
		counter++;
	}
	welcomePrompt();
	//guestCustomer.viewShoppingCart();
	cout << "\n\t\t\t\t\t   THANK YOU. SEE YOU AGAIN\n";
	return 0;
}
//WELCOME PROMPT
void welcomePrompt()
{
	//variables used for menu selection
	int signInChoice;
	char choice;
	cout << "\n\n\t\t\t\t\tWelcome to Phoenix Book Store!\n";
	cout << "\t\t1. Sign in(This feature is not available in this current version.)" << endl;
	cout << "\t\t2. Guest\n";
	cout << "\t\t3. Exit\n\t\t";
	cin >> signInChoice;
	while (signInChoice != 1 && signInChoice != 2 && signInChoice != 3) {
		cout << "\t\tPlease input a valid choice: ";
		cin >> signInChoice;
	}
	do {
		switch (signInChoice) {
		case 1://choose whether to sign in as admin or a user
			cout << "\t\t\tSing in. . .\n"
				<< "\t\ta. As admin\n"
				<< "\t\tb. As user\n\t\t";
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
			cout << "\t\t\t\t\t	Continuing as guest. . .\n\n";
			customer_interface();//show features menu
			break;
		case 3:
			exit(1);
			break;
		}
	} while (signInChoice != 3);
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
			customer_interface();//show features menu
		}
		else {
			cout << "Creating user account. . .\n";
			//create user account
		}
	}
}
void support()
{
	cout << "\n\t\t\tCustomer Support:\n";
	cout << "\t\t\t\tPhone number: 1 (800) 555-5555";
	cout << "\n\t\t\t\tEmail: uNeedHelp@weGotyou.net\n\n";
}
void admin_interface() {
	book new_book;
	int ch;
	char update_ch;
	size_t temp_isbn;
	size_t temp_quantity;
	do {
		cout << "\t\t\tWHICH OPERATION DO YOU WANT TO PERFORM ?" << endl << endl;
		cout << " \t\t 	Manage books" << endl;
		cout << " \t\t\t   1. Add a new book" << endl;
		cout << " \t\t\t   2. Update quantity of an exiting book" << endl;
		cout << " \t\t\t        Remove a book(TBD)" << endl;
		cout << " \t\t\t 	Manage orders (TBD)" << endl;
		cout << " \t\t\t 	Manage customers (TBD)" << endl;
		cout << " \t\t\t   3. Display sales report" << endl;
		cout << " \t\t\t   4. Exit" << endl;
		cout << "\t\tEnter your choice: ";
		cin >> ch;
		cout << "\n";
		while (ch != 1 && ch != 2 && ch != 3 && ch != 4)
		{
			cout << "\t\tPlease input a valid answer: ";
			cin >> ch;
		}
		switch (ch) {
		case 1:
			cout << "Enter the book's isbn: ";
			cin >> new_book.isbn_;
			cout << "Enter the book's title: ";
			cin >> new_book.title_;
			cout << "Enter the book's author: ";
			cin >> new_book.author_;
			cout << "Ener the book's quantity: ";
			cin >> new_book.quantity_;
			cout << "Enter the book's edition: ";
			cin >> new_book.edition_;
			cout << "Enter the book's category: ";
			cin >> new_book.category_;
			cout << "Enter the book's price: ";
			cin >> new_book.price_;
			bs.add(new_book);
			break;
		case 2:
			cout << endl;
			cout << " Enter the isbn: ";
			cin >> temp_isbn;
			cout << " Enter the updated quantity: ";
			cin >> temp_quantity;
			for (int i = 0; i < bs.getBook().size(); i++)
			{
				if (temp_isbn == bs.getBook()[i].isbn_) {
					bs.getBook()[i].quantity_ = temp_quantity;
				}
			}
			break;
		case 3:
			//printSales
			bs.printSales();
			break;
		case 4:
			welcomePrompt();
			break;
		default:
			break;
		}
	} while (ch != 4);
}
//CUSTOMER INTERFACE
void customer_interface() {//edited
	int ch;
	do {
		cout << "\n\n\t\t\t\t   WHICH OPERATION DO YOU WANT TO PERFORM ?" << endl << endl;
		cout << " \t\t1. 	Search for book(s)" << endl;
		cout << " \t\t2. 	View Shopping Cart" << endl;
		cout << " \t\t3. 	Create an account\t(N/A in this version)" << endl;
		cout << " \t\t4. 	Login\t\t\t(N/A in this version)" << endl;
		cout << " \t\t5. 	Contact customer support" << endl;
		cout << " \t\t6. 	Exit" << endl;
		cout << "\t\t\tEnter your choice: ";
		cin >> ch;
		while (ch != 1 && ch != 2 && ch != 3 && ch != 4 && ch != 5 && ch != 6)
		{
			cout << "\t\tPlease input a valid answer: ";
			cin >> ch;
		}
		switch (ch) {
		case 1:
			bs.search_interface();
			break;
		case 2:
			bs.viewShoppingCart();
			break;
		case 3:
			cout << "\t\t\tFEATURE NOT AVAILABLE IN THIS CURRENT VERSION\n";
			break;
		case 4:
			cout << "\t\t\tFEATURE NOT AVAILABLE IN THIS CURRENT VERSION\n";
			break;
		case 5:
			//call customer support function
			support();
			break;
		case 6:
			welcomePrompt();
			cout << "Exiting. . .\n";
			break;
		}
	} while (ch != 6);
}
//TEST LIST
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
