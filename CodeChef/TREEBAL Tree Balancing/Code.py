from random import *
inputBuffer=[]
def getInput():
    global inputBuffer
    if not inputBuffer:
        inputBuffer+=input().split();
def getString():
    getInput()
    global inputBuffer
    return inputBuffer.pop(0)
def getInteger():
    getInput()
    global inputBuffer
    return int(inputBuffer.pop(0))
print(1)
n=50
print(n)
w=20
q=200
chd=[[] for i in range(n+1)]
C=[[] for i in range(n+1)]
D=[[] for i in range(n+1)]
def addedge(u,v,c,d):
    global chd
    global C
    global D
    chd[u].append(v)
    C[u].append(c)
    D[u].append(d)
for i in range(2,n+1):
    f=randint(1,i-1)
    chd[f].append(i)
    c=randint(1,w)
    d=randint(1,w)
    C[f].append(c)
    D[f].append(d)
    print(str(f)+" "+str(i)+" "+str(c)+" "+str(d));
'''
addedge(1,2,5,4)
addedge(1 ,3 ,15 ,15)
addedge(2, 4, 3, 2)
addedge(2, 5, 5, 1)
'''
'''print(chd[1:])
'print(C[1:])
print(D[1:])
'''
dp={}
def dodp(i):

    global q
    global dp
    global chd
    if len(chd[i])==0:
        for j in range(-q, q + 1):
            dp[(i,j)]=2**63
        dp[(i,0)]=0
        return
    for j in chd[i]:
        dodp(j)
    for j in range(-q,q+1):
        dp[(i,j)]=0
        for k in range(len(chd[i])):
            global C
            global D
            ch=chd[i][k]
            c=C[i][k]
            d=D[i][k]
            tmp=2**63
            for jj in range(-q+j,q+j+1):
                tmp=min(tmp,abs(c-jj)*d+dp[(ch,j-jj)])
            dp[(i,j)]+=tmp
ans=2**63
dodp(1)
for j in range(-q,q+1):
    ans=min(ans,dp[(1,j)])
print(ans)
from pylab import *
def drawdp(i):
    global dp
    x=range(-q,q+1)
    y=[]
    for t in x:
        y.append(dp[(i,t)])
    plot(x,y)
    show()
