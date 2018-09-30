#include<bits/stdc++.h>

#define set(a,b) memset(a,(b),sizeof(a))

using namespace std;

typedef long long ll;

const int maxn=1000+5;
const double eps=1e-6;

class Vector{
public:
  double x,y,z;
  Vector(double x=0,double y=0,double z=0):x(x),y(y),z(z){}
  Vector Identify(){
    double M=Modulus();
    return Vector(x/M,y/M,z/M);
  }
  double Modulus(){
    return sqrt(x*x+y*y+z*z);
  }
  friend Vector operator * (const Vector V,const double p){
    return Vector(V.x*p,V.y*p,V.z*p);
  }
  friend Vector operator * (const double p,const Vector V){
    return Vector(V.x*p,V.y*p,V.z*p);
  }
  friend Vector operator * (const Vector Va,const Vector Vb){
    return Vector(Va.y*Vb.z-Va.z*Vb.y,-(Va.x*Vb.z-Va.z*Vb.x),Va.x*Vb.y-Va.y*Vb.x);
  }
  friend double operator ^ (const Vector Va,const Vector Vb){
    return Va.x*Vb.x+Va.y*Vb.y+Va.z*Vb.z;
  }
};

class Node{
public:
  double x,y,z;
  Node(double x=0,double y=0,double z=0):x(x),y(y),z(z){}
  double Distance(Node Vn){
    return sqrt((Vn.x-x)*(Vn.x-x)+(Vn.y-y)*(Vn.y-y)+(Vn.z-z)*(Vn.z-z));
  }
  friend Node operator + (const Node Vn,const Vector V){
    return Node(Vn.x+V.x,Vn.y+V.y,Vn.z+V.z);
  }
  friend Node operator - (const Node Vn,const Vector V){
    return Node(Vn.x-V.x,Vn.y-V.y,Vn.z-V.z);
  }
  friend Vector operator - (const Node Va,const Node Vb){
    return Vector(Va.x-Vb.x,Va.y-Vb.y,Va.z-Vb.z);
  }
};

class Line{
public:
  Node c;
  Vector v;
  double bound;
  Line(Node Va=Node(),Node Vb=Node()){
    c=Va,v=(Vb-Va).Identify();
    bound=(Vb-Va).Modulus();
  }
  Node Projection(Node Vn){
    Vector Vp=Vn-c;
    return c+(Vp^v)*v;
  }
  double Distance(Node Vn){
    return Vn.Distance(this->Projection(Vn));
  }
};

class Sphere{
  Node c;
  double r;
public:
  Sphere(double x=0,double y=0,double z=0,double r=0):c(Node(x,y,z)),r(r){}
  vector<Node> Intersection(Line L){
    vector<Node> res;
    double d=L.Distance(c);
    if( d>r ) return res;
    Node p=L.Projection(c);
    if( d==r ) res.push_back(p);
    else{
      double t=sqrt(r*r-d*d);
      res.push_back(p+L.v*t);
      res.push_back(p-L.v*t);
    }
    return res;
  }
};

class Ellispoid{
public:
  Node c;
  double A,B,C;
  int col;
  Ellispoid(Node c=Node(),double A=0,double B=0,double C=0,int col=0):c(c),A(A),B(B),C(C),col(col){}
  double Exdistance(Node Vn){
    return (Vn.x-c.x)*(Vn.x-c.x)/(A*A)+(Vn.y-c.y)*(Vn.y-c.y)/(B*B)+(Vn.z-c.z)*(Vn.z-c.z)/(C*C);
  }
  bool Internal(Node Vn){
    return Exdistance(Vn)<=1;
  }
};

typedef pair<double,int> pir;

int main(){
#ifndef ONLINE_JUDGE
  freopen("Geometry.in","r",stdin);
  freopen("Geometry.out","w",stdout);
#endif
  ios::sync_with_stdio(false);
  return 0;
}
