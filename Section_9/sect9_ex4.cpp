/*
    Written by Jtaim
    Date 18 Jan 2019
    Programming Principles and Practice Using C++ Second Edition, Bjarne Stroustrup

    Section 9 Exercise 4
*/

/*
// dangerously ugly code
struct X {
void f(int x) {
struct Y {
int f() { return 1; } int m; };
int m;
m=x; Y m2;
return f(m2.f()); }
int m; void g(int m) {
if (m) f(m+2); else {
g(m+2); }}
X() { } void m3() {
}
 void main() {
X a; a.f(2);}
};
*/

struct X
{
    void f( int x )
    {
        struct Y
        {
            int f() { return 1; }
            int m;
        };
        int m;      // declares a variable of type int hides the upper scpe of m
        m = x;      // assign the function argument to m
        Y m2;       // declares a variable of type Y
        return f( m2.f() );  // recursive function call which will throw a stack overflow error
    }

    int m;          // top most scoped declaration variable m of type int
    
    void g( int m )
    {
        if( m )     // statement is only false when m = 0;
        {
            f( m + 2 );
        }
        else
        {
            g( m + 2 );
        }
    }

    X() {}          // constructor for X
    void m3() {}    // member function of class which does nothing
};


int main()
{
    X a;
    a.f( 2 );
}