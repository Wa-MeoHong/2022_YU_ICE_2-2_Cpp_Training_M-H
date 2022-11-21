/*
  파일명 : "실습11_21912193_신대홍"
  프로그램의 목적 및 기본 기능:
	- HashMap, HashDict을 구성하여 영단어들을 처리하는 알고리즘을 수행한다
  프로그램 작성자 : 신대홍(2022년 11월 21일)
  최종 Update : Version 1.1.0, 2022년 11월 21일(신대홍)
===========================================================================================================
					프로그램 수정/보완 이력
===========================================================================================================
   수정자	  수정일			버전			     수정/보완내용
-----------------------------------------------------------------------------------------------------------
	신대홍		 2022/11/20		v1.0.0		  최초작성
	신대홍		 2022/11/21		v1.1.0		  완성

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
	List_Str thesaurus;					// 유의어 리스트
	List_Str usages;					// 사용 예 리스트
	int word_count = 0;
	string keyWord;						// 단어
	HashDict<string, MyVoca*>  myVocaDict("MyVocaDict");			// Hash Dictionary를 구성
	HashDict<string, MyVoca*>::Iterator itr;						// Hash Dictionary iterator
	HashDict<string, MyVoca*>::Range range;							// Hash Dictionary range

	Entry<string, MyVoca*> vocaEntry;

	fout << "Inserting My Vocabularies to " << myVocaDict.Name() << " . . . " << endl;
	for (int i = 0; i < NUM_MY_TOEIC_VOCA; i++)
	{
		pVoca = &myToeicVocaList[i];				// 단어의 정보를 읽어옴
		keyWord = pVoca->KeyWord();					// 키 : 단어
		myVocaDict.insert(keyWord, pVoca);			// Hash Dictionary에 집어넣음
	}

	fout << "Total " << myVocaDict.size() << " words in my Voca_Dictionary .. \n" << endl;

	// check All vocabularies in the Hash Dictionary
	for (itr = myVocaDict.begin(); itr != myVocaDict.end(); ++itr)
	{
		pVoca = itr.Value();
		fout << *pVoca << endl;			// 출력
	}
	fout << endl;
	
	// myVocaDict.fprintBucketSizes(fout);					// 모든 엔트리 사이즈 출력
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

	fout.close();				//	파일 닫기 
	return 0;

}