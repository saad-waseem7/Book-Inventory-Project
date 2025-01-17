#pragma once
#include "Library.h"
#include "Class.h"

// >>>Other Utility Functions Prototypes...

void addBook(Library &library);
void removeBook(Library &library);
void searchBook(Library &library);
void checkoutBook(Library &library);
void addMember(Member members[], int &numMembers);
void removeMember(Member members[], int &numMembers, int memberId);
void searchMember(const Member members[], int numMembers, int memberId);
void manageMembers(Member members[], int &numMembers);

// >>>Functions Definitions...

void addBook(Library &library)
{
    cout << "Enter book details:" << endl;
    Book book;
    string title, author, publisher, isbn;
    int quantity;

    cout << "Enter Title: ";
    while (true)
    {
        getline(cin, title);
        bool valid = true;
        for (char c : title)
        {
            if (!isalpha(c) && !isspace(c))
            {
                valid = false;
                break;
            }
        }
        if (!title.empty() && valid)
        {
            book.SetTitle(title);
            break;
        }
        // cout << "Error: Title must contain alphabetic characters only." << endl;
    }

    cout << "Enter Author: ";
    while (true)
    {
        getline(cin, author);
        bool valid = true;
        for (char c : author)
        {
            if (!isalpha(c) && !isspace(c))
            {
                valid = false;
                break;
            }
        }
        if (!author.empty() && valid)
        {
            book.SetAuthor(author);
            break;
        }
        cout << "Error: Author must contain alphabetic characters only." << endl;
    }

    cout << "Enter Publisher: ";
    while (true)
    {
        getline(cin, publisher);
        bool valid = true;
        for (char c : publisher)
        {
            if (!isalpha(c) && !isspace(c))
            {
                valid = false;
                break;
            }
        }
        if (!publisher.empty() && valid)
        {
            book.SetPublisher(publisher);
            break;
        }
        cout << "Error: Publisher must contain alphabetic characters only." << endl;
    }

    cout << "Enter ISBN: ";
    while (true)
    {
        getline(cin, isbn);
        bool valid = true;
        for (char c : isbn)
        {
            if (!isdigit(c))
            {
                valid = false;
                break;
            }
        }
        if (!isbn.empty() && valid)
        {
            book.SetIsbn(isbn);
            break;
        }
        cout << "Error: ISBN must contain numeric characters only." << endl;
    }

    cout << "Enter the quantity of the books to add: ";
    while (true)
    {
        cin >> quantity;
        if (quantity > 0 && quantity < 1000)
        {
            break;
        }
        cout << "Error: Quantity must be a positive integer." << endl;
        cin.clear();
        cin.ignore();
    }
    book.SetQuantity(quantity);

    library.AddBook(book);
}

void removeBook(Library &library)
{
    string isbn;
    cout << "Enter ISBN of the book to remove from library: ";
    while (true)
    {
        cin >> isbn;
        bool isValid = true;
        for (char c : isbn)
        {
            if (!isdigit(c))
            {
                isValid = false;
                break;
            }
        }
        if (!isbn.empty() && isValid)
        {
            break;
        }
        cout << "Error: ISBN must contain numeric characters only. Please enter again: ";
        cin.clear();
        cin.ignore();
    }

    int index = -1;
    for (int i = 0; i < library.getNumBooks(); ++i)
    {
        if (library.getBook(i).GetIsbn() == isbn)
        {
            index = i;
            break;
        }
    }

    if (index != -1)
    {
        Book &bookToRemove = const_cast<Book &>(library.getBook(index));

        int currentQuantity = bookToRemove.GetQuantity();
        if (currentQuantity > 1)
        {
            bookToRemove.SetQuantity(currentQuantity - 1);
        }
        else
        {
            library.RemoveBook(isbn);
        }
    }
    else
    {
        cout << "Book with ISBN " << isbn << " not found in the library." << endl;
    }
}

void searchBook(Library &library)
{
    string keyword;
    cout << "Enter keyword (Title, Author, ISBN, Publisher) to search: ";

    cin.ignore();

    while (true)
    {
        getline(cin, keyword);

        if (!keyword.empty())
        {
            break;
        }
        cout << "Error: Keyword cannot be empty. Please enter again: ";
    }

    library.SearchBook(keyword);
}

void checkoutBook(Library &library)
{
    int memberId;

    cout << "Enter your member ID: ";
    while (true)
    {
        cin >> memberId;
        if (memberId > 0 && memberId < 99999)
        {
            break;
        }
        else
        {
            cout << "Error: Invalid member ID. Please enter a positive integer." << endl;
            cin.clear();
            cin.ignore();
        }
    }

    string isbn;
    // cout << "Enter ISBN of the book to remove from library: ";
    cout << "Enter ISBN of the book to checkout from library: ";
    while (true)
    {
        cin >> isbn;
        bool isValid = true;
        for (char c : isbn)
        {
            if (!isdigit(c))
            {
                isValid = false;
                break;
            }
        }
        if (!isbn.empty() && isValid)
        {
            break;
        }
        cout << "Error: ISBN must contain numeric characters only. Please enter again: ";
        cin.clear();
        cin.ignore();
    }

    int index = -1;
    for (int i = 0; i < library.getNumBooks(); ++i)
    {
        if (library.getBook(i).GetIsbn() == isbn)
        {
            index = i;
            break;
        }
    }

    if (index != -1)
    {
        Book &bookToRemove = const_cast<Book &>(library.getBook(index));

        int currentQuantity = bookToRemove.GetQuantity();
        if (currentQuantity > 1)
        {
            bookToRemove.SetQuantity(currentQuantity - 1);
        }
        else
        {
            library.RemoveBook(isbn);
            cout << "Book with ISBN " << isbn << " checked out from library." << endl;
        }
    }
    else
    {
        cout << "Book with ISBN " << isbn << " not found in the library." << endl;
    }
}

