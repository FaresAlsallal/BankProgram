#pragma once

#include <vector>
#include <string>

#include "Client.h"
#include "User.h"

using namespace std;


// Convert Client Data
StClient ConvertLineDataToRecord(string Text);

string ConvertRecordToLine(
    const StClient& Client
);


// Convert User Data
StUser ConvertLineUserDataToRecord(string Text);

string ConvertUserRecordToLine(
    const StUser& User
);


// Load Data
vector<StClient> LoadClientDataFromFile(
    const string& FileName
);

vector<StUser> LoadUserDataFromFile(
    const string& FileName
);


// Save Data
void SaveClientsToFile(
    const string& FileName,
    const vector<StClient>& Clients
);

void SaveUsersToFile(
    const string& FileName,
    const vector<StUser>& Users
);


// Add Data To File
void LoadDataToFile(
    const string& FileName,
    const string& Data
);

void LoadUserDataToFile(
    const string& FileName,
    const string& Data
);