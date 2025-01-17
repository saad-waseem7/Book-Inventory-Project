import mysql.connector
from mysql.connector import Error


# Create a connection to the MySQL database
def create_connection():
    try:
        connection = mysql.connector.connect(
            host="localhost",
            database="BookStore",
            user="root",  # Replace with your MySQL username
            password="",  # Replace with your MySQL password
        )
        if connection.is_connected():
            print("Connected to MySQL database")
        return connection
    except Error as e:
        print(f"Error: '{e}'")
        return None


# Close the database connection
def close_connection(connection):
    if connection and connection.is_connected():
        connection.close()
        print("MySQL connection is closed")


# Book Management (Admin)
def add_book(connection, title, author, genre, price, stock):
    cursor = connection.cursor()
    try:
        query = "INSERT INTO Books (title, author, genre, price, stock) VALUES (%s, %s, %s, %s, %s)"
        cursor.execute(query, (title, author, genre, price, stock))
        connection.commit()
        print(f"Book '{title}' added successfully.")
    except Error as e:
        print(f"Error: '{e}'")
    finally:
        cursor.close()


def update_book(
    connection, book_id, title=None, author=None, genre=None, price=None, stock=None
):
    cursor = connection.cursor()
    updates = []
    values = []

    if title:
        updates.append("title = %s")
        values.append(title)
    if author:
        updates.append("author = %s")
        values.append(author)
    if genre:
        updates.append("genre = %s")
        values.append(genre)
    if price is not None:
        updates.append("price = %s")
        values.append(price)
    if stock is not None:
        updates.append("stock = %s")
        values.append(stock)

    if updates:
        values.append(book_id)
        query = f"UPDATE Books SET {', '.join(updates)} WHERE book_id = %s"
        try:
            cursor.execute(query, values)
            connection.commit()
            print(f"Book ID {book_id} updated successfully.")
        except Error as e:
            print(f"Error: '{e}'")
    else:
        print("No updates provided.")

    cursor.close()


def delete_book(connection, book_id):
    cursor = connection.cursor()
    try:
        query = "DELETE FROM Books WHERE book_id = %s"
        cursor.execute(query, (book_id,))
        connection.commit()
        print(f"Book ID {book_id} deleted successfully.")
    except Error as e:
        print(f"Error: '{e}'")
    finally:
        cursor.close()


def view_books(connection):
    cursor = connection.cursor()
    try:
        query = "SELECT * FROM Books"
        cursor.execute(query)
        books = cursor.fetchall()

        print("\nBook Inventory:")
        for book in books:
            print(
                f"ID: {book[0]}, Title: {book[1]}, Author: {book[2]}, Genre: {book[3]}, Price: {book[4]:.2f}, Stock: {book[5]}"
            )
    except Error as e:
        print(f"Error: '{e}'")
    finally:
        cursor.close()
    print("\n")


# Customer Management
def register_customer(connection, name, email, password):
    cursor = connection.cursor()
    try:
        query = "INSERT INTO Customers (name, email, password) VALUES (%s, %s, %s)"
        cursor.execute(query, (name, email, password))
        connection.commit()
        print(f"Customer '{name}' registered successfully.")
    except Error as e:
        print(f"Error: '{e}'")
    finally:
        cursor.close()


def login_customer(connection, email, password):
    cursor = connection.cursor()
    try:
        query = "SELECT * FROM Customers WHERE email = %s AND password = %s"
        cursor.execute(query, (email, password))
        customer = cursor.fetchone()

        if customer:
            print(f"Welcome back, {customer[1]}!")
            return customer[0]  # Returning customer_id
        else:
            print("Invalid email or password.")
            return None
    except Error as e:
        print(f"Error: '{e}'")
        return None
    finally:
        cursor.close()


# Order Management
def place_order(connection, customer_id, book_id, quantity):
    cursor = connection.cursor()
    try:
        # Check if the book is in stock
        cursor.execute("SELECT stock, price FROM Books WHERE book_id = %s", (book_id,))
        book = cursor.fetchone()

        if book and book[0] >= quantity:
            total_price = quantity * book[1]

            # Add order to Orders table
            query = "INSERT INTO Orders (customer_id, book_id, quantity) VALUES (%s, %s, %s)"
            cursor.execute(query, (customer_id, book_id, quantity))

            # Update the stock
            cursor.execute(
                "UPDATE Books SET stock = stock - %s WHERE book_id = %s",
                (quantity, book_id),
            )
            connection.commit()

            print(f"Order placed successfully! Total price: ${total_price:.2f}")
        else:
            print("Sorry, the book is out of stock.")
    except Error as e:
        print(f"Error: '{e}'")
    finally:
        cursor.close()


