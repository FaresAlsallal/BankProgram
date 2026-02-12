

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
void LoadDataToFile(const string &FileName, const string &Data)
{
	fstream ClientsFile;

	ClientsFile.open(FileName, ios::out | ios::app);

	if (ClientsFile.is_open())
	{
		ClientsFile << Data << endl;
		ClientsFile.close();
	}
}
void SaveClientsToFile(const string& FileName, const vector<StClient>& Clients)
{
	fstream File;
	File.open(FileName, ios::out);

	if (File.is_open())
	{
		for (const StClient& Client : Clients)
		{
			File << ConvertRecordToLine(Client) << endl;
		}
		File.close();
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
short ReadValidOperationNum(short NumberOfOperations)
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
string ReadAccountNumber()
{
	string AccountNumber;

	cout << "Please Enter Account Number ? ";
	getline(cin >> ws, AccountNumber);

	return AccountNumber;
}
StClient ReadClientDataToAdd( const vector <StClient>& Clients)
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
short ReadOperationType()
{
	return ReadValidOperationNum(7);
}
short ReadTransactionType()
{
	return ReadValidOperationNum(4);
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
enum enOperationType { enShow = 1, enAdd = 2, enDelete = 3, enUpdate = 4, enFind = 5, enTransactions = 6, enExit = 7 };
enum enTransactionsType { enDeposit = 1, enWithdraw = 2, enShowBalances = 3, enMainMenu = 4 };

bool ConfirmOperation(string OperationType)
{
	char Answer;


	while (true)
	{
		cout << "\n\nAre You sure You Want " << OperationType << " This Client (Y/N) : ";
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
void AddClient(vector <StClient>& Clients)
{

	do {



		StClient StData = ReadClientDataToAdd( Clients);

		Clients.push_back(StData);


		

	} while (AddAnotherClient());
}
void DeleteClient(vector <StClient> &Clients)
{
	string AccountNumber = ReadAccountNumber();
	if (IsClientExisting(AccountNumber, Clients))
	{
		StClient ClientFound = FindClient(Clients, AccountNumber);
		PrintClientRecord(ClientFound);
		if (ConfirmOperation("Delete"))
		{
			for (int i = 0; i < Clients.size(); i++)
			{
				if (Clients[i].AccountNumber == AccountNumber)
				{
					Clients.erase(Clients.begin() + i);
					cout << "\n\nClient Deleted Successfully.\n";
					return;
				}
			}

					
		}

	}
	else
		cout << "Client With Account Number (" << AccountNumber << ") Not Found!\n";
}
void UpdateClientData(vector <StClient> &Clients)
{
	string AccountNumber = ReadAccountNumber();
	if (IsClientExisting(AccountNumber, Clients))
	{
		StClient UpdateClientData;
		StClient ClientFound = FindClient(Clients, AccountNumber);
		PrintClientRecord(ClientFound);
		if (ConfirmOperation("Update"))
		{
			cout << endl;
			
		
			
			for (StClient& Client : Clients)
			{
				if (Client.AccountNumber == AccountNumber)
				{
					StClient Updated = ReadClientDataToUpdate();
					Updated.AccountNumber = AccountNumber;
					Client = Updated;
					cout << "\n\nClient Updated Successfully.\n";
					return;
				}
			}

		}

	}
	else
		cout << "Client With Account Number (" << AccountNumber << ") Not Found!\n";
}

void Deposit(vector <StClient> &Clients,const short &Maximum)
{
	
	double DepositAmount;
	string AccountNumber = ReadAccountNumber();
	if (IsClientExisting(AccountNumber, Clients))
	{

		
		StClient ClientFound = FindClient(Clients, AccountNumber);
		PrintClientRecord(ClientFound);


		

		
			for ( StClient& Client : Clients)
			{
				if (Client.AccountNumber == AccountNumber)
				{
					bool Loop = true;
					while (Loop)
					{
						cout << "Please Enter Deposit Amount? ";
						cin >> DepositAmount;
						if (DepositAmount<=Maximum)
						{
						
							if (ConfirmTransaction())
							{
								Client.AccountBalance += DepositAmount;
                              cout << "\n\nDone Successfully, New Balance Is : " << Client.AccountBalance << endl;
                              Loop = false;
							}
							
							
						}
						else
						{
							cout << "Maximum Deposit Per Transaction Is  " << Maximum <<" Please Choose The Correct Amount!!"<< endl;
						}
					}
				}
				
					

			}
			
			
		
	}
	else
		cout << "Client With Account Number (" << AccountNumber << ") Not Found!\n";

}
void Withdraw(vector <StClient> &Clients,const short &Maximum)
{
	double WithdrawAmount;

	string AccountNumber = ReadAccountNumber();
	if (IsClientExisting(AccountNumber, Clients))
	{
		StClient ClientFound = FindClient(Clients, AccountNumber);
		PrintClientRecord(ClientFound);

			for ( StClient& Client : Clients)
			{
				if (Client.AccountNumber == AccountNumber)
				{
					bool Loop=true;
					while (Loop)
					{
						cout << "Please Enter Withdraw Amount? ";
						cin >> WithdrawAmount;
						if (WithdrawAmount <= Maximum)
						{
							if (Client.AccountBalance >= WithdrawAmount)
							{
						
								if (ConfirmTransaction())
								{
									Client.AccountBalance -= WithdrawAmount;
									cout << "\n\nDone Successfully, New Balance Is : " << Client.AccountBalance << endl;
                                     Loop = false;
								}
								
								
							}
							else
							{
								cout << "Amount Exceeds The Balance , You Can Withdraw Up To : " << Client.AccountBalance << endl;
							}
						}
						else
						{
							cout << "Maximum Withdraw Per Transaction Is  " << Maximum << " Please Choose The Correct Amount!!" << endl;

						}
					} 
				}
				

			}
			
		
		
	}
	else
		cout << "Client With Account Number (" << AccountNumber << ") Not Found!\n";
	


}

void ShowClientsList(vector <StClient> &Clients)
{
	
	PrintClientsOfList(Clients);
}
void ShowBalancesList(vector <StClient>& Clients)
{
	PrintBalancesOfList(Clients);
	cout << "\t\t\t\t   Total Balances = " << TotalBalances(Clients)<<"\n\n";
}
void AddClientScreen(vector <StClient>& Clients)
{
	cout << "\n-------------------------------------\n";
	cout << "\tAdd New Clients Screen";
	cout << "\n-------------------------------------\n";
	cout << "Adding New Client :\n\n";

	AddClient(Clients);


}
void DeleteClientScreen(vector <StClient>& Clients)
{
	cout << "\n-------------------------------------\n";
	cout << "\tDelete Clients Screen";
	cout << "\n-------------------------------------\n";
	DeleteClient(Clients);
}
void UpdateClientScreen(vector <StClient>& Clients)
{
	cout << "\n-------------------------------------\n";
	cout << "\tUpdate Clients Screen";
	cout << "\n-------------------------------------\n\n";
	UpdateClientData(Clients);
}
void FindClientScreen(vector <StClient>& Clients)
{
	cout << "\n-------------------------------------\n";
	cout << "\tFind Clients Screen";
	cout << "\n-------------------------------------\n\n";
	
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
system("pause>0");
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
	cout << "\t[6] Transactions.\n";
	cout << "\t[7] Exit.\n";
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


void DepositScreen(vector <StClient>& Clients)
{
	cout << "\n-------------------------------------\n";
	cout << "\tDeposit Screen";
	cout << "\n-------------------------------------\n\n";
	Deposit(Clients,10000);
}
void WithdrawScreen(vector <StClient>& Clients)
{
	cout << "\n-------------------------------------\n";
	cout << "\tWithdraw Screen";
	cout << "\n-------------------------------------\n\n";
	Withdraw(Clients,3000);
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


void ExecuteTransaction(vector <StClient>& Clients, const string& FileName)
{
	short TransactionType;
	do
	{
		TransactionsMenuScreen();
		TransactionType = ReadTransactionType();
		switch (TransactionType)
		{
		case enTransactionsType::enDeposit:
		{
			system("cls");
			DepositScreen(Clients);
			SaveClientsToFile(FileName,Clients);
			ReturnTransactionsMenuScreen();

			break;
		}
		case enTransactionsType::enWithdraw:
		{
			system("cls");
			WithdrawScreen(Clients);
			SaveClientsToFile(FileName, Clients);
			ReturnTransactionsMenuScreen();

			break;
		}
		case enTransactionsType::enShowBalances:
		{
			system("cls");
			ShowBalancesList(Clients);
			ReturnTransactionsMenuScreen();

			break;
		}
		case enTransactionsType::enMainMenu:
		{

			 return;
		
		}
		}
	} while (TransactionType != enTransactionsType::enMainMenu);
}
void ExecuteOperation(vector <StClient> &Clients , const string& FileName)
{
	
	short OperationType;

	
		
	
	do 
	{

		MainMenuScreen();
           OperationType = ReadOperationType();
		
			switch (OperationType)
			{
			case enOperationType::enShow:
			{
				system("cls");
				ShowClientsList(Clients);
				ReturnMainMenuScreen();
				break;
			}
			case enOperationType::enAdd:
			{
				system("cls");
				AddClientScreen(Clients);
                SaveClientsToFile(FileName, Clients);
				ReturnMainMenuScreen();
				
				break;
			}
			case enOperationType::enDelete:
			{
				system("cls");
				DeleteClientScreen(Clients);
				SaveClientsToFile(FileName, Clients);
				ReturnMainMenuScreen();
				break;
			}
			case enOperationType::enUpdate:
			{
				system("cls");
				UpdateClientScreen(Clients);
				SaveClientsToFile(FileName, Clients);
				ReturnMainMenuScreen();
				break;
			}
			case enOperationType::enFind:
			{
				system("cls");
				FindClientScreen(Clients);
				ReturnMainMenuScreen();
				break;
			}
			case enOperationType::enTransactions:
			{
				ExecuteTransaction(Clients,FileName);
				SaveClientsToFile(FileName, Clients);
				break;
			}
			case enOperationType::enExit:
			{
				system("cls");
				 ExitScreen();
				 return;
			}
			}

	}while(OperationType != enOperationType::enExit);

}

void Start()
{

	string FileName = "ClientFile.txt";
	vector <StClient> Clients = LoadClientDataFromFile(FileName);
	ExecuteOperation(Clients,FileName);

	

}
int main()
{

	Start();
	
}