#ifndef MY_VOCA_LIST_H
#define MY_VOCA_LIST_H

#include "MyVoca.h"

int NUM_MY_TOEIC_VOCA = 13;
MyVoca myToeicVocaList[] =
{
	MyVoca("mean", NOUN, { "average", "norm", "median", "middle", "midpoint", "(ant) extremity" }, \
		{ "the mean error", "the golden mean", "the arithmetical mean", "the geometric mean" }),
	MyVoca("mean", ADJ, { "nasty", "poor", "middle", "miserly", "paltry" }, { "a man of mean intelligence", "a mean appearance" }),
	MyVoca("mean", VERB, { "require", "denote", "intend" }, { "What do you mean by \"perfect\" \?" }),
	MyVoca("offer", NOUN, { "proposal" }, { "He accepted out offer to write the business plan." }),
	MyVoca("offer", VERB, { "to propose" }, { "She must offer her banker new statistics in order to satisfy the bank's requirement for the loan." }),
	MyVoca("compromise", NOUN, { "give-and-take", "bargaining", "accommodation" }, { "The couple made a compromise and ordered food to take out." }),
	MyVoca("compromise", VERB, { "settle", "conciliate", "find a middle ground" }, \
		{ "He does not like sweet dishes so I compromised by adding just a small amount of sugar." }),
	MyVoca("delegate", NOUN, { "representative", "agent", "substitute" }, { "" }),
	MyVoca("delegate", VERB, { "authorize", "appoint", "designate" }, { "" }),
	MyVoca("foster", VERB, { "nurture", "raise", "promote", "advance" }, { "" }),
	MyVoca("foster", ADJ, { "substitute", "adoptive", "stand-in" }, { "" }),
	MyVoca("imperative", ADJ, { "authoritative", "vital" }, { "" }),
	MyVoca("imperative", NOUN, { "necessity", "essential", "requirement" }, { "" })
	//{ "-1", NOUN, { "" }, { "" } }, // end sentinel
};

#endif // !MY_VOCA_LIST_H

