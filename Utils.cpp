#include "Utils.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <limits>
#include <cctype>
#include <cmath>


using namespace std;
vector<string> SplitWords(string Text, string Delim)
{
	vector<string> words;
	size_t pos = 0;
	string word;

	while ((pos = Text.find(Delim)) != string::npos)
	{
		word = Text.substr(0, pos);

		if (!word.empty())
			words.push_back(word);

		Text.erase(0, pos + Delim.length());
	}

	if (!Text.empty())
		words.push_back(Text);

	return words;
}
bool IsClientExisting(const string& AccountNumber, const vector <StClient>& Clients)
{


	for (const StClient& Client : Clients)
	{
		if (Client.AccountNumber == AccountNumber)
		{

			return true;
		}

	}
	return false;


}
bool IsUserExisting(const string& UserName, const vector <StUser>& Users)
{


	for (const StUser& User : Users)
	{
		if (User.UserName == UserName)
		{

			return true;
		}

	}
	return false;


}
bool IsPerformMainMenueChoice(StUser CurrentUser, const short ChoiceNumber)
{
	short BinaryChoiceNumber = pow(2, ChoiceNumber - 1);
	return (((CurrentUser.Permissions & BinaryChoiceNumber) == BinaryChoiceNumber) || ChoiceNumber == 8);
}
bool CheckPermission(StUser& User, short Permission)
{
	return(User.Permissions & Permission) == Permission;
}
bool ConfirmOperation(string OperationType, string Name)
{
	char Answer;


	while (true)
	{
		cout << "\n\nAre You sure You Want " << OperationType << " This " << Name << " (Y / N) : ";
		cin >> Answer;

		Answer = toupper(Answer);
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		if (Answer == 'Y')
			return true;
		else if (Answer == 'N')
			return false;
		else
		{
			cout << "Invalid Answer Please Answer with (Y/N)\n";

		}
	}
}
bool ConfirmTransaction()
{
	char Answer;


	while (true)
	{
		cout << "\n\nAre You sure You Want To Perform This Transaction (Y/N) :";
		cin >> Answer;

		Answer = toupper(Answer);
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		if (Answer == 'Y')
			return true;
		else if (Answer == 'N')
			return false;
		else
		{
			cout << "Invalid Answer Please Answer with (Y/N)\n";

		}
	}
}
bool AddAnotherClient()
{
	char UserChoice;
	cout << "\nClient Added Successfully, Do You Want To Add More Clients (Y/N) ?\n";
	cin >> UserChoice;

	if (UserChoice == 'Y' || UserChoice == 'y')
		return true;
	else if (UserChoice == 'N' || UserChoice == 'n')
		return false;
	else
	{
		cout << "\nIncorrect, Answer With (Y/N).\n";
		return AddAnotherClient();
	}
}
bool AddAnotherUser()
{
	char UserChoice;
	cout << "\nUser Added Successfully, Do You Want To Add More Users (Y/N) ?\n";
	cin >> UserChoice;

	if (UserChoice == 'Y' || UserChoice == 'y')
		return true;
	else if (UserChoice == 'N' || UserChoice == 'n')
		return false;
	else
	{
		cout << "\nIncorrect, Answer With (Y/N).\n";
		return AddAnotherUser();
	}
}
bool IsUserDataValid(const StUser& UserToCheck, const vector <StUser>& Users)
{
	for (const StUser& User : Users)
	{
		if (UserToCheck.UserName == User.UserName)
		{
			if (UserToCheck.Passowrd == User.Passowrd)
				return true;
			else
				return false;
		}
	}
	return false;
}

