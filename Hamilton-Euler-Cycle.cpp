//Patryk Jędrzejewski
#include <string>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <typeinfo>
#include <fstream>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;
chrono::steady_clock sc;

int E, V, a, b;

string filename="example7.txt";

///////////
int MSS[1000][1000] = { 0 };
vector <int> NS[1000];

int MSNS[1000][1000] = { 0 };
vector <int> NNS[1000];

//Euler nieskierowany ms
int MSNS_1[1000][1000];
vector <int> NNS_1[1000];

//Euler skierowany ln
int MSS_1[1000][1000];
vector <int> NS_1[1000];
int visitedNS_1[1000] = { 0 };
int gdzie = 0;

//Hamilton nieskierowany ms
int MSNS_2[1000][1000];
vector <int> NNS_2[1000];
int visitedMSNS_2[1000] = { 0 };

//Hamilton skierowany ln
int MSS_2[1000][1000];
vector <int> NS_2[1000];
int visitedNS_2[1000] = { 0 };

//wyniki
vector <int> l_1;
vector <int> l_2;
vector <int> l_3;
vector <int> l_4;
vector <int> hamilton1;
vector <int> hamilton2;

//Euler MS NS
void dfsMSEulerNS(int v)
{
    for (int i = 1; i <= V; i++)
    {
        if (i != v)
        {
            if (MSNS_1[v][i] == 1)
            {
                MSNS_1[v][i] = 0;
                MSNS_1[i][v] = 0;
                dfsMSEulerNS(i);
            }
        }
    }
    l_1.push_back(v);
}

//Euler N S
bool EulerNS(int start3, int w, int gdzie)
{
    visitedNS_1[w] = 1;
    l_2.insert(l_2.begin() + gdzie + 1, 1, w);
    gdzie++;

    for (int i = 0; i < NS_1[w].size(); i++)
    {
        if (NS_1[w][i] == start3)
        {
            l_2.insert(l_2.begin() + gdzie + 1, 1, start3);

            //usuwanie krawedzi
            for (int s = 0; s < l_2.size() - 1; s++)
            {
                if (!NS_1[l_2[s]].empty())
                {
                    NS_1[l_2[s]].erase(remove(NS_1[l_2[s]].begin(), NS_1[l_2[s]].end(), l_2[s + 1]), NS_1[l_2[s]].end());
                }
            }

            return true;

            if (l_2[gdzie] == start3)
            {
                return true;
            }
            gdzie--;

        }
        if (visitedNS_1[NS_1[w][i]] == 0 && EulerNS(start3, NS_1[w][i], gdzie) == true)
        {
            return true;
        }
    }
    gdzie--;
    l_2.erase(l_2.begin() + gdzie + 1);
    return false;
}

//Hamilton MS NS
int odwiedzone2 = 0;
int start2 = 1;
int flaga2 = 0;
int czyhamilton2 = 0;
int niewchodz = 0;

bool HamiltonianMSNS(int v)
{
    l_3.push_back(v);
    visitedMSNS_2[v] = 1;
    odwiedzone2++;

    for (int j = 1; j <= V; j++)
    {
        if (MSNS_2[v][j] == 1 && v != j)
        {
            flaga2 = 0;
            if (MSNS_2[v][start2] == 1)
            {
                flaga2 = 1;
            }

            if (odwiedzone2 == V && flaga2 == 1 && niewchodz == 0)
            {
                niewchodz = 1;
                l_3.push_back(start2);
                for (int w = 0; w < l_3.size(); w++)
                {
                    hamilton1.push_back(l_3[w]);
                }
                czyhamilton2 = 1;
                return true;
            }

            if (visitedMSNS_2[j] == 0)
            {
                //cout << v << endl;
                HamiltonianMSNS(j);
            }
        }
    }


    visitedMSNS_2[v] = 0;
    l_3.pop_back();
    odwiedzone2--;
    return false;
}

