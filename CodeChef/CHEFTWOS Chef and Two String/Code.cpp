#include<bits/stdc++.h>
#define L(i,l,r)for(auto i=l;i<=r;++i)
#define R(i,r,l)for(auto i=r;i>=l;--i)
#define M int T;cin>>T;L(I,1,T)
using namespace std;
typedef long long ll;
typedef long double ld;
void _main();
int main(){
    ios::sync_with_stdio(0);
    _main();
    return 0;
}


void _main(){
    M{
        string a,b;
        cin>>a>>b;
        int n=a.size();
        static int f[100010][6][6];
        f[0][0][0]=1;
        static int tr[6][300];
        L(i,0,5)tr[i]['1']=tr[i]['2']=-1;
        tr[0]['2']=1;
        tr[1]['2']=2;
        tr[2]['1']=3;
        tr[3]['1']=4;
        tr[4]['1']=4;
        tr[4]['2']=5;
        tr[0]['1']=4;
        tr[5]['2']=2;
        tr[3]['2']=5;
        L(i,1,n){
            L(j,0,5)L(k,0,5)
                f[i][j][k]=0;
            //not swap
            L(j,0,5)L(k,0,5){
                if(tr[j][a[i-1]]!=-1&&tr[k][b[i-1]]!=-1){
                    f[i][tr[j][a[i-1]]][tr[k][b[i-1]]]+=f[i-1][j][k];
                    //if(f[i-1][j][k]){
                       // cout<<i-1<<" "<<j<<" "<<k<<endl;
                        //cout<<i<<" "<<tr[j][a[i-1]]<<" "<<tr[k][b[i-1]]<<endl;
                   // }
                    f[i][tr[j][a[i-1]]][tr[k][b[i-1]]]%=int(1e9+7);
                }
            }
            swap(a[i-1],b[i-1]);
            L(j,0,5)L(k,0,5){
                if(tr[j][a[i-1]]!=-1&&tr[k][b[i-1]]!=-1){
                    f[i][tr[j][a[i-1]]][tr[k][b[i-1]]]+=f[i-1][j][k];
                    f[i][tr[j][a[i-1]]][tr[k][b[i-1]]]%=int(1e9+7);
                }
            }
        }
        //cout<<f[1][4][4]<<endl;
        int ans=0;
        L(j,4,5)L(k,4,5)ans=(ans+f[n][j][k])%int(1e9+7);
        ans=(ans+f[n][1][1])%int(1e9+7);
        ans=(ans+f[n][1][4])%int(1e9+7);
        ans=(ans+f[n][4][1])%int(1e9+7);
        cout<<ans<<endl;
    }
}
/*

4
1111
2211
222
111
1111
2211
222
111

*/