

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <sstream>
#include <limits>

using namespace std;
struct StClient
{
	string AccountNumber, Name, Phone, PinCode;
	double AccountBalance = 0;
};
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
StClient ConvertLineDataToRecord(string Text)
{
	StClient Client;
	const string Delim = "#//#";
	vector <string> Data = SplitWords(Text, Delim);

	int I = 0;
	if (Data.size() < 5)
		return Client;

	Client.AccountNumber = Data[I++];

	Client.PinCode = Data[I++];

	Client.Name = Data[I++];

	Client.Phone = Data[I++];

	try {
		Client.AccountBalance = stod(Data[I++]);
	}
	catch (...) {
		Client.AccountBalance = 0;
	}


	return Client;
}
string ConvertRecordToLine(const StClient& Client)
{
	ostringstream out;

	const string Delim = "#//#";
	out << Client.AccountNumber + Delim
		<< Client.PinCode + Delim
		<< Client.Name + Delim
		<< Client.Phone + Delim
		<< fixed << setprecision(2) << (Client.AccountBalance);


	return out.str();
}
vector <StClient> LoadClientDataFromFile(const string& FileName)
{
	vector <StClient> ClientsData;
	fstream ClientsFile;

	ClientsFile.open(FileName, ios::in);

	if (ClientsFile.is_open())
	{
		string Line;
		StClient Client;

		while (getline(ClientsFile, Line))
		{
			Client = ConvertLineDataToRecord(Line);
			if (!Client.AccountNumber.empty())
				ClientsData.push_back(Client);

		}
		ClientsFile.close();
	}
	return ClientsData;

}
void LoadDataToFile(string FileName, string Data)
{
	fstream ClientsFile;

	ClientsFile.open(FileName, ios::out | ios::app);

	if (ClientsFile.is_open())
	{
		ClientsFile << Data << endl;
		ClientsFile.close();
	}
}
bool IsClientExisting(string AccountNumber, const vector <StClient>& Clients)
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
short ReadValidOperationNum()
{
	short Number;

	while (true)
	{
		cout << "Choose What Do You Want To Do [1 - 6] ? ";
		cin >> Number;

		if (!cin.fail() && Number >= 1 && Number <= 6)
		{

			return Number;
		}
		else
		{

			cout << "\nIncorrect Answer, Please Choose (1 To 6)!!\n";

			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}

	}
}
string ReadAccountNumber()
{
	string AccountNumber;

	cout << "Please Enter Account Number ? ";
	getline(cin >> ws, AccountNumber);

	return AccountNumber;
}
StClient ReadClientDataToAdd(const string& FileName, const vector <StClient>& Clients)
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
StClient ReadClientDataToUpdate(const string& FileName)
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
short ReadOperationType()
{
	return ReadValidOperationNum();
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
void PrintClientsRecordOfLines(const vector <StClient>& Clients)
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
enum enOperationType { Show = 1, Add = 2, Delete = 3, Update = 4, Find = 5, Exit = 6 };
bool ConfirmOperation(string OperationType)
{
	char Awnser;


	while (true)
	{
		cout << "\n\nAre You sure You Want " << OperationType << " This Client (Y/N) : ";
		cin >> Awnser;

		Awnser = toupper(Awnser);
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		if (Awnser == 'Y')
			return true;
		else if (Awnser == 'N')
			return false;
		else
		{
			cout << "Invalid Awnser Please Answer with (Y/N)\n";

		}
	}
}
bool AddAnotherClient()
{
	char YesNo;
	cout << "\nClient Add Successfully, Do You Want To Add More Clients (Y/N) ?\n";
	cin >> YesNo;

	if (YesNo == 'Y' || YesNo == 'y')
		return true;
	else if (YesNo == 'N' || YesNo == 'n')
		return false;
	else
	{
		cout << "\nIncorrect, Answer With (Y/N).\n";
		return AddAnotherClient();
	}
}
StClient FindClient(const vector <StClient>& Clients, string AccountNumber)
{
	StClient ClientFound;
	for (const StClient& Client : Clients)
	{
		if (Client.AccountNumber == AccountNumber)
		{
			ClientFound = Client;
			return ClientFound;
		}

	}
	return StClient{};
}
void AddClient(const string& FileName)
{
	vector <StClient> Clients = LoadClientDataFromFile(FileName);
	do {



		StClient StData = ReadClientDataToAdd(FileName, Clients);

		string Data = ConvertRecordToLine(StData);


		LoadDataToFile(FileName, Data);

	} while (AddAnotherClient());
}
void DeleteClient(const string& FileName)
{
	vector <StClient> Clients = LoadClientDataFromFile(FileName);
	string AccountNumber = ReadAccountNumber();
	if (IsClientExisting(AccountNumber, Clients))
	{
		StClient ClientFound = FindClient(Clients, AccountNumber);
		PrintClientRecord(ClientFound);
		if (ConfirmOperation("Delete"))
		{
			fstream ClientsFile;

			ClientsFile.open(FileName, ios::out);
			if (ClientsFile.is_open())
			{
				for (const StClient& Client : Clients)
				{
					if (Client.AccountNumber != AccountNumber)
						ClientsFile << ConvertRecordToLine(Client) << endl;

				}
				ClientsFile.close();
				cout << "\n\nClient Deleted Successfully.\n";
			}
		}

	}
	else
		cout << "Client With Account Number (" << AccountNumber << ") Not Found!\n";
}
void UpdateClientData(const string& FileName)
{
	vector <StClient> Clients = LoadClientDataFromFile(FileName);
	string AccountNumber = ReadAccountNumber();
	if (IsClientExisting(AccountNumber, Clients))
	{
		StClient UpdateClientData;
		StClient ClientFound = FindClient(Clients, AccountNumber);
		PrintClientRecord(ClientFound);
		if (ConfirmOperation("Update"))
		{
			fstream ClientsFile;
			cout << endl;
			ClientsFile.open(FileName, ios::out);
			if (ClientsFile.is_open())
			{
				for (const StClient& Client : Clients)
				{
					if (Client.AccountNumber == AccountNumber)
					{


						UpdateClientData = ReadClientDataToUpdate(FileName);
						UpdateClientData.AccountNumber = AccountNumber;
						ClientsFile << ConvertRecordToLine(UpdateClientData) << endl;
					}
					else
						ClientsFile << ConvertRecordToLine(Client) << endl;

				}
				ClientsFile.close();
				cout << "\n\nClient Updated Successfully.\n";
			}
		}

	}
	else
		cout << "Client With Account Number (" << AccountNumber << ") Not Found!\n";
}
void ShowClientsScreen(const string& FileName)
{
	vector <StClient> Clients = LoadClientDataFromFile(FileName);
	PrintClientsRecordOfLines(Clients);
}
void AddClientScreen(const string& FileName)
{
	cout << "\n-------------------------------------\n";
	cout << "\tAdd New Clients Screen";
	cout << "\n-------------------------------------\n";
	cout << "Adding New Client :\n\n";

	AddClient(FileName);


}
void DeleteClientScreen(const string& FileName)
{
	cout << "\n-------------------------------------\n";
	cout << "\tDelete Clients Screen";
	cout << "\n-------------------------------------\n";
	DeleteClient(FileName);
}
void UpdateClientScreen(const string& FileName)
{
	cout << "\n-------------------------------------\n";
	cout << "\tUpdate Clients Screen";
	cout << "\n-------------------------------------\n\n";
	UpdateClientData(FileName);
}
void FindClientScreen(const string& FileName)
{
	cout << "\n-------------------------------------\n";
	cout << "\tFind Clients Screen";
	cout << "\n-------------------------------------\n\n";
	vector <StClient>Clients = LoadClientDataFromFile(FileName);
	string  AccountNumber = ReadAccountNumber();
	StClient Client = FindClient(Clients, AccountNumber);
	if (IsClientExisting(AccountNumber, Clients))
		PrintClientRecord(Client);
	else
		cout << "\n\nClient With Account Number (" << AccountNumber << ") Not Found!\n";
}
void ExitScreen()
{
	cout << "\n-------------------------------------\n";
	cout << "\tProgram End :-)";
	cout << "\n-------------------------------------\n\n";
}
void MainMenueScreen()
{
	system("cls");
	cout << "===========================================\n";
	cout << "            Main Menue Screen\n";
	cout << "===========================================\n";
	cout << "\t[1] Show Clients List.\n";
	cout << "\t[2] Add New Client.\n";
	cout << "\t[3] Delete Client.\n";
	cout << "\t[4] Update Client Info.\n";
	cout << "\t[5] Find Client.\n";
	cout << "\t[6] Exit.\n";
	cout << "===========================================\n";

}
void ReturnMainMenueScreen()
{
	cout << "Press Any Key To Go Back To Main Menu...";
	system("pause>0");


}
void ExecuteOperation(enOperationType OperationType, string FileName)
{

	switch (OperationType)
	{
	case enOperationType::Show:
	{
		system("cls");
		ShowClientsScreen(FileName);
		ReturnMainMenueScreen();
		break;
	}
	case enOperationType::Add:
	{
		system("cls");
		AddClientScreen(FileName);
		ReturnMainMenueScreen();
		break;
	}
	case enOperationType::Delete:
	{
		system("cls");
		DeleteClientScreen(FileName);
		ReturnMainMenueScreen();
		break;
	}
	case enOperationType::Update:
	{
		system("cls");
		UpdateClientScreen(FileName);
		ReturnMainMenueScreen();
		break;
	}
	case enOperationType::Find:
	{
		system("cls");
		FindClientScreen(FileName);
		ReturnMainMenueScreen();
		break;
	}
	case enOperationType::Exit:
	{
		system("cls");
		ExitScreen();
		break;
	}
	}

}
void Start()
{

	string FileName = "ClientFile.txt";
	short OperationType;
	do
	{
		MainMenueScreen();
		OperationType = ReadOperationType();
		ExecuteOperation((enOperationType)OperationType, FileName);
	} while (OperationType != 6);


}
int main()
{
	Start();
	system("pause>0");
}