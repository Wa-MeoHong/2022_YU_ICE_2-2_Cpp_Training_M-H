/*
  파일명 : "실습10_21912193_신대홍"
  프로그램의 목적 및 기본 기능:
	- Binary Search Tree를 구성하고, BST의 단점을 보완하기위해, 리밸런싱을 진행하는 알고리즘
  프로그램 작성자 : 신대홍(2022년 11월 15일)
  최종 Update : Version 1.1.1, 2022년 11월 18일(신대홍)
===========================================================================================================
					프로그램 수정/보완 이력
===========================================================================================================
   수정자	  수정일			버전			     수정/보완내용
-----------------------------------------------------------------------------------------------------------
	신대홍		 2022/11/15		v1.0.0		  최초작성
	신대홍		 2022/11/16		v1.0.1		  헤더파일의 구성은 거의 다함( 코드 구현만 남음 ) 
	신대홍		 2022/11/17		v1.1.0		  코드 완성
	신대홍		 2022/11/18		v1.1.1		  rotate_RL 수정 
===========================================================================================================
*/

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <sstream>			// stringstream 을 한
#include "T_BST.h"
#include "T_Entry.h"
#include "T_Array.h"
#include "Date.h"
#include "Book.h"

using namespace std;

#define INPUT "books.txt"
#define OUTPUT "output.txt"
#define ReadNUM 256

BOOK* fGetBookRecords(string F_name, int* num_books)				// 파일을 통해 Book객체에 담을 데이터를 가져옴
{
	ifstream fin;
	BOOK* pBooks = NULL;
	string title, author, date_str;
	Date pd;
	int isbn = 0, year = 0, month = 0, day = 0;

	// 파일 열기 (읽기 형식으로 )
	fin.open(F_name, ios::in);
	if (fin.fail())
	{
		cout << "Error! does not open books.txt!\n"; 
		exit(-1);
	}

	fin >> *num_books;
	pBooks = new BOOK[*num_books];			// Book 객체 동적할당
	cout << "Number of Books (from file) = " << *num_books << endl;

	for (int i = 0; i < *num_books; i++)
	{
		fin >> title >> author >> date_str >> isbn;	 // 제목, 작가, 출판일 문자열, isbn 받아옴
		
		// 출판일을 년, 월, 일로 나누는 과정
		for (int i = 0; i < date_str.size(); i++)
		{
			if (date_str[i] == '-')
				date_str[i] = ' ';			// 1. '-'로 나눠진 날짜를 공백으로 나눈다. ( 문자 교체 )
		}
		stringstream date_ss;				// stringstream 객체, 문자열을 다루는 stream객체 (입력, 출력).
		date_ss.str(date_str);				// 먼저 공백, "\n"으로 나눠진 문자열을 stringstream으로 나눠준다.
		date_ss >> year >> month >> day;	// 그 후, year, month, day에 그 값들을 int형으로 담아준다.
	
		pBooks[i] = BOOK(title, author, Date(year, month, day), isbn);
	}
	fin.close();
	return pBooks;					// 파일을 닫고 Books배열을 반환함
}

