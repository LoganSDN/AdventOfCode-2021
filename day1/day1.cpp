#include <iostream>
#include <cstring>
#include <fstream>
#include <vector>

int main(void)
{
	std::fstream		input;
	std::string			buffer;
	std::vector<int>	inputTab;
	int					out = 0;

	input.open("input.txt");
	while(std::getline(input, buffer))
		inputTab.push_back(std::atoi(buffer.c_str()));
	input.close();
	std::vector<int>::iterator beg = inputTab.begin();
	std::vector<int>::iterator tmp = beg;
	while (beg != inputTab.end())
	{
		if (*beg > *tmp)
			out++;
		tmp = beg++;
	}
	std::cout << out << std::endl;
	return (0);
}