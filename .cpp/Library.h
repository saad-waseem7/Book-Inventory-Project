#pragma once
#include "Class.h"

// >>>All Classes Member Functions Definitions...

// Book Class Functions Definitions...

Book::Book()
{
    this->availability = true;
    this->quantity = 0;
}

void Book::SetTitle(const string &title)
{
    this->title = title;
}
void Book::SetAuthor(const string &author)
{
    this->author = author;
}
void Book::SetPublisher(const string &publisher)
{
    this->publisher = publisher;
}
void Book::SetIsbn(const string &ISBN)
{
    this->ISBN = ISBN;
}
void Book::SetAvailability(bool availability)
{
    this->availability = availability;
}
void Book::SetQuantity(int quantity)
{
    this->quantity = quantity;
}
const string &Book::GetTitle() const
{
    return this->title;
}
const string &Book::GetAuthor() const
{
    return this->author;
}
const string &Book::GetIsbn() const
{
    return this->ISBN;
}
const string &Book::GetPublisher() const
{
    return this->publisher;
}
bool Book::GetAvailability() const
{
    return this->availability;
}

int Book::GetQuantity() const
{
    return this->quantity;
}
void Book::DisplayBookDetails() const
{
    cout << "Title: " << this->title << endl;
    cout << "Author: " << this->author << endl;
    cout << "Publisher: " << this->publisher << endl;
    cout << "ISBN: " << this->ISBN << endl;
    cout << "Quantity: " << this->quantity << endl;
    if (availability)
    {
        cout << "The book is available" << endl;
    }
    if (!availability)
    {
        cout << "The book is not available" << endl;
    }
    cout << "The quantity available is " << this->quantity << endl;
}
Book::~Book()
{
    // cout << "The book is deleted" << endl;
}

// Book Class Functions End Here...

// Member Class Functions Definitions...

Member::Member()
{
    this->id = 0;
    this->name = "";
    for (int i = 0; i < 5; i++)
    {
        this->booksCheckedOut[i] = nullptr;
    }
    // cout << "The member is created" << endl;
}

Member::Member(const string &name, int id)
{
    this->name = name;
    this->id = id;
    for (int i = 0; i < 5; ++i)
    {
        *(booksCheckedOut + i) = nullptr;
    }
}

void Member::setName(const string &name)
{
    this->name = name;
}

string Member::getName() const
{
    return this->name;
}

void Member::setId(int id)
{
    this->id = id;
}

int Member::getId() const
{
    return this->id;
}

bool Member::checkOutBook(Book *book)
{
    for (int i = 0; i < 5; ++i)
    {
        if ((*(booksCheckedOut + i)) == nullptr)
        {
            *(booksCheckedOut + i) = book;
            int currentQuantity = book->GetQuantity();
            if (currentQuantity > 0)
            {
                book->SetQuantity(currentQuantity - 1);
            }
            book->SetAvailability(false);
            return true;
        }
    }
    return false;
}

bool Member::returnBook(Book *book)
{
    for (int i = 0; i < 5; ++i)
    {
        if ((*(booksCheckedOut + i)) == book)
        {
            *(booksCheckedOut + i) = nullptr;
            int currentQuantity = book->GetQuantity();
            book->SetQuantity(currentQuantity + 1);
            book->SetAvailability(true);
        }
    }
    return false;
}

void Member::displayCheckedOutBooks() const
{
    cout << "Books checked out by " << name << " (ID: " << id << "):\n";
    for (int i = 0; i < 5; ++i)
    {
        if ((*(booksCheckedOut + i)) != nullptr)
        {
            cout << "Title: " << (*(booksCheckedOut + i))->GetTitle();
            cout << ", Author: " << (*(booksCheckedOut + i))->GetAuthor();
            cout << ", ISBN: " << (*(booksCheckedOut + i))->GetIsbn();
            cout << ", Publisher: " << (*(booksCheckedOut + i))->GetPublisher() << endl;
        }
    }
}

Member::~Member()
{
    // cout << "The member is deleted" << endl;
    for (int i = 0; i < 5; ++i)
    {
        *(booksCheckedOut + i) = nullptr;
    }
}

// Member Class Functions End Here...

// Library Class Functions Definitions...

Library::Library()
{
    this->numBooks = 0;
    this->Quantity = 0;
}

void Library::AddBook(const Book &book)
{
    if (numBooks < MAX)
    {
        books[numBooks] = book;
        numBooks++;
    }
    else
    {
        cout << "Library is full. Cannot add more books." << endl;
    }
}

void Library::RemoveBook(const string &isbn)
{
    int i = 0;
    bool found = false;
    while (i < numBooks)
    {
        if (books[i].GetIsbn() == isbn)
        {
            found = true;
            break;
        }
        i++;
    }

    if (found)
    {

        for (int j = i; j < numBooks - 1; ++j)
        {
            books[j] = books[j + 1];
        }
        numBooks--;
        cout << "Book with ISBN " << isbn << " removed from the library." << endl;
    }
    else
    {
        cout << "Book with ISBN " << isbn << " not found in the library." << endl;
    }
}

void Library::SearchBook(const string &keyword) const
{
    bool found = false;
    int i = 0;
    while (i < numBooks)
    {
        const Book &book = books[i];
        if (book.GetIsbn() == keyword || book.GetAuthor() == keyword || book.GetTitle() == keyword)
        {
            book.DisplayBookDetails();
            found = true;
        }
        i++;
    }
    if (!found)
    {
        cout << "No results found." << endl;
    }
}
const Book &Library::getBook(int index) const
{
    return books[index];
}
int Library::getNumBooks() const
{
    return this->numBooks;
}

void Library::displayAvailableBooks() const
{
    bool found = false;
    int i = 0;
    while (i < numBooks)
    {
        const Book &book = books[i];
        if (book.GetAvailability())
        {
            book.DisplayBookDetails();
            found = true;
        }
        i++;
    }

    if (!found)
    {
        cout << "No available books in the library" << endl;
    }
}

Library::~Library()
{
    // cout << "The library is deleted" << endl;
}
