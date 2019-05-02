#pragma once
#include <string>

class ApplicationCurrentDirectoryManager {
private:
	std::string CurrentDirectory;
public:
	ApplicationCurrentDirectoryManager(const bool UseModuleFilePath = false);
	// カレントディレクトリをモジュールパスに変更する
	void ChangeAppCurrentDirectory(const bool UseModuleFilePath = false);
	// カレントディレクトリを指定パスにする
	void ChangeAppCurrentDirectory(const std::string& NewDirectory);
	// 相対パスを絶対パスに変更する
	std::string ChangeFullPath(const std::string& RelativePath) const;
};
