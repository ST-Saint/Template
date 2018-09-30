#include<bits/stdc++.h>

#define set(a,b) memset(a,(b),sizeof(a))

using namespace std;

typedef long long ll;
typedef pair<int,int> pii;

const int maxn=1e5+5;
const int maxt=262144+5;

class SegmentTreeNode{
public:
  int s[2],l,r;
  int w,sum;
  pii maxi;
};

class SegmentTree{
  SegmentTreeNode tr[maxt];
  void Update(int x){
    tr[x].maxi=max(tr[x<<1].maxi,tr[x<<1^1].maxi);
    tr[x].sum=tr[x<<1].sum+tr[x<<1^1].sum;
  }
public:
  void Modify(int x,int p,int w){
    if( tr[x].l==tr[x].r ){
      tr[x].w=tr[x].sum=w;
      tr[x].maxi=pii(w,p);
      return ;
    }
    if( p<=(tr[x].l+tr[x].r)/2 ) Modify(x<<1,p,w);
    else Modify(x<<1^1,p,w);
    Update(x);
  }
  int Query_Sum(int x,int l,int r){
    if( l<=tr[x].l && tr[x].r<=r ) return tr[x].sum;
    int res=0;
    if( l<=(tr[x].l+tr[x].r)/2 ) res+=Query_Sum(x<<1,l,r);
    if( (tr[x].l+tr[x].r)/2<r ) res+=Query_Sum(x<<1^1,l,r);
    return res;
  }
  int Query_Max(int x,int l,int r){
    if( l<=tr[x].l && tr[x].r<=r ) return tr[x].maxi.first;
    int ls=INT_MIN,rs=INT_MIN;
    if( l<=(tr[x].l+tr[x].r)/2 ) ls=Query_Max(x<<1,l,r);
    if( (tr[x].l+tr[x].r)/2<r ) rs=Query_Max(x<<1^1,l,r);
    return max(ls,rs);
  }
  pii Query_Maxp(int x,int l,int r){
    if( l<=tr[x].l && tr[x].r<=r ) return tr[x].maxi;
    pii ls=pii(INT_MIN,0),rs=pii(INT_MIN,0);
    if( l<=(tr[x].l+tr[x].r)/2 ) ls=Query_Maxp(x<<1,l,r);
    if( (tr[x].l+tr[x].r)/2<r ) rs=Query_Maxp(x<<1^1,l,r);
    return max(ls,rs);
  }
  void Build(int x,int l,int r){
    tr[x].l=l,tr[x].r=r;
    if( l==r ){
      tr[x].w=tr[x].sum=0;
      tr[x].maxi=pii(0,l);
      return ;
    }
    Build(x<<1,l,(l+r)/2),Build(x<<1^1,(l+r)/2+1,r);
    Update(x);
  }
};

int main(){
#ifndef ONLINE_JUDGE
  freopen("SegmentTree.in","r",stdin);
  freopen("SegmentTree.out","w",stdout);
#endif
  ios::sync_with_stdio(false);
  return 0;
}
