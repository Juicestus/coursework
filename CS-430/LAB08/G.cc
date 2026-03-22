#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int T;
    cin >>T;
    while (T--)
    {
        unordered_map<string, int> M;
        int n;
        cin >> n;
        while (n--)
        {
            string K;
            int V;
            cin >> K >> V;
            M[K] += V;
        }
        //auto C = [](auto &left, auto &right) {
            //return left.second < right.second;
        //};
        auto C = [](const auto& a, const auto& b) {
            if (a.second != b.second) {
                return a.second < b.second; 
            }
            return a.first < b.first;     
        };
        vector<pair<string, int>> A;
        for (auto [K, V] : M)
        {
            //printf("%s %d\n", K.c_str(), V);
            A.push_back({K, V});
        }
        sort(A.begin(), A.end(), C);
        printf("%d\n", A.size());
        for (auto [K, V] : M)
        {
            printf("%s %d\n", K.c_str(), V);
        }
    }

}
