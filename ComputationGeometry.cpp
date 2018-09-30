#include<bits/stdc++.h>

#define set(a,b) memset(a,(b),sizeof(a))

using namespace std;

typedef long long ll;
typedef pair<double,double> pii;

const double pi=2*acos(0);
const double eps=1e-6;

class Vector{
public:
  double x,y;

  Vector(double x=0,double y=0):x(x),y(y){}

  friend bool operator == (Vector Va,Vector Vb){
    return Va.x==Vb.x&&Va.y==Vb.y;
  }

  friend bool operator != (Vector Va,Vector Vb){
    return !(Va==Vb);
  }

  friend double operator ^ (const Vector &Va,const Vector &Vb){
    return Va.x*Vb.x+Va.y*Vb.y;
  }

  friend double operator * (const Vector &Va,const Vector &Vb){
    return Va.x*Vb.y-Va.y*Vb.x;
  }

  friend Vector operator * (const double &Da,const Vector &Vb){
    return Vector(Vb.x*Da,Vb.y*Da);
  }

  friend Vector operator * (const Vector &Va,const double &Db){
    return Vector(Va.x*Db,Va.y*Db);
  }

  double Modulus(){
    return sqrt(x*x+y*y);
  }

  Vector Identity(){
    double M=Modulus();
    return Vector(x/M,y/M);
  }

  /*
  double Angle(Vector Va){
    return asin((*this*Va)/((*this).Modulus()*Va.Modulus()));
  }
  */

  // double Angle(Vector Va){
  //   double angle=acos((*this^Va)/((*this).Modulus()*Va.Modulus()));
  //   if( (*this)*Va<=0 ) angle=2*pi-angle;
  //   return angle;
  // }

  double Angle(Vector Va){
    if( Modulus()==0 || Va.Modulus()==0 ) return 0;
    double angle=(*this^Va)/((*this).Modulus()*Va.Modulus());
    if( abs(angle)>1 ) return angle>0?0:pi;
    angle=acos(angle);
    if( (*this)*Va<0 ) angle=-angle;
    //if( (*this)*Va<0 ) angle=2*pi-angle;
    return angle;
  }


  Vector Rotate(double a){
    return Vector{x*cos(a)-y*sin(a),x*sin(a)+y*cos(a)};
  }
};

class Node{
public:
  double x,y;

  Node(double x=0,double y=0):x(x),y(y){}

  double Distance(Node Vn){
    return sqrt((Vn.x-x)*(Vn.x-x)+(Vn.y-y)*(Vn.y-y));
  }

  friend bool operator == (Node Va,Node Vb){
    return Va.x==Vb.x && Va.y==Vb.y;
  }

  friend bool operator != (Node Va,Node Vb){
    return !(Va==Vb);
  }

  friend bool operator < (Node Va,Node Vb){
    return Va.x==Vb.x?Va.y<Vb.y:Va.x<Vb.x;
  }

  friend Node operator + (Node Va,Vector Vb){
    return Node(Va.x+Vb.x,Va.y+Vb.y);
  }

  friend Node operator - (Node Va,Vector Vb){
     return Node(Va.x-Vb.x,Va.y-Vb.y);
  }

  friend Vector operator - (Node Va,Node Vb){
    return Vector{Va.x-Vb.x,Va.y-Vb.y};
  }
};

class Line{
public:
  Node Vn;
  Vector Vt;
  Line(Node Va,Node Vb){
    Vn=Va;
    assert(Va!=Vb);
    if( Va<Vb ) Vt=(Vb-Va).Identity();
    else Vt=(Va-Vb).Identity();
  }
  Node Project(Node Vx){
    return Vn+(Vt^(Vx-Vn))*Vt;
  }
  Node Intersection(Line Vl){
    assert((Vl.Vt^Vt)==0);
    return Node();
  }
};

