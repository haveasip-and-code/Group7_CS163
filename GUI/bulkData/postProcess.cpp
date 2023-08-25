#include <bits/stdc++.h>

using namespace std;

vector<pair<string,string>> p;

int main() {
    ifstream in;
    in.open("dataset1.txt");
    ofstream out;
    out.open("dataset1_clean.txt");
    string s1,s2,s;
    while (getline(in,s)) {
        getline(in,s1);
        string t="";
        while (true) {
            getline(in,s1);
            if (s1[1]!='-'||s1[2]!='-'||s1[3]!='-') {
            if (s1!="") {
                if (t=="") t=s1;
                else t+="\n"+s1;
            }
            }
            else break;
        }
        p.push_back({s,t});
        if (p.size()%100==0) cout<<p.size()<<'\n';
    }
    random_shuffle(p.begin(),p.end());
    for (int i=0;i<p.size();i++) {
        out<<p[i].first<<'\n'<<p[i].second<<"\n---------------\n";
    }
    in.close();
    out.close();
}
