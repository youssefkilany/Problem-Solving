   
#include <bits/stdc++.h>
using namespace std;

struct comp{
    bool operator() (string &t1, string &t2){
        return t1+t2 > t2+t1;
    }
};

string largestConcat(vector<string>& v) {
    sort(v.begin(), v.end(), comp());

    // for (int i = 0; i < (int)v.size(); ++i)
    //     printf("%s\n", v[i].c_str());

    string s = "";
    
    int i = 0, j = (int)v[i].size();
    for (; i < (int)v.size() && j == (int)v[i].size(); ++i)
        for (j = 0; j < (int)v[i].size(); ++j)
            if (v[i][j] != '0') {
                s += v[i].substr(i);
                break;
            }
        
    for (; i<(int)v.size(); ++i)
        s += v[i];

    return s[0]?s:"0";
}
   
int main() {
    int N;
    scanf("%d", &N);
    
    vector<string> v;
    for (int i = 0; i < N; ++i) {
        // 2-step way to read c++ strings, \n used to terminate scan, but it's safer to check scanf return, like this if (1 == scanf())
        char number_[100];
        scanf("%100s\n", number_);
        string number = number_;
        v.push_back(number);
    }
    
    printf("%d\n", largestConcat(v));
    return 0;
}
