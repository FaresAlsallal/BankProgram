#pragma once
#include "UserServices.h"

#include "Utils.h"
#include "FileManager.h"

#include <iostream>

using namespace std;

void AddUser(vector <StUser>& Users)
{

	do {

		StUser Data = ReadUserDataToAdd(Users);

		Users.push_back(Data);


	} while (AddAnotherUser());
}
StUser FindUser(const vector <StUser>& Users, string UserName)
{
	StUser UserFound;
	for (const StUser& User : Users)
	{
		if (User.UserName == UserName)
		{
			UserFound = User;
			return UserFound;
		}

	}
	return StUser{};
}
void DeleteUser(vector <StUser>& Users)
{
	string Username = ReadUesrName();
	if (IsUserExisting(Username, Users))
	{
		StUser UserFound = FindUser(Users, Username);
		PrintUserRecord(UserFound);
		if (ConfirmOperation("Delete", "User"))
		{
			for (int i = 0; i < Users.size(); i++)
			{
				if (Users[i].UserName == Username)
				{
					Users.erase(Users.begin() + i);
					cout << "\n\nUser Deleted Successfully.\n";
					return;
				}
			}


		}

	}
	else
		cout << "User With Username (" << Username << ") Not Found!\n";
}
void UpdateUserData(vector <StUser>& Users)
{
	string Username = ReadUesrName();
	if (IsUserExisting(Username, Users))
	{
		StUser UpdateUsertData;
		StUser UserFound = FindUser(Users, Username);
		PrintUserRecord(UserFound);
		if (ConfirmOperation("Update", "User"))
		{
			cout << endl;



			for (StUser& User : Users)
			{
				if (User.UserName == Username)
				{
					StUser Updated = ReadUserDataToUpdate();
					Updated.UserName = Username;
					User = Updated;
					cout << "\n\nClient Updated Successfully.\n";
					return;
				}
			}

		}

	}
	else
		cout << "User With Username (" << Username << ") Not Found!\n";
}

void ShowUsersList(const vector <StUser>& Users)
{
	system("cls");
	PrintUsersOfList(Users);
}
void AddUserScreen(vector <StUser>& Users)
{
	system("cls");
	cout << "\n-------------------------------------\n";
	cout << "\tAdd New Users Screen";
	cout << "\n-------------------------------------\n";
	cout << "Adding New User :\n\n";

	AddUser(Users);

}
void DeleteUserScreen(vector <StUser>& Users)
{
	system("cls");
	cout << "\n-------------------------------------\n";
	cout << "\tDelete Users Screen";
	cout << "\n-------------------------------------\n";

	DeleteUser(Users);
}
void UpdateUserScreen(vector <StUser>& Users)
{
	system("cls");
	cout << "\n-------------------------------------\n";
	cout << "\tUpdate Users Screen";
	cout << "\n-------------------------------------\n\n";

	UpdateUserData(Users);
}
void FindUserScreen(vector <StUser>& Users)
{
	system("cls");
	cout << "\n-------------------------------------\n";
	cout << "\tFind Users Screen";
	cout << "\n-------------------------------------\n\n";

	string UserName = ReadUesrName();

	StUser User = FindUser(Users, UserName);
	if (IsUserExisting(UserName, Users))
		PrintUserRecord(User);
	else
		cout << "\n\nUser With Username (" << UserName << ") Not Found!\n";

}
StUser LoginUser(const vector <StUser>& Users)
{
	StUser User = ReadUserDataToLogin();
	while (!IsUserDataValid(User, Users))
	{
		cout << "Invalid Username/Password!\n";
		User = ReadUserDataToLogin();
	}
	User = FindUser(Users, User.UserName);

	return User;
}
void LoginScreen(const vector <StUser>& Users, StUser& CurrentUser)
{
	cout << "\n-------------------------------------\n";
	cout << "\t     Login Screen";
	cout << "\n-------------------------------------\n";

	CurrentUser = LoginUser(Users);
}
