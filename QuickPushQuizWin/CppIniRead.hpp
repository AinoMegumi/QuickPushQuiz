#ifndef __CPPINIREAD_HPP__
#define __CPPINIREAD_HPP__
#include "IniData.hpp"
#include <fstream>
#include <algorithm>
#include <type_traits>

class IniReadA {
private:
	std::map<std::string, IniDataA> IniDataList;
	void SkipUTF8Bom(std::ifstream& fs) {
		int dst[3];
		for (auto& i : dst) i = fs.get();
		constexpr int utf8[] = { 0xEF, 0xBB, 0xBF };
		if (!std::equal(std::begin(dst), std::end(dst), utf8)) fs.seekg(0);
	}
public:
	IniReadA() = default;
	IniReadA(const std::string& FilePath) {
		std::ifstream ifs(FilePath);
		if (!ifs.is_open()) throw std::runtime_error("Reserved file is not found.");
		this->SkipUTF8Bom(ifs);
		std::vector<std::string> LineStrings;
		for (std::string LineStr, RootKey; std::getline(ifs, LineStr);) {
			if (LineStr.empty()) continue;
			if (';' == LineStr.front()) continue; // 行の途中にあるケースはIniDataクラスで処理するが、先頭からの場合はスルー
			if ('[' == LineStr.at(0)) {
				if (!RootKey.empty()) this->IniDataList.emplace(RootKey, LineStrings);
				LineStrings.clear();
				RootKey = LineStr.substr(LineStr.find_first_of('[') + 1, LineStr.find_first_of(']') - 1);
			}
			else LineStrings.emplace_back(LineStr);
		}
	}
	std::string GetString(const std::string& Root, const std::string& Key, const std::string& DefaultStr) const noexcept {
		try {
			return this->IniDataList.at(Root).SearchOf(Key);
		}
		catch (...) {
			return DefaultStr;
		}
	}
	template<typename T, std::enable_if_t<std::is_integral_v<T> && std::is_signed_v<T>, std::nullptr_t> = nullptr>
	T GetNum(const std::string& Root, const std::string& Key, const T DefaultNum) const noexcept {
		try {
			return static_cast<T>(std::stoll(this->GetString(Root, Key)));
		}
		catch (...) {
			return DefaultNum;
		}
	}
	template<typename T, std::enable_if_t<std::is_unsigned_v<T>, std::nullptr_t> = nullptr>
	T GetNum(const std::string& Root, const std::string& Key, const T DefaultNum) const noexcept {
		try {
			return static_cast<T>(std::stoull(this->GetString(Root, Key)));
		}
		catch (...) {
			return DefaultNum;
		}
	}
	template<typename T, std::enable_if_t<std::is_floating_point_v<T>, std::nullptr_t> = nullptr>
	T GetNum(const std::string& Root, const std::string& Key, const T DefaultNum) const noexcept {
		try {
			return static_cast<T>(std::stold(this->GetString(Root, Key)));
		}
		catch (...) {
			return DefaultNum;
		}
	}
};

class IniReadW {
private:
	std::map<std::wstring, IniDataW> IniDataList;
public:
	IniReadW() = default;
	IniReadW(const std::wstring& FilePath) {
		std::wifstream ifs(FilePath);
		if (!ifs.is_open()) throw std::runtime_error("Reserved file is not found.");
		std::vector<std::wstring> LineStrings;
		for (std::wstring LineStr, RootKey; std::getline(ifs, LineStr);) {
			if (L';' == LineStr.front()) continue; // 行の途中にあるケースはIniDataクラスで処理するが、先頭からの場合はスルー
			if (L'[' == LineStr.at(0)) {
				if (!RootKey.empty()) this->IniDataList.emplace(RootKey, LineStrings);
				LineStrings.clear();
				RootKey = LineStr.substr(LineStr.find_first_of(L'[') + 1, LineStr.find_first_of(L']') - 1);
			}
			else LineStrings.emplace_back(LineStr);
		}
	}
	std::wstring GetString(const std::wstring& Root, const std::wstring& Key, const std::wstring& DefaultStr) const noexcept {
		try {
			return this->IniDataList.at(Root).SearchOf(Key);
		}
		catch (...) {
			return DefaultStr;
		}
	}
	template<typename T, std::enable_if_t<std::is_integral_v<T> && std::is_signed_v<T>, std::nullptr_t> = nullptr>
	T GetNum(const std::wstring& Root, const std::wstring& Key, const T DefaultNum) const noexcept {
		try {
			return static_cast<T>(std::stoll(this->GetString(Root, Key)));
		}
		catch (...) {
			return DefaultNum;
		}
	}
	template<typename T, std::enable_if_t<std::is_unsigned_v<T>, std::nullptr_t> = nullptr>
	T GetNum(const std::wstring& Root, const std::wstring& Key, const T DefaultNum) const noexcept {
		try {
			return static_cast<T>(std::stoull(this->GetString(Root, Key)));
		}
		catch (...) {
			return DefaultNum;
		}
	}
	template<typename T, std::enable_if_t<std::is_floating_point_v<T>, std::nullptr_t> = nullptr>
	T GetNum(const std::wstring& Root, const std::wstring& Key, const T DefaultNum) const noexcept {
		try {
			return static_cast<T>(std::stold(this->GetString(Root, Key)));
		}
		catch (...) {
			return DefaultNum;
		}
	}
};

#ifdef UNICODE
typedef IniReadW IniRead;
#else
typedef IniReadA IniRead;
#endif
#endif
