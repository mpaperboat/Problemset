#include<bits/stdc++.h>
using namespace std;
#define lp(i,l,r)for(auto i=l;i<=r;++i)
#define rp(i,r,l)for(auto i=r;i>=l;--i)
void _main();
int main(){
    ios::sync_with_stdio(0);
    _main();
    #ifndef ONLINE_JUDGE
    //for(;;);
    #endif
    return 0;
}
struct C{
    C(int a=0,int b=0){
        c2=a;
        c5=b;
    }
    bool z(){
        return c2==0&&c5==0;
    }
    int c2,c5;
    int ans(){
        return min(c2,c5);
    }
};
static C cnt[100010];
C cntsum[100010];
C operator+(C a,C b){
    return C(a.c2+b.c2,a.c5+b.c5);
}
C operator-(C a,C b){
    return C(a.c2-b.c2,a.c5-b.c5);
}
C operator*(C a,int b){
    return C(a.c2*b,a.c5*b);
}
struct node{
    int l,r;
    node*lc,*rc;
    C s;
    C addtag;
    int rp_s;
    C rp_y;
    void down(){
        if(rp_s){
            if(lc){
                lc->addtag=C();
                rc->addtag=C();
                lc->rp_y=rp_y;
                rc->rp_y=rp_y;
                lc->rp_s=rp_s;
                rc->rp_s=rp_s+lc->r-lc->l+1;
            }
            s=rp_y*(r-l+1)+cntsum[rp_s+r-l]-cntsum[rp_s-1];
            rp_s=0;
        }
        if(!addtag.z()){
            s=s+addtag*(r-l+1);
            if(lc){
                lc->addtag=lc->addtag+addtag;
                rc->addtag=rc->addtag+addtag;
            }
            addtag=C();
        }
    }
    void up(){
        if(lc){
            lc->down();
            rc->down();
            s=lc->s+rc->s;
        }
    }
};
C fuck(int x);
node*build(int*a,int l,int r){
    node*t=new node;
    t->l=l;
    t->r=r;
    t->addtag=C();
    t->rp_s=0;
    if(l==r){
        t->s=fuck(a[l]);
        t->lc=t->rc=0;
    } else{
        int m=(l+r)/2;
        t->lc=build(a,l,m);
        t->rc=build(a,m+1,r);
        t->up();
    }
    return t;
}
C query(node*x,int l,int r){
    x->down();
    if(l<=x->l&&r>=x->r)
        return x->s;
    int m=(x->l+x->r)/2;
    C ret;
    if(l<=m)
        ret=ret+query(x->lc,l,r);
    if(r>m)
        ret=ret+query(x->rc,l,r);
    return ret;
}
void add(node*x,int l,int r,C ad){
    x->down();
    if(l<=x->l&&r>=x->r)
        x->addtag=ad;
    else{
        int m=(x->l+x->r)/2;
        if(l<=m)
            add(x->lc,l,r,ad);
        if(r>m)
            add(x->rc,l,r,ad);
        x->up();
    }
}
void rep(node*x,int l,int r,C rpy,int rps){
    x->down();
    if(l<=x->l&&r>=x->r){
        x->rp_s=rps;
        x->rp_y=rpy;
    }
    else{
        int m=(x->l+x->r)/2;
        if(r<=m){
            rep(x->lc,l,r,rpy,rps);
        } else if(l>m){
            rep(x->rc,l,r,rpy,rps);
        } else{
            rep(x->lc,l,m,rpy,rps);
            rep(x->rc,m+1,r,rpy,rps+m-l+1);
        }
        x->up();
    }
}
void remove(node*x){
    if(x){
        remove(x->lc);
        remove(x->rc);
        delete x;
    }
}

C fuck(int x){
    C ttt;
    while(x%2==0){
        x/=2;
        ttt.c2++;
    }
    while(x%5==0){
        x/=5;
        ttt.c5++;
    }
    return ttt;
}

void _main2(){
    lp(i,2,100000){
        if(i%2==0)
            cnt[i].c2=cnt[i/2].c2+1;
        if(i%5==0)
            cnt[i].c5=cnt[i/5].c5+1;
        cntsum[i]=cnt[i]+cntsum[i-1];
    }
    int T;cin>>T;
    while(T--){
        int n,m;
        cin>>n>>m;
        
        static int a[100010];
        lp(i,1,n)cin>>a[i];
        static C haha[100010];
        lp(i,1,n)
            haha[i]=fuck(a[i]);
        long long ans=0;
        lp(i,1,m){
            int tp;cin>>tp;
            int lt,rt;cin>>lt>>rt;
            if(tp==1){
                int x;cin>>x;
                //add(r,lt,rt,cnt[x]);
                lp(j,lt,rt)
                    haha[j]=haha[j]+fuck(x);
            } else if(tp==2){
                int x;cin>>x;
                //rep(r,lt,rt,cnt[x],1);
                lp(j,lt,rt)
                    haha[j]=fuck(x)+cnt[j-lt+1];
            } else{
                C tmp;
                lp(j,lt,rt)
                    tmp=tmp+haha[j];
                ans+=tmp.ans();
            }
        }
        cout<<ans<<endl;
    }
}
void _main(){
    lp(i,2,100000){
        if(i%2==0)
            cnt[i].c2=cnt[i/2].c2+1;
        if(i%5==0)
            cnt[i].c5=cnt[i/5].c5+1;
        cntsum[i]=cnt[i]+cntsum[i-1];
    }
	int T;cin>>T;
    while(T--){
        int n,m;
        cin>>n>>m;
        static int a[100010];
        lp(i,1,n)cin>>a[i];
        node*r=build(a,1,n);
        long long ans=0;
        lp(i,1,m){
            int tp;cin>>tp;
            int lt,rt;cin>>lt>>rt;
            if(tp==1){
                int x;cin>>x;
                add(r,lt,rt,fuck(x));
            } else if(tp==2){
                int x;cin>>x;
                rep(r,lt,rt,fuck(x),1);
            } else{
                ans+=query(r,lt,rt).ans();
            }
        }
        remove(r);
        cout<<ans<<endl;
	}
}

/*
 *
 *

 
 
 
 
 2
5 5
2 4 3 5 5
3 2 4
3 2 5
2 2 4 1
1 3 3 10
3 1 5
 
 5 5
2 4 3 5 5
3 2 4
3 2 5
2 2 4 1
1 3 3 10
3 1 5
 
 
 
 
 */