int main(void)
{
	ofstream fout;
	BOOK* books;
	int num_books = 0;

	books = fGetBookRecords(INPUT, &num_books);

	fout.open(OUTPUT);
	if (fout.fail())
	{
		cout << "Error! does not open output.txt!\n";
		exit(-1);
	}

	fout << "Input books[] array : " << endl;
	for (int i = 0; i < num_books; i++)
	{
		fout << books[i] << endl;					// 파일로부터 가져온 books객체를 출력(1줄씩)
	}
	fout << endl;

	/* 1. Balanced 이진탐색트리 제작 ( Key는 Book의 제목 ) */ 
	fout << endl << "Balanced Binary Search Tree (BBST) with key book title" << endl;
	T_Entry<string, BOOK*> entry_title_pBK;
	T_BST<string, BOOK*> BBST_BK_keyTitle("BBST_BK_keyTitle");
	T_BSTN<string, BOOK*>* pRoot= NULL, ** ppBBST_BK_Root = NULL;
	ppBBST_BK_Root = BBST_BK_keyTitle.RootAddr();

	// 이진탐색트리에 값을 집어넣음. (리밸런싱도 같이 진행)
	for (int i = 0; i < num_books; i++)
	{
		entry_title_pBK.SetKey(books[i].Title());
		entry_title_pBK.SetVal(&books[i]);
		BBST_BK_keyTitle.insertAndReBal(entry_title_pBK);			// insert와 리밸런싱을 동시에 처리
	}
	// 넣은 이진탐색트리를 출력함
	fout << "\nEntries in " << BBST_BK_keyTitle.Name() << " (in order to Book Title) : " << endl;
	BBST_BK_keyTitle.print_with_Depth(fout);

	/* 2. Balanced 이진탐색트리 제작 ( Key는 Book의 작가 ) */
	fout << endl << "Balanced Binary Search Tree (BBST) with key book-author" << endl;
	T_Entry<string, BOOK*> entry_Author_pBK;
	T_BST<string, BOOK*> BBST_BK_keyAuthor("BBST_BK_keyAuthor");
	T_BSTN<string, BOOK*>* pBBST_BK_keyAuthor= NULL, ** ppRoot_BBST_BK_keyAuthor = NULL;

	ppRoot_BBST_BK_keyAuthor = BBST_BK_keyAuthor.RootAddr();
	for (int i = 0; i < num_books; i++)
	{
		// 이진탐색트리에 값을 집어넣음. (리밸런싱도 같이 진행)
		entry_Author_pBK.SetKey(books[i].Author());
		entry_Author_pBK.SetVal(&books[i]);
		BBST_BK_keyAuthor.insertAndReBal(entry_Author_pBK);
	}
	// 넣은 이진탐색트리를 출력함
	fout << "\nEntries in " << BBST_BK_keyAuthor.Name() << " (in order to Book Author) : " << endl;
	BBST_BK_keyAuthor.print_with_Depth(fout);

	// Testing Search on Binary Search Tree
	string author = books[0].Author();
	Date d1, d2;
	BOOK* pBk;
	T_Array<BOOK*> array_pBook(1, string("Array_Book"));

	d1.setDate(2010, 1, 1);
	d2.setDate(2015, 12, 31);
	pBBST_BK_keyAuthor = BBST_BK_keyAuthor.searchBSTN(author);
	BBST_BK_keyAuthor.travelsal_inOrder(pBBST_BK_keyAuthor, array_pBook);
	fout << "Books of author (" << author << ") published during " << d1 << " ~ " << d2 << ":" << endl;
	for (int i = 0; i < array_pBook.size(); i++)
	{
		if (array_pBook[i]->Author() == author)
		{
			pBk = array_pBook[i];
			if ((pBk->PubDate() >= d1) && (pBk->PubDate() <= d2))
				fout << *(array_pBook[i]) << endl;
		}
	}

	/* 3. Balanced 이진탐색트리 제작 ( Key는 Book의 출판일 ) */
	fout << endl << "Balanced Binary Search Tree (BBST) with key publication-date" << endl;
	T_Entry<Date, BOOK*> entry_PubDate_pBK;
	T_BST<Date, BOOK*> BBST_BK_keyPubDate("BBST_BK_keyPubDate");
	T_BSTN<Date, BOOK*>** ppRoot_BBST_BK_keyPubDate = NULL;
	ppRoot_BBST_BK_keyPubDate = BBST_BK_keyPubDate.RootAddr();
	
	for (int i = 0; i < num_books; i++)
	{
		// 이진탐색트리에 값을 집어넣음. (리밸런싱도 같이 진행)
		entry_PubDate_pBK.SetKey(books[i].PubDate());
		entry_PubDate_pBK.SetVal(&books[i]);
		BBST_BK_keyPubDate.insertAndReBal(entry_PubDate_pBK);
	}
	// 넣은 이진탐색트리를 출력함
	fout << "\nEntries in " << BBST_BK_keyPubDate.Name() << " (in order to Book Publication Date) : " << endl;
	BBST_BK_keyPubDate.print_with_Depth(fout);


	/* 4. Remove root entry */
	fout << "\nRemoving the root entry in sequence . . ." << endl;
	for (int i = 0; i < num_books; i++)
	{
		pRoot = BBST_BK_keyTitle.Root();
		entry_title_pBK = pRoot->Entry();
		fout << "\nremove " << entry_title_pBK << endl;
		BBST_BK_keyTitle.eraseBSTN(&pRoot);
		BBST_BK_keyTitle.print_with_Depth(fout);
	}

	fout << "\nClearing BBST_BKs . . . " << endl;
	BBST_BK_keyTitle.clear();
	BBST_BK_keyAuthor.clear();
	BBST_BK_keyPubDate.clear();
	fout << "All BBST_BKs cleared !! " << endl;

	fout.close();
	if (books != NULL)
		delete[] books;

	return  0;

}