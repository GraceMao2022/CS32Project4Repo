#include "Recommender.h"
#include "UserDatabase.h"
#include "MovieDatabase.h"
#include "User.h"
#include "Movie.h"

#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <algorithm>
using namespace std;

Recommender::Recommender(const UserDatabase& user_database,
                         const MovieDatabase& movie_database)
{
    userDB = &user_database;
    movieDB = &movie_database;
}

vector<MovieAndRank> Recommender::recommend_movies(const string& user_email, int movie_count) const
{
    //if movie count wanted is negative or zero, return empty vector
    if(movie_count <= 0)
        return vector<MovieAndRank>();
    
    User* user = userDB->get_user_from_email(user_email);
    
    //if user not found
    if(user == nullptr)
        return vector<MovieAndRank>();
    
    //get movies watched by user
    vector<string> watchedMovies = user->get_watch_history();
    
    //hash map with the movie id as the key and compatibility score as value
    unordered_map<string, int> movieScoreMap;
    
    //make an unordered_set of the names of the movies user has already watched
    unordered_set<string> watchedMovieIDs;
    
    //loop through all watchedMovies
    for(int i = 0; i < watchedMovies.size(); i++)
    {
        //add this watched movie to the set of watched movie IDs
        watchedMovieIDs.insert(watchedMovies[i]);
        
        Movie* movie = movieDB->get_movie_from_id(watchedMovies[i]);
        
        //get all the directors of this movie
        vector<string> directors = movie->get_directors();
        //loop through each director
        for(int j = 0; j < directors.size(); j++)
        {
            //get all movies directed by this director
            vector<Movie*> moviesFromDirector = movieDB->get_movies_with_director(directors[j]);
            for(int h = 0; h < moviesFromDirector.size(); h++)
            {
                //if movie is not in the hash map yet
                if(movieScoreMap.find(moviesFromDirector[h]->get_id()) == movieScoreMap.end())
                    movieScoreMap[moviesFromDirector[h]->get_id()] = 20; //add initial score of 20
                else //movie is already in hashmap
                    movieScoreMap[moviesFromDirector[h]->get_id()] += 20; //add 20 to score for this movie
            }
        }
        
        //same thing as above but for actors
        vector<string> actors = movie->get_actors();
        for(int j = 0; j < actors.size(); j++)
        {
            vector<Movie*> moviesWithActor = movieDB->get_movies_with_actor(actors[j]);
            for(int h = 0; h < moviesWithActor.size(); h++)
            {
                //if movie is not in the hash map yet
                if(movieScoreMap.find(moviesWithActor[h]->get_id()) == movieScoreMap.end())
                    movieScoreMap[moviesWithActor[h]->get_id()] = 30; //add initial score of 30
                else //movie is already in hashmap
                    movieScoreMap[moviesWithActor[h]->get_id()] += 30; //add 30 to score for this movie
            }
        }
        
        //same thing as above but for genres
        vector<string> genres = movie->get_genres();
        for(int j = 0; j < genres.size(); j++)
        {
            vector<Movie*> moviesWithGenre = movieDB->get_movies_with_genre(genres[j]);
            for(int h = 0; h < moviesWithGenre.size(); h++)
            {
                //if movie is not in the hash map yet
                if(movieScoreMap.find(moviesWithGenre[h]->get_id()) == movieScoreMap.end())
                    movieScoreMap[moviesWithGenre[h]->get_id()] = 1; //add initial score of 1
                else //movie is already in hashmap
                    movieScoreMap[moviesWithGenre[h]->get_id()] += 1; //add 1 to score for this movie
            }
        }
    }
    
    //will store all the movies with compatibility score above 1 and then will be ordered
    vector<MovieAndRank> unorderedList;
    
    //loop through hash map and add the elements to an ordered map by score
    for(auto i : movieScoreMap)
    {
        //if movie is not already watched
        if(watchedMovieIDs.find(i.first) == watchedMovieIDs.end())
            unorderedList.push_back(MovieAndRank(i.first, i.second));
    }
    
    //std sort the vector of movies
    sort(unorderedList.begin(), unorderedList.end(), [this](const MovieAndRank& lhs, const MovieAndRank& rhs)
         {
        //if movie on the left has higher score than the one on the right, this is the correct order
        if(lhs.compatibility_score > rhs.compatibility_score)
            return true;
        //if lhs score is less than rhs score, switch them
        else if(lhs.compatibility_score < rhs.compatibility_score)
            return false;
        else
        {
            Movie* lhsMovie = movieDB->get_movie_from_id(lhs.movie_id);
            Movie* rhsMovie = movieDB->get_movie_from_id(rhs.movie_id);
            
            //if lhs rating is greater than rhs rating, this is correct order
            if(lhsMovie->get_rating() > rhsMovie->get_rating())
                return true;
            //if lhs rating is less than rhs rating, switch the order
            else if(lhsMovie->get_rating() < rhsMovie->get_rating())
                return false;
            else
            {
                //if lhs movie name is before rhs movie name alphabetically, this is correct order
                if(lhsMovie->get_title() < rhsMovie->get_title())
                    return true;
                //switch the order
                else
                    return false;
            }
        }
    });
    
    //will store the top movie_count movies that are recommended to the user
    vector<MovieAndRank> rankedList;
    
    //add up to movie_score movies to the rankedList, or all movies with compatibility score of at least 1 if number of movies is less than movie_score
    int i = 0;
    vector<MovieAndRank>::iterator it = unorderedList.begin();
    while(i < movie_count && it != unorderedList.end())
    {
        rankedList.push_back(*it);
        it++;
        i++;
    }
    
    return rankedList;
}
