#include <iostream>
#include <cstring>
#include <fstream>
#include <vector>

int main(void)
{
	std::fstream		input;
	std::string			buffer;
	std::vector<int>	inputTab, sumTab;
	int					out = 0;

	input.open("input.txt");
	while(std::getline(input, buffer))
		inputTab.push_back(std::atoi(buffer.c_str()));
	input.close();
	std::vector<int>::iterator beg = inputTab.begin();
	std::vector<int>::iterator tmp = beg;
	int sum = 0, stop = 0;
	while (beg != inputTab.end())
	{
		if (!stop)
		{
			tmp = beg;
			while (stop++ < 3)
			{
				if (beg != inputTab.end())
					sum += *(beg++);
			}
			sumTab.push_back(sum);
			if (beg == inputTab.end())
				break;
			beg = tmp;
			sum = 0;
			stop = 0;
		}
		beg++;
	}
	beg = sumTab.begin();
	tmp = beg;
	while (beg != sumTab.end())
	{
		if (*beg > *tmp)
			out++;
		tmp = beg++;
	}
	std::cout << out << std::endl;
	return (0);
}