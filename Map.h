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

// implementing map as an AVL tree
class Map
{
private:
    Node* insertHelper(Node* node, string title, pair<string, int> second);
    void findMoviesHelper(Node* node, string genre, int& counter);
    void heightUpdater(Node* node);
    Node* rotateLeft(Node* node);
    Node* rotateRight(Node* node);
    pair<string, int> searchTitle(Node *node, string title);

    Node* root;
    int count = 0;

public:
    void insert(string title, pair<string, int> second);
    pair<string, int> operator[](string title);
    void findMovies(string genre);
    Map() : root() {}
};
