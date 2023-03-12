#include "UserDatabase.h"
#include "User.h"

#include <iostream>
#include <fstream>
#include <cstring>

#include <string>
#include <vector>
using namespace std;

#include "treemm.h"

UserDatabase::UserDatabase()
{
    isLoaded = false;
}

UserDatabase::~UserDatabase()
{
    vector<User*>::iterator it = userList.begin();
    while(it != userList.end())
    {
        delete *it;
        it = userList.erase(it);
    }
}

bool UserDatabase::load(const string& filename)
{
    if(!isLoaded)
    {
        ifstream userDataFile(filename);
        string line;
        
        if(!userDataFile)
        {
            cerr << "Cannot find file" << endl;
            return false;
        }
        
        vector<string> userInfo;
        vector<string> movies;
        int numOfMovies = 0;
        
        while(userDataFile)
        {
            getline (userDataFile, line);
            
            if(line != "")
            {
                if(numOfMovies > 0)
                    movies.push_back(line);
                else if(userInfo.size() == 2)
                    numOfMovies = stoi(line);
                else
                    userInfo.push_back(line);
            }
            else
            {
                User* newUser = new User(userInfo[0], userInfo[1], movies);
                
                emailMap.insert(userInfo[1], newUser);
                userList.push_back(newUser);
                
                userInfo.clear();
                movies.clear();
                numOfMovies = 0;
            }
        }
        isLoaded = true;
        return true;
    }
    
    return false;
}

User* UserDatabase::get_user_from_email(const string& email) const
{
    if(!emailMap.find(email).is_valid())
        return nullptr;
    return emailMap.find(email).get_value();
}
