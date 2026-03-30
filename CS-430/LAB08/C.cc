#include <bits/stdc++.h>
using namespace std;

using ll = long long;

vector<int> cubes(1000000, 0);

int cube(int i)
{
    if (i <= 0) return 0;
    if (cubes[i] == 0)
    {
        cubes[i] = i * i * i;
    }
    return cubes[i];
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int n;
    cin >> n;
    
    //printf("B");
    vector<int> fmap(1000000, 0);
    for (int i = 1; i < 75; i++)
    {
        for (int j = 1; j < 75; j++)
        {
            int s2c = cube(i) + cube(j);
            //printf("%d\n", s2c);
            fmap[s2c]++;
        }
    }
    //printf("A");
    for (int k = n; k >= 1729; k--)
    {
        //printf("%d -> %d\n", k, fmap[k]);
        if (fmap[k] >= 2)
        {
            printf("%d\n", k);
            return 0;
        }
    }
    printf("none\n");
}
