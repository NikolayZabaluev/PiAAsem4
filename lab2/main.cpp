#include <iostream>
#include <vector>
#include <windows.h>
#include <ctime>

using namespace std;
bool finished = false;

bool is_a_solution(vector<int> sequence, int d)
{
    int n = sequence.size();
	int last = sequence.back();
	if ((n==d*d) && (last==(2*d+1)))
	{
		return true;
	}
	return false;
}

void process_solution(vector<int> sequence, int d)
{
	cout<<"\nНайдено решение!"<<endl;
	for (int i=0; i<d*d; i++)
	{
		cout<<sequence[i]<<" ";
		if ((i+1)%d==0)
		{
			cout<<endl;
		}
	}
	finished = true;
}

void construct_candidates (vector<int> sequence, vector<bool> available_cells, int d, vector<int> &candidates)
{
    int last = sequence.back();
    if(last/d > 1)
    {
        if((last%d >= 1) && (available_cells[last-2*d-1] == 0))
        {
        candidates.push_back(last-2*d-1);
        }
        if((last%d <= d-2) && (available_cells[last-2*d+1] == 0))
        {
            candidates.push_back(last-2*d+1);
        }
    }
    if(last%d < d-2)
    {
        if((last/d >=1) && (available_cells[last-d+2] == 0))
        {
            candidates.push_back(last-d+2);
        }
        if((last/d <= d-2) && (available_cells[last+d+2] == 0))
        {
            candidates.push_back(last+d+2);
        }
    }
    if(last/d < d-2)
    {
        if((last%d <= d-2) && (available_cells[last+2*d+1] == 0))
        {
            candidates.push_back(last+2*d+1);
        }
    if((last%d >= 1) && (available_cells[last+2*d-1] == 0))
        {
            candidates.push_back(last+2*d-1);
        }
    }
    if(last%d > 1)
    {
        if((last/d <= d-2) && (available_cells[last+d-2] == 0))
        {
            candidates.push_back(last+d-2);
        }
        if((last/d >= 1) && (available_cells[last-d-2] == 0))
        {
            candidates.push_back(last-d-2);
        }
    }

    for(int i=0; i<candidates.size(); i++)
    {
        if ((sequence.size()!=d*d-1) && (candidates.at(i)==(2*d+1)))
        {
            candidates.erase (candidates.begin()+i);
            break;
        }
        if (candidates.at(i)==(d-1))
        {
            candidates.clear();
            candidates.push_back(d-1);
            break;
        }
        if (candidates.at(i)==(d*d-1))
        {
            candidates.clear();
            candidates.push_back(d*d-1);
            break;
        }
        if (candidates.at(i)==((d-1)*d))
        {
            candidates.clear();
            candidates.push_back((d-1)*d);
            break;
        }
    }
}
void sort_candidates(vector<int> sequence, vector<bool> available_cells, int d, vector<int> &candidates)
{
    int a=7;
    int b=candidates.size();
    vector<int> next_candidates;

    for (int i=0; i<b; i++)
		{
		    sequence.push_back(candidates.at(i));
		    construct_candidates(sequence, available_cells, d, next_candidates);
		    if (next_candidates.size()<a)
            {
                a=next_candidates.size();
                swap(candidates.at(i), candidates.front());
            }
            sequence.pop_back();
		}
}

void backtrack( vector<int> sequence, vector<bool> available_cells, int d)
{
	vector<int> candidates;
	if (is_a_solution(sequence, d))
	{
		process_solution(sequence, d);

	}
	else
	{
		construct_candidates(sequence, available_cells, d, candidates);
		sort_candidates(sequence, available_cells, d, candidates);
		for (int i=0; i<candidates.size(); i++)
		{
			sequence.push_back(candidates.at(i));
			available_cells[sequence.back()]=1;
			backtrack(sequence, available_cells, d);
			available_cells[sequence.back()]=0;
			sequence.pop_back();
			if (finished) return;
		}
	}
}

int main()
{
    setlocale(LC_ALL, "Russian");
	int d=0;
	cout<<"Введите размер доски (d>=6): "<<endl;
    cin>>d;
	while (d<6)
	{
	    cout<<"Ошибка! Для доски меньше, чем 6*6 не существует замкнутого обхода конём."<<endl;
		cout<<"Введите размер доски (d>=6): "<<endl;
		cin>>d;
		system("cls");
	}
	vector<int> sequence;
	vector<bool> available_cells(d*d, 0);
	sequence.push_back(0);
	available_cells[0]=1;
	sequence.push_back(d+2);
	available_cells[d+2]=1;
	clock_t t;
	t = clock();
	backtrack(sequence, available_cells, d);
	t = clock() - t;
	printf ("It took me %d clicks (%f seconds).\n",t,((float)t)/CLOCKS_PER_SEC);
	if (!finished)
    {
        cout<<"\nРешений не найдено.";
    }
	system("pause");
}
