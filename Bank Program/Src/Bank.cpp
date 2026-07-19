#include "Services/ClientServices.h"
#include "Services/UserServices.h"  
#include "Utils/FileManager.h"    
#include "Utils/Utils.h"           
#include "Utils/Enum.h"           
#include <iostream>
#include <vector>
#include <string>

using namespace std;

void ExecuteManageUsers(vector <StUser>& Users, const string& UsersFileName)
{
	short ManageUsersType;
	do
	{
		ManageUsersMenuScreen();
		ManageUsersType = ReadManageUsersType();
		switch (ManageUsersType)
		{
		case enManageType::enUsersList:
		{
			
			ShowUsersList(Users);
			SaveUsersToFile(UsersFileName, Users);
			ReturnManageUsersMenuScreen();
			break;
		}
		case enManageType::enAddUser:
		{
			
			AddUserScreen(Users);
			SaveUsersToFile(UsersFileName, Users);
			ReturnManageUsersMenuScreen();
			break;
		}
		case enManageType::enDeleteUser:
		{
			
			DeleteUserScreen(Users);
			SaveUsersToFile(UsersFileName, Users);
			ReturnManageUsersMenuScreen();
			break;
		}
		case enManageType::enUpdateUser:
		{
			UpdateUserData(Users);
			SaveUsersToFile(UsersFileName, Users);
			ReturnManageUsersMenuScreen();
			break;

		}
		case enManageType::enFindUser:
		{
			
			FindUserScreen(Users);
			SaveUsersToFile(UsersFileName, Users);
			ReturnManageUsersMenuScreen();
			break;
		}
		case enManageType::enBackMainMenu:
		{
			

			return;
		}
		}
	} while (ManageUsersType != enManageType::enBackMainMenu);
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
			SaveClientsToFile(FileName, Clients);
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
void ExecuteOperation(vector <StClient>& Clients, vector <StUser>& Users, const string& ClientsFileName, const string& UsersFileName)
{

	short OperationType;

	StUser CurrentUser;
	
	
	LoginScreen(Users,CurrentUser);
	do
	{
		
		MainMenuScreen();
		OperationType = ReadOperationType();
		if (CheckPermission(CurrentUser, GetPermission(OperationType)))
		{
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
				SaveClientsToFile(ClientsFileName, Clients);
				ReturnMainMenuScreen();

				break;
			}
			case enOperationType::enDelete:
			{
				system("cls");
				DeleteClientScreen(Clients);
				SaveClientsToFile(ClientsFileName, Clients);
				ReturnMainMenuScreen();
				break;
			}
			case enOperationType::enUpdate:
			{
				system("cls");
				UpdateClientScreen(Clients);
				SaveClientsToFile(ClientsFileName, Clients);
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
				ExecuteTransaction(Clients, ClientsFileName);
				SaveClientsToFile(ClientsFileName, Clients);
				break;
			}
			case enOperationType::enManageUsers:
			{
				ExecuteManageUsers(Users, UsersFileName);
				
				break;
			}
			case enOperationType::enLogout:
			{
				system("cls");
				LoginScreen(Users,CurrentUser);
			}
			}
		}
		else
		{
			NoPermission();
			ReturnMainMenuScreen();
		}

	} while (true);

}

void Start()
{

	string ClientsFileName = "ClientFile.txt";
	string UsersFileName = "Users.txt";

	vector <StClient> Clients = LoadClientDataFromFile(ClientsFileName);
	vector <StUser> Users = LoadUserDataFromFile(UsersFileName);
	ExecuteOperation(Clients,Users, ClientsFileName,UsersFileName);

}
int main()
{
	Start();
} 