#include<bits/stdc++.h>
#include<iostream>

using namespace std;

# define inf 0x3f3f3f3f

class node
{
public:
    vector<int> next;
    vector<int> weight;
    int n = 0;
    int ndeg = 0;

    void add(int i, int w)
    {
        next.push_back(i);
        weight.push_back(w);
        n++;
        ndeg++;
    }

    void direcToAdd()
    {
        ndeg++;
    }

    void direcFromAdd(int j, int w)
    {
        next.push_back(j);
        weight.push_back(w);
        n++;
    }


};


void graphBFS(node a[], int start, int n)
{
    queue<int> q;
    int check[n+1];
    for(int i=0; i<=n; i++)
    {
        check[i] = 0;
    }

    q.push(start);
    int count =0;
    while(q.size() != 0)
    {
        if(check[q.front()] == 0)
        {
            for(auto i=a[q.front()].next.begin(); i != a[q.front()].next.end(); i++)
            {
                if(check[*i] == 0)
                {
                    q.push(*i);
                }
            }
            cout << q.front() << endl;
            check[q.front()] = 1;
            count++;
        }
        q.pop();
        if(count >= n)
        {
            break;
        }
    }
}


void graphDFS(node a[], int start, int n)
{
    int check[n+1];
    int t;
    for(int i=0; i<=n; i++)
    {
        check[i]=0;
    }

    stack<int> s;
    s.push(start);
    int count = 0;
    while(s.size() != 0)
    {
        if(check[s.top()] == 0)
        {
            cout << s.top() << endl;
            t = s.top();
            check[t] = 1;
        }
        s.pop();
        for(auto j = a[t].next.begin(); j != a[t].next.end(); j++)
        {
            if(check[*j] == 0)
            {
                s.push(*j);
            }
        }
    }
}


void undirectedAdd(node a[],int i, int j, int w)
{
    a[i].add(j,w);
    a[j].add(i,w);
}


void directedAdd(node a[], int from, int to, int w)
{
    a[to].direcToAdd();
    a[from].direcFromAdd(to, w);
}


void graphDisplayStats(node a[])
{
    for(int i=1; i<9; i++)
    {
        cout << i << "\n>>connections = ";
        for(auto j=a[i].next.begin(), k=a[i].weight.begin(); j!=a[i].next.end(); j++, k++)
        {
            cout << *j << " at " << *k << " ";
        }
        cout << "\n>>n = " << a[i].n << " ndeg = " << a[i].ndeg << "\n\n";
    }
}


int graphSsspDijkstra(node a[], int start, int to, int n)
{
    int i;
    vector < pair <int, int> > record;
    priority_queue < pair <int, int> ,vector <pair <int, int> >, greater <pair <int, int> > > pq;


    for( i =0; i<=n; i++)
    {
        if(i == start)
        {
            record.push_back(make_pair(0, i));
        }
        else
        {
            record.push_back(make_pair(inf, i));
        }
    }

    pq.push(make_pair(0, start));

    while(!pq.empty())
    {
        i = pq.top().second;

        for(auto j = a[i].next.begin(), k = a[i].weight.begin(); j!=a[i].next.end(); j++, k++)
        {
            if(record[*j].first > *k + record[i].first)
            {
                record[*j].first = *k + record[i].first;
                record[*j].second = i;
                pq.push(make_pair(*k + record[i].first, *j));
            }
        }

        pq.pop();
    }

    if(record[to].first == inf){return -1;}
    else{return record[to].first;}
}


vector < pair <int, int> > graphSsspBellmanFord(node a[], int start, int n)
{
    int i;
    vector < pair <int, int> > record;

    for( i =0; i<=n; i++)
    {
        if(i == start)
        {
            record.push_back(make_pair(0, i));
        }
        else
        {
            record.push_back(make_pair(inf, i));
        }
    }

    int b = n-1;
    while(b--)
    {
        for(i=0; i<=n; i++)
        {
            for(auto j=a[i].next.begin(), k=a[i].weight.begin(); j!=a[i].next.end(); j++,k++)
            {
                if(record[*j].first > record[i].first + *k)
                {
                    record[*j].first = record[i].first + *k;
                    record[*j].second = i;
                }
            }
        }
    }

    return record;
}


int main()
{
    int q, t = 0;
    cin >> q;
    while(q > t)
    {
        node n[27];
        string s;
        cin >> s;


        int m;
        cin >> m;
        string in;
        int done[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
        vector<int> fin;

        for(int i =0; i<m; i++)
        {
            cin >> in;
            if(done[int(in[1]) - 65] == 0)
            {
                done[int(in[1]) - 65] = 1;
                fin.push_back(int(in[1]) - 64);
            }

            directedAdd(n, int(in[0]) - 64, int(in[1]) - 64, 1);
        }

        int count = 0;
        for(int i =1; i<s.length(); i++)
        {
            if(s[i] == s[0])
            {
                count++;
            }
        }

        if(count == s.length()-1)
        {
            cout << "Case #" << t+1 << ": " << 0 << endl;
            t++;
            continue;
        }

        int dist, curr, flag, ans = inf, haveans = 0;
        for(auto j = fin.begin(); j!= fin.end(); j++)
        {
            dist = 0;
            flag = 0;
            for(int i=0; i<s.length(); i++)
            {
                curr = graphSsspDijkstra(n, int(s[i]) - 64, *j, 27);
                if(curr == -1){flag = 1; break;}

                dist = dist + curr;
            }
            if(ans > dist && flag == 0)
            {
                ans = dist;
                haveans = 1;
            }
        }
        if(haveans){cout << "Case #" << t+1 << ": " << ans << endl;}
        else{cout << "Case #" << t+1 << ": " << -1 << endl;}
        t++;
    }
}
