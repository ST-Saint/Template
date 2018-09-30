#include<bits/stdc++.h>

#define set(a,b) memset(a,(b),sizeof(a))

using namespace std;

typedef long long ll;
typedef pair<int,int> pii;

const int maxp=26;
const int maxn=1e5+5;

string str;
int fail[maxn],End[maxn],sz;
int first[maxn],ind;

struct Side{
  int u,v,next;
  Side(int u=0,int v=0):u(u),v(v),next(first[u]){first[u]=ind;}
}s[maxn];

struct AC_Automaton{
  int trans[maxp];
  void Init(){
    set(trans,0);
  }
}AC[maxn];

void Insert(int u,int v){
  s[ind]=Side(u,v),ind++;
}

int Extend(string s){
  int p=0,c;
  for(int i=0;i<(int)s.size();i++){
    c=s[i]-'a';
    if( !AC[p].trans[c] ){
      AC[p].trans[c]=++sz;
      AC[sz].Init();
    }
    p=AC[p].trans[c];
  }
  return p;
}

void Build(){
  queue<int> q;
  q.push(0);
  set(fail,0);
  while( !q.empty() ){
    int st=q.front();q.pop();
    for(int i=0;i<maxp;i++)
      if( AC[st].trans[i] ){
        int np=AC[st].trans[i],t=fail[st];
        while( t && !AC[t].trans[i] ) t=fail[t];
        if( AC[t].trans[i] && st ) t=AC[t].trans[i];
        fail[np]=t;
        q.push(np);
      }
      else AC[st].trans[i]=AC[fail[st]].trans[i];
  }
  for(int i=1;i<=sz;i++) Insert(fail[i],i);
}

int main(){
#ifndef ONLINE_JUDGE
  freopen("AC_Automaton.in","r",stdin);
  freopen("AC_Automaton.out","w",stdout);
#endif
  ios::sync_with_stdio(false);
  set(first,-1),ind=0;
  return 0;
}
