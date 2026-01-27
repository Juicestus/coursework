#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int T;
    cin >> T;
    while (T--)
    {
        long long  Ncs, Ne;
        cin >> Ncs >> Ne;
        vector<long long> cs{};
        long long Acs = 0, Ae = 0;
        for (int i = 0; i < Ncs; i++)
        {
            int k;
            cin >> k;
            cs.push_back(k);
            Acs += k;
        }
        int c = 0;
        for (int i = 0; i < Ne; i++)
        {
            int k;
            cin >> k;
            Ae += k;
        }

        //sort(cs.begin(), cs.end());
        for (long long s : cs)
        {

            if ((Acs-s)/(Ncs-1.0) > (Acs/(Ncs+0.0))
                    && (Ae+s)/(Ne+1.0) > (Ae/(Ne+0.0)))
                c++;
    /*

            if (s * Ncs < Acs && s * Ne > Ae)
            {
                c++;
                Acs -= s;
                Ae += s;
                Ncs--;
                Ne++;*/
            //else break;
        }
        std::cout << c << "\n";
    }

}
