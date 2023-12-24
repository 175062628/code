#include<bits/stdc++.h>
using namespace std;
int q_pow(int base,int power,int mod){
	int res=1;
	while(power){
		if(power&1) res=res*base%mod;
		base=base*base%mod;
		power>>=1;
	}
	return res;
}
