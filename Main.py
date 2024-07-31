# Book Inventory using Python...


class Book:
    def __init__(self, book_id, title, author, price, stock):
        self.book_id = book_id
        self.title = title
        self.author = author
        self.price = price
        self.stock = stock

    def __str__(self):
        return f"{self.book_id} | {self.title} | {self.author} | ${self.price} | {self.stock}"

    def update_stock(self, quantity):
        self.stock -= quantity


class Inventory:
    def __init__(self):
        self.books = []

    def add_book(self, book):
        self.books.append(book)

    def remove_book(self, book_id):
        book = self.find_book(book_id)
        if book:
            self.books.remove(book)
            return True
        return False

    def find_book(self, book_id):
        for book in self.books:
            if book.book_id == book_id:
                return book
        return None

    def display_books(self):
        if not self.books:
            print("No books available in the inventory.")
            return
        print("\nAvailable Books:")
        print("ID | Title | Author | Price | Stock")
        for book in self.books:
            print(book)

    def search_books(self, keyword):
        results = [
            book
            for book in self.books
            if keyword.lower() in book.title.lower()
            or keyword.lower() in book.author.lower()
        ]
        return results


class Order:
    def __init__(self, book, quantity):
        self.book = book
        self.quantity = quantity
        self.total_cost = book.price * quantity


class BookStore:
    def __init__(self):
        self.inventory = Inventory()
        self.order_history = []
        self.book_id_counter = 1

    def add_book(self):
        try:
            title = input("Enter the book title: ")
            if not title:
                raise ValueError("Title cannot be empty.")
            author = input("Enter the author name: ")
            if not author:
                raise ValueError("Author cannot be empty.")
            price = float(input("Enter the price: "))
            if price <= 0:
                raise ValueError("Price must be positive.")
            stock = int(input("Enter the stock quantity: "))
            if stock < 0:
                raise ValueError("Stock cannot be negative.")
            book = Book(self.book_id_counter, title, author, price, stock)
            self.inventory.add_book(book)
            self.book_id_counter += 1
            print(f"Book '{title}' by {author} added successfully.")
        except ValueError as e:
            print(f"Invalid input: {e}")

    def remove_book(self):
        try:
            book_id = int(input("Enter the book ID to remove: "))
            if self.inventory.remove_book(book_id):
                print(f"Book ID {book_id} removed successfully.")
            else:
                print("Book ID not found. Please try again.")
        except ValueError:
            print("Invalid input. Please enter a numeric value.")

    def update_book(self):
        try:
            book_id = int(input("Enter the book ID to update: "))
            book = self.inventory.find_book(book_id)
            if book:
                title = (
                    input(f"Enter the new title (current: {book.title}): ")
                    or book.title
                )
                author = (
                    input(f"Enter the new author (current: {book.author}): ")
                    or book.author
                )
                price = input(f"Enter the new price (current: ${book.price}): ")
                stock = input(f"Enter the new stock (current: {book.stock}): ")
                book.title, book.author = title, author
                if price:
                    book.price = float(price)
                if stock:
                    book.stock = int(stock)
                print(f"Book '{book.title}' updated successfully.")
            else:
                print("Book ID not found. Please try again.")
        except ValueError:
            print("Invalid input. Please enter numeric values for price and stock.")

    def search_books(self):
        keyword = input("Enter the title or author to search: ").lower()
        results = self.inventory.search_books(keyword)
        if results:
            print("\nSearch Results:")
            print("ID | Title | Author | Price | Stock")
            for book in results:
                print(book)
        else:
            print("No books found matching the search criteria.")

    def place_order(self):
        try:
            book_id = int(input("Enter the book ID you want to order: "))
            book = self.inventory.find_book(book_id)
            if book:
                quantity = int(
                    input(
                        f"How many copies of '{book.title}' would you like to order? "
                    )
                )
                if quantity <= 0:
                    raise ValueError("Quantity must be positive.")
                if quantity <= book.stock:
                    total_cost = quantity * book.price
                    print(f"The total cost is: ${total_cost:.2f}")
                    if self.process_payment(total_cost):
                        book.update_stock(quantity)
                        order = Order(book, quantity)
                        self.order_history.append(order)
                        print(
                            f"Order placed successfully! {book.stock} copies of '{book.title}' remaining in stock."
                        )
                    else:
                        print("Payment failed. Please try again.")
                else:
                    print(
                        f"Sorry, we only have {book.stock} copies of '{book.title}' in stock."
                    )
            else:
                print("Invalid book ID. Please try again.")
        except ValueError as e:
            print(f"Invalid input: {e}")

    def process_payment(self, amount):
        try:
            print("Processing payment...")
            payment = float(input(f"Enter the amount to pay (${amount:.2f}): "))
            if payment == amount:
                print("Payment successful!")
                return True
            else:
                print("Incorrect payment amount. Transaction canceled.")
                return False
        except ValueError:
            print("Invalid input. Please enter a numeric value.")
            return False

    def view_order_history(self):
        if self.order_history:
            print("\nOrder History:")
            print("Book ID | Title | Author | Quantity | Total Cost")
            for order in self.order_history:
                print(
                    f"{order.book.book_id} | {order.book.title} | {order.book.author} | {order.quantity} | ${order.total_cost:.2f}"
                )
        else:
            print("No orders have been placed yet.")

    def main_menu(self):
        while True:
            print("\nBook Ordering System")
            print("1. View Available Books")
            print("2. Place an Order")
            print("3. Add a New Book")
            print("4. Remove a Book")
            print("5. Update Book Information")
            print("6. Search Books")
            print("7. View Order History")
            print("8. Exit")
            choice = input("Enter your choice: ")

            if choice == "1":
                self.inventory.display_books()
            elif choice == "2":
                self.place_order()
            elif choice == "3":
                self.add_book()
            elif choice == "4":
                self.remove_book()
            elif choice == "5":
                self.update_book()
            elif choice == "6":
                self.search_books()
            elif choice == "7":
                self.view_order_history()
            elif choice == "8":
                print("Thank you for using the Book Ordering System. Goodbye!")
                break
            else:
                print("Invalid choice. Please try again.")


# Run the main program
if __name__ == "__main__":
    bookstore = BookStore()
    bookstore.main_menu()
