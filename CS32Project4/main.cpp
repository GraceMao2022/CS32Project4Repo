#include "UserDatabase.h"
#include "User.h"
#include <iostream>
#include <string>
using namespace std;


#include "treemm.h"
class Iterator;

//////////////////////////i/////////////////////////////////////////////////////
//
// You are free to do whatever you want with this file, since you won't
// be turning it in.  Presumably, you will make changes to help you test
// your classes.  For example, you might try to implement only some User
// member functions to start out with, and so replace our main routine with
// one that simply creates a User and verifies that the member functions you
// implemented work correctly.
//
//////////////////////////i/////////////////////////////////////////////////////


  // If your program is having trouble finding these files. replace the
  // string literals with full path names to the files.  Also, for test
  // purposes, you may want to create some small, simple user and movie
  // data files to makde debuggiing easier, so you can replace the string
  // literals with the names of those smaller files.

const string USER_DATAFILE  = "users.txt";
const string MOVIE_DATAFILE = "movies.txt";

int main()
{
    //TreeMultimap<int, int> tmm;
    TreeMultimap<int,int>::Iterator it;
    if (!it.is_valid()) std::cout << "This will print!\n";
    
    /*TreeMultimap<std::string, string>* tmmptr =
     new TreeMultimap<std::string, string>();
     tmmptr->insert("carey", "hi");
     tmmptr->insert("cindy", "bye");
     delete tmmptr; // TreeMultimap's destructor runs*/
    
    TreeMultimap<std::string, int> tmm;
     tmm.insert("carey", 5);
     tmm.insert("carey", 6);
    
     tmm.insert("carey", 7);
     tmm.insert("david", 25);
     tmm.insert("david", 425);
     TreeMultimap<std::string,int>::Iterator it2 = tmm.find("carey");
     // prints 5, 6, and 7 in some order
        while (it2.is_valid()) {
     std::cout << it2.get_value() << std::endl;
     it2.advance();
     }
    
    TreeMultimap<std::string,int>::Iterator it4 = tmm.find("david");
    // prints 5, 6, and 7 in some order
       while (it4.is_valid()) {
    std::cout << it4.get_value() << std::endl;
    it4.advance();
    }
     //Iterator it3 = tmm.find("laura");
     //if (!it3.is_valid())
     //std::cout << "laura is not in the multimap!\n";
	UserDatabase udb;
	if (0&&!udb.load(USER_DATAFILE))  // In skeleton, load always return false
	{
		cout << "Failed to load user data file " << USER_DATAFILE << "!" << endl;
		return 1;
	}
	for (;;)
	{
		cout << "Enter user email address (or quit): ";
		string email;
		getline(cin, email);
		if (email == "quit")
			return 0;
		User* u = udb.get_user_from_email(email);
		if (u == nullptr)
			cout << "No user in the database has that email address." << endl;
		else
			cout << "Found " << u->get_full_name() << endl;
	}
}
