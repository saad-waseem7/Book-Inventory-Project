#pragma once
#include <iostream>
#include <string>
#include <cctype>
#include <Windows.h>
using namespace std;

//Book Class Definition...

class Book
{
private:
    string title;
    string author;
    string publisher;
    string ISBN;
    bool availability;
    int quantity;

public:
    Book();
    void SetTitle(const string &title);
    void SetAuthor(const string &author);
    void SetPublisher(const string &publisher);
    void SetIsbn(const string &ISBN);
    void SetAvailability(bool availability);
    void SetQuantity(int quantity);
    const string &GetTitle() const;
    const string &GetAuthor() const;
    const string &GetIsbn() const;
    const string &GetPublisher() const;
    bool GetAvailability() const;
    int GetQuantity() const;
    void DisplayBookDetails() const;
    ~Book();
};

// Member Class Definition...

class Member
{
private:
    string name;
    int id;
    Book *booksCheckedOut[5];

public:
    Member();
    Member(const string &name, int id);
    void setName(const string &name);
    string getName() const;
    void setId(int id);
    int getId() const;
    bool checkOutBook(Book *book);
    bool returnBook(Book *book);
    void displayCheckedOutBooks() const;
    ~Member();
};


// Library Class Definition...

class Library
{
private:
    static const int MAX = 100;
    Book books[MAX];
    int numBooks;
    int Quantity;

public:
    Library();
    void AddBook(const Book &book);
    void RemoveBook(const string &isbn);
    void SearchBook(const string &keyword) const;
    const Book &getBook(int index) const;
    int getNumBooks() const;
    void displayAvailableBooks() const;
    ~Library();
};