def view_order_history(connection, customer_id):
    cursor = connection.cursor()
    try:
        query = """
            SELECT Orders.order_id, Books.title, Orders.quantity, Orders.order_date, Orders.status
            FROM Orders
            JOIN Books ON Orders.book_id = Books.book_id
            WHERE Orders.customer_id = %s
            ORDER BY Orders.order_date DESC
        """
        cursor.execute(query, (customer_id,))
        orders = cursor.fetchall()

        print("\nOrder History:")
        for order in orders:
            print(
                f"Order ID: {order[0]}, Title: {order[1]}, Quantity: {order[2]}, Date: {order[3]}, Status: {order[4]}"
            )
    except Error as e:
        print(f"Error: '{e}'")
    finally:
        cursor.close()
    print("\n")


# Admin credentials (for simplicity, hardcoded)
ADMIN_USERNAME = "admin"
ADMIN_PASSWORD = "pass"


# Admin Login
def admin_login():
    print("\nAdmin Login")
    username = input("Enter Admin Username: ")
    password = input("Enter Admin Password: ")

    if username == ADMIN_USERNAME and password == ADMIN_PASSWORD:
        print("Admin login successful!")
        return True
    else:
        print("Invalid Admin credentials.")
        return False


# Main Menu Function
def main_menu():
    while True:
        print("\nMain Menu")
        print("1. Admin Login")
        print("2. User Login")
        print("3. Exit")

        choice = input("Choose an option: ")

        if choice == "1":
            if admin_login():
                admin_menu()
        elif choice == "2":
            user_menu()
        elif choice == "3":
            confirm_exit = input("Are you sure you want to exit? (y/n): ")
            if confirm_exit.lower() == "y":
                print("Exiting the system.")
                break
        else:
            print("Invalid choice, please try again.")


# Admin Menu
def admin_menu():
    connection = create_connection()
    if not connection:
        return

    while True:
        print("\nAdmin Menu")
        print("1. Add Book")
        print("2. Update Book")
        print("3. Delete Book")
        print("4. View Books")
        print("5. Logout")

        choice = input("Choose an option: ")

        if choice == "1":
            title = input("Enter book title: ")
            author = input("Enter book author: ")
            genre = input("Enter book genre: ")
            price = float(input("Enter book price: "))
            stock = int(input("Enter book stock: "))
            add_book(connection, title, author, genre, price, stock)
        elif choice == "2":
            book_id = int(input("Enter book ID: "))
            title = input("Enter new title (leave blank to skip): ") or None
            author = input("Enter new author (leave blank to skip): ") or None
            genre = input("Enter new genre (leave blank to skip): ") or None
            price_input = input("Enter new price (leave blank to skip): ")
            price = float(price_input) if price_input else None
            stock_input = input("Enter new stock (leave blank to skip): ")
            stock = int(stock_input) if stock_input else None
            update_book(connection, book_id, title, author, genre, price, stock)
        elif choice == "3":
            book_id = int(input("Enter book ID to delete: "))
            delete_book(connection, book_id)
        elif choice == "4":
            view_books(connection)
        elif choice == "5":
            close_connection(connection)
            break
        else:
            print("Invalid option, try again.")


# User Menu
def user_menu():
    connection = create_connection()
    if not connection:
        return

    customer_id = None

    while True:
        print("\nUser Menu")
        print("1. Register")
        print("2. Login")
        print("3. View Books")
        print("4. Place Order")
        print("5. View Order History")
        print("6. Logout")

        choice = input("Choose an option: ")

        if choice == "1":
            name = input("Enter name: ")
            email = input("Enter email: ")
            password = input("Enter password: ")
            register_customer(connection, name, email, password)
        elif choice == "2":
            email = input("Enter email: ")
            password = input("Enter password: ")
            customer_id = login_customer(connection, email, password)
        elif choice == "3":
            view_books(connection)
        elif choice == "4":
            if customer_id:
                book_id = int(input("Enter book ID: "))
                quantity = int(input("Enter quantity: "))
                place_order(connection, customer_id, book_id, quantity)
            else:
                print("Please login first.")
        elif choice == "5":
            if customer_id:
                view_order_history(connection, customer_id)
            else:
                print("Please login first.")
        elif choice == "6":
            close_connection(connection)
            break
        else:
            print("Invalid option, try again.")


if __name__ == "__main__":
    main_menu()
