#include<bits/stdc++.h>

#define set(a,b) memset(a,(b),sizeof(a))

using namespace std;

typedef long long ll;

const int maxn=200+5;
const double pi=2*acos(0);
const double eps=1e-6;

class Vector{
public:
  double x,y;

  Vector():x(0),y(0){}

  Vector(double x,double y):x(x),y(y){}

  friend double operator ^ (const Vector &Va,const Vector &Vb){
    return Va.x*Vb.x+Va.y*Vb.y;
  }

  friend double operator * (const Vector &Va,const Vector &Vb){
    return Va.x*Vb.y-Va.y*Vb.x;
  }

  double Modulus(){
    return sqrt(x*x+y*y);
  }

  Vector Rotate(double a){
    return Vector{x*cos(a)-y*sin(a),x*sin(a)+y*cos(a)};
  }
};

class Node{
public:
  double x,y;
  int id;

  Node(double x,double y,int id=0){
    this->x=x;
    this->y=y;
    this->id=id;
  }

  friend Vector operator - (Node Va,Node Vb){
    return Vector{Va.x-Vb.x,Va.y-Vb.y};
  }
};

class Circle{
public:
  double x,y,r;
  int id;

  Circle(double x,double y,double r,int id=0):x(x),y(y),r(r),id(id){}

  int Internal(Circle Vc){
    double dis=sqrt((Vc.x-x)*(Vc.x-x)+(Vc.y-y)*(Vc.y-y));
    if( Vc.r-r>=dis ) return 1;
    else if( r-Vc.r>=dis ) return -1;
    else return 0;
  }

  bool Internal(Node Vn){
    double dis=sqrt((Vn.x-x)*(Vn.x-x)+(Vn.y-y)*(Vn.y-y));
    return dis<r;
  }

  Node upperTangentNode(Circle Vc){
    double dis=sqrt((Vc.x-x)*(Vc.x-x)+(Vc.y-y)*(Vc.y-y));
    double theta=atan2(Vc.y-y,Vc.x-x)+(asin((Vc.r-r)/dis)+pi/2);
    return Node(x+cos(theta)*r,y+sin(theta)*r,id);
  }

  Node lowerTangentNode(Circle Vc){
    double dis=sqrt((Vc.x-x)*(Vc.x-x)+(Vc.y-y)*(Vc.y-y));
    double theta=atan2(Vc.y-y,Vc.x-x)-(asin((Vc.r-r)/dis)+pi/2);
    return Node(x+cos(theta)*r,y+sin(theta)*r,id);
  }
};

class Convex_Circle{
  vector<Circle> cir;
  vector<Node> upper_Convex;
  vector<Node> lower_Convex;
public:

  void add(Node Vn){
    upper_Convex.push_back(Vn);
    lower_Convex.push_back(Vn);
  }

  void add(Circle Vc){
    cir.push_back(Vc);
  }

  void CreateConvex(){
    Deduplicate();
    for(int i=0;i<cir.size();i++)
      for(int j=0;j<cir.size();j++)
	if( i!=j ){
          add(cir[i].upperTangentNode(cir[j]));
          add(cir[i].lowerTangentNode(cir[j]));
	}
    Remove();
    CreateUpperConvex();
    CreateLowerConvex();
  }

  double Circumference(){
    if( cir.size()==1 ) return 2*pi*cir[0].r;
    double C=0;
    vector<Node> s;
    for(int i=0;i<upper_Convex.size()-1;i++) s.push_back(upper_Convex[i]);
    for(int i=lower_Convex.size()-1;i>=0;i--) s.push_back(lower_Convex[i]);
    for(int i=0;i<s.size()-1;i++)
      if( s[i].id==s[i+1].id ){
	Vector v1,v2;
	if( i==0 ) v1=s[i]-lower_Convex[1];
	else v1=s[i]-s[i-1];
	if( i==s.size()-2 ) v2=upper_Convex[1]-s[i+1];
	else v2=s[i+2]-s[i+1];
	double theta=acos((v2^v1)/(v2.Modulus()*v1.Modulus()));
	if( v2*v1<0 ) theta=2*pi-theta;
	C+=theta*cir[s[i].id].r;
      }
      else C+=(s[i+1]-s[i]).Modulus();
    return C;
  }

protected:
  static bool compareScanner(Node Va,Node Vb){
    return Va.x==Vb.x?Va.y>Vb.y:Va.x<Vb.x;
  }

  void Deduplicate(){
    vector<Circle> s;
    for(int i=0;i<cir.size();i++){
      bool flag=true;
      for(int j=0;j<s.size()&&flag;j++)
	if( cir[i].Internal(s[j])==1 )
          flag=false;
      for(int j=i+1;j<cir.size()&&flag;j++)
	if( cir[i].Internal(cir[j])==1 )
          flag=false;
      if( flag ){
	cir[i].id=s.size();
	s.push_back(cir[i]);
      }
    }
    cir=s;
  }

  void Remove(){
    vector<Node> s;
    s=upper_Convex;
    upper_Convex.clear();
    lower_Convex.clear();
    for(int i=0;i<s.size();i++){
      bool flag=false;
      for(int j=0;j<cir.size();j++)
	if( s[i].id!=j && cir[j].Internal(s[i]) ){
          flag=true;
          break;
	}
      if( !flag ) add(s[i]);
    }
  }

  void CreateUpperConvex(){
    vector<Node> s;
    int size=0;
    sort(upper_Convex.begin(),upper_Convex.end(),compareScanner);
    for(int i=0;i<upper_Convex.size();i++){
      if( size<=1 ) s.push_back(upper_Convex[i]),size++;
      else{
	while( size>1 && (s[size-1]-s[size-2])*(upper_Convex[i]-s[size-1])>=0 )
          s.pop_back(),size--;
	s.push_back(upper_Convex[i]),size++;
      }
    }
    upper_Convex=s;
  }

  void CreateLowerConvex(){
    vector<Node> s;
    int size=0;
    sort(lower_Convex.begin(),lower_Convex.end(),compareScanner);
    for(int i=0;i<lower_Convex.size();i++){
      if( size<=1 ) s.push_back(lower_Convex[i]),size++;
      else{
	while( size>1 && (s[size-1]-s[size-2])*(lower_Convex[i]-s[size-1])<=0 )
          s.pop_back(),size--;
	s.push_back(lower_Convex[i]),size++;
      }
    }
    lower_Convex=s;
  }
}C;

int n;

int main(){
#ifndef ONLINE_JUDGE
  freopen("Circle.in","r",stdin);
  freopen("Circle.out","w",stdout);
#endif
  ios::sync_with_stdio(false);
  cin >> n ;
  for(int i=1;i<=n;i++){
    int x,y,r;
    cin >> x >> y >> r ;
    r+=10;
    Circle cir=Circle(x,y,r,i-1);
    C.add(cir);
  }
  C.CreateConvex();
  cout << fixed << setprecision(3) << C.Circumference() << endl ;
  return 0;
}
