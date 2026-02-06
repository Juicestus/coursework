#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    unordered_map<string, int> vars{};
    map<ll, string> invars{};
    
    string cmd;
    while (cin >> cmd)
    {
        if (cmd == "def")
        {
            string var;
                ll val;
            cin >> var >> val;
            auto itv = vars.find(var);
            auto iti = invars.find(val);
            if (itv != vars.end())
            {
                invars.erase(itv->second);
                vars.erase(itv);
            }
            if (iti != invars.end())
            {
                invars.erase(iti);
            }
            vars[var] = val;
            invars[val] = var;
        }
        if (cmd == "calc")
        {
            string res;
            string var;
            cin >> var;
            res += var + ' ';
            ll val;
            bool ok = true;

            if (vars.find(var) != vars.end())
                val  = vars[var];
            else ok = false;
            char op;
            while (cin >> op && op != '=')
            {
                cin >> var;
                res += op;
                res += " " + var + " " ;
                if (vars.find(var) == vars.end())
                    ok = false;
                if (ok)
                {
                    if (op == '+')
                        val += vars[var];
                    else val -= vars[var];
                }
            }
            res += "= ";
            cout << res;
            if (ok && invars.find(val) != invars.end())
            {
                cout << invars[val];
            }
            else  cout << "unknown";
            cout << "\n";
        }

        if (cmd == "clear")
        {
            vars.clear();
            invars.clear();
        }
    }
    
}
