#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    
    int n;
    cin >>n;
    int H = n, L = 1;

    while (H-L > 2)
    {
        int l1 = L;
        int l2 = L + (H-L+1) * 0.25;
        int r1 = L + (H-L+1) * 0.5 - 1;
        int r2 = L + (H-L+1) * 0.75 - 1;
        
        printf("Q %d %d %d %d\n", l1, r1, l2, r2);
        fflush(stdout);
    
        int w1, w2;
        cin>> w1 >> w2;
        if (w1)      
        {
            if (w2)
            {
                L=l2-1;
                H=r1+1;
                if (l2==r1)
                {
                    H--;
                    goto done;
                }
            }
            else 
            {
                H=l2;
                if (l2-l1 <= 1) { H=l1; goto done; }
            }
        }
        else 
        {
            if (w2)
            {
                L=r1;
                H=r2+1;
                if (r2-r1 <= 1)
                {
                    H--;
                    goto done;
                }
            }
            else
            {
                L=r2;
                if (++H > n) H = n;
                if (H-r2==1) goto done;
            }
        }

    }
    printf("Q %d %d %d %d\n", L, L, L+1, L + 1);
    fflush(stdout);

    int w1, w2;
    cin >>w1>>w2;
    if (w1 != w2)
        H=L + w2;

done:
    printf("A %d\n", H);

}
