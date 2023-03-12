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
    //delete all users in the vector userList
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
        
        vector<string> userInfo; //will store name, email, etc of user as each line of the file is read in
        vector<string> movies; //will store all movies watched by individual user as each line of file is read in
        int numOfMovies = 0;
        
        while(userDataFile)
        {
            getline (userDataFile, line);
            
            if(line != "")
            {
                //if it is time to read in movie ids user has watched
                if(numOfMovies > 0)
                    movies.push_back(line);
                //if current line has num of movies user has watched
                else if(userInfo.size() == 2)
                    numOfMovies = stoi(line);
                //current line has user name or email
                else
                    userInfo.push_back(line);
            }
            else
            {
                //create new user object with info from file
                User* newUser = new User(userInfo[0], userInfo[1], movies);
                
                //add user to the email map and to the vector of all User objects
                emailMap.insert(userInfo[1], newUser);
                userList.push_back(newUser);
                
                //reset variables for next user
                userInfo.clear();
                movies.clear();
                numOfMovies = 0;
            }
        }
        
        //if file didn't end with empty line so we still need to add the final user
        if(userInfo.size() != 0)
        {
            User* newUser = new User(userInfo[0], userInfo[1], movies);
            
            emailMap.insert(userInfo[1], newUser);
            userList.push_back(newUser);
            
            userInfo.clear();
            movies.clear();
            numOfMovies = 0;
        }
        
        isLoaded = true;
        return true;
    }
    
    return false;
}

User* UserDatabase::get_user_from_email(const string& email) const
{
    //if email is not found
    if(!emailMap.find(email).is_valid())
        return nullptr;
    return emailMap.find(email).get_value();
}
