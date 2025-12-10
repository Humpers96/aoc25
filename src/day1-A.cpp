#include <iostream>
#include <fstream>
#include <string>

int next_number(const int i, const int movement)
{
	int normalised_movement = movement % 100;
	int result = i + normalised_movement;

	std::cout << "normalised move: " << normalised_movement << std::endl;

	if (result < 0)
	{
		result = (100 + result);
	}
	else if (result > 99)
	{
		result -= 100;
	}

	return result;
}

int main(int argc, char** argv)
{
	if (argc != 2)
	{
		std::cout << "incorrect usage." << std::endl;
		return -1;
	}

	std::cout << "in: " << argv[1] << std::endl;

	std::ifstream ifs(argv[1]);

	if (!ifs.is_open())
	{
		std::cout << "invalid filepath." << std::endl;
		return -1;
	}

	std::string line;
	int current_number = 50;
	int password = 0;

	while (std::getline(ifs, line))
	{
		std::cout << line <<std::endl;
		std::cout << "current number: " << current_number << std::endl;

		const char LR = line.front();
		int movement = std::stoi(line.substr(1, line.size()));

		if (LR == 'L')
		{
			current_number = next_number(current_number, movement * -1);
		}	
		else if (LR == 'R')
		{
			current_number = next_number(current_number, movement);
		}
		else
		{
			return -1;
		}

		if (current_number == 0)
		{
			password++;
		}

		std::cout << "result: " << current_number << std::endl;
	}

	std::cout << "password: " << password << std::endl;

	return 0;
}