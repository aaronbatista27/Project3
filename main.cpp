#include "Map.h"
#include "Hash.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <chrono>

using namespace std;
using namespace chrono;

int main()
{
    Map map;
    Set hash;

    // NOTE: the address of the read-in file must be changed per machine
    ifstream inFile("C:/Users/Aaron Batista/CLionProjects/MovieProject/newestMovieSet.csv");
    string line;

    string key;
    string value1;
    string value2;
    int year;

    // initialize mapTime and hashTime with the same value;
    auto temp1 = high_resolution_clock::now();
    auto temp2 = high_resolution_clock::now();
    auto mapTime = duration_cast<microseconds>(temp2 - temp1);
    auto hashTime = duration_cast<microseconds>(temp2 - temp1);

    //auto mapTime = duration_cast<microseconds>(0);

    while (getline(inFile, line))
    {
        istringstream stream(line);
        // get movie title
        getline(stream, key, ',');

        // get genres for movie
        getline(stream, value1, ',');

        getline(stream, value2);
        year = stoi(value2);

        // time from before and after each of these functions
        auto startMap = high_resolution_clock::now();
        map.insert(key, make_pair(value1, year));
        auto endMap = high_resolution_clock::now();
        mapTime += duration_cast<microseconds>(endMap - startMap);

        // time from before and after of each of these functions
        auto startHash = high_resolution_clock::now();
        hash.insert(value1, key, year);
        auto endHash = high_resolution_clock::now();
        hashTime += duration_cast<microseconds>(endHash - startHash);

        key.clear();
        value1.clear();
        value2.clear();
    }

    cout << "Welcome to the Movie Searcher 2000!" << endl;
    cout << "In this program, you are able to search for movies based on the genres YOU select (ain't that somethin'?)" << endl;
    cout << "You also have the option of searching for movies by year (only from 1975 onwards)" << endl;
    cout << endl;
    cout << "Now go ahead a get movie searching!" << endl;
    cout << endl;
    cout << "If you would like to search solely on genres, type 1" << endl;
    cout << "If you would like to provide a range of years as well, type 2" << endl;

    int choice;
    cin >> choice;

    if (choice == 1)
    {
        string genres;

        // only genre stuff
        cout << "Great choice!" << endl;
        cout << "Now, input up to 3 genres! We will recommend the best movies for you based on your input" << endl;
        cout << "(NOTE: only add one space between genres. For example, action comedy romance)" << endl;
        cin.ignore();
        getline(cin, genres);

        cout << "Coming right up!" << endl;

        // map doesn't print anything, still checks for timing purposes
        auto startMap = high_resolution_clock::now();
        map.findMovies(genres);
        auto endMap = high_resolution_clock::now();
        mapTime += duration_cast<microseconds>(endMap - startMap);

        // hash prints the movies
        auto startHash = high_resolution_clock::now();
        hash.search(genres, -1, -1);
        auto endHash = high_resolution_clock::now();
        hashTime += duration_cast<microseconds>(endHash - startHash);
    }

    if (choice == 2)
    {
        string genres;

        //genre + year
        cout << "GREAT choice! Just tell me what years you'd like to search between:" << endl;
        int startYear;
        int endYear;

        cout << "Starting year: ";
        cin >> startYear;
        cout << "End year: ";
        cin >> endYear;
        cout << endl;

        cout << "Now, input up to 3 genres! We will recommend the best movies for you based on your input" << endl;
        cout << "(NOTE: only add one space between genres. For example, action comedy romance)" << endl;

        cin.ignore();
        getline(cin, genres);

        cout << "Coming right up!" << endl;

        // map doesn't print anything, still checks for timing purposes
        auto startMap = high_resolution_clock::now();
        map.findYears(genres, startYear, endYear);
        auto endMap = high_resolution_clock::now();
        mapTime += duration_cast<microseconds>(endMap - startMap);

        // hash prints the movies
        auto startHash = high_resolution_clock::now();
        hash.search(genres, startYear, endYear);
        auto endHash = high_resolution_clock::now();
        hashTime += duration_cast<microseconds>(endHash - startHash);

        cout << endl;
        cout << "Hope we helped you pick your next movie!" << endl;
    }

    cout << endl;
    cout << "Map Time: " << mapTime.count() << " microseconds" << endl;
    cout << "Hash Time: " << hashTime.count() << " microseconds" << endl;

    return 0;
}
