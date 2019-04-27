#ifndef __INIDATA_HPP__
#define __INIDATA_HPP__
#include "Split.hpp"
#include <utility>
#include <type_traits>
#include <map>

template<typename T, std::enable_if_t<std::is_same_v<T, char> || std::is_same_v<T, wchar_t>, std::nullptr_t> = nullptr>
static inline void RemoveReservedStrings(std::basic_string<T>& str, const T RemoveData) {
	const std::vector<std::basic_string<T>> List = SplitString(str, RemoveData);
	str.clear();
	for (const auto& i : List) str += i;
}

class IniDataA {
private:
	std::map<std::string, std::string> Data;
public:
	IniDataA(const std::vector<std::string> DataList) {
		auto ConvertPair = [](const std::string& LineData) -> std::pair<std::string, std::string> {
			auto p = std::make_pair(LineData.substr(0, LineData.find_first_of('=')), LineData.substr(LineData.find_first_of('=') + 1));
			if (p.first.find(';') != std::string::npos) return std::make_pair<std::string, std::string>("", "");
			else if (p.second.find(';')) p.second = p.second.substr(0, p.second.find_first_of(';'));
			RemoveReservedStrings(p.first, '\"');
			RemoveReservedStrings(p.second, '\"');
			return p;
		};
		for (const auto& i : DataList) {
			if (const auto Info = ConvertPair(i); !Info.first.empty()) this->Data.emplace(Info.first, Info.second);
		}
	}
	std::string SearchOf(const std::string Key) const {
		return this->Data.at(Key);
	}
};

class IniDataW {
private:
	std::map<std::wstring, std::wstring> Data;
public:
	IniDataW(const std::vector<std::wstring> DataList) {
		auto ConvertPair = [](const std::wstring & LineData) -> std::pair<std::wstring, std::wstring> {
			auto p = std::make_pair(LineData.substr(0, LineData.find_first_of(L'=')), LineData.substr(LineData.find_first_of(L'=') + 1));
			if (p.first.find(L';') != std::wstring::npos) return std::make_pair<std::wstring, std::wstring>(L"", L"");
			else if (p.second.find(L';')) p.second = p.second.substr(0, p.second.find_first_of(L';'));
			RemoveReservedStrings(p.first, L'\"');
			RemoveReservedStrings(p.second, L'\"');
			return p;
		};
		for (const auto& i : DataList) {
			if (const auto Info = ConvertPair(i); !Info.first.empty()) this->Data.emplace(Info.first, Info.second);
		}
	}
	std::wstring SearchOf(const std::wstring Key) const {
		return this->Data.at(Key);
	}
};
#endif
