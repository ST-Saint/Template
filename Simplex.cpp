#include<bits/stdc++.h>

#define eps 1e-6
#define maxn 1000+5
#define maxm 10000+5
#define set(a,b) memset(a,(b),sizeof(a))

using namespace std;

typedef long long ll;

double g[maxn][maxm];
int n,m,ans;

void Pivot(int x,int y)
{
  double k=g[x][y];g[x][y]=1;
  for(int i=0;i<=m;i++) g[x][i]/=k;
  for(int i=0;i<=n;i++)
    if( i!=x && abs(g[i][y])>eps ){
      k=g[i][y],g[i][y]=0;
      for(int j=0;j<=m;j++)
	g[i][j]-=k*g[x][j];
    }
}

int Simplex()
{
  bool flag=true;
  while( flag ){
    flag=false;
    for(int i=1;i<=m;i++)
      if( g[0][i]>eps ){
	double cur=LLONG_MAX;int p;
	for(int j=1;j<=n;j++)
	  if( g[j][i]>eps && g[j][0]<cur*g[j][i] )
	    cur=g[j][0]/g[j][i],p=j;
	if( cur==LLONG_MAX ){
	  g[0][0]=LLONG_MAX;
	  break;
	}
	flag=true,Pivot(p,i);
	break;
      }
  }
  return -g[0][0];
}

int main()
{
#ifndef ONLINE_JUDGE
  freopen("Simplex.in","r",stdin);
  freopen("Simplex.out","w",stdout);
#endif
  ios::sync_with_stdio(false);
  ans=(int)Simplex();
  return 0;
}
