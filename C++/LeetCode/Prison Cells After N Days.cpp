class Solution {
public:
    vector<int> prisonAfterNDays(vector<int>& cells, int N) {
        
        map<int, int> patterns;
        int cycle = 0;
        char msk1=0, msk2=0;
        bool t;

        for(int i = 1; i < 7; ++i)
            msk1|=((cells[i-1]==cells[i+1])<<(7-i));

        for(N -= 1; N>0; N--){
            for(int i = 1; i < 7; ++i){
                t = (msk1&(1<<(8-i)))>0;
                t = t ^ ((msk1&(1<<(6-i)))>0);
                msk2 |= (!t) << (7-i);
            }

            if (patterns.count(msk1)){
                cycle = patterns[msk1] - N;
                N %= cycle;
            }
            else patterns[msk1] = N;
            if (N<=0) break;
            msk1 = msk2;
            msk2 = 0;
        }

        for (int i = 0; i < 8; i++) cells[i] = (msk1&(1<<(7-i)))>0;
        
        return cells;
    }
};
