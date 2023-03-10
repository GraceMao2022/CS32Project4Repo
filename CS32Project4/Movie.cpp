#include "Movie.h"

#include <string>
#include <vector>
using namespace std;

Movie::Movie(const string& id, const string& title, const string& release_year,
             const vector<string>& directors, const vector<string>& actors,
             const vector<string>& genres, float rating)
{
    this->id = id;
    this->title = title;
    releaseYear = release_year;
    this->directors = directors;
    this->actors = actors;
    this->genres = genres;
    this->rating = rating;
}

string Movie::get_id() const
{
    return id;
}

string Movie::get_title() const
{
    return title;
}

string Movie::get_release_year() const
{
    return releaseYear;
}

float Movie::get_rating() const
{
    return rating;
}

vector<string> Movie::get_directors() const
{
    return directors;
}

vector<string> Movie::get_actors() const
{
    return actors;
}

vector<string> Movie::get_genres() const
{
    return genres;
}
