#include "MovieDatabase.h"
#include "Movie.h"

#include <iostream>
#include <fstream>
#include <cstring>

#include <string>
#include <vector>
using namespace std;

#include "treemm.h"

MovieDatabase::MovieDatabase()
{
    isLoaded = false;
}

MovieDatabase::~MovieDatabase()
{
    //delete all movies in the vector movieList
    vector<Movie*>::iterator it = movieList.begin();
    while(it != movieList.end())
    {
        delete *it;
        it = movieList.erase(it);
    }
}

bool MovieDatabase::load(const string& filename)
{
    //if hasn't been loaded before
    if(!isLoaded)
    {
        ifstream movieDataFile(filename);
        string line;
        
        if(!movieDataFile)
        {
            cerr << "Cannot find file" << endl;
            return false;
        }
        
        vector<string> movieInfo; //will store id, name, etc of movie as each line of the file is read in
        float rating = -1;
        
        while(movieDataFile)
        {
            getline (movieDataFile, line);
            
            if(line != "")
            {
                //if current line has the rating
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
                
                //create new movie pointer with information from file
                Movie* newMovie = new Movie(movieInfo[0], movieInfo[1], movieInfo[2], directors, actors, genres, rating);
                
                //insert new movie into all of the maps
                idMap.insert(toLower(movieInfo[0]), newMovie);
                
                for(int i = 0; i < directors.size(); i++)
                    directorMap.insert(toLower(directors[i]), newMovie);
                for(int i = 0; i < actors.size(); i++)
                    actorMap.insert(toLower(actors[i]), newMovie);
                for(int i = 0; i < genres.size(); i++)
                    genreMap.insert(toLower(genres[i]), newMovie);
                
                //add new movie to the vector that stores all the movies
                movieList.push_back(newMovie);
                
                //reset variables for next movie
                movieInfo.clear();
                rating = -1;
            }
        }
        
        //if file didn't end with empty line so we still need to add the final movie
        if(movieInfo.size() != 0)
        {
            vector<string> directors = getVectorFromString(movieInfo[3]);
            vector<string> actors = getVectorFromString(movieInfo[4]);
            vector<string> genres = getVectorFromString(movieInfo[5]);
            Movie* newMovie = new Movie(movieInfo[0], movieInfo[1], movieInfo[2], directors, actors, genres, rating);
            
            idMap.insert(toLower(movieInfo[0]), newMovie);
            
            for(int i = 0; i < directors.size(); i++)
                directorMap.insert(toLower(directors[i]), newMovie);
            for(int i = 0; i < actors.size(); i++)
                actorMap.insert(toLower(actors[i]), newMovie);
            for(int i = 0; i < genres.size(); i++)
                genreMap.insert(toLower(genres[i]), newMovie);
            
            movieList.push_back(newMovie);
            
            movieInfo.clear();
            rating = -1;
        }
        
        isLoaded = true;
        return true;
    }
    
    return false;
}

Movie* MovieDatabase::get_movie_from_id(const string& id) const
{
    //if id is not found
    if(!idMap.find(toLower(id)).is_valid())
        return nullptr;
    return idMap.find(toLower(id)).get_value();
}

vector<Movie*> MovieDatabase::get_movies_with_director(const string& director) const
{
    //if director is not found
    if(!directorMap.find(toLower(director)).is_valid())
        return vector<Movie*>();
    vector<Movie*> movies;
    
    TreeMultimap<string, Movie*>::Iterator it = directorMap.find(toLower(director));
    
    //add all of the movies stored under this director to the vector
    while(it.is_valid())
    {
        movies.push_back(it.get_value());
        it.advance();
    }
    return movies;
}

vector<Movie*> MovieDatabase::get_movies_with_actor(const string& actor) const
{
    //if actor is not found
    if(!actorMap.find(toLower(actor)).is_valid())
        return vector<Movie*>();
    vector<Movie*> movies;
    
    TreeMultimap<string, Movie*>::Iterator it = actorMap.find(toLower(actor));
    
    //add all of the movies stored under this actor to the vector
    while(it.is_valid())
    {
        movies.push_back(it.get_value());
        it.advance();
    }
    return movies;
}

vector<Movie*> MovieDatabase::get_movies_with_genre(const string& genre) const
{
    //if genre is not found
    if(!genreMap.find(toLower(genre)).is_valid())
        return vector<Movie*>();
    vector<Movie*> movies;
    
    TreeMultimap<string, Movie*>::Iterator it = genreMap.find(toLower(genre));
    
    //add all of the movies stored under this genre to the vector
    while(it.is_valid())
    {
        movies.push_back(it.get_value());
        it.advance();
    }
    return movies;
}

//takes in a string with format name,name,.... and returns a vector of strings with each individual name
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

//returns the lowercase version of the word passed in
string MovieDatabase::toLower(const string& word) const
{
    string lowerWord;
    for(int i = 0; i < word.size(); i++)
    {
        lowerWord += tolower(word[i]);
    }
    return lowerWord;
}
