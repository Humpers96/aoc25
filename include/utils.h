#pragma once
#include <vector>
#include <string>
#include <algorithm>

std::vector<std::string> split_string(const std::string& s, const char delim)
{
	size_t pos_first = *s.begin() == delim ? 1 : 0;
	size_t pos_last = s.find(delim);

	std::vector<std::string> ret;
	if (pos_last == std::string::npos)
	{
		ret.push_back(s.substr(pos_first, s.size()));
		return ret;
	}

	while (true)
	{
		ret.push_back(s.substr(pos_first, pos_last - pos_first));
		pos_first = pos_last + 1;

		if (size_t next_last = s.find(delim, pos_last + 1); next_last != std::string::npos)
		{
			pos_last = std::move(next_last);
		}
		else
		{
			ret.push_back(s.substr(pos_first, s.size() - pos_first));
			break;
		}
	}

	return ret;
}

std::vector<std::string> chunk_string(const std::string& s, int chunk_size)
{
	if (s.size() % chunk_size != 0 || chunk_size == s.size() || chunk_size == 0 || s.size() == 0 || chunk_size > s.size())
	{
		return {};
	}

	std::string::const_iterator it_first = s.begin();
	std::vector<std::string> ret;

	while (it_first != s.end())
	{
		int remaining = std::distance(it_first, s.end());
		int clamp = std::min(chunk_size, remaining);
		std::string::const_iterator it_last = it_first + clamp;

		ret.push_back(std::string(it_first, it_last));

		it_first = it_last;
	}

	return ret;
}

bool chunks_match(const std::vector<std::string>& chunks)
{
	bool match_next = true;
	std::vector<std::string>::const_iterator it = chunks.begin(); 

	if (it == chunks.end())
		return false;

	while (match_next)
	{
		auto& curr = it;
		auto next = curr + 1;

		if (next == chunks.end())
		{
			return match_next;
		}

		match_next = *curr == *next;
		++curr;
	}

	return match_next;
}