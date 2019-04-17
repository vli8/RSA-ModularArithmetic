#include <iostream>
#include <algorithm>
#include <bits/stdc++.h>
using namespace std;


/* precondition: a>=b>=0 */
/* postcondition: return d=gcd(a,b) */
int gcd(int a, int b){
        if(a == 0) return b;
        return gcd(b%a, a);
}

/* precondition: a>=b>=0 */
/* postcondition: return d=gcd(a,b), s and t are set so that d=sa+tb */
int gcdExtended(int a, int b, int & x, int & y) {
    if (a == 0) {
        x = 0;
        y = 1;
        return b;
    }
    int x1, y1;
    int d = gcdExtended(b % a, a, x1, y1);
    x = y1 - (b / a) * x1;
    y = x1;
    return d;
}

/* precondition: n is greater than 1,a can be negative
 postcondition: return a mod n (as defined in class)
 a mod n = r if and only if a = nk+r, 0 =< r < n (note that
 r needs to be non-negative).
*/
int mod (int a, int b)
{
   if(b < 0) //you can check for b == 0 separately and do what you want
     return mod(a, -b);
   int ret = a % b;
   if(ret < 0)
 ret+=b;
   return ret;
}

/* return an integer that is relatively prime with n, and greater than 1
 i.e., the gcd of the returned int and n is 1
 Note: Although gcd(n,n-1)=1, we don't want to return n-1*/
int RelativelyPrime (int n){
        int q = 2;
        do {
                q++;
        } while (gcd(n, q) != 1);
        return q;
}

/* n>1, a is nonnegative */
/* a<=n */
/* a and n are relative prime to each other */
/* return s such that a*s mod n is 1 */
int inverse (int a, int n)
{
        int s, t;
        int d = gcdExtended (n, a, s, t);

        if (d == 1)
        {
                return (mod (t, n));
        }
        else
        {
                return -1;
        }
}


int Encode (int M, int d, int PQ){
 int product = 1;
        for(int i=0; i<d;i++)
                product = (product * M) % PQ;

        return product;
}

// Returns C^e mod PQ
int Decode (int C, int e, int PQ){
        int product = 1;
        for(int i=0; i<e;i++)
                product = (product * C) % PQ;

        return product;
}


int main(){
        int a = 20, b = 10;
        cout << "GCD of " << a << " and " << b << " = "<< gcd(a, b)<< endl;
        int x,y;
        int n = 35, m=15;
        cout << "Extended GCD of " << n << " and " << m  << " = "<< gcdExtended(n,m,x,y) << endl ;
        cout << "Module of -7 and 8 = " << mod(-7,8) << endl;
        cout << "Relatively prime of 7 = " << RelativelyPrime(7) << endl ;
        cout << "Inverse of 7 and 8 = " << inverse(7,8) << endl;
        cout << "RSA algorithm: " << endl;
        int p, q;

        // two random prime numbers
        cout << "Please insert p: ";
        cin >> p;
        cout << "Please insert q: ";
        cin >> q;

        cout <<endl;
int pq = p*q;
        cout << "n = pq =  " << pq << endl;

        int phi = (p-1)*(q-1);
        cout << "phi =  " << phi << endl;

        int e = RelativelyPrime(phi);
        cout << "e = " << e << endl;

        int D = inverse(e, phi);
        cout << "D using inverse = " << D << endl;

        int k = 2;
        while ((1+k*phi)%e != 0){
                k++;
        }
        cout << "k = " << k << endl;

        int d = (1 + (k*phi))/e;
        cout << " d = " << d << endl;

        cout << endl;

        int M;
        cout << "Your message" <<endl;
        cout << "Enter an integer that is smaller than " << pq << ": ";
        cin >> M;

        int C = Encode(M, e, pq);
        cout << "The encoded message is " << C << endl;
        int DC = Decode(C, d, pq);
        cout << "The original message is " << DC << endl;
        assert(M == DC);

        return 0;

}
