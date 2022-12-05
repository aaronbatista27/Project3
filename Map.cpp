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

// most of insertion for map is from Project 2: AVL. with permission from Professor Aman
Node* Map::insertHelper(Node *node, string title, pair<string, int> second)
{
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

pair<string, int> Map::operator[](string title)
{
    return searchTitle(this->root, title);
}

pair<string, int> Map::searchTitle(Node *node, string title)
{
    //
    if (node == nullptr)
    {
        this->count++;
    }

    //if new ufid < than current node's, travel down left branch
    if (title < node->first)
    {
        return searchTitle(node->left, title);
    }

    //if new ufid > than current node's, travel down right branch
    else if (title > node->first)
    {
        return searchTitle(node->right, title);
    }

    // if new title == current node, return pair
    else if (title == node->first)
    {
        return node->second;
    }
}

void Map::findMovies(string genre)
{
    int counter = 0;
    findMoviesHelper(this->root, genre, counter);
}

void Map::findMoviesHelper(Node *node, string genre, int &counter)
{
    if (node == nullptr)
    {
        cout << "";
    }
    else
    {
        if (genre == node->second.first)
        {
            cout << node->first << endl;
        }

        findMoviesHelper(node->left, genre, counter);
        findMoviesHelper(node->right, genre, counter);
    }
}