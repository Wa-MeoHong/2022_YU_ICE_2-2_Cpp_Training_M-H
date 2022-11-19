/*
  ���ϸ� : "�ǽ�10_21912193_�Ŵ�ȫ"
  ���α׷��� ���� �� �⺻ ���:
	- Binary Search Tree�� �����ϰ�, BST�� ������ �����ϱ�����, ���뷱���� �����ϴ� �˰���
  ���α׷� �ۼ��� : �Ŵ�ȫ(2022�� 11�� 15��)
  ���� Update : Version 1.1.1, 2022�� 11�� 18��(�Ŵ�ȫ)
===========================================================================================================
					���α׷� ����/���� �̷�
===========================================================================================================
   ������	  ������			����			     ����/���ϳ���
-----------------------------------------------------------------------------------------------------------
	�Ŵ�ȫ		 2022/11/15		v1.0.0		  �����ۼ�
	�Ŵ�ȫ		 2022/11/16		v1.0.1		  ��������� ������ ���� ����( �ڵ� ������ ���� ) 
	�Ŵ�ȫ		 2022/11/17		v1.1.0		  �ڵ� �ϼ�
	�Ŵ�ȫ		 2022/11/18		v1.1.1		  rotate_RL ���� 
===========================================================================================================
*/

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <sstream>			// stringstream �� ��
#include "T_BST.h"
#include "T_Entry.h"
#include "T_Array.h"
#include "Date.h"
#include "Book.h"

using namespace std;

#define INPUT "books.txt"
#define OUTPUT "output.txt"
#define ReadNUM 256

BOOK* fGetBookRecords(string F_name, int* num_books)				// ������ ���� Book��ü�� ���� �����͸� ������
{
	ifstream fin;
	BOOK* pBooks = NULL;
	string title, author, date_str;
	Date pd;
	int isbn = 0, year = 0, month = 0, day = 0;

	// ���� ���� (�б� �������� )
	fin.open(F_name, ios::in);
	if (fin.fail())
	{
		cout << "Error! does not open books.txt!\n"; 
		exit(-1);
	}

	fin >> *num_books;
	pBooks = new BOOK[*num_books];			// Book ��ü �����Ҵ�
	cout << "Number of Books (from file) = " << *num_books << endl;

	for (int i = 0; i < *num_books; i++)
	{
		fin >> title >> author >> date_str >> isbn;	 // ����, �۰�, ������ ���ڿ�, isbn �޾ƿ�
		
		// �������� ��, ��, �Ϸ� ������ ����
		for (int i = 0; i < date_str.size(); i++)
		{
			if (date_str[i] == '-')
				date_str[i] = ' ';			// 1. '-'�� ������ ��¥�� �������� ������. ( ���� ��ü )
		}
		stringstream date_ss;				// stringstream ��ü, ���ڿ��� �ٷ�� stream��ü (�Է�, ���).
		date_ss.str(date_str);				// ���� ����, "\n"���� ������ ���ڿ��� stringstream���� �����ش�.
		date_ss >> year >> month >> day;	// �� ��, year, month, day�� �� ������ int������ ����ش�.
	
		pBooks[i] = BOOK(title, author, Date(year, month, day), isbn);
	}
	fin.close();
	return pBooks;					// ������ �ݰ� Books�迭�� ��ȯ��
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
		fout << books[i] << endl;					// ���Ϸκ��� ������ books��ü�� ���(1�پ�)
	}
	fout << endl;

	/* 1. Balanced ����Ž��Ʈ�� ���� ( Key�� Book�� ���� ) */ 
	fout << endl << "Balanced Binary Search Tree (BBST) with key book title" << endl;
	T_Entry<string, BOOK*> entry_title_pBK;
	T_BST<string, BOOK*> BBST_BK_keyTitle("BBST_BK_keyTitle");
	T_BSTN<string, BOOK*>* pRoot= NULL, ** ppBBST_BK_Root = NULL;
	ppBBST_BK_Root = BBST_BK_keyTitle.RootAddr();

	// ����Ž��Ʈ���� ���� �������. (���뷱�̵� ���� ����)
	for (int i = 0; i < num_books; i++)
	{
		entry_title_pBK.SetKey(books[i].Title());
		entry_title_pBK.SetVal(&books[i]);
		BBST_BK_keyTitle.insertAndReBal(entry_title_pBK);			// insert�� ���뷱���� ���ÿ� ó��
	}
	// ���� ����Ž��Ʈ���� �����
	fout << "\nEntries in " << BBST_BK_keyTitle.Name() << " (in order to Book Title) : " << endl;
	BBST_BK_keyTitle.print_with_Depth(fout);

	/* 2. Balanced ����Ž��Ʈ�� ���� ( Key�� Book�� �۰� ) */
	fout << endl << "Balanced Binary Search Tree (BBST) with key book-author" << endl;
	T_Entry<string, BOOK*> entry_Author_pBK;
	T_BST<string, BOOK*> BBST_BK_keyAuthor("BBST_BK_keyAuthor");
	T_BSTN<string, BOOK*>* pBBST_BK_keyAuthor= NULL, ** ppRoot_BBST_BK_keyAuthor = NULL;

	ppRoot_BBST_BK_keyAuthor = BBST_BK_keyAuthor.RootAddr();
	for (int i = 0; i < num_books; i++)
	{
		// ����Ž��Ʈ���� ���� �������. (���뷱�̵� ���� ����)
		entry_Author_pBK.SetKey(books[i].Author());
		entry_Author_pBK.SetVal(&books[i]);
		BBST_BK_keyAuthor.insertAndReBal(entry_Author_pBK);
	}
	// ���� ����Ž��Ʈ���� �����
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

	/* 3. Balanced ����Ž��Ʈ�� ���� ( Key�� Book�� ������ ) */
	fout << endl << "Balanced Binary Search Tree (BBST) with key publication-date" << endl;
	T_Entry<Date, BOOK*> entry_PubDate_pBK;
	T_BST<Date, BOOK*> BBST_BK_keyPubDate("BBST_BK_keyPubDate");
	T_BSTN<Date, BOOK*>** ppRoot_BBST_BK_keyPubDate = NULL;
	ppRoot_BBST_BK_keyPubDate = BBST_BK_keyPubDate.RootAddr();
	
	for (int i = 0; i < num_books; i++)
	{
		// ����Ž��Ʈ���� ���� �������. (���뷱�̵� ���� ����)
		entry_PubDate_pBK.SetKey(books[i].PubDate());
		entry_PubDate_pBK.SetVal(&books[i]);
		BBST_BK_keyPubDate.insertAndReBal(entry_PubDate_pBK);
	}
	// ���� ����Ž��Ʈ���� �����
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