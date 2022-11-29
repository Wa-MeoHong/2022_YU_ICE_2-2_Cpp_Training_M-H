#ifndef MY_VOCA_LIST_H
#define MY_VOCA_LIST_H

#include "MyVoca.h"
#define NUM_MY_TOEIC_VOCA 13

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
	/*MyVoca("access", NOUN, {"admission", "entry", "passage","ingress"}, {" access potnt", " Do not Access this area"}),
	MyVoca("independent", ADJ, {"separate"}, { "Two independent studies have been carried out."}),
	MyVoca("interact", ADJ, {"unrelated"}, {"irrelevant details"}),
	MyVoca("access", VERB, { "get", "acquire", "obtain"}, { "We can access the Internet wherever we are with our smart phone."}),
	MyVoca("ensure", VERB, { "make sure", "confirm", "certify"}, {"The company's sole concern is to ensure the safety of its employees" }),
	MyVoca("markedly", ADJ, {"noticeably", "obviously"}, {"The quality of their relationship improved markedly."}),
	MyVoca("name", NOUN, {"title"}, {"I don't even know if Sullivan is his real name."}),
	MyVoca("name", VERB, {"call", "christen"} ,{"My mother insisted on naming me Horace."}),
	MyVoca("handle", NOUN, {"opprotunity", "chance", "occasion"}, {"That's some handle to go through life with!"}),
	MyVoca("handle", VERB, {"manage", "deal with"} ,{"A new man was appointed to handle the crisis."}),
	MyVoca("ideal", NOUN , { "principle", "standard"} ,{"The party has drifted too far from its socialist ideals"}),
	MyVoca("ideal",ADJ, {"imaginary", "impractical", "poetic"} ,{"Their ideal society collapsed around them in revolution."}),
	MyVoca("knowledgeable", ADJ, {"well-informed", "acquainted", "aware"}, {"school-age children who were very knowledgeable about soccer"}),
	MyVoca("locate", VERB, {"find", "discover"}, {"We've simply been unable to locate him."}),
	MyVoca("overall", ADJ, {"total", "whole", "general"}, {"The council needs to cut down its overall spending."}),
	MyVoca("overall", ADV, {"generally", "mostly"}, {"Overall, I was disappointed with the result."}),
	MyVoca("precious", ADJ, {"valuable", "prized"}, {"jewellery and precious objects belonging to her mother"}),
	MyVoca("radical", ADJ, {"extreme"}, {"periods of radical change"}),
	MyVoca("universal", ADJ, {"widespread", "general"}, {"proposals for universal health care"}),
	MyVoca("decline", VERB, {"fall", "contract"}, {"a declining birth rate"})*/
};
#endif // !MY_VOCA_LIST_H
