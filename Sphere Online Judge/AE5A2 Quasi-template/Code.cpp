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
#include<bits/stdc++.h>
using namespace std;
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
        }while(a);
        while(q>t)
            p.push_back(*--q);
        return*this;
    }
};
FastWriter fw(stdout);
#include<bits/stdc++.h>
using namespace std;
#if __GNUC__
    #if __x86_64__||__ppc64__
        extern int _main(void) __asm__ ("_main");
    #else
        extern int _main(void) __asm__ ("__main");
    #endif
    int Main();
    int _main() {
        Main();
        exit(0);
    }
    int main(){
        __asm__ __volatile__(
            #if __x86_64__||__ppc64__
                "movq %0,%%rsp\n"
                "pushq $exit\n"
                "jmp _main\n"
            #else
                "movl %0,%%esp\n"
                "pushl $_exit\n"
                "jmp __main\n"
            #endif
                ::"r"((char *)malloc(1<<28)+(1<<28))
        );
    }
#elif defined(_MSC_VER)
    #pragma comment(linker,"/STACK:1024000000,1024000000")
    #define Main main
#endif
#include<bits/stdc++.h>
using namespace std;
template<class T>struct StringMatching{
    StringMatching(T*p,int t=1):
        b(2,p[1]),f(2),l(2){
        for(int i=0;p[l]?1:(--l,0);b.push_back(p[l++])){
            for(;i&&p[i+1]!=p[l];i=f[i]);
            f.push_back(i=i+(p[i+1]==p[l]));
        }
        for(int i=2;t&&i<l;++i)
            if(p[f[i]+1]==p[i+1])
                f[i]=f[f[i]];
    }
    int run(T*t,int k=0){
        for(int i=k?k+l:1,j=k?f[l]:0;t[i];++i){
            for(;j&&b[j+1]!=t[i];j=f[j]);
            if((j+=b[j+1]==t[i])==l)
                return i-l+1;
        }
        return 0;
    }
    int l;
    vector<T>b;
    vector<int>f;
};
StringMatching<char>*smm;
#include<bits/stdc++.h>
using namespace std;
template<class T,int N,int M,T D>struct SuffixTree{
    int node(){
        pr[++nc]=dp[nc]=sf[nc]=0;
        memset(tr[nc],0,4*M);
        return nc;
    }
    void build(const T*s,int n){
        nc=0,node();
        for(int i=n-1,c,p=1,q,np,nq;i>=0;--i,p=np){
            dp[np=node()]=dp[p]+1,id[np]=i+1,sf[np]=1;
            for(c=s[i]-D;p&&!tr[p][c];p=pr[p])
                tr[p][c]=np;
            if(p&&dp[q=tr[p][c]]!=dp[p]+1){
                dp[nq=node()]=dp[p]+1,pr[nq]=pr[q],id[nq]=i+1;
                memcpy(tr[pr[q]=pr[np]=nq],tr[q],4*M);
                for(;p&&tr[p][c]==q;p=pr[p])
                    tr[p][c]=nq;
            }else
                pr[np]=p?q:1;
        }
        for(int i=2,j,c;i<=nc;++i)
            c=s[id[i]+dp[j=pr[i]]-1]-D,
            el[j][c]=s+id[i]+dp[j]-1,
            er[j][c]=s+id[i]+dp[ch[j][c]=i]-1;
    }
    const T*el[2*N][M],*er[2*N][M];
    int nc,pr[2*N],tr[2*N][M],dp[2*N],id[2*N],sf[2*N],ch[2*N][M];
};
int quickmi,quickcnt,quickstop;
int quickmx,quickgap;
#include<bits/stdc++.h>
using namespace std;
template<class T,class U>struct MergeableSet{
    struct node{
//        node(T _f):f(_f){
//            c[0]=c[1]=0;
//        }
        T f;
        node*c[2];
    };
    static node nds[4000010*2];static int nps;
    node*newnode(T f){
              node*p=nds+nps++;
    //          if(nps%10000==0)
        //      fw<<nps<<'\n';
              p->f=f;
              p->c[0]=p->c[1]=0;
              return p;
    }
    MergeableSet(U l,U r):vl(l),vr(r){
    }
    inline void update(node*x){
        if(x->c[0]&&x->c[1])
            x->f=x->c[0]->f+x->c[1]->f;
        else
            x->f=x->c[0]?x->c[0]->f:x->c[1]->f;
    }
    node*insert(node*x,T f,U v,U l=0,U r=0){
        if(!l&&!r)
            l=vl,r=vr;
        if(l==r){
            if(x)
                x->f=x->f+f;
            else
                x=newnode(f);
        }else{
            U m=l+(r-l)/2;
            int d=v>m;
            node*y=insert(x?x->c[d]:0,f,v,d?m+1:l,d?r:m);
            if(!x)
                x=newnode(y->f);
            x->c[d]=y,update(x);
        }
        return x;
    }
    node*erase(node*x,U v,U l=0,U r=0){
        if(!l&&!r)
            l=vl,r=vr;
        if(l==r){
            //delete x;
            return 0;
        }
        U m=l+(r-l)/2;
        int d=v>m;
        x->c[d]=erase(x?x->c[d]:0,v,d?m+1:l,d?r:m);
        if(!x->c[0]&&!x->c[1]){
            //delete x;
            return 0;
        }
        update(x);
        return x;
    }
    node*merge(node*x,node*y,U l=0,U r=0){
        if(!l&&!r)
            l=vl,r=vr;
        if(!x||!y)
            return x?x:y;
        if(l==r)
            x->f=x->f+y->f;
        else{
            U m=l+(r-l)/2;
            x->c[0]=merge(x->c[0],y->c[0],l,m);
            x->c[1]=merge(x->c[1],y->c[1],m+1,r);
            update(x);
        }
        return x;
    }
    void query2(node*x,U ql,U qr,U l,U r){
        if(!x||ql>r||qr<l)
            return;
        if(ql<=l&&qr>=r){
        if(quickmi>x->f.mi)
            quickmi=x->f.mi;
        if(quickmx<x->f.mx)
            quickmx=x->f.mx;
        if(quickgap<x->f.mxgap)
            quickgap=x->f.mxgap;
        return;
        }
        U m=l+(r-l)/2;
        query2(x->c[0],ql,qr,l,m),
          query2(x->c[1],ql,qr,m+1,r);
        }
    void qquery(node*x,U ql,U qr,U l,U r){
        if(!x||ql>r||qr<l)
            return;
        if(ql<=l&&qr>=r){
        if(quickmi>x->f.mi)
            quickmi=x->f.mi;
        quickcnt+=x->f.cnt;
        return;
        }
        U m=l+(r-l)/2;
        qquery(x->c[0],ql,qr,l,m),
          qquery(x->c[1],ql,qr,m+1,r);
        }
    void destroy(node*u){
        if(u)
            destroy(u->c[0]),
            destroy(u->c[1]),
            delete u;
    }
    U vl,vr;
};
template<class T,class U>int MergeableSet<T,U>::nps=0;
template<class T,class U> typename MergeableSet<T,U>::node MergeableSet<T,U>::nds[4000010*2];
struct info{
    info(int v){
        l=r=v;
        mxgap=-1;
        mx=v;
        mi=v;
        cnt=1;
    }
    info(){
    }
    int l,r;
    int mx,mi,mxgap,cnt;
};
inline info operator+(info a,info b){
    info c;
    if(a.l>b.l)
        swap(a,b);
    c.l=a.l;
    c.r=b.r;
    c.mi=a.mi;
    c.cnt=a.cnt+b.cnt;
    c.mx=b.mx;
    if(quickstop)return c;
    c.mxgap=max(a.mxgap,b.mxgap);
    c.mxgap=max(c.mxgap,b.mi-a.mx);
    return c;
}
const int NN=200010;
SuffixTree<char,NN,26,'a'>st;
int n;char s[NN];
char*ansptr;
MergeableSet<info,int>*ms;
MergeableSet<info,int>::node*ns[NN*2];
int anslen;
long long ansnum;
struct pans{
    int start,endmi,endmx,nodeid;
};
pans panss[2*NN],pa2[2*NN];int pansssize;
int pht;
void trv(int u,int tail=n+1){
    ++pht;int ct=pht;
    //cout<<u<<":"<<st.sf[u]<<" "<<st.dp[u]<<endl;
    if(u==1){
        for(int i=0;i<26;++i)
            if(st.ch[u][i]){
                //cout<<u<<"-"<<char(i+'a')<<"-"<<st.ch[u][i]<<endl;
                trv(st.ch[u][i]);
            }
    }else{
        if(st.sf[u])
            ns[u]=ms->insert(0,info(st.id[u]),st.id[u]);
        for(int i=0;i<26;++i)
            if(st.ch[u][i]){
                //cout<<u<<"-"<<char(i+'a')<<"-"<<st.ch[u][i]<<endl;
                trv(st.ch[u][i],st.sf[u]?st.id[u]:tail);
                ns[u]=ms->merge(ns[u],ns[st.ch[u][i]]);
            }
        const info&ifo=ns[u]->f;
        int mxgap=ifo.mxgap;
        if(mxgap<0)mxgap=0;
        if(st.dp[u]<mxgap)
            return;
        int canr=st.dp[u];
        int canl=mxgap;
        if(canl<st.dp[st.pr[u]]+1)
            canl=st.dp[st.pr[u]]+1;
        if(ifo.mi!=1){
            if(canr<=ifo.mi-1)
                return;
            canl=max(canl,ifo.mi);
        }
        int tmp=tail-ifo.mx;
        if(canr<tmp)
            return;
        canl=max(canl,tmp);
        pans pa;
        pa.start=ifo.mi;
       // pa.coverl=canl;
        pa.endmi=ifo.mi+canl-1;
        pa.endmx=ifo.mi+canr-1;
        pa.nodeid=ct;
        panss[pansssize++]=(pa);
    }
}
bool operator<(pans a,pans b){
    return a.start>b.start;
}
int toobg[NN],toonx[NN],toova[NN],tooptr;
inline void addtoo(int u,int v){
    int t=++tooptr;
    toova[t]=v;
    toonx[t]=toobg[u];
    toobg[u]=t;
}
int to2bg[NN],to2nx[NN],to2va[NN],to2ptr;
inline void addto2(int u,int v){
    int t=++to2ptr;
    to2va[t]=v;
    to2nx[t]=to2bg[u];
    to2bg[u]=t;
}
MergeableSet<info,int>::node*seg=0;
int cur;
void push(int u){
    while(cur>u){
        --cur;
        for(int i=to2bg[cur];i;i=to2nx[i]){
            int v=to2va[i];
            seg=ms->insert(seg,info(v),v);
        }
    }
}
MergeableSet<info,int>::node*ss2;
int stk[NN];int stks;
void dfs(int u){
    for(int i=toobg[u];i;i=toonx[i]){
        int v=toova[i];
        stk[++stks]=v;
        dfs(v);
        --stks;
    }
    if(!u)
        return;
    int mybest=0;
    int l=1,r=stks;
    while(true){
        if(l==r){
            mybest=max(mybest,min(stk[l]+1,u-stk[l]+1));
            break;
        }
        int m=(l+r)/2;
        if(stk[m]<=u/2){
            mybest=max(mybest,min(stk[m]+1,u-stk[m]+1));
            l=m+1;
        }else{
            mybest=max(mybest,min(stk[m+1]+1,u-stk[m+1]+1));
            r=m;
        }
    }
// co

    addto2(mybest,u);
    //to2[mybest].push_back(u);
}
FastReader fr(stdin);
//auto fr=cin;
//#define fr cin

