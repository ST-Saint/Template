#include<bits/stdc++.h>

#define set(a,b) memset(a,(b),sizeof(a))

using namespace std;

typedef long long ll;

const int maxp=26;
const int maxn=2e5+5;

string str;
ll num[maxn],ans;
int T,sz,p,np;

struct Suffix_Automaton{
  int trans[maxp],par,len,right,pos;
}SAM[maxn];

struct Suffix_Tree{
  int e[maxp];
}Suf[maxn];

void Insert(int u,int v,char c){
  Suf[u].e[c-'a']=v;
}

void Dfs(int x){
  for(int i=0;i<maxp;i++)
    if( Suf[x].e[i]!=0 ){
      Dfs(Suf[x].e[i]);
      SAM[x].right+=SAM[Suf[x].e[i]].right;
    }
}

void Suffix_Tree_Build(){
  for(int i=1;i<=sz;i++) set(Suf[i].e,0);
  for(int i=2;i<=sz;i++)
    Insert(SAM[i].par,i,str[SAM[i].pos-SAM[SAM[i].par].len]);
  Dfs(1);
}

void Extend(char ch,int k){
  int c=ch-'a';
  np=++sz,set(SAM[np].trans,0);
  SAM[np].right=1,SAM[np].len=SAM[p].len+1,SAM[np].pos=k;
  while( !SAM[p].trans[c] && p ) SAM[p].trans[c]=np,p=SAM[p].par;
  if( p==0 ) SAM[np].par=1;
  else{
    int q=SAM[p].trans[c];
    if( SAM[q].len==SAM[p].len+1 ) SAM[np].par=q;
    else{
      int nq=++sz;
      SAM[nq]=SAM[q],SAM[nq].right=0,SAM[nq].len=SAM[p].len+1;
      SAM[np].par=SAM[q].par=nq;
      while( SAM[p].trans[c]==q && p ) SAM[p].trans[c]=nq,p=SAM[p].par;
    }
  }
  p=np;
}

int main(){
#ifndef ONLINE_JUDGE
  freopen("Suffix_Tree.in","r",stdin);
  freopen("Suffix_Tree.out","w",stdout);
#endif
  ios::sync_with_stdio(false);
  cin >> T ;
  while( T-- ){
    cin >> str ;
    reverse(str.begin(),str.end());
    p=np=sz=1;
    set(SAM[np].trans,0);
    for(int i=0;i<(int)str.size();i++) Extend(str[i],i);
    Suffix_Tree_Build();
  }
  return 0;
}