double ReadValidBalance()
{
	double Balance;

	while (true)
	{
		cout << "Enter Account Balance: ";
		cin >> Balance;

		if (!cin.fail())
			return Balance;

		cout << "Invalid input! Please enter a number.\n";

		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');


	}
}
short ReadValidOperationNum(const short& NumberOfOperations)
{
	short Number;

	while (true)
	{
		cout << "Choose What Do You Want To Do [1 - " << NumberOfOperations << "]";
		cin >> Number;

		if (!cin.fail() && Number >= 1 && Number <= NumberOfOperations)
		{

			return Number;
		}
		else
		{

			cout << "\nIncorrect Answer, Please Choose (1 To " << NumberOfOperations << ") !!\n";

			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}

	}
}
short ReadPermissions()
{
	short Permissions = 0;
	char Approve = ' ';
	cout << "\nDo You Want To Give Full Access? Y/N: ";
	cin >> Approve;

	if (toupper(Approve) == 'Y')
	{
		return -1;
	}
	else
	{


		cout << "\nDo You Want To Give Access To:\n";

		cout << "Show Clients List? Y/N: ";
		cin >> Approve;
		if (toupper(Approve) == 'Y')
			Permissions += 1;

		cout << "Add New Client? Y/N: ";
		cin >> Approve;
		if (toupper(Approve) == 'Y')
			Permissions += 2;

		cout << "Delete Client? Y/N: ";
		cin >> Approve;
		if (toupper(Approve) == 'Y')
			Permissions += 4;

		cout << "Update Client? Y/N: ";
		cin >> Approve;
		if (toupper(Approve) == 'Y')
			Permissions += 8;

		cout << "Find Client? Y/N: ";
		cin >> Approve;
		if (toupper(Approve) == 'Y')
			Permissions += 16;

		cout << "Transactions? Y/N: ";
		cin >> Approve;
		if (toupper(Approve) == 'Y')
			Permissions += 32;

		cout << "Manage Users? Y/N: ";
		cin >> Approve;
		if (toupper(Approve) == 'Y')
			Permissions += 64;
		return Permissions;
	}

}
short ReadOperationType()
{
	return ReadValidOperationNum(8);
}
short ReadTransactionType()
{
	return ReadValidOperationNum(4);
}
short ReadManageUsersType()
{
	return ReadValidOperationNum(6);
}


StClient ReadClientDataToAdd(const vector <StClient>& Clients)
{
	StClient Client;

	cout << "Please Enter Client Data :\n\n";

	cout << "Enter Account Number : \n";
	getline(cin >> ws, Client.AccountNumber);
	while (IsClientExisting(Client.AccountNumber, Clients))
	{
		cout << "Client With [" << Client.AccountNumber << "] already exists, Enter another Account Number? ";
		getline(cin >> ws, Client.AccountNumber);
	}
	cout << "Enter PinCode : \n";
	getline(cin, Client.PinCode);

	cout << "Enter Name : \n";
	getline(cin, Client.Name);

	cout << "Enter Phone Number : \n";
	getline(cin, Client.Phone);

	Client.AccountBalance = ReadValidBalance();

	return Client;
}
StClient ReadClientDataToUpdate()
{
	StClient Client;

	cout << "Please Enter Client Data :\n\n";


	cout << "Enter PinCode ? ";
	getline(cin >> ws, Client.PinCode);

	cout << "Enter Name ? ";
	getline(cin, Client.Name);

	cout << "Enter Phone Number ? ";
	getline(cin, Client.Phone);

	Client.AccountBalance = ReadValidBalance();

	return Client;
}

