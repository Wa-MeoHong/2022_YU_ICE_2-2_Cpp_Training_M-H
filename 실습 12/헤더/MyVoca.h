#ifndef MY_VOCA_H
#define MY_VOCA_H

#include <iostream>
#include <string>
#include <list>

using namespace std;

enum Word_Type { NOUN, VERB, ADJ, ADV, PREPOS };	// noun (���), verb(����), adjective(�����), adverb(�λ�) , preposition(��ġ��)
typedef list<string> List_Str;						// ����Ʈ �����̳� ������
typedef list<string> ::iterator Lst_Str_Itr;		// 

class MyVoca
{
	friend ostream& operator<<(ostream& ostr, MyVoca& mv)
	{
		// �ܾ��� ���¸� ǥ���ϴ� ���ڿ� �迭
		const string wd_ty[] = { "n", "v", "adj", "adv", "prepos" };

		Lst_Str_Itr itr;

		// �ܾ� ���� ����
		ostr << mv.KeyWord() << "(" << wd_ty[mv.type] << "):" << endl;

		// ���Ǿ� ���� 
		ostr << " - thesaurus(";
		for (itr = mv.thesaurus.begin(); itr != mv.thesaurus.end(); ++itr)
			ostr << *itr << ", ";
		ostr << ")" << endl;

		// ���� 
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
	string keyWord;		// �ܾ�
	Word_Type type;		// ����
	List_Str thesaurus;	// ���Ǿ�� 
	List_Str usages;	// ���ӻ�
};


#endif MY_VOCA_H