//Hamilton N S
int odwiedzone = 0;
int start3 = 1;
int flaga = 0;
int czyhamilton = 0;
int niewchodz2 = 0;

bool HamiltonianNS(int v)
{
    l_4.push_back(v);
    //cout << v << endl;
    visitedNS_2[v] = 1;
    odwiedzone++;

    for (int i = 0; i < NS_2[v].size(); i++)
    {
        flaga = 0;
        for (int z = 0; z < NS_2[v].size(); z++)
        {
            if (NS_2[v][z] == start3)
            {
                flaga = 1;
            }
        }

        if (odwiedzone == V && flaga == 1 && niewchodz2 == 0)
        {
            int niewchodz = 0;
            niewchodz2 = 1;
            l_4.push_back(start3);
            for (int w = 0; w < l_4.size(); w++)
            {
                hamilton2.push_back(l_4[w]);
            }
            czyhamilton = 1;
            return true;
        }

        if (visitedNS_2[NS_2[v][i]] == 0)
        {
            HamiltonianNS(NS_2[v][i]);
        }
    }

    visitedNS_2[v] = 0;
    l_4.pop_back();
    odwiedzone--;
    return false;
}

////////////////////////////////////////

void copythis()
{
    for (int i = 1; i <= V; i++)
    {
        for (int j = 1; j <= V; j++)
        {
            MSS_1[i][j] = MSS[i][j];
            MSS_2[i][j] = MSS[i][j];
            MSNS_1[i][j] = MSNS[i][j];
            MSNS_2[i][j] = MSNS[i][j];
        }
    }

    for (int j = 1; j <= V; j++)
    {
        for (int i = 0; i < NS[j].size(); i++)
        {
            NS_1[j].push_back(NS[j][i]);
            NS_2[j].push_back(NS[j][i]);
        }
        for (int i = 0; i < NNS[j].size(); i++)
        {
            NNS_1[j].push_back(NNS[j][i]);
            NNS_2[j].push_back(NNS[j][i]);
        }
    }
}

bool czyistniejecykleulerans()
{
    for (int i = 1; i <= V; i++)
    {
        int temp = 0;
        for (int j = 1; j <= V; j++)
        {
            if (MSNS_1[i][j] == 1)
            {
                temp++;
            }
        }
        if (temp % 2 == 1)
        {
            return false;
        }
    }
    return true;
}

bool czyistniejecykleuleras()
{
    int wejscie[1000] = { 0 };
    int wyjscie[1000] = { 0 };

    for (int i = 1; i <= V; i++)
    {
        for (int j = 1; j <= V; j++)
        {
            if (MSS_2[i][j] == 1)
            {
                wyjscie[i]++;
                wejscie[j]++;
            }
        }
    }

    for (int z = 0; z < V; z++)
    {
        if (wejscie[z] != wyjscie[z])
        {
            return false;
        }
    }
    return true;
}

bool czyliczba(string s)
{
    for (int i = 0; i < s.length(); i++)
        if (isdigit(s[i]) == false)
            return false;

    return true;
}