string ReadUesrName()
{
	string Name;

	cout << "Enter Username? ";
	cin >> Name;

	return Name;
}
string ReadUserPassword()
{
	string Password;
	cout << "Enter Password? ";
	cin >> Password;
	return Password;
}
string ReadAccountNumber()
{
	string AccountNumber;

	cout << "Please Enter Account Number ? ";
	getline(cin >> ws, AccountNumber);

	return AccountNumber;
}
StUser ReadUserDataToLogin()
{
	StUser User;

	User.UserName = ReadUesrName();
	User.Passowrd = ReadUserPassword();

	return User;
}
StUser ReadUserDataToUpdate()
{
	StUser User;

	cout << "Please Enter User Data :\n\n";


	cout << "Enter Username ? ";
	getline(cin >> ws, User.UserName);

	cout << "Enter Password ? ";
	getline(cin, User.Passowrd);

	User.Permissions = ReadPermissions();


	return User;
}
StUser ReadUserDataToAdd(const vector <StUser>& Users)
{
	StUser User;

	cout << "Enter Username? ";
	getline(cin >> ws, User.UserName);
	while (IsUserExisting(User.UserName, Users))
	{
		cout << "User With [" << User.UserName << "] already exists, Enter another UserName? ";
		getline(cin >> ws, User.UserName);
	}
	cout << "Enter Password? ";
	getline(cin, User.Passowrd);

	User.Permissions = ReadPermissions();

	return User;
}

short GetPermission(short OperationType)
{
	switch (OperationType)
	{
	case enShow:
		return pShowClients;

	case enAdd:
		return pAddClient;

	case enDelete:
		return pDeleteClient;

	case enUpdate:
		return pUpdateClient;

	case enFind:
		return pFindClient;

	case enTransactions:
		return pTransactions;

	case enManageUsers:
		return pManageUsers;

	default:
		return 0;
	}
}
double TotalBalances(const vector <StClient>& Clients)
{
	double Total = 0;

	for (const StClient& Client : Clients)
	{
		Total += Client.AccountBalance;
	}
	return Total;
}

void PrintClientRecord(const StClient& Client)
{
	cout << "\nThe Following Are The Client Details:\n";
	cout << "\n-----------------------------------\n";
	cout << "Account Number  : " << Client.AccountNumber << endl;
	cout << "PinCode         : " << Client.PinCode << endl;
	cout << "Name            : " << Client.Name << endl;
	cout << "Phone Number    : " << Client.Phone << endl;
	cout << "Account Balance : " << fixed << setprecision(2) << Client.AccountBalance << endl;
	cout << "-----------------------------------\n";

}
void PrintClientRecordOfLine(const StClient& Client)
{
	cout << "|  " << setw(15) << left << Client.AccountNumber;
	cout << "|  " << setw(10) << left << Client.PinCode;
	cout << "|  " << setw(40) << left << Client.Name;
	cout << "|  " << setw(12) << left << Client.Phone;
	cout << "|  " << setw(12) << left << fixed << setprecision(2) << Client.AccountBalance;

}
void PrintClientBalanceOfLine(const StClient& Client)
{
	cout << "|  " << setw(15) << left << Client.AccountNumber;
	cout << "|  " << setw(40) << left << Client.Name;
	cout << "|  " << setw(12) << left << fixed << setprecision(2) << Client.AccountBalance;

}
void PrintClientsOfList(const vector <StClient>& Clients)
{
	cout << "\n\t\t\t\t\tClients List (" << Clients.size() << ")(s)." << endl;
	cout << "______________________________________________________________________________________________________\n";
	cout << "|  " << setw(15) << left << "Account Number";
	cout << "|  " << setw(10) << left << "Pin Code";
	cout << "|  " << setw(40) << left << "Client Name";
	cout << "|  " << setw(12) << left << "Phone";
	cout << "|  " << setw(12) << left << fixed << setprecision(2) << "Balance";
	cout << "\n\n______________________________________________________________________________________________________\n\n";

	for (const StClient& Client : Clients)
	{
		PrintClientRecordOfLine(Client);
		cout << endl;
	}
	cout << "\n______________________________________________________________________________________________________\n\n";

}
void PrintBalancesOfList(const vector <StClient>& Clients)
{
	cout << "\n\t\t\t\t\tBalances List (" << Clients.size() << ")(s)." << endl;
	cout << "______________________________________________________________________________________________________\n";
	cout << "|  " << setw(15) << left << "Account Number";
	cout << "|  " << setw(40) << left << "Client Name";
	cout << "|  " << setw(12) << left << fixed << setprecision(2) << "Balance";
	cout << "\n\n______________________________________________________________________________________________________\n\n";

	for (const StClient& Client : Clients)
	{
		PrintClientBalanceOfLine(Client);
		cout << endl;
	}
	cout << "\n______________________________________________________________________________________________________\n\n";

}