class Segment{
public:
  Node ln,rn;
  Segment(Node Ln,Node Rn){
    if( Ln.x<Rn.x ) this->ln=Ln,this->rn=Rn;
    else this->ln=Rn,this->rn=Ln;
  }
  bool Intersect(Segment Vs){
    if( ((Vs.ln-ln)*(rn-ln))*((Vs.rn-ln)*(rn-ln))>=0 ) return false;
    if( ((ln-Vs.ln)*(Vs.rn-Vs.ln))*((rn-Vs.ln)*(Vs.rn-Vs.ln))>=0 ) return false;
    return true;
  }
  Node Intersection(Segment Vs){
    return Line(ln,rn).Intersection(Line(Vs.ln,Vs.rn));
  }
};

class Polygon{
public:
  int n;
  vector<Node> node;
  double LBoard=DBL_MAX,RBoard=-DBL_MAX;

  Polygon(int n=0):n(n){}
  void add(Node Va){
    n++;
    node.push_back(Va);
    LBoard=min(LBoard,Va.x);
    RBoard=max(RBoard,Va.x);
  }

  bool Internal(Node Vn,Node Vs=Node(1e9,1)){
    int cnt=0;
    Segment S=Segment(Vn,Vs);
    for(int i=0;i<n-1;i++)
      cnt^=S.Intersect(Segment(node[i],node[i+1]));
    return cnt&1;
  }

  void Ajust(){
    if( Square()<0 )
      reverse(node.begin(),node.end());
  }

  double Square(){
    int d = 0;
    for(int i=0;i<n;i++){
      d-=(node[(i+1)%n].y+node[i].y)*(node[(i+1)%n].x-node[i].x);
    }
    return d/2.;
  }

  double Square(Node Vn){
    double S=0;
    for(int i=0;i<n-1;i++)
      S+=(node[i]-Vn)*(node[i+1]-Vn)/2;
    S+=(node[n-1]-Vn)*(node[0]-Vn)/2;
    return S;
  }
};

class Circle{
public:
  double x,y,r;
  Node C;

  Circle(double x=0,double y=0,double r=0):x(x),y(y),r(r),C(Node(x,y)){}
  Circle(Node Vn,double r=0):x(Vn.x),y(Vn.y),r(r),C(Vn){}

  int Internal(Circle Vc){
    double dis=Vc.C.Distance(C);
    if( Vc.r-r>=dis ) return 1;
    else if( r-Vc.r>=dis ) return -1;
    else return 0;
  }

  bool Internal(Node Vn){
    double dis=Vn.Distance(C);
    return dis<=r;
  }

  double Upper(double vx){
    assert(vx>=x-r);
    assert(vx<=x+r);
    return y+sqrt(r*r-(vx-x)*(vx-x));
  }

  double Lower(double vx){
    assert(vx>=x-r);
    assert(vx<=x+r);
    return y-sqrt(r*r-(vx-x)*(vx-x));
  }

  vector<Node> Intersection(Line Vl,int k=0){
    vector<Node> res;
    Node Np=Vl.Project(C);
    double D=Np.Distance(C);
    if( D>r ) return res;
    D=sqrt(r*r-D*D);
    if( k<=0 ) res.push_back(Np-D*Vl.Vt);
    if( k>=0 ) res.push_back(Np+D*Vl.Vt);
    return res;
  }

  Node upperTangentNode(Circle Vc){
    double dis=sqrt((Vc.x-x)*(Vc.x-x)+(Vc.y-y)*(Vc.y-y));
    double theta=atan2(Vc.y-y,Vc.x-x)+(asin((Vc.r-r)/dis)+pi/2);
    return Node(x+cos(theta)*r,y+sin(theta)*r);
  }

  Node lowerTangentNode(Circle Vc){
    double dis=sqrt((Vc.x-x)*(Vc.x-x)+(Vc.y-y)*(Vc.y-y));
    double theta=atan2(Vc.y-y,Vc.x-x)-(asin((Vc.r-r)/dis)+pi/2);
    return Node(x+cos(theta)*r,y+sin(theta)*r);
  }
};

