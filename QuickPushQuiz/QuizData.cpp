#include "QuizData.hpp"
#include "HandleManager.hpp"
#include <rapidjson/document.h>

QuizData::QuizData(const std::string& FilePath) {
	rapidjson::Document doc{};
	doc.Parse(FilePath.c_str());
	if (const bool error = doc.HasParseError(); error) throw std::runtime_error("Failed to parse " + FilePath);
	this->Question = doc["quiz"].GetString();
	const rapidjson::Value& answerdata = doc["answers"];
	if (4u != answerdata.Size()) throw std::runtime_error("answer data is wrong.");
	for (unsigned int i = 0u; i < 4u; i++) this->AnswerGroup[i] = answerdata[i].GetString();
	this->CorrectAnswer = standard::number<unsigned short>(doc["correct"].GetInt(), 0, 4);
}

static inline void ReleaseHandle(HANDLE handle) { FindClose(handle); }

std::vector<QuizData> QuizData::LoadQuizData(const std::string& QuizRootDir) {
	WIN32_FIND_DATAA Find{};
	HandleManager<ReleaseHandle> hFind = FindFirstFileA(QuizRootDir.c_str(), &Find);
	if (INVALID_HANDLE_VALUE == hFind) return {};
	std::vector<QuizData> DataArr;
	do {
		if (Find.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) continue;
		DataArr.emplace_back(Find.cFileName);
	} while (FALSE != FindNextFileA(hFind.Get(), &Find));
	return DataArr;
}
