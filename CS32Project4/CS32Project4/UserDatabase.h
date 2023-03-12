#ifndef USERDATABASE_INCLUDED
#define USERDATABASE_INCLUDED

#include <string>
#include <vector>

class User;
#include "treemm.h"

class UserDatabase
{
  public:
    UserDatabase();
    ~UserDatabase();
    bool load(const std::string& filename);
    User* get_user_from_email(const std::string& email) const;

  private:
    std::vector<User*> userList; //stores pointers to all the User objects
    
    TreeMultimap<std::string, User*> emailMap; //tree for email map with email as key, user pointers as values
    
    bool isLoaded; //becomes true once user database is loaded in the first time
};

#endif // USERDATABASE_INCLUDED
