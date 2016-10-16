#include<bits/stdc++.h>
#define lp(i,l,r)for(auto i=l;i<=r;++i)
#define rp(i,r,l)for(auto i=r;i>=l;--i)
using namespace std;
typedef long long ll;
typedef long double ld;
int n,m,e[80010];
ll s[80010];
namespace ac{
    ll calc(int i,int j){
        if(j%i==0)
            return 0;
        ll t=s[i-1];
        int h=j/i+1;
        int ii=i-j/h;
        int jj=j%h;
        ll t2=calc(ii,jj)+s[ii]*(j/h);
        return min(t,t2);
    }
}
namespace dp{
    int f[80][800][800];
    void print(int i,int j,int k){
        if(i==1){
            cout<<j<<" ";
        } else if(k==0){
            lp(t,1,i)
                cout<<"0 ";
        } else if(k*i==j){
            lp(t,1,i)
                cout<<k<<" ";
        } else{
            rp(i2,i-1,1){
                if(j-(i-i2)*k<0)
                    break;
                lp(k2,0,k-1){
                    if(k2>j-(i-i2)*k)
                        break;
                    if(f[i2][j-(i-i2)*k][k2]==~0u>>1)
                        continue;
                    int tmp=f[i2][j-(i-i2)*k][k2]+s[i2]*(i-i2);
                    if(tmp==f[i][j][k]){
                        print(i2,j-(i-i2)*k,k2);
                        lp(t,i2+1,i)
                            cout<<k<<" ";
                        return;
                    }
                }
            }
        }
    }
    void run(){

        lp(i,1,n)lp(j,0,m)lp(k,0,j){
            if(i==1){
                if(j==k){
                    f[i][j][k]=0;
                } else{
                    f[i][j][k]=~0u>>1;
                }
            } else if(k==0){
                if(j==0){
                    f[i][j][k]=0;
                } else{
                    f[i][j][k]=~0u>>1;
                }
            } else{
                f[i][j][k]=~0u>>1;
                rp(i2,i-1,1){
                    if(j-(i-i2)*k<0)
                        break;
                    lp(k2,0,k-1){
                        if(k2>j-(i-i2)*k)
                            break;
                        if(f[i2][j-(i-i2)*k][k2]==~0u>>1)
                            continue;
                        int tmp=f[i2][j-(i-i2)*k][k2]+s[i2]*(i-i2);
                        if(tmp<f[i][j][k])
                            f[i][j][k]=tmp;
                    }
                }
                if(k*i==j){
                    f[i][j][k]=0;
                }
            }
            //if(f[i][j][k]!=~0u>>1)printf("(%d,%d,%d,%d)\n",i,j,k,f[i][j][k]);
        }
        int ans=~0u>>1;
        lp(k,0,m)
            if(f[n][m][k]<ans)
                ans=f[n][m][k];
        cout<<ans<<endl;
        //lp(k,0,m)
         //   if(f[n][m][k]==ans)
              //  cout<<"[",print(n,m,k),cout<<endl;
       // cout<<endl<<endl;
    }
}
int main(){
    int T;cin>>T;
    while(T--){
     
    
    //srand(time(0));
    //int n=33;
    //lp(i,1,n)
    //    dp::e[i]=rand()%77;
   // sort(dp::e+1,dp::e+n+1);
   // cout<<n<<endl;
    //lp(i,1,n)
    //    cout<<dp::e[i]<<" ";
    //cout<<endl;
   // cout<<endl;
   // lp(m,0,400){
        //cout<<m<<endl;
        cin>>n>>m;
        lp(i,1,n)
            cin>>e[i];
        sort(e+1,e+n+1);
        s[0]=0;
        lp(i,1,n)
            s[i]=s[i-1]+e[i];
        //dp::run();
        cout<<ac::calc(n,m)<<endl;
    }
   // }
    return 0;
}
/*
1
10 26
1 3 4 5 5 6 7 9 9 10

100
10 30
1 3 4 5 5 6 7 9 9 10
10 29
1 3 4 5 5 6 7 9 9 10
10 28
1 3 4 5 5 6 7 9 9 10
10 27
1 3 4 5 5 6 7 9 9 10
10 26
1 3 4 5 5 6 7 9 9 10
10 25
1 3 4 5 5 6 7 9 9 10
10 24
1 3 4 5 5 6 7 9 9 10
10 23
1 3 4 5 5 6 7 9 9 10
10 22
1 3 4 5 5 6 7 9 9 10
10 21
1 3 4 5 5 6 7 9 9 10
10 20
1 3 4 5 5 6 7 9 9 10
10 19
1 3 4 5 5 6 7 9 9 10
10 18
1 3 4 5 5 6 7 9 9 10
10 17
1 3 4 5 5 6 7 9 9 10
10 16
1 3 4 5 5 6 7 9 9 10
10 15
1 3 4 5 5 6 7 9 9 10
10 14
1 3 4 5 5 6 7 9 9 10
10 13
1 3 4 5 5 6 7 9 9 10
10 12
1 3 4 5 5 6 7 9 9 10
10 11
1 3 4 5 5 6 7 9 9 10
10 10
1 3 4 5 5 6 7 9 9 10
10 9
1 3 4 5 5 6 7 9 9 10
10 8
1 3 4 5 5 6 7 9 9 10
10 7
1 3 4 5 5 6 7 9 9 10
10 6
1 3 4 5 5 6 7 9 9 10
10 5
1 3 4 5 5 6 7 9 9 10
10 4
1 3 4 5 5 6 7 9 9 10
10 3
1 3 4 5 5 6 7 9 9 10
10 2
1 3 4 5 5 6 7 9 9 10
10 1
1 3 4 5 5 6 7 9 9 10
10 0
1 3 4 5 5 6 7 9 9 10
*/