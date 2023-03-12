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
    std::vector<Movie*> movieList;
    
    TreeMultimap<std::string, Movie*> directorMap;
    TreeMultimap<std::string, Movie*> actorMap;
    TreeMultimap<std::string, Movie*> genreMap;
    
    TreeMultimap<std::string, Movie*> idMap;
    
    bool isLoaded;
    std::vector<std::string> getVectorFromString(const std::string& stringList) const;
    
    std::string toLower(const std::string& word) const;
};

#endif // MOVIEDATABASE_INCLUDED
