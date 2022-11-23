#include <iostream>
#include <cstring>
#include <fstream>
#include <vector>
#include <list>

#define PAIR_PT std::pair<std::pair<int, int>, std::pair<int, int> >
#define PT std::pair<int, int>

class grid
{
private:
	size_t	size;
	size_t	height;
	size_t	col;
	int		**tab;

public:
	grid(PT corner) : height(corner.second), col(corner.first) 
	{
		size = height * col;
		tab = new int*[height];
		for(int i = 0; i < height; ++i)
   			tab[i] = new int[col];
		for (int i = 0; i < height; i++)
    	    for (int j = 0; j < col; j++) 
        		tab[i][j] = 0;
	}

	~grid()
	{
		for (int i = 0; i < height; i++)
				delete tab[i];
		delete[] tab;
	}
	void displayGrid()
	{
		for (size_t i = 0; i < height; i++)
		{
			for (size_t j = 0; j < col; j++)
				std::cout << tab[i][j] << "";
			std::cout << "\n";
		}
	}
	void drawVert(PAIR_PT pts)
	{
		int x1 = pts.first.first, x2 = pts.second.first, y1 = pts.first.second, y2 = pts.second.second;
		if (y1 > y2)
			while (y1 >= y2)
				tab[y1--][x1] += 1;
		else
			while (y1 <= y2)
				tab[y1++][x1] += 1;
	}
	void drawHorz(PAIR_PT pts)
	{
		int x1 = pts.first.first, x2 = pts.second.first, y1 = pts.first.second, y2 = pts.second.second;
		if (x1 > x2)
			while (x1 >= x2)
				tab[y1][x1--] += 1;
		else
			while (x1 <= x2)
				tab[y1][x1++] += 1;
	}
	void drawDiag(PAIR_PT pts)
	{
		int x1 = pts.first.first, x2 = pts.second.first, y1 = pts.first.second, y2 = pts.second.second;
		if (x1 < x2 && y1 < y2)
			while (x1 <= x2 && y1 <= y2)
				tab[y1++][x1++] += 1;
		else if (x1 > x2 && y1 < y2)
			while (x1 >= x2 && y1 <= y2)
				tab[y1++][x1--] += 1;
		else if (x1 > x2 && y1 > y2)
			while (x1 >= x2 && y1 >= y2)
				tab[y1--][x1--] += 1;
		else if (x1 < x2 && y1 > y2)
			while (x1 <= x2 && y1 >= y2)
				tab[y1--][x1++] += 1;

	}
	void answer()
	{
		size_t i = 0, j = 0, out = 0;
		
		for (size_t i = 0; i < height; i++)
			for (size_t j = 0; j < col; j++)
				if (tab[i][j] > 1)
					out++;
		std::cout << "answer : " << out << std::endl;
	}
};

PT makePairNb(std::string str)
{
	size_t pos = str.find(',');
	return (std::make_pair<int, int>(std::atoi(str.substr(0, pos).c_str()), std::atoi(str.substr(pos + 1).c_str())));
}

PAIR_PT extractNb(std::string str)
{
	std::string::iterator beg = str.begin();

	size_t pos = str.find("->");
	PT X1Y1 = makePairNb(str.substr(0, pos));
	while (!std::isdigit(str[pos]))
		pos++;
	PT X2Y2 = makePairNb(str.substr(pos));
	return (PAIR_PT(X1Y1, X2Y2));
}

void	displayPairPt(PAIR_PT pr)
{
	std::cout	<< pr.first.first << " " << pr.first.second << " | "\
				<< pr.second.first << " " << pr.second.second << std::endl;
}

PT max(std::list<PAIR_PT> lst)
{
	std::list<PAIR_PT>::iterator beg = lst.begin();
	PT max(0, 0);
	while (beg != lst.end())
	{
		if ((*beg).first.first > max.first)
			max.first = (*beg).first.first;
		else if ((*beg).second.first  > max.first)
			max.first = (*beg).second.first;
		else if ((*beg).first.second > max.second) 
			max.second = (*beg).first.second;
		else if ((*beg).second.second > max.second) 
			max.second = (*beg).second.second;
		beg++;
	}
	return (PT(max.first + 1, max.second + 1));
}

void draw(PAIR_PT pts, grid *gr)
{
	int x1 = pts.first.first, x2 = pts.second.first, y1 = pts.first.second, y2 = pts.second.second;
	if (x1 != x2 && y1 != y2)
		gr->drawDiag(pts);	
	if (x1 == x2)
		gr->drawVert(pts);
	else if (y1 == y2)
		gr->drawHorz(pts);
}

int main(void)
{
	std::fstream				input;
	std::string					buffer;
	std::vector<std::string>	inputTab;
	std::list<PAIR_PT>			lstNb;

	input.open("input.txt");
	while(std::getline(input, buffer))
		inputTab.push_back(buffer);
	input.close();
	for (std::vector<std::string>::iterator beg = inputTab.begin(); beg != inputTab.end(); beg++)
		lstNb.push_back(extractNb(*beg));
	grid	gr(max(lstNb));
	for (std::list<PAIR_PT>::iterator it = lstNb.begin(); it != lstNb.end(); it++)
		draw(*it, &gr);
	gr.displayGrid();
	gr.answer();
	return (0);
}