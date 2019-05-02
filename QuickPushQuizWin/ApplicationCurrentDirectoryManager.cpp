#include "ApplicationCurrentDirectoryManager.hpp"
#include "Win32Exception.hpp"

static inline std::string GetModuleFilePath() {
	std::string Buffer;
	Buffer.resize(MAX_PATH);
	if (0 == GetModuleFileNameA(NULL, &Buffer[0], MAX_PATH)) throw Win32Exception();
	Buffer.resize(std::strlen(Buffer.c_str()));
	return Buffer.substr(0, Buffer.find_last_of("\\") + 1);
}

static inline std::string GetApplicationCurrentDirectory() {
	std::string Buffer;
	Buffer.resize(MAX_PATH);
	if (0 == GetCurrentDirectoryA(MAX_PATH, &Buffer[0])) throw Win32Exception();
	Buffer.resize(std::strlen(Buffer.c_str()));
	return Buffer;
}

ApplicationCurrentDirectoryManager::ApplicationCurrentDirectoryManager(const bool UseModuleFilePath) 
	: CurrentDirectory(UseModuleFilePath ? GetModuleFilePath() : GetApplicationCurrentDirectory()){}

void ApplicationCurrentDirectoryManager::ChangeAppCurrentDirectory(const bool UseModuleFilePath) {
	this->CurrentDirectory = UseModuleFilePath ? GetModuleFilePath() : GetApplicationCurrentDirectory();
}

void ApplicationCurrentDirectoryManager::ChangeAppCurrentDirectory(const std::string& NewDirectory) {
	this->CurrentDirectory = NewDirectory;
}

std::string ApplicationCurrentDirectoryManager::ChangeFullPath(const std::string& RelativePath) const {
	return RelativePath.at(1) == ':' ? RelativePath : (this->CurrentDirectory + "\\" + RelativePath);
}