int main(int argc, const char* argv[])
{
    int wyjscie = 0;
    int wyjscie2 = 0;

    ifstream graf;
    graf.open(filename);

    int c = 0;
    string e;
    srand(static_cast<unsigned int>(time(nullptr)));
    int x = 0;
    string xd;

    cout << "To choose an option, type equivalent number " << endl << "Input from file (specified in 'filename' variable)- 1" << endl << "Input from keyboard - 2" << endl << "Exit- 3" << endl;
    while (c != 1)
    {
        cin >> xd;
        if (czyliczba(xd))
        {
            x = stoi(xd);
            if ((x > 0) && (x <= 3))
            {
                c = 1;
            }
            else
                cout << "Entered value is invalid" << endl;
        }
        else
        {
            cout << "Entered value is invalid" << endl;
        }
    }

    switch (x)
    {
    case 1:
        graf >> V >> E;
        while (!graf.eof())
        {
            graf >> a >> b;
            cout << a << " " << b << endl;

            NNS[a].push_back(b);
            NNS[b].push_back(a);
            NS[a].push_back(b);

            MSS[a][b] = 1;
            MSS[b][a] = -1;
            MSNS[a][b] = 1;
            MSNS[b][a] = 1;
        }
        graf.close();
        break;
    case 2:
        cout << "Enter number of nodes and edges" << endl;
        cin >> V;
        cin >> E;
        cout << "Enter " << E << " pairs of numbers" << endl;
        for (int i = 0; i < E; i++)
        {
            string ah;
            string bh;
            cout << "Enter 2 numbers" << endl;
            cin >> ah;
            cin >> bh;
            int ae, be;
            ae = stoi(ah);
            be = stoi(bh);

            if (czyliczba(ah) && czyliczba(bh) && stoi(ah) > 0 && stoi(bh) > 0)
            {
                NNS[ae].push_back(be);
                NNS[be].push_back(ae);
                NS[ae].push_back(be);

                MSS[ae][be] = 1;
                MSS[be][ae] = -1;
                MSNS[ae][be] = 1;
                MSNS[be][ae] = 1;
            }

            else
            {
                cout << "Entered values aren't number or entered this pair before (so the cycle exists), enter new pair" << endl;
                i--;
            }
        }
        break;
    case 3:
        return 0;
        break;

    }
    cout << "Adjacency matrix - Undirected Graph" << endl;
    for (int i = 1; i <= V; i++)
    {
        for (int j = 1; j <= V; j++)
            cout << MSNS[i][j] << "\t";
        cout << endl;
    }

    cout << "Edge list from: to - Undirected Graph" << endl;
    for (int j = 1; j <= V; j++)
    {
        cout << j << ": ";
        for (int i = 0; i < NNS[j].size(); i++)
        {
            cout << NNS[j][i] << " ";
        }
        cout << endl;
    }

    cout << "Incidence Matrix - Directed Graph" << endl;
    for (int i = 1; i <= V; i++)
    {
        for (int j = 1; j <= V; j++)
            cout << MSS[i][j] << "\t";
        cout << endl;
    }
    //sortowanie vectora
    for (int i = 1; i <= V; i++)
    {
        sort(NS[i].begin(), NS[i].end());
        sort(NNS[i].begin(), NNS[i].end());
    }
    cout << "Edge list from: to - Directed Graph" << endl;
    for (int j = 1; j <= V; j++)
    {
        cout << j << ": ";
        for (int i = 0; i < NS[j].size(); i++)
        {
            cout << NS[j][i] << " ";
        }
        cout << endl;
    }


    copythis();

   /* int czypelny = 1;
    for (int i = 1; i <= V; i++)
    {
        int licznik = 0;
        for (int j = 1; j <= V; j++)
        {
            if (MSNS[i][j] == 0)
            {
                licznik++;
            }
        }
        if (licznik == V)
        {
            czypelny = 0;
            break;
        }
    }
    if (czypelny == 0)
    {
        cout << "Graf nieskierowany nie jest spojny" << endl;
        wyjscie2 = 1;
    }

    czypelny = 1;
    for (int i = 1; i <= V; i++)
    {
        int licznik = 0;
        for (int j = 1; j <= V; j++)
        {
            if (MSS[i][j] == 0)
            {
                licznik++;
            }
        }
        if (licznik == V)
        {
            czypelny = 0;
            break;
        }
    }
    if (czypelny == 0)
    {
        cout << "Graf skierowany nie jest spojny" << endl;
        wyjscie2 = 1;
    }*/

    while (wyjscie2 == 0)
    {
        cout << endl;
        cout << "To choose an option, type equivalent number" << endl << "Euler Cycle - Adjacency matrix - Undirected Graph - 1" << endl << "Euler Cycle - Edge list (from:to) - Directed Graph - 2" << endl;
        cout << "Hamilton Cycle - Adjacency matrix - Undirected Graph - 3" << endl << "Hamilton Cycle - Edge list (from:to) - Directed Graph - 4" << endl << "Exit - 5" << endl;
        int h = 0, f = 0;
        string fe;
        while (h != 1)
        {
            cin >> fe;
            if (czyliczba(fe))
            {
                f = stoi(fe);
                if ((f > 0) && (f <= 5))
                {
                    h = 1;
                }
                else
                    cout << "Entered value is invalid" << endl;
            }
            else
            {
                cout << "Entered value is invalid" << endl;
            }
        }
        cout << endl;

        if (f == 1)
        {
            if (czyistniejecykleulerans() == false)
            {
                cout << "In the undirected graph there is not Euler cycle" << endl;
            }
            else
            {
                cout << "Euler Cycle Undirected: " << endl;
                auto start = sc.now();
                dfsMSEulerNS(1);
                auto end = sc.now();
                for (int i = 0; i < l_1.size(); i++)
                {
                    cout << l_1[i] << " ";
                }
                auto time_span = static_cast<chrono::duration<double, std::milli>>(end - start);
                cout << endl << "Finding of Euler Cycle using Adjacency Matrix in undirected graph took " << time_span.count() << " microseconds." << endl;
            }
        }
        if (f == 2)
        {
            if (czyistniejecykleuleras() == false)
            {
                cout << "In the directed graph there is not Euler cycle" << endl;
            }
            else
            {
                cout << "Euler Cycle Directed: " << endl;
                l_2.push_back(1);
                gdzie = 0;
                auto start = sc.now();
                while (gdzie < l_2.size())
                {
                    for (int i = 0; i < NS_1[l_2[gdzie]].size(); i++)
                    {
                        for (int j = 0; j < 100; j++)
                        {
                            visitedNS_1[j] = 0;
                        }
                        EulerNS(l_2[gdzie], NS_1[l_2[gdzie]][i], gdzie);
                    }
                    gdzie++;
                }
                auto end = sc.now();
                for (int i = 0; i < l_2.size(); i++)
                {
                    cout << l_2[i] << " ";
                }
                auto time_span = static_cast<chrono::duration<double, std::milli>>(end - start);
                cout << endl << "Finding of Euler Cycle using Edge list from:to in directed graph took  " << time_span.count() << " microseconds." << endl;
            }
        }
        if (f == 3)
        {
            auto start = sc.now();
            HamiltonianMSNS(start2);
            auto end = sc.now();
            if (czyhamilton2 == 0)
            {
                cout << "In the undirected graph there is not Hamilton cycle" << endl;
            }
            else
            {

                cout << "Hamilton cycle Undirected " << endl;
                for (int i = 0; i < hamilton1.size(); i++)
                {
                    cout << hamilton1[i] << " ";
                }
                auto time_span = static_cast<chrono::duration<double, std::milli>>(end - start);
                cout << endl << "Finding of Hamilton Cycle using Adjacency matrix in undirected graph took " << time_span.count() << " microseconds." << endl;
            }


        }
        if (f == 4)
        {
            auto start = sc.now();
            HamiltonianNS(start3);
            auto end = sc.now();
            if (czyhamilton == 0)
            {
                cout << "In the directed graph there is not Hamilton cycle" << endl;
            }
            else
            {
                cout << "Hamilton cycle Directed" << endl;
                for (int i = 0; i < hamilton2.size(); i++)
                {
                    cout << hamilton2[i] << " ";
                }
                auto time_span = static_cast<chrono::duration<double, std::milli>>(end - start);
                cout << endl << "Finding of Hamilton Cycle using Edge list from:to in directed graph took " << time_span.count() << " microseconds." << endl;
            }
        }

        if (f == 5)
        {
            wyjscie2 = 1;
        }
    }
}
