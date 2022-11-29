#ifndef MY_VOCA_H
#define MY_VOCA_H

#include <iostream>
#include <string>
#include <list>

using namespace std;

enum Word_Type { NOUN, VERB, ADJ, ADV, PREPOS };	// noun (명사), verb(동사), adjective(형용사), adverb(부사) , preposition(전치사)
typedef list<string> List_Str;						// 리스트 컨테이너 가져옴
typedef list<string> ::iterator Lst_Str_Itr;		// 

class MyVoca
{
	friend ostream& operator<<(ostream& ostr, MyVoca& mv)
	{
		// 단어의 형태를 표현하는 문자열 배열
		const string wd_ty[] = { "n", "v", "adj", "adv", "prepos" };

		Lst_Str_Itr itr;

		// 단어 사전 오픈
		ostr << mv.KeyWord() << "(" << wd_ty[mv.type] << "):" << endl;

		// 유의어 모음 
		ostr << " - thesaurus(";
		for (itr = mv.thesaurus.begin(); itr != mv.thesaurus.end(); ++itr)
			ostr << *itr << ", ";
		ostr << ")" << endl;

		// 예시 
		ostr << " - example usage(";
		for (itr = mv.usages.begin(); itr != mv.usages.end(); ++itr)
			ostr << *itr << " ";
		ostr << ")" << endl;

		return ostr;
	}
public:
	// constructor 
	MyVoca(string kw, Word_Type wt, List_Str thes, List_Str ex_usg)	// constructor		
		: keyWord(kw), type(wt), thesaurus(thes), usages(ex_usg) {};
	MyVoca() {};			// default constructor

	// getter
	string KeyWord() { return keyWord; }
private:
	string keyWord;		// 단어
	Word_Type type;		// 형태
	List_Str thesaurus;	// 유의어들 
	List_Str usages;	// 쓰임새
};


#endif MY_VOCA_H