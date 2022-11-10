#include <iostream>
#include <cstring>
#include <string>
#include <iomanip>
using namespace std;

class Book {
    public:
        char *title;
        char *author;
        char *isbn;
        char *publisher;
        Book *nextBook = NULL;

        Book() {
            title = new char[51];
            author = new char[51];
            isbn = new char[51];
            publisher = new char[51];
        }

        Book(const char *t,const char *a, const char *i, const char *p) {
            title = new char[strlen(t) + 1];
            strcpy(title, t);
            author = new char[strlen(a) + 1];
            strcpy(author, a);
            isbn = new char[strlen(i) + 1];
            strcpy(isbn, i);
            publisher = new char[strlen(p) + 1];
            strcpy(publisher, p);
        }
        ~Book(){ 
            delete[] title;
            delete[] author;
            delete[] isbn;
            delete[] publisher;
        }
};

class Library {
public:
    Book* front = NULL;
    Book* rear = NULL;
    Book* temporary;

    void enqueueBook() {
        char title[51], author[51], isbn[51], publisher[51];
        cin.ignore();
        cout << "Enter title of the book: ";
        cin.get(title, 51);
        cin.ignore();
        cout << "Enter author of the book: ";
        cin.get(author, 51);
        cin.ignore();
        cout << "Enter ISBN of the book: ";
        cin.get(isbn, 51);
        cin.ignore();
        cout << "Enter publisher of the book: ";
        cin.get(publisher, 51);
        
        if (front == NULL && rear == NULL) {
            rear = new Book(title, author, isbn, publisher);
            rear->nextBook = NULL;

            front = rear;
        }
        else
        {
            temporary = new Book(title, author, isbn, publisher);
            rear->nextBook = temporary;
            temporary->nextBook = NULL;
            rear = temporary;
        }
    }

    void dequeueBook() {
        temporary = front;
        if (front == NULL) {
            cout << "Library is empty";
        }
        else if (temporary->nextBook != NULL) {
            temporary = temporary->nextBook;
            cout <<  front->title << " has been removed from the library" << endl;
            front = temporary;
        }
        else {
            cout << front->title << " has been removed from the library" << endl;
            front = NULL;
            rear = NULL;
        }

    }

    int findBook() {
        char lookUp[50];
        char* searchResult = NULL;
		
		cin.ignore();
        cout << "Enter the title or the  book you want to remove:";
        cin.get(lookUp, 50);
        
//        temporary = front;
//        int position = -1;
//        while (temporary != NULL) {
//        	position++;
//            searchResult = strstr(temporary->title, lookUp);
//            if (searchResult != NULL)
//                return position;
//            searchResult = strstr(temporary->isbn, lookUp);
//            if (searchResult != NULL)
//                return position;
//            temporary = temporary->nextBook;
//        }
		int position = -1;
		for(temporary = front; temporary != NULL; temporary = temporary->nextBook){
			position++;
			searchResult = strstr(temporary->title, lookUp);
            if (searchResult != NULL)
                return position;
            searchResult = strstr(temporary->isbn, lookUp);
            if (searchResult != NULL)
                return position;
            temporary = temporary->nextBook;
		}
        return position;

    }

    void removeBook()
    {
    	char input[51];
    	char* lookUp;
        char* searchResult = NULL;
		
		cin.ignore();
        cout << "Enter the title or the ISBN of the book you want to remove:";
        cin.get(input, 51);
        lookUp = new char[strlen(input)+1];
        strcpy(lookUp,input);
        bool found = false;
        int position;
        int index = 0;
        temporary = front;
		while (temporary != NULL) {
			
            searchResult = strstr(temporary->title, lookUp);
            if (searchResult != NULL){
	                found = true;
	                position = index;
	            }

            searchResult = strstr(temporary->isbn, lookUp);
            if (searchResult != NULL){
	                found = true;
	                position = index;
	            }

            temporary = temporary->nextBook;
            index++;
        }
        
        Book* current;
        Book* previous;
        if (!found) {
            cout << "The book you entered are not available\n";
        }
        else {
        	int count = 0;
        	temporary = front;
        	while(temporary != NULL){
        		temporary = temporary->nextBook;
        		count++;
			}
			if(count == 1 || position == 0){
				dequeueBook();
			}else{
		
            current = front;
            for (int i = 0; i < position; i++)
            {
                previous = current;
                current = current->nextBook;
            }
            previous->nextBook = current->nextBook;
            cout << current->title << " has been removed from the library\n";
            delete current;
        	}

        }
    }

    void displayBook(Library &objLib) {
        temporary = objLib.front;
        if ((front == NULL) && (rear == NULL)) {
            cout << "Library is empty" << endl;
        }
        else {
            cout << "The following books are available: " << endl;
            while (temporary != NULL) {
                cout << temporary->title << "; "
					 << temporary->author << "; "
					 << temporary->isbn << "; "
					 << temporary->publisher << endl;
                temporary = temporary->nextBook;
            }
            cout << endl;
        }
    }

    void LibraryMenu() {
        cout << "How can I help you?" << endl;
        cout << "1) Enter new book" << endl;
        cout << "2) Take out the first book " << endl;
        cout << "3) Remove a book" << endl;
        cout << "4) Display all the Books" << endl;
        cout << "5) Exit" << endl;
        cout << "Your choice: ";
    }

};


int main()
{
    Library library;
    int choice;
    do
    {
        library.LibraryMenu();
        cin >> choice;
        switch (choice) {
        case 1: library.enqueueBook();
            break;
        case 2: library.dequeueBook();
            break;
        case 3: library.removeBook();
            break;
        case 4: library.displayBook(library);
            break;
        case 5: cout << "Exit" << endl;
            break;
        default: cout << "Invalid choice" << endl;
        }

    } while (choice != 5);

    return 0;

}

