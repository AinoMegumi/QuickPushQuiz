#include "QuizData.hpp"
#ifdef WIN32
#include "HandleManager.hpp"
#else
#include <sys/stat.h>
#include <dirent.h>
#endif
#include <rapidjson/document.h>

QuizData::QuizData(const std::string& FilePath) {
	rapidjson::Document doc{};
	doc.Parse(FilePath.c_str());
	const bool error = doc.HasParseError(); 
	if(error) throw std::runtime_error("Failed to parse " + FilePath);
	this->Question = doc["quiz"].GetString();
	const rapidjson::Value& answerdata = doc["answers"];
	if (4u != answerdata.Size()) throw std::runtime_error("answer data is wrong.");
	for (unsigned int i = 0u; i < 4u; i++) this->AnswerGroup[i] = answerdata[i].GetString();
	this->CorrectAnswer = standard::number<unsigned short>(doc["correct"].GetInt(), 0, 4);
}

#ifdef WIN32
static inline void ReleaseHandle(HANDLE handle) { FindClose(handle); }
#endif
static inline bool isReservedExtensionFile(const std::string& Path, const std::string& Extension) {
	return Path.substr(Path.find_last_of(".")) == Extension;
}

std::vector<QuizData> QuizData::LoadQuizData(const std::string& QuizRootDir) {
#ifdef WIN32
	WIN32_FIND_DATAA Find{};
	HandleManager hFind = { FindFirstFileA(QuizRootDir.c_str(), &Find), ReleaseHandle };
	if (INVALID_HANDLE_VALUE == hFind) return {};
	std::vector<QuizData> DataArr;
	do {
		if (Find.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) continue;
		if (isReservedExtensionFile(Find.cFileName, ".json")) DataArr.emplace_back(Find.cFileName);
	} while (FALSE != FindNextFileA(hFind.Get(), &Find));
#else
	dirent** namelist{};
	const int dirElements = scandir(QuizRootDir.c_str(), &namelist, nullptr, nullptr);
	if (dirElements == -1) return {};
	std::vector<QuizData> DataArr{};
	for (int i = 0; i < dirElements; i++) {
		struct stat statbuf {};
		const std::string SearchPath = QuizRootDir + namelist[i]->d_name;
		if (0 != stat(SearchPath.c_str(), &statbuf)) continue;
		if (0 == (statbuf.st_mode & S_IFMT)) continue;
		if (isReservedExtensionFile(SearchPath, ".json")) DataArr.emplace_back(SearchPath);
	}
#endif 
	return DataArr;
}
