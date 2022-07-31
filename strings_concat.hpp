#pragma once
#include <vector>
#include <string>

template <typename StringType>
class strings_concat_helper
{
private:
	std::vector<const StringType*> data_pointers;
	std::vector<StringType> saved_strings;
public:
	size_t size() const
	{
		size_t res = 0;
		for (auto it : data_pointers) {
			res += it->size();
		}
		return res;
	}

	operator StringType() const
	{
		StringType result;
		result.reserve(size());

		for (auto str : data_pointers) {
			for (auto ch : *str) {
				result.push_back(ch);
			}
		}

		return result;
	}

	strings_concat_helper<StringType>&
		operator+(const StringType& other)
	{
		data_pointers.push_back(&other);
		return *this;
	}

	strings_concat_helper<StringType>&
		operator+(StringType&& other)
	{
		data_pointers.push_back(&saved_strings.emplace_back(other));
		return *this;
	}
};

using strings_concat = strings_concat_helper<std::string>;
using wstrings_concat = strings_concat_helper<std::wstring>;
