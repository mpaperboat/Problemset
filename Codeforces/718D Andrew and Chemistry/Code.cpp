#include<bits/stdc++.h>
using namespace std;
#define lp(i,l,r)for(auto i=l;i<=r;++i)
#define rp(i,r,l)for(auto i=r;i>=l;--i)

#include<bits/stdc++.h>
using namespace std;
struct TreeHashing{
	int n,p,d2;
	vector<int>hu,hd,sz;
	vector<vector<int>>adj;
	vector<long long>pw,hash;
	TreeHashing(int _n):
		n(_n),pw(2*n),hu(n+1),hd(n+1),sz(n+1,1),
		d2(0),adj(n+1),hash(n+1),p(1e9+7){
	}
	void add(int u,int v){
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	void down(int u,int d1=0,int f=0){
		vector<pair<int,int>>t;
		for(int v:adj[u])
			if(v!=f){
				down(v,d1,u);
				if(!d2)
					sz[u]+=sz[v]*(1-d1);
				t.push_back(make_pair(sz[v]*2,hd[v]));
			}
		if(d1*f)
			t.push_back(make_pair((n-sz[u])*2,hu[u]));
		sort(t.begin(),t.end());
		int l=1,&s=d1?*((int*)&hash[u]+d2):(hd[u]=0);
		for(auto i:t){
			s=(s+pw[l]*i.second)%p;
			l+=i.first;
		}
		s=(s+pw[l])%p;
	}
	void up(int u,int f=0){
		int l=0,sl=0,sr=1;
		vector<pair<pair<int,int>,int>>t;
		if(f)
			t.push_back(make_pair(make_pair((n-sz[u])*2,hu[u]),0));
		for(int i=0;i<adj[u].size();++i)
			if(adj[u][i]!=f){
				int v=adj[u][i];
				t.push_back(make_pair(make_pair(sz[v]*2,hd[v]),v));
			}
		sort(t.begin(),t.end());
		for(auto i:t){
			sl=(sl+i.first.second*pw[l])%p;
			l+=i.first.first;
		}
		for(int i=int(t.size()-1);i>=0;--i){
			sl=(sl-t[i].first.second*pw[l-=t[i].first.first]%p+p)%p;
			if(i+1<t.size())
				sr=(sr*pw[t[i+1].first.first]+t[i+1].first.second)%p;
			if(t[i].second)
				hu[t[i].second]=(sl+sr*pw[l])*pw[1]%p;
		}
		for(int v:adj[u])
			if(v!=f)
				up(v,u);
	}
	void run(){
		pw[0]=1;
		for(int i=1;i<2*n;++i)
			pw[i]=pw[i-1]*2%p;
		down(1),up(1),down(1,1);
		d2=1,p=1e9+9;
		for(int i=1;i<2*n;++i)
			pw[i]=pw[i-1]*7%p;
		down(1),up(1),down(1,1);
	}
};
pair<int,int>yy[200010];
void p1(int u){
	cout<<yy[u].first<<" "<<yy[u].second<<endl;
}
void p2(int u,TreeHashing&hs){
	lp(i,0,int(hs.adj[u].size()-1)){
		int v=hs.adj[u][i];
	}
}
int main(){
	ios::sync_with_stdio(0);
	int n;cin>>n;
	TreeHashing th(n);
	vector<int>d(n+1);
	lp(i,1,n-1){
		int u,v;
		cin>>u>>v;
		++d[u],++d[v];
		th.add(u,v);
	}
	th.run();
	set< long long >s;
	lp(i,1,n)if(d[i]<4){

		s.insert(th.hash[i]);
	}
	// lp(i,1,n)
	//if(make_pair(th.hash[i][0],th.hash[i][1])==make_pair(th.hash[42049][0],th.hash[42049][1]))
	//cout<<i<<endl;
	cout<<s.size()<<endl;
	#ifndef ONLINE_JUDGE
	//for(;;);
	#endif
	int u1=42049;
	int u2=43963;
	//p1(u1),p1(u2);
	return 0;
}
