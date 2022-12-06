#include <iostream>
#include <vector>

#pragma once
using namespace std;


class Set
{
private:
    vector<pair<string, int>> hashSet[1000];
    string genre;
    string name;
    int startYear;
    int endYear;

public:
    void insert(string genre, string name, int year);

    //bool search(string genre, string name, int startYear, int endYear);
    void search(string genre, int startYear, int endYear);
};

void Set::insert(string genre, string name, int year)
{
    //find the hash of the value
    //reduce the hash to get an index
    int asciiValue = 0;

    for(int i = 0; i < genre.size(); i++){
        int letterToInt = (int)toupper(genre[i]);
        asciiValue = asciiValue + letterToInt;
    }
    asciiValue = asciiValue % 1000;

    //insert the name and year of the movie into its corresponding genre
    /*
    if(genre == "\\N"){
        arraySet[0].push_back(make_pair(name, year));
    }
    else {
        arraySet[asciiValue].push_back(make_pair(name, year));
    }
    */
    hashSet[asciiValue].emplace_back(make_pair(name, year));
}

/*
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
        for (auto itr = hashSet[hashValue].begin(); itr != hashSet[hashValue].end(); itr++) {
            if (itr->second >= startYear && itr->second <= endYear) {
                cout << "Name of the movie: " << name << " Genre: " << genre << " Year: " << itr->second << endl;
            }

        }
    }
    if(genre == "\\N"){
        for (auto itr = hashSet[0].begin(); itr != hashSet[0].end(); itr++) {
            if (itr->second >= startYear && itr->second <= endYear) {
                cout << "Name of the movie: " << name << " Genre: " << genre << " Year: " << itr->second << endl;
            }

        }
    }


}

*/

void Set::search(string genre, int startYear, int endYear)
{
    if (endYear == -1)
    {
        //find the hash of the value and the corresponding index
        int hashValue = 0;

        for (int i = 0; i < genre.size(); i++) {
            int letterToInt = (int) toupper(genre[i]);
            hashValue = hashValue + letterToInt;
        }
        hashValue = hashValue % 1000;

        /*
        //print out the matching movie title/genre/year of the genre chosen if it is in the range of inputted years
        for (auto itr = hashSet[hashValue].begin(); itr != hashSet[hashValue].end(); itr++) {
            if (itr->second >= startYear && itr->second <= endYear) {
                cout << name << " Genre: " << genre << " Year: " << itr->second << endl;
            }

        }
         */
        for (int i = 0; i < hashSet[hashValue].size(); ++i)
        {
            cout << hashSet[hashValue].at(i).first << ", " << hashSet[hashValue].at(i).second << endl;
        }
    }
    else
    {
        int hashValue = 0;

        for (int i = 0; i < genre.size(); i++) {
            int letterToInt = (int) toupper(genre[i]);
            hashValue = hashValue + letterToInt;
        }
        hashValue = hashValue % 1000;

        for (int i = 0; i < hashSet[hashValue].size(); ++i)
        {
            if ((startYear <= hashSet[hashValue].at(i).second) && (endYear >= hashSet[hashValue].at(i).second))
            {
                cout << hashSet[hashValue].at(i).first << ", " << hashSet[hashValue].at(i).second << endl;
            }
        }
    }
}