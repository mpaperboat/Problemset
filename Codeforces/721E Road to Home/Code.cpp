#include<iostream>
#include<vector>
#include<utility>
#include<string>
#include<algorithm>
#include<set>
#include<utility>
#include<queue>
using namespace std;
int main(){
	ios::sync_with_stdio(false);
	int L,n,p,t;
	static int l[100010],r[100010],bd[100010],f[100010];
	cin>>L>>n>>p>>t;
	for(int i=1;i<=n;++i)
		cin>>l[i]>>r[i];
	long long bg=0;

	set<pair<long long,int> >md;
	queue<int>mdq;

	queue<int>edq;
	int ans=0;
	for(int i=1;i<=n;++i){
		if(r[i]-l[i]<p)
			continue;
		while(edq.size()&&bd[edq.front()]<=r[i]-p){
			int j=edq.front();
			edq.pop();
			mdq.push(j);
			md.insert(make_pair((long long)p*f[j]-bd[j],j));
		}
		while(mdq.size()&&bd[mdq.front()]<l[i]){
			int j=mdq.front();
			mdq.pop();
			md.erase(make_pair((long long)p*f[j]-bd[j],j));
			long long tmp=(long long)p*f[j];
			bg=max(bg,tmp);
		}
		long long ty;
		ty=r[i]-l[i]+bg;
		if(md.size())
			ty=max(ty,md.rbegin()->first+r[i]);
		f[i]=ty/p;
		bd[i]=r[i]-ty%p+t;
		edq.push(i);
		ans=max(ans,f[i]);
	}
	//cout<<bd[1]<<bd[2]<<endl;
	cout<<ans<<endl;
	//for(;;);
	return 0;
}