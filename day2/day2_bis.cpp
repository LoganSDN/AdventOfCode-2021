#include <iostream>
#include <cstring>
#include <fstream>
#include <vector>

int main(void)
{
	std::fstream				input;
	std::string					buffer;
	std::vector<std::string>	inputTab;

	input.open("input.txt");
	while(std::getline(input, buffer))
		inputTab.push_back(buffer);
	input.close();
	std::vector<std::string>::iterator beg = inputTab.begin();
	int hPos = 0, depth = 0, aim = 0;
	while (beg != inputTab.end())
	{
		size_t pos = (*beg).find(" ");
		std::string tmp = (*beg).substr(pos);
		(*beg).erase(pos);
		int sum = std::atoi(tmp.c_str());
		if ((*beg) == "forward")
		{
			hPos += sum;
			depth += (aim * sum);
		}
		else if ((*beg) == "down")
			aim += sum;
		else
			aim -= sum;
		beg++;
	}
	std::cout << depth * hPos << std::endl;
	return (0);
}