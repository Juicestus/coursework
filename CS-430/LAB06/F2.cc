 1 #include <bits/stdc++.h>
⚠   2 using namespace std;
    3
    4 using ll = long long;
    5
>>  6 vector<int> par;
>>  7 map<string, int> c1;
>>  8 map<int, string> c2;
    9
   10 int find(int i)
   11 {
   12     if (par[i] == i) return i;
   13     return (par[i] = find(i: par[i]));
   14 }
   15
   16 void unin(int i, int j)
   17 {
   18     int ir = find(i);
   19     int jr = find(i: j);
   20     par[ir] = jr;
   21 }
   22
   23 int main()
   24 {
>> 25     ios_base::sync_with_stdio(false);
>> 26     cin.tie(0); cout.tie(0);
   27
   28     int n;
>> 29     cin >> n;
   30
>> 31     vector<pair<string, string>> k(n);
   32     for (int i = 0; i < n; i++)
   33     {
>> 34         string a, b;
>> 35         cin >> a >> b;
   36         par[i] = i;
>> 37         k[i] = make_pair(a, b);
   38     }
   39
   40     //for (auto& [a, b] : par)
   41         //cout << a << " " << b << "\n";
>> 42     while (int i = 0; i < 100; i++)
   43         for (int i = 0; i < n; i++)
   44             cout << k[i] << " " << find(k[i]) << "\n";
   45
   46 }
~
