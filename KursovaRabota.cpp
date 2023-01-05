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
	Book() {
		bookTitle = "N/A";
		bookAuthor = "N/A";
		isTaken = false;
	}

	Book(const string& tBookTitle) {
		bookTitle = tBookTitle;
	}

	Book(const string& tBookTitle, const bool& tIsTaken) {
		bookTitle = tBookTitle;
		isTaken = tIsTaken;
	}

	void TakeBook() {
		isTaken = true;
	}

	void ReturnBook() {
		isTaken = false;
	}

	string getBookTitle()const { return bookTitle; }
	string getBookAuthor()const { return bookAuthor; }
	bool getIsTaken()const { return isTaken; }

	void setBookTitle(const string& tBookTitle) { bookTitle = tBookTitle; }
	void setBookAuthor(const string& tBookAuthor) { bookAuthor = tBookAuthor; }
	void setIsTaken(const bool& tIsTaken) { isTaken = tIsTaken; }

	bool operator==(const Book& obj){ return (bookTitle == obj.bookTitle && bookAuthor == obj.bookAuthor && isTaken == obj.isTaken); }
	bool operator<(const Book& obj) { return bookTitle < obj.bookTitle; }

	string transformToString() { return "Book title: " + bookTitle + " book author: " + bookAuthor + " Taken: " + to_string(isTaken); }

	friend ostream& operator<<(ostream& out, const Book& obj) {
		out << obj.bookTitle << obj.bookAuthor << obj.isTaken;
		return out;
	}
	friend istream& operator>>(istream& in, Book& obj) {
		in >> obj.bookTitle >> obj.bookAuthor >> obj.isTaken;
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
				Book temp;
				filein >> temp;
				books.push_back(temp);
			}
			filein.close();
		}
		else
			throw runtime_error("File not found");

		sort(books.begin(),books.end());
		int br = 1;
		list<Book>::iterator it = books.begin();
		for (list<Book>::iterator i = books.begin(); i != books.end(); ++i)
		{
			if (it->getBookTitle()[0] != i->getBookTitle()[0])
			{
				charToNumberStillage.insert({ it->getBookTitle()[0],br });
				while (it->getBookTitle()[0] != i->getBookTitle()[0])
				{
					placementInLibrary.insert({ br, *it });
					advance(it, 1);
				}
				br++;
			}
		}
	}

	vector<Book> freeBooksByStillaage(const int& stillage) {
		vector<Book> book;
		multimap<int, Book>::iterator it;
		for (it = placementInLibrary.begin(); it != placementInLibrary.end(); ++it)
		{
			if (it->first == stillage && !it->second.getIsTaken())
			{
				book.push_back(it->second);
			}
		}
		return book;
	}

	vector<Book> takenBooksByStillaage(const int& stillage) {
		vector<Book> book;
		multimap<int, Book>::iterator it;
		for (it = placementInLibrary.begin(); it != placementInLibrary.end(); ++it)
		{
			if (it->first == stillage && it->second.getIsTaken())
			{
				book.push_back(it->second);
			}
		}
		return book;
	}

	Book searchFreeBookByName(const string& bookName) {
		multimap<int, Book>::iterator it;
		for (it = placementInLibrary.begin(); it != placementInLibrary.end(); ++it)
		{
			if (it->second.getBookTitle() == bookName && !it->second.getIsTaken())
			{
				return it->second;
			}
		}
	}

	Book takeFreeBookByName(const string& bookName) {
		multimap<int, Book>::iterator it;
		for (it = placementInLibrary.begin(); it != placementInLibrary.end(); ++it)
		{
			if (it->second.getBookTitle() == bookName && !it->second.getIsTaken())
			{
				it->second.TakeBook();
				return it->second;
			}
		}
	}

	Book searchTakenBookByName(const string& bookName) {
		multimap<int, Book>::iterator it;
		for (it = placementInLibrary.begin(); it != placementInLibrary.end(); ++it)
		{
			if (it->second.getBookTitle() == bookName && it->second.getIsTaken())
			{
				return it->second;
			}
		}
	}

	Book returnBookByName(const string& bookName) {
		multimap<int, Book>::iterator it;
		for (it = placementInLibrary.begin(); it != placementInLibrary.end(); ++it)
		{
			if (it->second.getBookTitle() == bookName && it->second.getIsTaken())
			{
				it->second.ReturnBook();
				return it->second;
			}
		}
	}
};

int main()
{
	Library lib("Library.txt");
	vector<Book> freeBooks = lib.freeBooksByStillaage(1);
	vector<Book> takenBooks = lib.takenBooksByStillaage(1);

	for (vector<Book>::iterator i = freeBooks.begin(); i != freeBooks.end(); ++i)
	{
		cout << *i << endl;
	}

	for (vector<Book>::iterator i = takenBooks.begin(); i != takenBooks.end(); ++i)
	{
		cout << *i << endl;
	}

	Book b = lib.takeFreeBookByName("Book12");
	cout << b<<endl;
	Book c = lib.returnBookByName("Book12");
	cout << c << endl;


}