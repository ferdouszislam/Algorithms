/**
    Euler's totient function, phi: number of coprimes of 'N' from 1 to N.

    Find phi(1...MAX), MAX = [1, 10^6]

    Complexity: O(loglogN)

    Useful Properties:

        1. phi(m*n) = phi(m)*phi(n)

        2. if 'x' is coprime to 'y' then 'x%y' is also comprime to y

        3. The divisors of 10 are 1, 2, 5 and 10 => Phi(1) + Phi(2) + Phi(5) + Phi(10) = 10.

**/

#include <bits/stdc++.h>

using namespace std;

///------------------- Euler's totient function start -------------------///

const int MAX_N = 1000000;

// phi[x] = euler's totient function for X
long long phi[MAX_N];

// call this to calculate all phi[] upto N
// calculates phi values using the formula: <https://forthright48.com/euler-totient-or-phi-function/>
// primes are used following to Sieve of Eratosthenes to reduce time complexity
void calculatePhiUpto(int n){

    phi[0] = 0;
    phi[1] = 1;
    for (int i = 2; i <= n; i++) phi[i] = i;

    for (int i = 2; i <= n; i++) {
        if (phi[i] == i) {

            int currentPrime = i;

            for (int aMulOfCurrentPrime = currentPrime; aMulOfCurrentPrime <= n; aMulOfCurrentPrime += currentPrime){

                phi[aMulOfCurrentPrime] /= currentPrime;
                phi[aMulOfCurrentPrime] *= (currentPrime-1);
            }
        }
    }

}

/**
    returns phi of n,
    time complexity: O(sqrt(N)),
    no limit on value of N
**/
long long phi(long long n) {

    long long result = n;

    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            while (n % i == 0)
                n /= i;

            result /= i;
            result *= (i-1);
        }
    }

    if (n > 1){
        result /= n;
        result *= (n-1);
    }

    return result;
}

///------------------- Euler's totient function end -------------------///


int getRandomNumberInRange(int lower, int upper){
// generate a random number in the range- ['lower', 'upper']
    srand(time(0));
    return rand()%(upper-lower+1)+lower;
}

void exec(){
// execute the algorithm

    int N = getRandomNumberInRange(0, MAX_N);

    calculatePhiUpto(N);

    cout<<"Phi("<<N<<") = "<<phi[N]<<"\n";
}


int main()
{
    exec();

    return 0;
}

