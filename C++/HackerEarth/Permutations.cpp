// https://www.hackerearth.com/challenges/competitive/march-circuits-22/algorithm/nevedle-and-permutations-c6acb85e/

#include <bits/stdc++.h>

#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);

#ifdef H2E
#define printtime(t) cerr<< "Used: " <<(int)(float(clock() - t) / 1000 * CLOCKS_PER_SEC) << " ms";
#else
#define printtime(t) //...
#endif
using namespace std;

typedef long long ll;
typedef vector<vector<ll>> vvll;

void buildMax(int A[], int T[], int idx, int tl, int tr){
	if (tl == tr) {
		T[idx] = A[tl];
		return;
	}	
	int tm = (tr+tl)/2;
	buildMax(A, T, 2*idx, tl, tm);
	buildMax(A, T, 2*idx+1, tm+1, tr);
	T[idx] = max(T[2*idx], T[2*idx+1]);
}

int queryMax(int T[], int idx, int tl, int tr, int l, int r){
	
	if (l > r) return 0;
	
	if (l == tl && r == tr)
		return T[idx];
	
	int tm = (tl+tr)/2;
	int maxl = queryMax(T, 2*idx, tl, tm, l, min(tm, r));
	int maxr = queryMax(T, 2*idx+1, tm+1, tr, max(l, tm+1), r);

	return max(maxl, maxr);
}

int main() {
 
    fast const clock_t begin_time = clock();
    
    int n, q, A[100100], T[400400], l, r;
    scanf("%d %d", &n, &q);
    
    for (int i = 0; i < n; ++i)
    	scanf("%d", A+i);
    
	buildMax(A, T, 1, 0, n-1);
	
    for (int i = 0; i < q; ++i){
    	scanf("%d %d", &l, &r);
    	int ret = 0;
    	if (l > 1)
	    	ret = max(ret, queryMax(T, 1, 0, n-1, 0, l-2));
    	if (r < n)
	    	ret = max(ret, queryMax(T, 1, 0, n-1, r, n-1));
    	printf("%d\n", ret);
    }
    
    printtime(begin_time);
    return 0;
}
