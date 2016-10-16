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

#include<bits/stdc++.h>
using namespace std;
struct FastReader{
    FILE*f;
    char*p,*e;
    vector<char>v;
    void ipt(){
        for(int i=1,t;;i<<=1){
            v.resize(v.size()+i);
            if(i!=(t=fread(&v[0]+v.size()-i,1,i,f))){
                p=&v[0],e=p+v.size()-i+t;
                break;
            }
        }
    }
    void ign(){
        while(p!=e&&isspace(*p))
            ++p;
    }
    int isc(){
        return p!=e&&!isspace(*p);
    }
    int isd(){
        return p!=e&&isdigit(*p);
    }
    FastReader(FILE*_f):
        f(_f){
        ipt();
    }
    FastReader(string _f):
        f(fopen(_f.c_str(),"r")){
        ipt();
    }
    ~FastReader(){
        fclose(f);
    }
    template<class T>FastReader&operator>>(T&a){
        int n=1;
        ign();
        if(*p=='-')
            n=-1,++p;
        for(a=0;isd();)
            a=a*10+*p++-'0';
        a*=n;
        return*this;
    }
    FastReader&operator>>(char&a){
        ign();
        a=*p++;
        return*this;
    }
    FastReader&operator>>(char*a){
        for(ign();isc();)
            *a++=*p++;
        *a=0;
        return*this;
    }
    char get(){
        return*p++;
    }
};
struct FastWriter{
    FILE*f;
    vector<char>p;
    FastWriter(FILE*_f):
        f(_f){
    }
    FastWriter(string _f):
        f(fopen(_f.c_str(),"w")){
    }
    ~FastWriter(){
        if(p.size())
            fwrite(&p[0],1,p.size(),f);
        fclose(f);
    }
    FastWriter&operator<<(char a){
        p.push_back(a);
        return*this;
    }
    FastWriter&operator<<(const char*a){
        while(*a)
            p.push_back(*a++);
        return*this;
    }
    template<class T>FastWriter&operator<<(T a){
        if(a<0)
            p.push_back('-'),a=-a;
        static char t[19];
        char*q=t;
        do{
            T b=a/10;
            *q++=a-b*10+'0',a=b;
        } while(a);
        while(q>t)
            p.push_back(*--q);
        return*this;
    }
};


