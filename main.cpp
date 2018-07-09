#include <iostream>
#include <ctype.h>
#include <iomanip>

using namespace std;

void welcomePrompt();
void signInPrompt();
void featureMenu();

int main() {
	featureMenu();//just testing here, so we could see what the feature menu looks like
	welcomePrompt();

	return 0;
}//end of main

 //WELCOM PROMPT
void welcomePrompt()
{
	//variables used for menu selection
	int signInChoice;

	cout << "\t\t\tWelcome to Phoenix Book Store!\n";
	cout << "\t\t1. Sign in" << endl;
	cout << "\t\t2. Guest" << endl;
	cin >> signInChoice;
	while (signInChoice != 1 && signInChoice != 2) {
		cout << "Please input a valid choice: ";
		cin >> signInChoice;
	}

	switch (signInChoice) {
	case 1:
		cout << "Continuing as user. . .\n";
		//show features menu
		signInPrompt();
		break;

	case 2:
		cout << "Continuing as guest. . .\n";
		//show features menu
		break;

	default:
		break;
	}
}

//SIGN IN PROMPT
void signInPrompt()
{
	char signInAnswer, createAccountAnswer;

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
		cin >> createAccountAnswer;
		while ((createAccountAnswer != 'Y') && (createAccountAnswer != 'y') && (createAccountAnswer != 'N') && (createAccountAnswer != 'n')) {
			cout << "Please input a valid choice: ";
			cin >> createAccountAnswer;
		}

		tolower(createAccountAnswer);//forces singInAnswer to be lower case

		if (createAccountAnswer == 'n') {

			cout << "Continuing as guest. . .\n";
			//show features menu

		}
		else {

			cout << "Creating user account. . .\n";
			//create user account 

		}

	}

}

//FEATURE MENU
void featureMenu() {
	cout << "Please select from the menu:\n";
	cout << setw(30) << "1.\n"
		<< setw(30) << "2.\n"
		<< setw(30) << "3.\n"
		<< setw(30) << "4.\n"
		<< setw(30) << "5.\n"
		<< setw(30) << "6.\n"
		<< setw(30) << "7.\n"
		<< setw(30) << "8.\n"
		<< setw(30) << "9.\n"
		<< setw(30) << "10.\n"
		<< setw(30) << "11.\n";

}