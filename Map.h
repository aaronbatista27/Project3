#include <string>
#include <vector>

#pragma once

using namespace std;

class Node
{
public:
    string first;
    pair<string, int> second;

    int height;
    int balance;
    Node* left;
    Node* right;

    Node(string title, pair<string, int>);
    ~Node();
};

class Map
{
private:
    Node* insertHelper(Node* node, string title, pair<string, int> second);
    void findMoviesHelper(Node* node, string genre);
    void findYearsHelper(Node* node, string genre, int startYear, int endYear);
    void heightUpdater(Node* node);
    Node* rotateLeft(Node* node);
    Node* rotateRight(Node* node);

    Node* root;
    int count = 0;

public:
    void insert(string title, pair<string, int> second);
    void findMovies(string genre);
    void findYears(string genre, int startYear, int endYear);
    Map() : root() {}
};
