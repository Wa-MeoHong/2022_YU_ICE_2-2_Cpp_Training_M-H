/*
  ���ϸ� : "�ǽ�12_21912193_�Ŵ�ȫ"
  ���α׷��� ���� �� �⺻ ���:
	- Trie�� �����Ͽ� �ڵ��ϼ� ����� Ȯ���غ���.
  ���α׷� �ۼ��� : �Ŵ�ȫ(2022�� 11�� 28��)
  ���� Update : Version 1.1.0, 2022�� 11�� 28��(�Ŵ�ȫ)
===========================================================================================================
					���α׷� ����/���� �̷�
===========================================================================================================
   ������	  ������			����			     ����/���ϳ���
-----------------------------------------------------------------------------------------------------------
	�Ŵ�ȫ		 2022/11/27		v1.0.0		  �����ۼ�
	�Ŵ�ȫ		 2022/11/28		v1.1.0		  �ϼ�

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

	// ���� Trie�� ������ �ְ� ���
	fout << "Testing basic operations of trie inserting ";
	for (int i = 0; i < NUM_TEST_VOCAS; i++)
	{
		trie_myVoca.insert(testVocas[i].KeyWord(), &testVocas[i]);
	}
	trie_myVoca.fprintTrie(fout);

	// ����
	fout << "\nTesting Trie Destroy...\n";
	trie_myVoca.eraseTrie();
	trie_myVoca.fprintTrie(fout);

	/* Ű���带 ���� */
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
