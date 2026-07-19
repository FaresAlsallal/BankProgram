#pragma once

#include "Services/ClientServices.h"

#include "Utils/Utils.h"
#include "Utils/FileManager.h"

#include <iostream>
#include <iomanip>

using namespace std;



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



		StClient StData = ReadClientDataToAdd(Clients);

		Clients.push_back(StData);




	} while (AddAnotherClient());
}
void DeleteClient(vector <StClient>& Clients)
{
	string AccountNumber = ReadAccountNumber();
	if (IsClientExisting(AccountNumber, Clients))
	{
		StClient ClientFound = FindClient(Clients, AccountNumber);
		PrintClientRecord(ClientFound);
		if (ConfirmOperation("Delete", "Client"))
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
void UpdateClientData(vector <StClient>& Clients)
{
	string AccountNumber = ReadAccountNumber();
	if (IsClientExisting(AccountNumber, Clients))
	{
		StClient UpdateClientData;
		StClient ClientFound = FindClient(Clients, AccountNumber);
		PrintClientRecord(ClientFound);
		if (ConfirmOperation("Update", "Client"))
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

void Deposit(vector <StClient>& Clients, const short& Maximum)
{

	double DepositAmount;
	string AccountNumber = ReadAccountNumber();
	if (IsClientExisting(AccountNumber, Clients))
	{


		StClient ClientFound = FindClient(Clients, AccountNumber);
		PrintClientRecord(ClientFound);





		for (StClient& Client : Clients)
		{
			if (Client.AccountNumber == AccountNumber)
			{
				bool Loop = true;
				while (Loop)
				{
					cout << "Please Enter Deposit Amount? ";
					cin >> DepositAmount;
					if (DepositAmount <= Maximum)
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
						cout << "Maximum Deposit Per Transaction Is  " << Maximum << " Please Choose The Correct Amount!!" << endl;
					}
				}
			}



		}



	}
	else
		cout << "Client With Account Number (" << AccountNumber << ") Not Found!\n";

}
void Withdraw(vector <StClient>& Clients, const short& Maximum)
{
	double WithdrawAmount;

	string AccountNumber = ReadAccountNumber();
	if (IsClientExisting(AccountNumber, Clients))
	{
		StClient ClientFound = FindClient(Clients, AccountNumber);
		PrintClientRecord(ClientFound);

		for (StClient& Client : Clients)
		{
			if (Client.AccountNumber == AccountNumber)
			{
				bool Loop = true;
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

void ShowClientsList(vector <StClient>& Clients)
{

	PrintClientsOfList(Clients);
}
void ShowBalancesList(vector <StClient>& Clients)
{
	PrintBalancesOfList(Clients);
	cout << "\t\t\t\t   Total Balances = " << TotalBalances(Clients) << "\n\n";
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

void DepositScreen(vector <StClient>& Clients)
{
	cout << "\n-------------------------------------\n";
	cout << "\tDeposit Screen";
	cout << "\n-------------------------------------\n\n";
	Deposit(Clients, 10000);
}
void WithdrawScreen(vector <StClient>& Clients)
{
	cout << "\n-------------------------------------\n";
	cout << "\tWithdraw Screen";
	cout << "\n-------------------------------------\n\n";
	Withdraw(Clients, 3000);
}