class Convex{
  vector<Node> upper_Convex;
  vector<Node> lower_Convex;
public:
  void add(Node Vn){
    upper_Convex.push_back(Vn);
    lower_Convex.push_back(Vn);
  }

  void CreateConvex(){
    CreateUpperConvex();
    CreateLowerConvex();
  }

  double LBound(){
    return upper_Convex[0].x;
  }

  double RBound(){
    return upper_Convex.back().x;
  }

  vector<pii> Distinguish(){
    vector<pii> Vr;
    Vector p=(upper_Convex[0]-upper_Convex[1]),c=(lower_Convex[1]-lower_Convex[0]);
    Vr.push_back((pii){c.Modulus(),p.Angle(c)});
    for(int i=1;i<(int)lower_Convex.size()-1;i++){
      p=c,c=lower_Convex[i+1]-lower_Convex[i];
      Vr.push_back((pii){c.Modulus(),p.Angle(c)});
    }
    p=c,c=upper_Convex[upper_Convex.size()-2]-upper_Convex.back();
    Vr.push_back((pii){c.Modulus(),p.Angle(c)});
    for(int i=upper_Convex.size()-2;i>0;i--){
      p=c,c=upper_Convex[i-1]-upper_Convex[i];
      Vr.push_back((pii){c.Modulus(),p.Angle(c)});
    }
    return Vr;
  }

  double Square(){
    double S=0;
    for(int i=1;i<(int)lower_Convex.size()-1;i++){
      Vector v1=lower_Convex[i]-lower_Convex[0],v2=lower_Convex[i+1]-lower_Convex[i];
      S+=(v1*v2);
    }
    for(int i=(int)upper_Convex.size()-1;i>1;i--){
      Vector v1=upper_Convex[i]-upper_Convex[0],v2=upper_Convex[i-1]-upper_Convex[i];
      S+=(v1*v2);
    }
    return S/2;
  }

  double Upper(double x){
    assert(x>=upper_Convex[0].x);
    assert(x<=upper_Convex.back().x);
    if( x==upper_Convex.back().x ) return upper_Convex.back().y;
    int l=0,r=upper_Convex.size()-1;
    while( l!=r ){
      int mid=(l+r+1)/2;
      if( upper_Convex[mid].x>x ) r=mid-1;
      else l=mid;
    }
    return (upper_Convex[l]+(x-upper_Convex[l].x)/(upper_Convex[l+1]-upper_Convex[l]).x*(upper_Convex[l+1]-upper_Convex[l])).y;
  }

  double Lower(double x){
    assert(x>=lower_Convex[0].x);
    assert(x<=lower_Convex.back().x);
    if( x==lower_Convex.back().x ) return lower_Convex.back().y;
    int l=0,r=lower_Convex.size()-1;
    while( l!=r ){
      int mid=(l+r+1)/2;
      if( lower_Convex[mid].x>x ) r=mid-1;
      else l=mid;
    }
    return (lower_Convex[l]+(x-lower_Convex[l].x)/(lower_Convex[l+1]-lower_Convex[l]).x*(lower_Convex[l+1]-lower_Convex[l])).y;
  }

protected:

  void CreateUpperConvex(){
    vector<Node> s;
    int size=0;
    sort(upper_Convex.begin(),upper_Convex.end());
    for(int i=0;i<(int)upper_Convex.size();i++){
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
    sort(lower_Convex.begin(),lower_Convex.end());
    for(int i=0;i<(int)lower_Convex.size();i++){
      if( size<=1 ) s.push_back(lower_Convex[i]),size++;
      else{
    while( size>1 && (s[size-1]-s[size-2])*(lower_Convex[i]-s[size-1])<=0 )
      s.pop_back(),size--;
    s.push_back(lower_Convex[i]),size++;
      }
    }
    lower_Convex=s;
  }
};

int main(){
#ifndef ONLINE_JUDGE
  freopen("Computationgeometry","r",stdin);
  freopen("Computationgeometry","w",stdout);
#endif
  ios::sync_with_stdio(false);
  return 0;
}
