#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <map>
#include <vector>
#include <tuple>
#include<algorithm>

using namespace std;

class BalanceScale
{
	map<string, pair<pair<string, string>, int>> m_InputDataMap;
	map<string, tuple<long, long, long>> m_OutputDataMap;

	bool isNumericString(const string& s)
	{
		return !s.empty() && find_if(s.begin(), s.end(), [](unsigned char c) { return !std::isdigit(c); }) == s.end();
	}

	int balanceScale(const string& scale_name, const pair<string, string>& wts)
	{
		constexpr short SCALE_WT(1);
		long left = 0, right = 0;

		if (!isNumericString(wts.first) && !isNumericString(wts.second))
		{
			auto it = m_OutputDataMap.find(wts.first);
			if (it == m_OutputDataMap.end())
				return -1;
			else
			{
				left = get<2>(it->second);
			}

			it = m_OutputDataMap.find(wts.second);
			if (it == m_OutputDataMap.end())
				return -1;
			else
			{
				right = get<2>(it->second);
			}
		}
		else if (!isNumericString(wts.first) && isNumericString(wts.second))
		{
			auto it = m_OutputDataMap.find(wts.first);
			if (it == m_OutputDataMap.end())
				return 0;
			else
			{
				left = get<2>(it->second);
				right = abs(stol(wts.second));
			}
		}
		else if (isNumericString(wts.first) && !isNumericString(wts.second))
		{
			auto it = m_OutputDataMap.find(wts.second);
			if (it == m_OutputDataMap.end())
				return 0;
			else
			{
				right = get<2>(it->second);
				left = abs(stol(wts.first));
			}
		}
		else
		{
			left = abs(stol(wts.first));
			right = abs(stol(wts.second));
		}


		long difference = abs(left - right);
		long total = left + right + difference + SCALE_WT;
		if (left > right)
			m_OutputDataMap[scale_name] = make_tuple(0, difference, total);
		else
			m_OutputDataMap[scale_name] = make_tuple(difference, 0, total);

		return 1;
	}

public:
	void parseAndStoreTokens(const string file_name)
	{
		ifstream myfile(file_name);
		string line;
		if (myfile.is_open())
		{
			while (getline(myfile, line))
			{
				std::stringstream linestr(line);
				if ((!linestr) || (linestr.str()[0] == '#'))
					continue;

				std::string token, firstToken;
				vector<string> tmpVec;
				while (getline(linestr, token, ','))
					tmpVec.push_back(token);

				if(tmpVec.size() == 3)
					m_InputDataMap[tmpVec[0]] = make_pair(make_pair(tmpVec[1], tmpVec[2]), 0);
			}

			
		}
		else
			cout << "Couldn't open input file\n";

		myfile.close();
	}

	void iterateInputDataMap()
	{
		//iterate through input for all the records which is not balanced
		int iBalancedNodeCnt = 0;
		while (true)
		{
			bool isAnyNodeBalanced = false;
			for (auto& element : m_InputDataMap)  // iterate over map elements
			{
				string key = element.first;
				pair<pair<string, string>, int>& val_type = element.second;

				if (!val_type.second) //dont enter if already balanced
				{
					if (val_type.second = balanceScale(key, val_type.first))
						iBalancedNodeCnt++;
				}
			}

			if (m_InputDataMap.size() == iBalancedNodeCnt)
				break;
		}

		//now check if there are any nodes which have not yet be processed ..i.e. having -1 flag...
		for (auto& element : m_InputDataMap)  // iterate over map elements
		{
			string key = element.first;
			pair<pair<string, string>, int>& val_type = element.second;

			if (val_type.second < 0)
			{
				val_type.second = balanceScale(key, val_type.first);
				if (val_type.second < 0)
				{
					cout << "Error: both the scale wts can't be non numeric for scale: " << key << ". Left: " << val_type.first.first << " and Right : " << val_type.first.second;
				}
			}
		}
	}

	void displayOutput()
	{
		for (auto it = m_OutputDataMap.cbegin(); it != m_OutputDataMap.cend(); ++it)
		{
			std::cout << it->first << "," << get<0>(it->second) << "," << get<1>(it->second)<< "\n";
		}
	}
};


int main()
{
	std::string line;
	cout << "Specify file name: " << endl;
	while (std::getline(std::cin, line))
	{
		BalanceScale balScale;
		balScale.parseAndStoreTokens(line);// InputScaleData.txt
		balScale.iterateInputDataMap();
		balScale.displayOutput();

		cout << "\nSpecify file name: " << endl;
	}

	return 0;
}