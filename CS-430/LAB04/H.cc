#include <bits/stdc++.h>
using namespace std;

using ll = long long;

void rec(int n, int& p, int& q)
{
    printf("%d %d %d\n", n, p, q);
    if (n == 1) {
        p = 1; q = 1;
        return;
    }
    // parent
    rec(n/2, p, q);

    if (n % 2 == 1) // left 
        p = p + q;
    else 
        q = p + q;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int N;
    cin >> N;
    while (N--)
    {
        int k;
        cin >> k;
        int p, q;
        char _;
        cin >> p >> _ >> q;
        printf("parsed %d / %d\n", p, q);
        int _n = p;
        rec(_n, p, q);
        cout << p << "/" << q << "\n";
    }

}
