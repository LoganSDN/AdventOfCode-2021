#include <iostream>
#include <cstring>
#include <fstream>
#include <vector>
#include <list>

# define RESET			"\033[0m"
# define BLACK			"\033[30m"
# define RED			"\033[31m"
# define GREEN			"\033[32m"
# define YELLOW			"\033[33m"
# define BLUE			"\033[34m"
# define MAGENTA		"\033[35m"
# define CYAN			"\033[36m"
# define WHITE			"\033[37m"
# define BOLDBLACK		"\033[1m\033[30m"
# define BOLDRED		"\033[1m\033[31m"
# define BOLDGREEN		"\033[1m\033[32m"
# define BOLDYELLOW		"\033[1m\033[33m"
# define BOLDBLUE		"\033[1m\033[34m"
# define BOLDMAGENTA	"\033[1m\033[35m"
# define BOLDCYAN		"\033[1m\033[36m"
# define BOLDWHITE		"\033[1m\033[37m"

class cell
{
	private:
		int		nb;
		bool	marked;
	public:
		cell(int nb) : nb(nb), marked(false) { }
		~cell() { }

		bool	getMarked()		{ return(marked); }
		int		getNb()			{ return(nb); }
		void	markedCell()	{ marked = true; }
};

class grid
{
private:
	size_t	height;
	size_t	column;

	std::vector<std::vector<cell> > map;
public:
	grid() : height(0), column(0), map(1) {}

	~grid()
	{
	}

	void addNb(int nb) { map[height].push_back(cell(nb)); }
	void newLine() { map.resize(map.size() + 1); height++; }
	void displayLine(std::vector<cell> ln)
	{
		std::vector<cell>::iterator beg = ln.begin();
		while (beg != ln.end())
		{
			(*beg).getMarked() ? std::cout << BOLDGREEN : std::cout << BOLDRED;
			std::cout << (*beg).getNb() << RESET << " ";
			beg++;
		}
		std::cout << "\n";
	}
	void displayGrid()
	{
		size_t i = 0;
		while (i < height)
			displayLine(map[i++]);
	}
	void clean()
	{
		size_t i = 0;
		while (i < height)
			map[i++].clear();
		height = 0;
	}
	void markNb(int nb)
	{
		size_t i = 0;
		while (i < height)
		{
			size_t j = 0;
			while (j < map[i].size())
			{
				if (map[i][j].getNb() == nb)
					map[i][j].markedCell();
				j++;
			}
			i++;
		}
	}
	bool checkLine(std::vector<cell> ln)
	{
		std::vector<cell>::iterator beg = ln.begin();
		int len = 0;

		while (beg != ln.end())
		{
			if ((*beg).getMarked())
				len++;
			beg++;
		}
		return (len == ln.size());
	}
	bool checkCol(std::vector<std::vector<cell> > gr)
	{
		size_t i = 0, j = 0;
		while (j < map[i].size())
		{
			while (i < height && map[i][j].getMarked())
				i++;
			if (i == height)
				return (true);
			i = 0;
			j++;
		}
		return (false);
	}
	bool checkWin()
	{
		size_t i = 0;
		while (i < height)
		{
			if (checkLine(map[i]))
				return (true);
			i++;
		}
		return (checkCol(map) ? true : false);
	}
	int answer(int nb)
	{
		int unmarked = 0;
		size_t i = 0, j = 0;

		while (i < height)
		{
			while (j < map[i].size())
			{
				if (!map[i][j].getMarked())
					unmarked += map[i][j].getNb();
				j++;
			}
			j = 0;
			i++;
		}
		return (unmarked * nb);
	}
};

std::string cleanStr(std::string str)
{
	std::string::iterator it = str.begin();
	for (; (*it) == ' ' && it != str.end(); it++);
	if (it == str.begin())
		return (str);
	str.erase(str.begin(), it);
	return (std::string(str));
}

std::list<int> extractNb(std::string str, char c)
{
	std::string::iterator beg = str.begin();
	std::list<int> winNb;
	std::string nb;

	while (beg != str.end())
	{
		if ((*beg) == c)
		{
			winNb.push_back(std::atoi(nb.c_str()));
			str.erase(str.begin(), beg + 1);
			beg = str.begin();
			nb.clear();
		}
		nb += (*beg);
		beg++;
	}
	winNb.push_back(std::atoi(nb.c_str()));
	return (winNb);
}

void addNb(std::list<int> lst, grid *gr)
{
	std::list<int>::iterator it = lst.begin();
	while (it != lst.end())
	{
		gr->addNb((*it));
		it++;
	}
}

void markedNb(int nb, std::vector<grid> *vecGr)
{
	std::vector<grid>::iterator beg = vecGr->begin();

	while (beg != vecGr->end())
	{
		(*beg).markNb(nb);
		beg++;
	}
}

bool checkWin(int nb, std::vector<grid> *vecGr)
{
	std::vector<grid>::iterator beg = vecGr->begin();

	while (beg != vecGr->end())
	{
		if ((*beg).checkWin())
		{
			if (vecGr->size() == 2)
			{
				(*beg).displayGrid();
				std::cout << "Answer(nb * unmarked) : " << (*beg).answer(nb) << std::endl;
				return (true);
			}
			else
			{
				vecGr->erase(beg);
				beg = vecGr->begin();
			}
		}
		else
			beg++;
	}
	return (false);
}

void routine(std::list<int> winNb, std::vector<grid> *vecGr)
{
	std::list<int>::iterator lst = winNb.begin();

	while (lst != winNb.end())
	{
		markedNb(*lst, vecGr);
		if (checkWin(*lst, vecGr))
			return ;
		lst++;
	}
}

int main(void)
{
	std::fstream				input;
	std::string					buffer;
	std::vector<std::string>	inputTab;
	std::list<int>				winNb;

	input.open("input.txt");
	while(std::getline(input, buffer))
		inputTab.push_back(buffer);
	input.close();
	winNb = extractNb(inputTab[0], ',');
	grid gr;
	std::vector<grid> vecGr;
	std::vector<std::string>::iterator it = inputTab.begin() + 1;
	for (; it != inputTab.end(); it++)
	{
		*it = cleanStr(*it);
		std::list<int> tmp = extractNb(*it, ' ');
		if (tmp.size() > 1)
		{
			addNb(tmp, &gr);
			gr.newLine();
		}
		else
		{
			vecGr.push_back(gr);
			gr.clean();
		}
	}
	std::list<int> tmp = extractNb(*it, ' ');
	if (tmp.size() > 1)
	{
		addNb(tmp, &gr);
		gr.newLine();
	}
	else
	{
		vecGr.push_back(gr);
		gr.clean();
	}
	routine(winNb, &vecGr);
	return (0);
}