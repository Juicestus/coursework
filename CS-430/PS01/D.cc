#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    char _;

    int h1, h2, m1, m2, s1, s2;
    cin >> h1 >> _ >> m1 >> _ >> s1 >> h2 >> _ >> m2>> _ >> s2;

    //std::cout << h1 << m1 << s1 << " " << h2 << m2 << s2 << "\n";
    
    int h=h2 - h1, m=m2-m1, s = s2 - s1;

    if (s<0) 
    { 
        s+=60; 
        m--;
    }
    if (m<0)
    {
        m += 60;
        h--;
    }
    if (h < 0)h += 24;
    if (h == 0 && m == 0 && s == 0) h = 24;
    
    printf("%02d:%02d:%02d", h, m, s);
    

}
