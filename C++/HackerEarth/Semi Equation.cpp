// https://www.hackerearth.com/challenges/competitive/march-circuits-22/algorithm/semi-equation-bec91fcd/
 
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
 
vector<vvll> fibs(61, vvll());
ll MOD = 1000000007;
 
vvll multiplyMatrix(vvll &x, vvll &y){
	
	vvll ret = {{0,0},{0,0}};
	
	for(int i = 0; i < 2; ++i)
		for(int j = 0; j < 2; ++j)
			for(int k = 0; k < 2; ++k)
				ret[i][j] = (ret[i][j]+(x[i][k]*y[k][j])%MOD)%MOD;
  	return ret;
}
 
vvll getFibExponent(ll n){
	vvll ret = {{1,0},{0,1}};
	for (int i = 0; i < 61; ++i)
		if (n & 1ll<<i)
			ret = multiplyMatrix(ret, fibs[i]);
	return ret;
}

void prepareFibs(){
	fibs[0] = {{0,1}, {1,1}};
	for(int i = 1; i<61; ++i)
		fibs[i] = multiplyMatrix(fibs[i-1], fibs[i-1]);
}
 
int main() {

  fast const clock_t begin_time = clock();

  prepareFibs();

  int tests = 1;
  scanf("%d", &tests);

  for(int t_ = 0; t_ < tests; ++t_) {

    ll n;
    scanf("%lld", &n);

    if (n == 1){
      printf("1\n");
      continue;
    }

    vvll ret = getFibExponent(n+1);
    printf("%lld\n", ret[1][1]-1);
  }

  printtime(begin_time);
  return 0;
}
