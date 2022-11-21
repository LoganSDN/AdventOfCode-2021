#include <iostream>
#include <cstring>
#include <fstream>
#include <vector>

void	cleanTab(std::vector<std::string> *tab, size_t pos, char c)
{
	std::vector<std::string>::iterator beg = tab->begin();
	while (beg != tab->end())
	{
		if ((*beg).at(pos) == c)
		{
			tab->erase(beg);
			beg = tab->begin();
		}
		else
			beg++;
	}
}

size_t compute(std::vector<std::string> *inputTab, bool opt)
{
	int i = 0;
	size_t len = inputTab->at(0).length();
	std::vector<std::string> binTab(1, "");
	std::vector<std::string>::iterator beg = inputTab->begin();
	while (beg != inputTab->end())
	{
		binTab[i].push_back((*beg)[i]);
		beg++;
		if (beg == inputTab->end())
		{
			std::string::iterator it = binTab[i].begin();
			int x = 0, y = 0;
			while(it != binTab[i].end())
			{
				if ((*it) == '1')
					x++;
				else
					y++;
				it++;
			}
			if (opt)
				cleanTab(inputTab, i, (y <= x ? '1' : '0'));
			else
				cleanTab(inputTab, i, (x >= y ? '0' : '1'));
			beg = inputTab->begin();
			i++;
			if (i >= len || inputTab->size() == 1)
				break;
			binTab.push_back("");
		}
	}
	return (std::stol(inputTab->at(0), 0, 2));
}

int main(void)
{
	std::fstream				input;
	std::string					buffer;
	std::vector<std::string>	inputTab;

	input.open("input.txt");
	while(std::getline(input, buffer))
		inputTab.push_back(buffer);
	input.close();
	std::vector<std::string>	CSR(inputTab), OGR(inputTab);
	std::cout << compute(&CSR, true) * compute(&OGR, false) << std::endl;
	return (0);
}