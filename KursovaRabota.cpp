#include <iostream>
#include <string>
#include <map>
#include <list>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

class Book
{
private:
	string bookTitle;
	string bookAuthor;
	bool isTaken;
public:
	Book(const string& tBookTitle) {
		bookTitle = tBookTitle;
	}

	Book(const string& tBookTitle, const bool& tIsTaken) {
		bookTitle = tBookTitle;
		isTaken = tIsTaken;
	}

	void TakeBook() { isTaken = true; }
	void ReturnBook() { isTaken = false; }

	string getBookTitle()const { return bookTitle; }
	string getBookAuthor()const { return bookAuthor; }
	bool getIsTaken()const { return isTaken; }

	void setBookTitle(const string& tBookTitle) { bookTitle = tBookTitle; }
	void setBookAuthor(const string& tBookAuthor) { bookAuthor = tBookAuthor; }
	void setIsTaken(const bool& tIsTaken) { isTaken = tIsTaken; }

	bool operator==(const Book& obj){ return (bookTitle == obj.bookTitle && isTaken == obj.isTaken); }
	bool operator<(const Book& obj) { return bookTitle < obj.bookTitle; }

	string convertBoolToString(const bool& b) { return (b) ? "Yes" : "No"; }
	string transformToString() { return "Book title: " + bookTitle + " Book author: " + bookAuthor + " Taken: " + convertBoolToString(isTaken); }

	friend ostream& operator<<(ostream& out, Book& obj) {
		out << obj.transformToString();
		return out;
	}
	friend istream& operator>>(istream& in, Book& obj) {
		in >> obj.bookTitle >> obj.bookAuthor;
		return in;
	}
};

class Library
{
private:
	string libraryName;
	int numberOfStillages;
	int capacityOfStillage;
	multimap<int, Book> placementInLibrary;
	map<char, int> charToNumberStillage;
	list<Book> books;

public:
	Library(const string& filename) {
		ifstream filein(filename);
		if (filein.good())
		{
			filein >> libraryName;
			filein >> numberOfStillages;
			filein >> capacityOfStillage;
			while (!filein.eof())
			{
				Book temp("");
				filein >> temp;
				temp.setIsTaken(false);
				books.push_back(temp);
			}
			filein.close();
		}
		else
			throw runtime_error("File not found");

		books.sort();

		int br = 1;
		for (Book& i : books)
		{
			charToNumberStillage.insert({ i.getBookTitle()[0],br });
			placementInLibrary.insert({ charToNumberStillage.find(i.getBookTitle()[0])->second, i });
			br = charToNumberStillage.size() +1;
		}

	}

	vector<Book> freeBooksByStillaage(const int& stillage) {
		vector<Book> book;
		if (placementInLibrary.find(stillage) != placementInLibrary.end())
		{
			for (multimap<int, Book>::iterator it = placementInLibrary.lower_bound(stillage); it != placementInLibrary.upper_bound(stillage); ++it)
			{
				if (!it->second.getIsTaken())
				{
					book.push_back(it->second);
				}
			}
		}
		else
			throw runtime_error("No stillage found!");
		return book;
	}

	vector<Book> takenBooksByStillaage(const int& stillage) {
		vector<Book> book;
		if (placementInLibrary.find(stillage) != placementInLibrary.end())
		{
			for (multimap<int, Book>::iterator it = placementInLibrary.lower_bound(stillage); it != placementInLibrary.upper_bound(stillage); ++it)
			{
				if (it->second.getIsTaken())
				{
					book.push_back(it->second);
				}
			}
		}
		else
			throw runtime_error("No stillage found!");
		return book;
	}

	Book searchFreeBookByName(const string& bookName) {
		Book b(bookName, false);
		map<char,int>::iterator i = charToNumberStillage.find(bookName[0]);
		multimap<int, Book>::iterator it;
		if (i != charToNumberStillage.end())
		{
			for (it = placementInLibrary.lower_bound(i->second); it != placementInLibrary.upper_bound(i->second); ++it)
			{
				if (it->second == b)
				{
					return it->second;
				}
			}
			if (it == placementInLibrary.end())
				throw runtime_error("That book is taken!");
		}
		else
			throw runtime_error("No such book found!");
	}

	Book takeFreeBookByName(const string& bookName) {
		Book b(bookName, false);
		map<char, int>::iterator i = charToNumberStillage.find(bookName[0]);
		multimap<int, Book>::iterator it;
		if (i != charToNumberStillage.end())
		{
			for (it = placementInLibrary.lower_bound(i->second); it != placementInLibrary.upper_bound(i->second); ++it)
			{
				if (it->second == b)
				{
					it->second.TakeBook();
					return it->second;
				}
			}
			if (it == placementInLibrary.end())	
				throw runtime_error("This book is already taken!");
		}
		else
			throw runtime_error("No such book found!");

		
		
	}

	Book searchTakenBookByName(const string& bookName) {
		Book b(bookName, true);
		map<char, int>::iterator i = charToNumberStillage.find(bookName[0]);
		multimap<int, Book>::iterator it;
		if (i != charToNumberStillage.end()) {
			for (it = placementInLibrary.lower_bound(i->second); it != placementInLibrary.upper_bound(i->second); ++it)
			{
				if (it->second == b)
				{
					return it->second;
				}
			}
			if (it == placementInLibrary.end())
				throw runtime_error("This book is free!");
		}
		else
			throw runtime_error("No such book found!");
		
	}

	Book returnBookByName(const string& bookName) {
		Book b(bookName, true);
		map<char, int>::iterator i = charToNumberStillage.find(bookName[0]);
		multimap<int, Book>::iterator it;
		if (i != charToNumberStillage.end()) {
			for (it = placementInLibrary.lower_bound(i->second); it != placementInLibrary.upper_bound(i->second); ++it)
			{
				if (it->second == b)
				{
					it->second.ReturnBook();
					return it->second;
				}
			}
			if (it == placementInLibrary.end())
				throw runtime_error("This book is already free!");
		}
		else
			throw runtime_error("No such book found!");
	}
};

int main()
{
	Library lib("Library.txt");
	vector<Book> freeBooks = lib.freeBooksByStillaage(1);


	cout << "Free Books in stillaage 1: " << endl;
	for (Book& i : freeBooks) {
		cout << i << endl;
	}


	Book b = lib.takeFreeBookByName("Book12");
	if (b.getIsTaken())
	{
		cout << "Taken book:  ";
		cout << b << endl;
	}

	Book c = lib.returnBookByName("Book20");
	if (c.getIsTaken())
	{
		cout << "Freed book:   ";
		cout << c << endl;
	}

	vector<Book> takenBooks = lib.takenBooksByStillaage(1);
	cout << "Taken Books in stillaage 1: " << endl;
	for (Book& i : takenBooks) {
		cout << i << endl;
	}

	return 0;

}
