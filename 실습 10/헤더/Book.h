#ifndef BOOK_H
#define BOOK_H

#include <iostream>
#include <iomanip>
#include <string>
#include "Date.h"

class BOOK
{
	friend ostream& operator<< (ostream& ostr, BOOK bk)
	{
		ostr.setf(ios::left);
		ostr << "[" << setw(8) << bk.title << setw(8) << bk.author << ", " << bk.pubDate
			<< ", " << bk.isbn << "]";
		return ostr;
	}
public:
	// constructor 
	BOOK() {
		title = ""; author = ""; pubDate = Date(1, 1, 1); isbn = 0;
	}
	BOOK(string T, string BK_a, Date pd, int bn)
		: title(T), author(BK_a), pubDate(pd), isbn(bn) {}
	
	// getter
	string Title() { return title; }
	string Author() { return author; }
	Date PubDate() { return pubDate; }
	int ISBN() { return isbn; }

	// setter
	void SetTitle(string bk_title) { title = bk_title; }
	void SetAuthor(string bk_author) { author = bk_author; }
	void SetPubDate(Date pd) { pubDate = pd; }
	void SetISBN(int bn) { isbn = bn; }

private:
	string title;
	string author;
	Date pubDate;		// date of publish
	int isbn;			// intermational standard book number 

};

#endif BOOK_H
