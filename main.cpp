#include <iostream>
#include <vector>
using namespace std;


class Set
{
    public:
        vector<pair<string, int>> arraySet[100];
        string genre;
        string name;
        int startYear;
        int endYear;

    public:
        void insert(string genre, string name, int year);
        bool search(string genre, string name, int startYear, int endYear);
};

void Set::insert(string genre, string name, int year)
{
    //find the hash of the value
    //reduce the hash to get an index
    int asciiValue = 0;

    for(int i = 0; i < genre.size(); i++){
        int letterToInt = (int)genre[i];
        asciiValue = asciiValue + letterToInt;
    }
    asciiValue = asciiValue % 100;

    //insert the name and year of the movie into its corresponding genre
    if(genre == "\\N"){
        arraySet[0].push_back(make_pair(name, year));
    }
    else {
        arraySet[asciiValue].push_back(make_pair(name, year));
    }

}

bool Set::search(string genre, string name, int startYear, int endYear)
{
    //find the hash of the value and the corresponding index
    int hashValue = 0;

    for(int i = 0; i < genre.size(); i++){
        int letterToInt = (int)genre[i];
        hashValue = hashValue + letterToInt;
    }
    hashValue = hashValue % 100;

    //print out the matching movie title/genre/year of the genre chosen if it is in the range of inputted years
    if(genre != "\\N") {
        for (auto itr = arraySet[hashValue].begin(); itr != arraySet[hashValue].end(); itr++) {
            if (itr->second >= startYear && itr->second <= endYear) {
                cout << "Name of the movie: " << name << " Genre: " << genre << " Year: " << itr->second << endl;
            }

        }
    }
    if(genre == "\\N"){
        for (auto itr = arraySet[0].begin(); itr != arraySet[0].end(); itr++) {
            if (itr->second >= startYear && itr->second <= endYear) {
                cout << "Name of the movie: " << name << " Genre: " << genre << " Year: " << itr->second << endl;
            }

        }
    }


}


