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
	std::vector<std::string> binTab(1, "");
	int i = 0, j = 0;
	while (beg != inputTab.end())
	{
		binTab[i].push_back((*beg)[j]);
		beg++;
		if (beg == inputTab.end())
		{
			beg = inputTab.begin();
			i++;
			j++;
			if (i >= inputTab[0].length())
				break;
			binTab.push_back("");
		}
	}
	beg = binTab.begin();
	std::string::iterator ite;
	std::string gamma, epsilon;
	while (beg != binTab.end())
	{
		int x = 0, y = 0;
		ite = (*beg).begin();
		while (ite != (*beg).end())
		{
			if (*(ite++) == '1')
				x++;
			else
				y++;
		}
		(x > y) ? gamma.push_back('1') : gamma.push_back('0');
		(x > y) ? epsilon.push_back('0') : epsilon.push_back('1');
		beg++;
	}
	std::cout << std::stoi(gamma, 0, 2) * std::stoi(epsilon, 0, 2) << std::endl;
	return (0);
}