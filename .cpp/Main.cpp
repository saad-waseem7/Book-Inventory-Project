#include "Class.h"
#include "Library.h"
#include "Function.h"

int main()
{
    Library library;
    Member members[100];
    int numMembers = 0;
    int choice = 0;
    while (choice != 7)
    {
        cout << "\n==========================================" << endl;
        cout << "|\t                              \t |" << endl;
        cout << "|\t\"Library Management System\" \t |" << endl;
        cout << "|\t                              \t |" << endl;
        cout << "==========================================" << endl;
        cout << "|\t1. Add a book              \t |" << endl;
        cout << "|\t2. Remove a book           \t |" << endl;
        cout << "|\t3. Search for a book       \t |" << endl;
        cout << "|\t4. Display available books \t |" << endl;
        cout << "|\t5. Checkout a book         \t |" << endl;
        cout << "|\t6. Manage Members          \t |" << endl;
        cout << "|\t7. Exit                    \t |" << endl;
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
            if (!(choice == 1 || choice == 2 || choice == 3 || choice == 4 || choice == 5 || choice == 6 || choice == 7))
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
            addBook(library);
            system("cls");
            cout << ">>>Book Added to Library" << endl;
            break;

        case 2:
            system("cls");
            removeBook(library);
            break;
        case 3:
            system("cls");
            searchBook(library);
            break;
        case 4:
            system("cls");
            cout << ">>>Available books in the library are following :" << endl;
            library.displayAvailableBooks();
            break;
        case 5:
            system("cls");
            checkoutBook(library);
            break;
        case 6:
            system("cls");
            cout << "\n>>>Loading Member Management Menu...Please Wait...\n";
            cout << endl;
            Sleep(2000);
            system("cls");
            manageMembers(members, numMembers);
            break;
        case 7:
            system("cls");
            cout << "\n>>>Exiting the program..." << endl;
            break;
        default:
            cout << "Invalid choice. Please enter a number between 1 and 7." << endl;
            break;
        }
        cout << endl;
    }
    return 0;
}