#include<bits/stdc++.h>
using namespace std;
template<class IFO>
struct DynamicSequence{
    struct node{
        node(IFO _ifo):
            ifo(_ifo),val(_ifo),siz(1),rev(0){
            chd[0]=chd[1]=0;
            static int g;
            wei=g=(214013*g+2531011);
        }
        IFO ifo,val;
        int siz,rev,wei;
        node*chd[2];
    }*sl,*sr;
    struct pool{
        node*ps,*pp,**ss,**sp;
        int pm,sm;
        vector<node*>ns;
        pool():
            ps((node*)malloc(sizeof(node))),pp(ps),pm(1),ss((node**)malloc(4)),sp(ss),sm(1){
            ns.push_back(ps);
        }
        ~pool(){
            free(ss);
            for(int i=0;i<ns.size();++i)
                free(ns[i]);
        }
        node*_new(IFO a){
            if(sp!=ss){
                --sp;
                **sp=node(a);
                return*sp;
            }
            if(pp==ps+pm){
                pp=ps=(node*)malloc(sizeof(node)*(pm*=2));
                ns.push_back(ps);
            }
            *pp=node(a);
            return pp++;
        }
        void _delete(node*x){
            if(sp==ss+sm){
                node**t=(node**)malloc(8*sm);
                memcpy(t,ss,4*sm);
                free(ss);
                sp=(ss=t)+sm;
                sm<<=1;
            }
            *(sp++)=x;
        }
    }mem;
    node*build(IFO*a,int l,int r){
        if(l>r)
            return 0;
        int m=l+r>>1;
        node*t=mem._new(a[m]);
        t->ch[0]=build(a,l,m-1);
        t->ch[1]=build(a,m+1,r);
        up(t);
        return t;
    }
    void clear(node*x){
        if(x)
            clear(x->chd[0]),clear(x->chd[1]),mem._delete(x);
    }
    void down(node*x){
        for(int d=0;d<2;++d){
            if(x->chd[d])
                x->ifo>>x->chd[d]->ifo;
            if(!d)
                x->ifo>>x->val;
        }
        *x->ifo;
        *x->val;
        if(x->rev){
            -x->ifo;
            for(int d=0;d<2;++d)
                if(x->chd[d])
                    x->chd[d]->rev^=1;
            swap(x->chd[0],x->chd[1]);
            x->rev=0;
        }
    }
    void up(node*x){
        x->ifo=x->val;
        x->siz=1;
        for(int d=0;d<2;++d)
            if(x->chd[d]){
                down(x->chd[d]);
                x->siz+=x->chd[d]->siz;
                x->ifo=d?x->ifo+x->chd[d]->ifo:x->chd[d]->ifo+x->ifo;
            }
    }
    node*join(node*x,node*y){
        if(!x)
            return y;
        if(!y)
            return x;
        down(x);
        down(y);
        if(x->wei<y->wei){
            x->chd[1]=join(x->chd[1],y);
            up(x);
            return x;
        } else{
            y->chd[0]=join(x,y->chd[0]);
            up(y);
            return y;
        }
    }
    node*join(node*x){
        return join(join(sl,x),sr);
    }
    int size(node*x){
        return x?x->siz:0;
    }
    void array(node*x,vector<IFO>&r){
        if(x){
            down(x);
            array(x->chd[0],r);
            r.push_back(x->val);
            array(x->chd[1],r);
        }
    }
    auto array(node*x){
        vector<IFO>r;
        array(x,r);
        return r;
    }
    void split(node*x,int p){
        if(!x){
            sl=sr=0;
            return;
        }
        down(x);
        int t=x->chd[0]?x->chd[0]->siz:0;
        if(t<p)
            split(x->chd[1],p-t-1),x->chd[1]=sl,sl=x;
        else
            split(x->chd[0],p),x->chd[0]=sr,sr=x;
        up(x);
    }
    node*split(node*x,int l,int r){
        split(x,l-1);
        node*t=sl;
        split(sr,r-l+1);
        swap(sl,t);
        return t;
    }
    void insert(node*&x,IFO a,int p){
        x=insert(&a-1,1,p);
    }
    void insert(node*&x,IFO*a,int n,int p){
        split(x,p+1,p);
        x=join(build(a,1,n));
    }
    void erase(node*&x,int p){
        erase(x,p,p);
    }
    void erase(node*&x,int l,int r){
        clear(split(x,l,r));
        x=join(0);
    }
    IFO query(node*&x,int p){
        return query(x,p,p);
    }
    IFO query(node*&x,int l,int r){
        node*t=split(x,l,r);
        IFO i=t->i;
        x=join(t);
        return i;
    }
    void modify(node*&x,IFO a,int l){
        modify(x,a,l,l);
    }
    void modify(node*&x,IFO a,int l,int r){
        node*t=split(x,l,r);
        a>>t->i;
        x=join(t);
    }
    void reverse(node*&x,int l,int r){
        node*t=split(x,l,r);
        t->r=1;
        x=join(t);
    }
    void split(node*x,IFO p,int d=0){
        if(!x){
            sl=sr=0;
            return;
        }
        down(x);
        if((!d&&x->val<p)||(d&&!(p<x->val)))
            split(x->chd[1],p,d),x->chd[1]=sl,sl=x;
        else
            split(x->chd[0],p,d),x->chd[0]=sr,sr=x;
        up(x);
    }
    node*split(node*x,IFO l,IFO r){
        split(x,l);
        node*t=sl;
        split(sr,r,1);
        swap(sl,t);
        return t;
    }
    void insert(node*&x,IFO a){
        split(x,a);
        x=join(mem._new(a));
    }
    void insert(node*&x,IFO*a,int n,IFO p){

        x=join(build(a,1,n));
    }
    void erase(node*&x,IFO p){
        return x=erase(x,p,p);
    }
    void erase(node*&x,IFO l,IFO r){
        clear(split(x,l,r));
        x=join(0);
    }
    IFO query(node*&x,IFO p){
        return query(x,p,p);
    }
    IFO query(node*&x,IFO l,IFO r){
        node*t=split(x,l,r);
        IFO i=t?t->i:IFO();
        x=join(t);
        return i;
    }
    int count(node*&x,IFO p){
        return count(x,p,p);
    }
    int count(node*&x,IFO l,IFO r){
        node*t=split(x,l,r);
        int s=t?t->siz:0;
        x=join(t);
        return s;
    }
    void modify(node*&x,IFO a,IFO l){
        modify(x,a,l,l);
    }
    void modify(node*&x,IFO a,IFO l,IFO r){
        node*t=split(x,l,r);
        if(t)
            a>>t->ifo;
        x=join(t);
    }
    void reverse(node*&x,IFO l,IFO r){
        node*t=split(x,l,r);
        if(t)
            t->r=1;
        x=join(t);
    }
    IFO predecessor(node*x,IFO a){
        IFO t;
        while(x){
            down(x);
            if(x->val<a){
                t=x->val;
                x=x->chd[1];
            } else
                x=x->chd[0];
        }
        return t;
    }
    IFO successor(node*x,IFO a){
        IFO t;
        while(x){
            down(x);
            if(a<x->val){
                t=x->val;
                x=x->chd[0];
            } else
                x=x->chd[1];
        }
        return t;
    }
    IFO front(node*x){
        IFO t;
        while(x){
            down(x);
            t=x->val;
            x=x->chd[0];
        }
        return t;
    }
    IFO back(node*x){
        IFO t;
        while(x){
            down(x);
            t=x->val;
            x=x->chd[1];
        }
        return t;
    }
};
struct ifo{
    ifo(){
    }
    void operator*(){
        y+=add;
        add=0;
    }
    void operator-(){
    }
    ll add;
    ll x,eps;
    ll y;

};
ifo operator+(const ifo&a,const ifo&b){
    ifo t;
    t.add=0;
    return t;
}
void operator>>(const ifo&a,ifo&b){
    b.add+=a.add;
}
bool operator<(const ifo&a,const ifo&b){
    if(a.x!=b.x)
        return a.x<b.x;
    return a.eps<b.eps;
}
typedef DynamicSequence<ifo> DS;
DS ds;
ll xmin=numeric_limits<ll>::min();
ll xmax=numeric_limits<ll>::max();
struct func{
    DS::node*root;
    ll xd;
    func(){
        root=0;
        xd=0;
    }
    void pf(){
        return;
        cout<<xd<<" ";
        auto tmp=ds.array(root);
        for(auto t:tmp){
            if(t.x==xmin)
                cout<<"("<<"-inf"<<","<<t.y<<")";
            else if(t.x==xmax)
                cout<<"("<<"+inf"<<","<<t.y<<")";
            else
                cout<<"("<<t.x<<","<<t.y<<")";
        }
        if(tmp.empty())
            cout<<"nothing";
        cout<<endl;
    }
    func(ll c,ll d){
        xd=0;
        root=0;
        ifo l1,r1,l2,r2;
        l1.add=0;
        l2.add=0;
        r1.add=0;
        r2.add=0;
        l1.x=xmin;
        r1.x=c;
        l2.x=c;
        r2.x=xmax;
        l1.eps=1;
        r1.eps=0;
        l2.eps=1;
        r2.eps=0;
        l1.y=-d;
        r1.y=-d;
        l2.y=d;
        r2.y=d;
        ds.insert(root,l1);
        ds.insert(root,l2);
        ds.insert(root,r1);
        ds.insert(root,r2);
        //cout<<233;
        //pf();
    }
    void add(ll x1,ll x2,ll d){
        ifo tmp,l,r;
        tmp.add=d;
        l.x=x1;
        l.eps=1;
        l.add=0;
        r.x=x2;
        r.eps=0;
        r.add=0;
        ds.modify(root,tmp,l,r);
        pf();
        if(!ds.count(root,l)){
            ll y1=ds.predecessor(root,l).y;
            ll y2=ds.successor(root,l).y;
            l.y=y2;
            ds.insert(root,l);
            l.y=y1;
            l.eps=0;
            ds.insert(root,l);
        }
        pf();
        r.eps=0;
        if(!ds.count(root,r)){
            ll y1=ds.predecessor(root,r).y;
            ll y2=ds.successor(root,r).y;
            r.y=y1;
            ds.insert(root,r);
            r.y=y2;
            r.eps=1;
            ds.insert(root,r);
        }
        pf();
    }
};
void pf(func f){
    return;
    cout<<f.xd<<" ";
    auto tmp=ds.array(f.root);
    for(auto t:tmp){
        if(t.x==xmin)
            cout<<"("<<"-inf"<<","<<t.y<<")";
        else if(t.x==xmax)
            cout<<"("<<"+inf"<<","<<t.y<<")";
        else
            cout<<"("<<t.x<<","<<t.y<<")";
    }
    if(tmp.empty())
        cout<<"nothing";
    cout<<endl;
}
func operator+(func f1,func f2){
    //cout<<"add start!\n";
    if(ds.size(f1.root)<ds.size(f2.root))
        swap(f1,f2);
    pf(f1);
    pf(f2);
    auto tmp=ds.array(f2.root);
    for(int i=0;i<tmp.size();i+=2){
        ll x1=tmp[i].x;
        ll x2=tmp[i+1].x;
        if(x1!=xmin&&x1!=xmax){
            x1+=f2.xd-f1.xd;
        }
        if(x2!=xmin&&x2!=xmax){
            x2+=f2.xd-f1.xd;
        }
        //cout<<"step "<<i<<":"<<x1<<" "<<x2<<" "<<tmp[i+1].y<<endl;
        f1.add(x1,x2,tmp[i+1].y);

        //pf(f1);
    }
    ds.clear(f2.root);
    //cout<<"ok,ansis:\n";
    pf(f1);
    //cout<<endl;
    return f1;
}
func trans(func f,ll c,ll d,ll&x0,ll&x1){
    while(ds.front(f.root).y<-d){
        ds.erase(f.root,1);
    }
    ll tmp;
    if((tmp=ds.front(f.root).x)!=xmin){
        ifo l,r;
        l.add=r.add=0;
        l.eps=1;
        r.eps=0;
        l.x=xmin;
        r.x=tmp;
        l.y=-d;
        r.y=-d;
        ds.insert(f.root,l);
        ds.insert(f.root,r);
    }
    x0=tmp;
    while(ds.back(f.root).y>d){
        ds.erase(f.root,f.root->siz);
    }
    if((tmp=ds.back(f.root).x)!=xmax){
        ifo l,r;
        l.add=r.add=0;
        l.eps=1;
        r.eps=0;
        l.x=tmp;
        r.x=xmax;
        l.y=d;
        r.y=d;
        ds.insert(f.root,l);
        ds.insert(f.root,r);
    }
    x1=tmp;
    f.xd+=c;
    if(x0!=xmin)
        x0+=f.xd;
    if(x1!=xmax)
        x1+=f.xd;
    return f;
}
int n;
vector<int>to[200010];
vector<int>C[200010];
vector<int>D[200010];
vector<int>eid[200010];
ll cst[200010];
ll lt[200010],rt[200010];
int islead[200010];
ll fc[200010];
ll fd[200010];
func dfs(int u,int p=0){
    func f;
    islead[u]=1;
    for(int i=0;i<to[u].size();++i){
        int v=to[u][i];
        if(v==p)
            continue;
        islead[u]=0;
        int c=C[u][i],d=D[u][i];
        fc[v]=c;
        fd[v]=d;
        auto f2=dfs(v,u);
        if(islead[v]){
            f=f+func(c,d);
            lt[v]=c;
            rt[v]=c;
        } else{
            f=f+trans(f2,c,d,lt[v],rt[v]);
        }
    }
    return f;
}
ll glb=0;
void dp(int u,ll ax,int p=0){
    if(islead[u])
        return;
    for(int i=0;i<to[u].size();++i){
        int v=to[u][i];
        if(v==p)
            continue;
        int c=C[u][i],d=D[u][i];
        int id=eid[u][i];
        if(ax>=lt[v]&&ax<=rt[v]){
            dp(v,ax-c,u);
            cst[id]=c;
        } else if(ax>rt[v]){
            dp(v,rt[v]-c,u);
            cst[id]=ax-rt[v]+c;
            glb+=(ax-rt[v])*d;
        } else{
            dp(v,lt[v]-c,u);
            cst[id]=ax-lt[v]+c;
            glb+=(-ax+lt[v])*d;
        }
    }
}
void _main(){
    FastReader fr(stdin);
    FastWriter fw(stdout);
    int T;fr>>T;
    while(T--){
        fr>>n;
    L(i,1,n)
        to[i].clear(),C[i].clear(),D[i].clear(),eid[i].clear();
    L(i,1,n-1){
        int u,v,c,d;
        fr>>u>>v>>c>>d;
        to[u].push_back(v);
        C[u].push_back(c);
        D[u].push_back(d);
        eid[u].push_back(i);
        to[v].push_back(u);
        C[v].push_back(c);
        D[v].push_back(d);
        eid[v].push_back(i);
    }
    auto f=dfs(1);
    auto v=ds.array(f.root);
    ll ansx;
    for(int i=0;i+1<v.size();++i){
        if(v[i].y<=0&&v[i+1].y>0)
            ansx=v[i].x+f.xd;
    }
    ds.clear(f.root);
    glb=0;
    dp(1,ansx);
    fw<<glb<<'\n';
    L(i,1,n-1)
        fw<<cst[i]<<'\n';
    }
}
/*
4
5
1 2 5 4
1 3 15 15
2 4 3 2
2 5 5 1
5
1 2 5 4
1 3 15 15
2 4 3 2
2 5 5 1
50
1 2 6 10
2 3 4 8
3 4 17 5
3 5 7 13
4 6 19 8
6 7 7 18
3 8 15 19
6 9 16 3
1 10 16 3
2 11 11 3
9 12 11 3
6 13 14 13
7 14 17 2
10 15 1 9
1 16 8 15
14 17 7 20
1 18 2 14
16 19 6 9
19 20 7 19
9 21 8 11
4 22 18 16
17 23 18 16
8 24 10 14
9 25 11 13
18 26 1 13
19 27 6 16
11 28 8 19
3 29 18 12
3 30 15 5
10 31 14 16
2 32 14 1
19 33 18 7
9 34 10 1
8 35 14 17
19 36 2 1
29 37 17 11
19 38 8 14
15 39 6 13
17 40 13 19
29 41 19 9
22 42 19 8
24 43 6 20
8 44 17 6
8 45 20 6
23 46 3 12
9 47 3 14
11 48 11 1
27 49 5 15
43 50 6 3
50
1 2 20 13
2 3 9 3
2 4 8 5
2 5 16 4
5 6 13 18
1 7 7 12
3 8 1 19
8 9 7 5
5 10 10 6
6 11 15 4
5 12 5 6
4 13 14 4
6 14 14 20
12 15 5 11
4 16 14 18
14 17 1 11
8 18 16 1
8 19 14 12
19 20 7 11
5 21 6 19
8 22 1 17
1 23 3 10
7 24 2 1
2 25 13 17
4 26 12 6
16 27 5 17
3 28 16 9
5 29 13 19
21 30 11 17
12 31 7 7
25 32 8 14
17 33 4 14
5 34 4 9
12 35 8 17
12 36 13 8
11 37 5 19
29 38 16 17
2 39 14 14
23 40 8 12
5 41 19 2
14 42 3 19
40 43 2 8
37 44 15 19
14 45 2 13
15 46 12 1
16 47 15 20
13 48 14 1
23 49 8 9
32 50 19 17
*/