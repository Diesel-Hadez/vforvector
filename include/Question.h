#ifndef QUESTION_H
#define QUESTION_H
#include <string>

struct Question {
		std::string m_Question;
		std::vector<std::string> m_Answers;
		std::size_t correctIndex;
};
#endif
