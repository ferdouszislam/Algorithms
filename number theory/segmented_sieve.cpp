/**
    Segmented Sieve

    Find all prime numbers in the range- [a, b] where (a, b)<=10^14 and b-a<=10^5

    Complexity: O(loglogN)

**/

#include <bits/stdc++.h>

using namespace std;

///------------------- Segmented Sieve start -------------------///

vector<int> primes;

// Sieve Of Eratosthenes to find primes upto 10^7
// and populate the vector 'primes'
void findPrimesUpto(int n) {

    primes.clear();

    vector<bool> prime(n+1, true);
    //bool prime[n + 1];
    //memset(prime, true, sizeof(prime));

    for (int p = 2; p * p <= n; p++){
        if (prime[p] == true){
            for (int i = p * p; i <= n; i += p)
                prime[i] = false;
        }
    }

    for (int p = 2; p <= n; p++)
        if (prime[p])
            primes.push_back(p);
}

vector<long long> primesInSegment;

void findPrimesInSegment(long long a, long long b){

    primesInSegment.clear();

    if (a == 1) a++;

    int sqrtn = sqrt(b);

    findPrimesUpto(sqrtn);

    vector<bool> prime(b-a+1, true);
    //bool prime[b-a+1];
    //memset(prime, true, sizeof prime);

    for (int i = 0; i < primes.size() && primes[i] <= sqrtn; i++) {
        long long p = primes[i];
        long long j = p * p;

        // If j is smaller than a, then shift it inside of segment [a,b]
        if (j < a) j = ( ( a + p - 1 ) / p ) * p;

        for ( ; j <= b; j += p ) {
            prime[j-a] = false;
        }
    }

    for (long long i = a; i <= b; i++) {
        int pos = i-a;
        if (prime[pos]) primesInSegment.push_back(i);
    }
}

///------------------- Segmented Sieve end -------------------///


int getRandomNumberInRange(int lower, int upper){
// generate a random number in the range- ['lower', 'upper']
    srand(time(0));
    return rand()%(upper-lower+1)+lower;
}

void exec(){
// execute the algorithm

    long long a = 10e14-1000;
    long long b = 10e14-100;

    findPrimesInSegment(a, b);

    for(long long x : primesInSegment) cout<<x<<"\n";
}


int main()
{
    exec();

    return 0;
}

