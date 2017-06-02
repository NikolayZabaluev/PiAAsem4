#include <iostream>
#include <vector>
#include <climits>
#include <fstream>

using namespace std;
bool finished=false;

void matrix_input (int n, vector < vector <int> > &matrix, istream &in)
{
	for (size_t i=0; i<(n-1); i++)
    {
        for (size_t j=(i+1); j<n; j++)
        {
            matrix[i][i]=0;
            cout << "Введите элемент матрицы [" << i << "]" << "[" << j << "]:";
            in >> matrix[i][j];
            cout << matrix[i][j] << endl;
            //cin>>matrix[i][j];
            matrix[j][i]=matrix[i][j];
        }
    }
    matrix[n-1][n-1]=0;
}

void matrix_output(int n, vector < vector <int> > matrix)
{
	for (size_t i=0; i<n; i++)
    {
        for (size_t j=0; j<n; j++)
            cout<<matrix[i][j]<<'\t';
        cout<<endl;
    }
}

void show_solutions(int n, vector < vector <int> > solution)
{
	for (size_t i=0; i<solution.size(); i++)
	{
		for (size_t j=0; j<n; j++)
		{
			cout << solution[i][j]+1 << " ";
		}
		cout<<endl;
	}
}

bool is_a_solution(vector<int> perm, int n, int current_cost, int lowcost)
{
    if ((perm.size()==n) && (current_cost<=lowcost))
		return true;
	else
		return false;
}

void process_solution(vector<int> perm, int n, vector < vector <int> > &solution, int current_cost, int &lowcost)
{
	cout<<"\nНайдено 'выгодное' решение!"<<endl<<"Его 'стоимость' равна: "<<current_cost<<endl;
	if (current_cost<lowcost)
		{
		    solution.clear();
            solution.push_back(perm);
            lowcost=current_cost;
		}
	else
		solution.push_back(perm);
	for (size_t i=0; i<n-1; i++)
	{
		if (perm.at(i)>perm.at(i+1))
			finished=true;
		else
		{
			finished=false;
			break;
		}
	}

}

void construct_candidates (vector<bool> in_perm, int n, vector<int> &candidates)
{
	for (size_t i=0; i<n; i++)
	{
		if (in_perm.at(i)==0)
			candidates.push_back(i);
	}
}

int additional_cost(int n, vector < vector <int> > C, vector < vector <int> > D, vector<int> perm, int current_cost, int lowcost)
{
	int add=0;
	for (size_t i=0; i<(perm.size()-1); i++)
	{
		add+=D[i][perm.size()-1]*C[perm.back()][perm.at(i)];
		if (add+current_cost>lowcost)
			break;
	}
	return add;
}


void backtrack( vector<int> &perm, vector<bool> &in_perm, int n, vector < vector <int> > C, vector < vector <int> > D, int &lowcost, int &current_cost, vector < vector <int> > &solution)
{
	vector<int> candidates;
	if (is_a_solution(perm, n, current_cost, lowcost))
	{
		process_solution(perm, n, solution, current_cost, lowcost);
	}
	else
	{
		construct_candidates(in_perm, n, candidates);

		for (size_t i=0; i<candidates.size(); i++)
		{
			perm.push_back(candidates.at(i));
			in_perm.at(candidates.at(i))=1;
			int added = additional_cost(n, C, D, perm, current_cost, lowcost);
			current_cost+=added;
			if (current_cost>lowcost)
				{
				    current_cost-=added;
                    in_perm.at(candidates.at(i))=0;
                    perm.pop_back();
                    break;
				}
			else
				backtrack(perm, in_perm, n, C, D, lowcost, current_cost, solution);
			current_cost-=added;
			in_perm.at(candidates.at(i))=0;
			perm.pop_back();
		}
	}
	if (finished) return;
}

int main()
{
    setlocale( LC_ALL,"Russian" );
    int n=0;
	int lowcost=INT_MAX;
    int current_cost=0;
    ifstream in ("in.txt");
	cout << "Введите количество ячеек на плате:";
	in >> n;
	cout<<n<<endl;
    //cin >> n;
    //while(n<3)
    //{
    //    system("sls");
    //    cout << "Введите количество ячеек на плате (>1):";
    //    cin >> n;
    //}


    vector < vector <int> > C(n, vector <int> (n) );
    vector < vector <int> > D(n, vector <int> (n) );
    cout << "Введите матрицу смежности С:" << endl;
	matrix_input(n, C, in);
	cout << "Введите матрицу 'стоимостей' D:" << endl;
	matrix_input(n, D, in);

	vector < vector <int> > solution;
	vector<int> perm;
	vector<bool> in_perm(n, 0);

    backtrack(perm, in_perm, n, C, D, lowcost, current_cost, solution);

	cout << "\nДля " << n << " плат, при следующих матрицах C и D:" << endl << "\nC:" << endl;
	matrix_output(n, C);
	cout << "\nD:" << endl;
    matrix_output(n, D);
	cout << "\nНаименее затратными (со 'стоимостью' "<<lowcost<<") являются следующие перестановки:" << endl;
	show_solutions(n, solution);
    system("pause");
    return 0;
}
