#pragma once

#include <vector>
#include <string>

#include "User.h"
#include "Enum.h"

using namespace std;


// User Operations
void AddUser(vector<StUser>& Users);

void DeleteUser(vector<StUser>& Users);

void UpdateUserData(vector<StUser>& Users);


// Search
StUser FindUser(
    const vector<StUser>& Users,
    string UserName
);

bool IsUserExisting(
    const string& UserName,
    const vector<StUser>& Users
);


// Display
void ShowUsersList(
    const vector<StUser>& Users
);


// Screens
void AddUserScreen(
    vector<StUser>& Users
);

void DeleteUserScreen(
    vector<StUser>& Users
);

void UpdateUserScreen(
    vector<StUser>& Users
);

void FindUserScreen(
    vector<StUser>& Users
);


// Login
StUser LoginUser(
    const vector<StUser>& Users
);

void LoginScreen(
    const vector<StUser>& Users,
    StUser& CurrentUser
);