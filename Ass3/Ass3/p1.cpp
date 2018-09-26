#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
using namespace std;

void function(vector<vector<int> > v, int s, int *dist, int *p, bool *visited, int N)
{
	for (int j = 0; j < N; j++)
	{
		visited[j] = false;
		p[j] = 0;
		dist[j] = 999;
	}
    dist[s] = 0;
    p[s] = 1;
    queue <int> q;
    q.push(s);
    visited[s] = true;
    while (!q.empty())
    {
        int curr = q.front();
        q.pop();
 
        // Neighbors of current vertex
        for (size_t j=0; j < v[curr].size(); j++)
        {
            // Push to queue if not visited yet
            if (visited[v[curr][j] - 1] == false)
            {
                q.push(v[curr][j]- 1);
                visited[v[curr][j]- 1] = true;
            }
 
            // check if there's a better path
            if (dist[v[curr][j]- 1] > dist[curr] + 1)
            {
                dist[v[curr][j]- 1] = dist[curr] + 1;
                p[v[curr][j]- 1] = p[curr];
            }
 
            // where more shortest paths found
            else if (dist[v[curr][j]- 1] == dist[curr] + 1)
                p[v[curr][j]- 1] += p[curr];
        }
    }
	for(int j = 0; j < N; j++)
			cout << p[j] << ", ";
	cout << endl;
	/*
	char choice;
	cout << "Do you want to continue (y/n):" << endl;
	cin >> choice;
	while ((choice =! 'y') && (choice =! 'n'))
		cout << "Invalid input. Do you want to continue (y/n):" << endl;
	if (choice =! "n")
	{
		cout << "Please enter source node" << endl;
	cin >> s;
	function(v, s-1, dist, p, visited, N);
	}
	*/
}

int main(void)
{
	char ch;
    fstream fin("graph-file.txt", fstream::in);
    if(!fin)
	{
        cerr << "Something is wrong...! Exiting..." << endl;
        return -1;
    }
    int N; // number of sets
    fin >> N;
	//cout << N << endl;
    vector<vector<int> > v;
    v.resize(N);
    int i = 0;
    while (fin >> ch) 
	{
          //  cout << ch << endl;
        if(ch == '{' || ch == ',')
            continue;
        if(ch == '}') {
            i++;
            continue;
        }
        v[i].push_back(ch - '0');
    }
	/*
    if(i == N) {
        cout << "Parsing the file completed successfully." << endl;
    } else {
        cout << "Parsed only " << i << " sets, instead of " << N << endl;
    }
    for(size_t i = 0; i < v.size(); ++i) {
        if(v[i].size() == 0)
            cout << i + 1 << "-th set is empty\n";
        else {
            for(size_t j = 0; j < v[i].size(); ++j)
                cout << v[i][j] << " ";
            cout << endl;
        }
    }
	*/
    bool *visited;
	visited = new bool[N];
	int *p, *dist;
	p = new int[N];
	dist = new int[N];
	int s;
	cout << "Please enter source node" << endl;
	cin >> s;
	function(v, s-1, dist, p, visited, N);
	system("pause");
    return 0;
}