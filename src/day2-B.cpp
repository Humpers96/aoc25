#include "utils.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

struct range
{
	const long first_i;
	const long second_i;

	long total() const
	{
		return second_i - first_i + 1;
	}

	std::vector<std::string> string_range() const
	{
		if (first_i == second_i)
			return {};
		
		std::vector<std::string> ret;

		for (long i = first_i; i < second_i + 1; i++)
		{
			ret.push_back(std::to_string(i));
		}

		return ret;
	}
};

int main(int argc, char** argv)
{
	if (argc != 2)
	{
		std::cout << "invalid usage." << std::endl;
		return -1;
	}

	std::ifstream ifs(argv[1]);

	if (!ifs.is_open())
	{
		std::cout << "invalid input." << std::endl;
		return -1;
	}

	std::string file_contents;
	std::getline(ifs, file_contents);
	ifs.close();

	std::vector<std::string> splits = split_string(file_contents, ',');
	std::vector<range> id_ranges;
		
	for (const auto& split : splits)
	{
		auto pair = split_string(split, '-');

		if (pair.size() != 2)
		{
			std::cout << split << ": failed on split to pair" << std::endl;
		}

		id_ranges.push_back({ std::stol(pair.front()), std::stol(pair.back()) });
	}

	unsigned long total_iterations = 0;

	for (const auto& range : id_ranges)
	{
		total_iterations += range.total();
	}

	unsigned long current_iterations = 0;
	std::vector<long> invalid_ids;

	for (const auto& range : id_ranges)
	{
		for (long i = range.first_i; i < range.second_i + 1; i++)
		{
			current_iterations++;
			static int percentage = ((float)current_iterations / (float)total_iterations) * 100;
			
			if (int pcg = ((float)current_iterations / (float)total_iterations) * 100; pcg % 10 == 0 && pcg != percentage)
			{
				std::cout << pcg << "% done" << std::endl;
				percentage = pcg;
			}

			auto i_string = std::to_string(i);
			auto s_size = i_string.size();

			for (int j = s_size; j > 0; j--)
			{
				auto string_vec = chunk_string(i_string, j);
				
				if (string_vec.empty())
					continue;
				
				if (chunks_match(string_vec))
				{
					invalid_ids.push_back(i);
					break;
				}
			}
		}
	}

	unsigned long password = 0;

	for (const auto& id : invalid_ids)
	{
		password += id;
	}

	std::cout << std::endl << "password: " << password << std::endl;

	return 0;
}