void PrintUserRecord(const StUser& User)
{
	cout << "\nThe Following Are The User Details:\n";
	cout << "\n-----------------------------------\n";
	cout << "Username    : " << User.UserName << endl;
	cout << "Password    : " << User.Passowrd << endl;
	cout << "Permissions : " << User.Permissions << endl;
	cout << "-----------------------------------\n";

}
void PrintUserRecordOfLine(const StUser& User)
{
	cout << "|  " << setw(15) << left << User.UserName;
	cout << "|  " << setw(10) << left << User.Passowrd;
	cout << "|  " << setw(40) << left << User.Permissions;
}
void PrintUsersOfList(const vector <StUser>& Users)
{
	cout << "\n\t\t\t\t\tUsers List (" << Users.size() << ") User(s)." << endl;
	cout << "______________________________________________________________________________________________________\n";
	cout << "|  " << setw(15) << left << "Username";
	cout << "|  " << setw(10) << left << "Password";
	cout << "|  " << setw(40) << left << "Permissions";
	cout << "\n\n______________________________________________________________________________________________________\n\n";

	for (const StUser& User : Users)
	{
		PrintUserRecordOfLine(User);
		cout << endl;
	}
	cout << "\n______________________________________________________________________________________________________\n\n";

}

void NoPermission()
{
	system("cls");
	cout << "\n-------------------------------------\n";
	cout << " Access Denied,\n";
	cout << " You Dont Have permission To Do This,\n";
	cout << " Please Contant Your Admin.\n";
	cout << "\n-------------------------------------\n\n";
}
void MainMenuScreen()
{
	system("cls");
	cout << "===========================================\n";
	cout << "            Main Menu Screen\n";
	cout << "===========================================\n";
	cout << "\t[1] Show Clients List.\n";
	cout << "\t[2] Add New Client.\n";
	cout << "\t[3] Delete Client.\n";
	cout << "\t[4] Update Client Info.\n";
	cout << "\t[5] Find Client.\n";
	cout << "\t[6] Transactions [Menu].\n";
	cout << "\t[7] Manage Users [Menu].\n";
	cout << "\t[8] Logout.\n";
	cout << "===========================================\n";

}

void TransactionsMenuScreen()
{
	system("cls");
	cout << "===========================================\n";
	cout << "         Transactions Menu Screen\n";
	cout << "===========================================\n";
	cout << "\t[1] Deposit.\n";
	cout << "\t[2] Withdraw.\n";
	cout << "\t[3] Total Balances.\n";
	cout << "\t[4] Main Menu.\n";
	cout << "===========================================\n";
}

void ManageUsersMenuScreen()
{
	system("cls");
	cout << "===========================================\n";
	cout << "        Manage Users Menu Screen\n";
	cout << "===========================================\n";
	cout << "\t[1] List Users.\n";
	cout << "\t[2] Add New User.\n";
	cout << "\t[3] Delete User.\n";
	cout << "\t[4] Update User.\n";
	cout << "\t[5] Find User.\n";
	cout << "\t[6] Main Menue.\n";
	cout << "===========================================\n";
}




void ReturnMainMenuScreen()
{
	cout << "\nPress Any Key To Go Back To Main Menu...";
	system("pause>0");


}
void ReturnTransactionsMenuScreen()
{
	cout << "\nPress Any Key To Go Back To Transactions Menu...";
	system("pause>0");


}
void ReturnManageUsersMenuScreen()
{
	cout << "\nPress Any Key To Go Back To Manage Users Menu...";
	system("pause>0");


}