#ifndef MOVIEDATABASE_INCLUDED
#define MOVIEDATABASE_INCLUDED

#include <string>
#include <vector>

class Movie;
#include "treemm.h"

class MovieDatabase
{
  public:
    MovieDatabase();
    ~MovieDatabase();
    bool load(const std::string& filename);
    Movie* get_movie_from_id(const std::string& id) const;
    std::vector<Movie*> get_movies_with_director(const std::string& director) const;
    std::vector<Movie*> get_movies_with_actor(const std::string& actor) const;
    std::vector<Movie*> get_movies_with_genre(const std::string& genre) const;

  private:
    std::vector<Movie*> movieList; //stores pointers to all the Movie objects
    
    TreeMultimap<std::string, Movie*> directorMap; //tree for director map with director as key, movie pointers as values
    TreeMultimap<std::string, Movie*> actorMap; //tree for actor map with actor as key, movie pointers as values
    TreeMultimap<std::string, Movie*> genreMap; //tree for genre map with genre as key, movie pointers as values
    
    TreeMultimap<std::string, Movie*> idMap; //tree for id map with id as key, movie pointers as values
    
    bool isLoaded; //becomes true once movie database is loaded in the first time
    
    std::vector<std::string> getVectorFromString(const std::string& stringList) const;
    
    std::string toLower(const std::string& word) const;
};

#endif // MOVIEDATABASE_INCLUDED
