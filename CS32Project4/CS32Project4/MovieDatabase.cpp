#include "MovieDatabase.h"
#include "Movie.h"

#include <iostream>
#include <fstream>
#include <cstring>

#include <string>
#include <vector>
using namespace std;

//#include "treemm.h"

MovieDatabase::MovieDatabase()
{
    isLoaded = false;
}

bool MovieDatabase::load(const string& filename)
{
    if(!isLoaded)
    {
        ifstream movieDataFile(filename);
        string line;
        
        if(!movieDataFile)
        {
            cerr << "Cannot find file" << endl;
            return false;
        }
        
        vector<string> movieInfo;
        float rating = -1;
        
        while(movieDataFile)
        {
            getline (movieDataFile, line);
            if(line != "")
            {
                if(movieInfo.size() == 6)
                    rating = stof(line);
                else
                    movieInfo.push_back(line);
            }
            else
            {
                vector<string> directors = getVectorFromString(movieInfo[3]);
                vector<string> actors = getVectorFromString(movieInfo[4]);
                vector<string> genres = getVectorFromString(movieInfo[5]);
                Movie* newMovie = new Movie(toLower(movieInfo[0]), toLower(movieInfo[1]), movieInfo[2], directors, actors, genres, rating);
                
                idMap.insert(toLower(movieInfo[0]), newMovie);
                
                for(int i = 0; i < directors.size(); i++)
                    directorMap.insert(toLower(directors[i]), newMovie);
                for(int i = 0; i < actors.size(); i++)
                    actorMap.insert(toLower(actors[i]), newMovie);
                for(int i = 0; i < genres.size(); i++)
                    genreMap.insert(toLower(genres[i]), newMovie);
                
                movieInfo.clear();
                rating = -1;
            }
        }
        isLoaded = true;
        return true;
    }
    
    return false;  // Replace this line with correct code.
}

Movie* MovieDatabase::get_movie_from_id(const string& id) const
{
    if(!idMap.find(id).is_valid())
        return nullptr;
    return idMap.find(id).get_value();
}

vector<Movie*> MovieDatabase::get_movies_with_director(const string& director) const
{
    return vector<Movie*>();  // Replace this line with correct code.
}

vector<Movie*> MovieDatabase::get_movies_with_actor(const string& actor) const
{
    return vector<Movie*>();  // Replace this line with correct code.
}

vector<Movie*> MovieDatabase::get_movies_with_genre(const string& genre) const
{
    return vector<Movie*>();  // Replace this line with correct code.
}

vector<string> MovieDatabase::getVectorFromString(const string& stringList) const
{
    vector<string> list;
    string word;
    for(int i = 0; i < stringList.size(); i++)
    {
        if(stringList[i] == ',')
        {
            list.push_back(toLower(word));
            word = "";
        }
        else
            word += stringList[i];
    }
    if(word != "")
        list.push_back(word);
    
    return list;
}

string MovieDatabase::toLower(const string& word) const
{
    string lowerWord;
    for(int i = 0; i < word.size(); i++)
    {
        lowerWord += tolower(word[i]);
    }
    return lowerWord;
}
