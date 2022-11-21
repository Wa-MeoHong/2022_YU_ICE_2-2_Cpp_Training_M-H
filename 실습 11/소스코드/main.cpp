/*
  ���ϸ� : "�ǽ�11_21912193_�Ŵ�ȫ"
  ���α׷��� ���� �� �⺻ ���:
	- HashMap, HashDict�� �����Ͽ� ���ܾ���� ó���ϴ� �˰����� �����Ѵ�
  ���α׷� �ۼ��� : �Ŵ�ȫ(2022�� 11�� 21��)
  ���� Update : Version 1.1.0, 2022�� 11�� 21��(�Ŵ�ȫ)
===========================================================================================================
					���α׷� ����/���� �̷�
===========================================================================================================
   ������	  ������			����			     ����/���ϳ���
-----------------------------------------------------------------------------------------------------------
	�Ŵ�ȫ		 2022/11/20		v1.0.0		  �����ۼ�
	�Ŵ�ȫ		 2022/11/21		v1.1.0		  �ϼ�

===========================================================================================================
*/

#include <iostream>
#include <fstream>
#include <string>
#include "HashMap.h"
#include "CyclicShiftHashCode.h"
#include "Entry.h"
#include "HashDict.h"
#include "MyVoca.h"
#include "MyVocaList.h"

#define OUTPUT "output.txt"

int main(void)
{
	ofstream fout(OUTPUT);

	if (fout.fail())
	{
		cout << "Error!! Fail to open output.txt! " << endl;
		exit(-1);
	}
	MyVoca* pVoca = NULL, voca, mv;
	List_Str thesaurus;					// ���Ǿ� ����Ʈ
	List_Str usages;					// ��� �� ����Ʈ
	int word_count = 0;
	string keyWord;						// �ܾ�
	HashDict<string, MyVoca*>  myVocaDict("MyVocaDict");			// Hash Dictionary�� ����
	HashDict<string, MyVoca*>::Iterator itr;						// Hash Dictionary iterator
	HashDict<string, MyVoca*>::Range range;							// Hash Dictionary range

	Entry<string, MyVoca*> vocaEntry;

	fout << "Inserting My Vocabularies to " << myVocaDict.Name() << " . . . " << endl;
	for (int i = 0; i < NUM_MY_TOEIC_VOCA; i++)
	{
		pVoca = &myToeicVocaList[i];				// �ܾ��� ������ �о��
		keyWord = pVoca->KeyWord();					// Ű : �ܾ�
		myVocaDict.insert(keyWord, pVoca);			// Hash Dictionary�� �������
	}

	fout << "Total " << myVocaDict.size() << " words in my Voca_Dictionary .. \n" << endl;

	// check All vocabularies in the Hash Dictionary
	for (itr = myVocaDict.begin(); itr != myVocaDict.end(); ++itr)
	{
		pVoca = itr.Value();
		fout << *pVoca << endl;			// ���
	}
	fout << endl;
	
	// myVocaDict.fprintBucketSizes(fout);					// ��� ��Ʈ�� ������ ���
	fout << endl;

	string testWord = "offer";
	range = myVocaDict.findAll(testWord);
	fout << "Thesaurus of [" << testWord << "]:" << endl;
	for (itr = range.begin(); itr != range.end(); ++itr)
	{
		pVoca = itr.Value();
		fout << *pVoca << endl;
	}
	fout << endl;
	
	cout << "file input complete! " << endl;

	fout.close();				//	���� �ݱ� 
	return 0;

}