void sort(){
    static int c[NN];
    for(int i=0;i<pansssize;++i)
        ++c[n-panss[i].start+1];
    for(int i=1;i<=n;++i)
        c[i]+=c[i-1];
    for(int i=0;i<pansssize;++i)
        pa2[--c[n-panss[i].start+1]]=panss[i];
}
int ansst,ansid,ansbg;
int Main(){
   //st/ring t;
    //cin>>t;
    //freopen(("sza"+t+".in").c_str(),"r",stdin);
    //freopen("1.txt","w",stdout);
    //BigStack;
    //chkstk(5000000);
    //freopen("in.txt","r",stdin);
    fr>>s;
    //for(int i=0;i<200000;++i)
        //s[i]='a'+rand()%26;
    n=strlen(s);
   // cout<<n<<endl;
    //return 0;
    st.build(s,n);
    anslen=n+1;
    cur=n+1;
    smm=new StringMatching<char>(s-1,0);
    for(int i=1;i<=n;++i){
        addtoo(smm->f[i],i);
        //too[].push_back(i);
        //cout<<i<<" "<<smm->f[i]<<endl;
    }
    ms=new MergeableSet<info,int>(1,n);
    trv(1);
    quickstop=1;
    sort();
//    for(auto t:panss){
//        cout<<"start:"<<t.start<<endl;
//        cout<<"endmi:"<<t.endmi<<endl;
//        cout<<"endmx:"<<t.endmx<<endl;
//        cout<<endl;
//    }
    dfs(0);
    for(int i=0;i<pansssize;++i){
        int start=pa2[i].start;
        int endmi=pa2[i].endmi;
        int endmx=pa2[i].endmx;
        push(start);
        quickmi=~0u>>1;
        quickcnt=0;
        ms->qquery(seg,endmi,endmx,1,n);
        //vector<info>ifo=ms->query(seg,endmi,endmx);
        if(quickmi==~0u>>1)continue;
        //cout<<start<<" "<<endmi<<" "<<endmx<<":"<<ifo[0].cnt<<endl;
        ansnum+=quickcnt;
        //hasmin[pa2[i].nodeid]=quickmi-start+1;
        int ty=quickmi-start+1;
        if(ty<anslen||(ty==anslen&&pa2[i].nodeid<ansid)){
            anslen=ty;
            ansid=pa2[i].nodeid;
            ansbg=start;
        }
    }
    fw<<ansnum<<'\n';
    for(int i=0;i<anslen;++i)
        fw<<s[ansbg+i-1];
    fw<<'\n';
    //fw<<MergeableSet<info,int>::ns<<endl;
    return 0;
}
