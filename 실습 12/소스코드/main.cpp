/*
  파일명 : "실습12_21912193_신대홍"
  프로그램의 목적 및 기본 기능:
	- Trie를 구성하여 자동완성 기능을 확인해본다.
  프로그램 작성자 : 신대홍(2022년 11월 28일)
  최종 Update : Version 1.1.0, 2022년 11월 28일(신대홍)
===========================================================================================================
					프로그램 수정/보완 이력
===========================================================================================================
   수정자	  수정일			버전			     수정/보완내용
-----------------------------------------------------------------------------------------------------------
	신대홍		 2022/11/27		v1.0.0		  최초작성
	신대홍		 2022/11/28		v1.1.0		  완성

===========================================================================================================
*/

#include <iostream>
#include <fstream>
#include <list>
#include <string>
#include "MyVoca.h"
#include "MyVocaList.h"
#include "Trie.h"
#include "TrieNode.h"

using namespace std;

#define MAX_WORD_LENGTH 100
#define NUM_TEST_VOCAS  7
#define OUTPUT "output.txt"

int main(void)
{
	ofstream fout(OUTPUT);
	if (fout.fail())
	{
		cout << "Error in opening output.txt file " << endl;
		exit(-1);
	}

	Trie<MyVoca*> trie_myVoca("Trie_MyVoca");
	TrieNode<MyVoca*>* pTN = NULL;
	MyVoca* pVoca = NULL;
	int word_count = 0;
	string keystr;
	char keyWord[MAX_WORD_LENGTH];
	List_pVoca predictVocas;
	List_pVoca_Iter itr;

	// testing basic operation in trie 
	MyVoca testVocas[NUM_TEST_VOCAS] =
	{
		MyVoca("xyz", NOUN, { "" }, { "" }),
		MyVoca("ABCD", NOUN, { "" }, { "" }),
		MyVoca("ABC", NOUN, { "" }, { "" }),
		MyVoca("AB", NOUN, { "" }, { "" }),
		MyVoca("A", NOUN, { "" }, { "" }),
		MyVoca("xy", NOUN, { "" }, { "" }),
		MyVoca("x", NOUN, { "" }, { "" }),
	};

	// 먼저 Trie에 내용을 넣고 출력
	fout << "Testing basic operations of trie inserting ";
	for (int i = 0; i < NUM_TEST_VOCAS; i++)
	{
		trie_myVoca.insert(testVocas[i].KeyWord(), &testVocas[i]);
	}
	trie_myVoca.fprintTrie(fout);

	// 삭제
	fout << "\nTesting Trie Destroy...\n";
	trie_myVoca.eraseTrie();
	trie_myVoca.fprintTrie(fout);

	/* 키워드를 삽입 */
	fout << "Inserting My Vocabularies to myVocaDict . . . " << endl;
	word_count = 0;
	pVoca = &myToeicVocaList[0];
	while (pVoca->KeyWord() != "")
	{
		keystr = pVoca->KeyWord();
		trie_myVoca.insert(keystr, pVoca);
		pVoca++;
	}
	fout << "Total " << trie_myVoca.size() << " words in trie_myVoca .." << endl;
	trie_myVoca.fprintTrie(fout);

	/* testing keyWord search in trie */
	while (1)
	{
		cout << "\nInput any prefix to search in trie(. to finish) : ";
		cin >> keystr;
		if (keystr == string("."))
			break;
		predictVocas.clear();

		trie_myVoca.findPrefixMatch(keystr, predictVocas);
		cout << "list of predictive wors with prefix (" << keystr << ") :" << endl;

		itr = predictVocas.begin();

		for (int i = 0; i < predictVocas.size(); i++)
		{
			pVoca = *itr;
			cout << *pVoca << endl;
			++itr;
		}
	}
	cout << "\nErasing trie_myVoca ...." << endl;
	fout << "\nErasing trie_myVoca ...." << endl;
	trie_myVoca.eraseTrie();

	fout.close();
	return 0;

}
