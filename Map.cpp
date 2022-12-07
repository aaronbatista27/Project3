#include "Map.h"
#include <iostream>
#include <string>
#include <queue>

using namespace std;

Node::Node(string title, pair<string, int> second)
{
    this->first = title;
    this->second = second;
    this->height = 1;
    this->balance = 0;
    this->left = nullptr;
    this->right = nullptr;
}

Node::~Node()
{

}

void Map::insert(string title, pair<string, int> second)
{
    this->root = insertHelper(this->root, title, second);
}

// insertHelper cited from Aaron Batista's AVL Project implementation
// usage of Project 2 code permitted by Professor Aman
Node* Map::insertHelper(Node *node, string title, pair<string, int> second)
{
    //lines 33-56 get logic from slide 28 of Module 4 - Balanced Trees
    
    // if at bottom of tree, insert
    if (node == nullptr)
    {
        this->count++;
        return new Node(title, second);
    }

    // if new title ASCII < current node title ASCII, go down left
    if (title < node->first)
    {
        node->left = insertHelper(node->left, title, second);
    }

    // if new title ASCII > current node title ASCII, go down right
    else if (title > node->first)
    {
        node->right = insertHelper(node->right, title, second);
    }

    // if new title == current node title, do not insert
    else if (title == node->first)
    {
        return node;
    }

    //update heights/balances after insertion
    heightUpdater(node);

    // check for non-balanced nodes
    if (node->balance > 1)
    {
        //left-left scenario
        if (node->left->balance == 1)
        {
            node = rotateRight(node);
        }
        //left-right scenario
        else if (node->left->balance == -1)
        {
            node->left = rotateLeft(node->left);
            node = rotateRight(node);
        }
    }
    else if (node->balance < -1)
    {
        //right-left scenario
        if (node->right->balance == 1)
        {
            node->right = rotateRight(node->right);
            node = rotateLeft(node);
        }
        //right-right scenario
        else if (node->right->balance == -1)
        {
            node = rotateLeft(node);
        }
    }

    return node;
}

// heightUpdater from Aaron Batista's AVL Project
void Map::heightUpdater(Node *node)
{
    // no children
    if ((node->left == nullptr) && (node->right == nullptr))
    {
        node->height = 1;
        node->balance = 0;
    }

    // if only left child
    else if (node->right == nullptr)
    {
        node->height = node->left->height + 1;
        node->balance = node->left->height;
    }

    //if only right child
    else if (node->left == nullptr)
    {
        node->height = node->right->height + 1;
        node->balance = 0 - node->right->height;
    }

    //two children: left height > right height
    else if ((node->left->height) > (node->right->height))
    {
        node->height = node->left->height + 1;
        node->balance = node->left->height - node->right->height;
    }

    //two children: left height < right height
    else if (node->left->height <= node->right->height)
    {
        node->height = node->right->height + 1;
        node->balance = node->left->height - node->right->height;
    }
}

//cited from slide 12 in Module 4 - Balanced Trees
Node* Map::rotateLeft(Node *node)
{
    Node* grandchild = node->right->left;
    Node* newParent = node->right;
    newParent->left = node;
    node->right = grandchild;

    //update heights of nodes after rotation
    heightUpdater(node);
    heightUpdater(newParent);

    return newParent;
}

//cited from slide 12 in Module 4 - Balanced Trees
Node* Map::rotateRight(Node *node)
{
    Node* grandchild = node->left->right;
    Node* newParent = node->left;
    newParent->right = node;
    node->left = grandchild;

    //update heights of nodes after rotation
    heightUpdater(node);
    heightUpdater(newParent);

    return newParent;
}

// for search by genre only
void Map::findMovies(string genre)
{
    findMoviesHelper(this->root, genre);
}

void Map::findMoviesHelper(Node *node, string genre)
{
    if (node == nullptr)
    {
        cout << "";
    }
    else
    {
        int ASCIIone = 0;
        int ASCIItwo = 0;

        // convert genres to ASCII, compare values
        for (int i = 0; i < genre.size(); ++i)
        {
            ASCIIone += (int)toupper(genre.at(i));
        }

        for (int j = 0; j < node->second.first.size(); ++j)
        {
            ASCIItwo += (int)toupper(node->second.first.at(j));
        }

        // if a match, print
        if (ASCIIone == ASCIItwo)
        {
            //cout << node->first << endl;
        }

        findMoviesHelper(node->left, genre);
        findMoviesHelper(node->right, genre);
    }
}

// for search by genre + year range
void Map::findYears(string genre, int startYear, int endYear)
{
    findYearsHelper(this->root, genre, startYear, endYear);
}

void Map::findYearsHelper(Node *node, string genre, int startYear, int endYear)
{
    if (node == nullptr)
    {
        cout << "";
    }
    else
    {
        int ASCIIone = 0;
        int ASCIItwo = 0;

        for (int i = 0; i < genre.size(); ++i)
        {
            ASCIIone += (int)toupper(genre.at(i));
        }

        for (int j = 0; j < node->second.first.size(); ++j)
        {
            ASCIItwo += (int)toupper(node->second.first.at(j));
        }

        if (ASCIIone == ASCIItwo)
        {
            int compare = node->second.second;
            
            // check if year fits in year range
            if ((startYear <= compare) && (endYear >= compare))
            {
                //cout << node->first << ", " << node->second.second << endl;
            }
        }

        findYearsHelper(node->left, genre, startYear, endYear);
        findYearsHelper(node->right, genre, startYear, endYear);
    }
}
