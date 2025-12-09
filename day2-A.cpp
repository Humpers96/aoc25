#include "utils.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

struct range
{
	const long first_i;
	const long second_i;

	long total() const
	{
		return second_i - first_i;
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

	long password = 0;
	long total_iterations = 0;
	long iterations = 0;

	for (const auto& id_range : id_ranges)
		total_iterations += id_range.total();

	int percentage = 0;

	for (const auto& id_range : id_ranges)
	{
		for (long i = id_range.first_i; i < id_range.second_i; i++)
		{
			std::cout << percentage << "% done" << std::endl;
			iterations++;

			std::string i_str = std::to_string(i);

			if (i_str.size() % 2 != 0)
				continue;
			
			size_t str_length = i_str.size();
			size_t half = str_length / 2;

			std::string first_half = i_str.substr(0, half);
			std::string second_half = i_str.substr(half, i_str.size());

			if (first_half == second_half)
				password += i;
		
			percentage = ((float)iterations / (float)total_iterations) * 100;
		}
	}

	std::cout << "password: " << password << std::endl;
	return 0;
}