void addMember(Member members[], int &numMembers)
{
    if (numMembers >= 100)
    {
        cout << "Maximum number of members reached. Cannot add more members." << endl;
        return;
    }

    int memberId;
    string name;

    cout << "Enter your member ID: ";
    while (true)
    {
        cin >> memberId;
        if (memberId > 0 && memberId < 99999)
        {
            break;
        }
        else
        {
            cout << "Error: Invalid member ID. Please enter a positive integer." << endl;
            cin.clear();
            cin.ignore();
        }
    }

    while (true)
    {
        cout << "Enter name of Member: ";
        cin >> name;
        bool valid = true;
        for (char c : name)
        {
            if (!isalpha(c))
            {
                valid = false;
                break;
            }
        }
        if (!name.empty() && valid)
        {
            break;
        }
        cout << "Error: Name must contain alphabetic characters only. Please enter again: ";
    }

    members[numMembers] = Member(name, memberId);
    numMembers++;

    cout << "Member added successfully." << endl;
}

void removeMember(Member members[], int &numMembers, int memberId)
{
    int index = -1;
    for (int i = 0; i < numMembers; ++i)
    {
        if (members[i].getId() == memberId)
        {
            index = i;
            break;
        }
    }

    if (index != -1)
    {
        for (int i = index; i < numMembers - 1; ++i)
        {
            members[i] = members[i + 1];
        }
        numMembers--;
        cout << "Member with ID " << memberId << " removed successfully." << endl;
    }
    else
    {
        cout << "Member with ID " << memberId << " not found." << endl;
    }
}

void searchMember(const Member members[], int numMembers, int memberId)
{
    bool found = false;
    for (int i = 0; i < numMembers; ++i)
    {
        if (members[i].getId() == memberId)
        {
            cout << "Member found:" << endl;
            cout << "Name: " << members[i].getName() << endl;
            cout << "ID: " << members[i].getId() << endl;
            found = true;
            break;
        }
    }

    if (!found)
    {
        cout << "Member with ID " << memberId << " not found." << endl;
    }
}

void manageMembers(Member members[], int &numMembers)
{
    int choice = 0;
    while (choice != 4)
    {
        cout << "\n==========================================" << endl;
        cout << "|\t                              \t |" << endl;
        cout << "|\t      \"Manage Members\"      \t |" << endl;
        cout << "|\t                              \t |" << endl;
        cout << "==========================================" << endl;
        cout << "|\t1. Add a member            \t |" << endl;
        cout << "|\t2. Remove a member         \t |" << endl;
        cout << "|\t3. Search for a member     \t |" << endl;
        cout << "|\t4. Back to Main Menu       \t |" << endl;
        cout << "==========================================" << endl;
        string input;
        bool inputIsValid;

        do
        {
            cout << "\nEnter your choice: ";
            cin >> input;

            inputIsValid = true;

            for (char c : input)
            {
                if (!isdigit(c))
                {
                    inputIsValid = false;
                    break;
                }
            }

            if (!inputIsValid)
            {
                cout << "Error: Please enter a numeric value.\n";
            }
            else
            {

                choice = stoi(input);
            }
        } while (!inputIsValid);

        while (true)
        {
            if (!(choice == 1 || choice == 2 || choice == 3 || choice == 4))
            {
                cout << "Error: Invalid choice. Please enter again: ";
                cin >> choice;
            }
            else
            {
                break;
            }
        }

        cout << endl;

        switch (choice)
        {
        case 1:
            system("cls");
            addMember(members, numMembers);
            break;
        case 2:
            system("cls");
            int memberIdToRemove;
            cout << "Enter the ID of the member to remove: ";
            while (true)
            {
                cin >> memberIdToRemove;
                if (cin.good() && (memberIdToRemove > 99999 && memberIdToRemove < 0))
                {
                    break;
                }
                cout << "Error: Invalid input. Please enter a valid member ID: ";
                cin.clear();
                cin.ignore();
            }
            removeMember(members, numMembers, memberIdToRemove);
            break;
        case 3:
            system("cls");
            int memberIdToSearch;
            cout << "Enter the ID of the member to search: ";

            while ((!(cin >> memberIdToSearch)) || (memberIdToSearch > 99999 && memberIdToSearch < 0))
            {
                cin.clear();
                cin.ignore();
            }
            searchMember(members, numMembers, memberIdToSearch);
            break;
        case 4:
            system("cls");
            cout << "\n>>>Returning to Main Menu...Please Wait..\n";
            cout << endl;
            Sleep(2000);
            system("cls");
            break;
        default:
            cout << "Invalid choice. Please enter a number between 1 and 4." << endl;
            break;
        }
        cout << endl;
    }
}
