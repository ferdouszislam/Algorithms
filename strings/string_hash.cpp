/***

    Courtesy- https://github.com/sgtlaugh/algovault/blob/master/code_library/string_hash.cpp

 *
 * String hashing with double hash
 * Get the forward and reverse hash of any substring
 * Complexity - O(n) to build and O(1) for substring hash query
 *

***/

#include <iostream>
#include <bits/stdc++.h>

using namespace std;


///--------------------------------------------------------- String Hashing start ---------------------------------------------------------///

const int PRIMES[] = {2147462393, 2147462419, 2147462587, 2147462633, 2147462747, 2147463167, 2147463203, 2147463569, 2147463727, 2147463863, 2147464211, 2147464549, 2147464751, 2147465153, 2147465563, 2147465599, 2147465743, 2147465953, 2147466457, 2147466463, 2147466521, 2147466721, 2147467009, 2147467057, 2147467067, 2147467261, 2147467379, 2147467463, 2147467669, 2147467747, 2147468003, 2147468317, 2147468591, 2147468651, 2147468779, 2147468801, 2147469017, 2147469041, 2147469173, 2147469229, 2147469593, 2147469881, 2147469983, 2147470027, 2147470081, 2147470177, 2147470673, 2147470823, 2147471057, 2147471327, 2147471581, 2147472137, 2147472161, 2147472689, 2147472697, 2147472863, 2147473151, 2147473369, 2147473733, 2147473891, 2147473963, 2147474279, 2147474921, 2147474929, 2147475107, 2147475221, 2147475347, 2147475397, 2147475971, 2147476739, 2147476769, 2147476789, 2147476927, 2147477063, 2147477107, 2147477249, 2147477807, 2147477933, 2147478017, 2147478521, 2147478563, 2147478649, 2147479447, 2147479589, 2147480707, 2147480837, 2147480927, 2147480971, 2147481263, 2147481311, 2147481337, 2147481367, 2147481997, 2147482021, 2147482063, 2147482081, 2147482343, 2147482591, 2147483069, 2147483123};

struct SingleHash{
// Create hash of a string by converting it to a number system of 'base' in the range [0, 'mod']
// store hash of each position of string to compute substring hashes (similar to Prefix-Array-Sum)
// this struct is a suplement to StringHash struct

    // 'base': base of number system to convert
    // 'mod': highest value of a hash
    long long base, mod;
    // 'basepow': basepow[i] = base^i
    // 'f_hash': f_hash[i] = hash of string from 0 to ith position
    // 'r_hash': f_hash[i] = hash of string from n(size) to ith position in reverse (nth position comes first)
    vector <int> basepow, f_hash, r_hash;

    SingleHash() {}

    SingleHash(string str, long long base, long long mod): base(base), mod(mod){
        int len = str.size();
        basepow.resize(len + 3, 1), f_hash.resize(len + 3, 0), r_hash.resize(len + 3, 0);

        for (int i = 1; i <= len; i++){
            basepow[i] = basepow[i - 1] * base % mod;
            f_hash[i] = (f_hash[i - 1] * base + str[i - 1] + 1007) % mod;
        }

        for (int i = len; i >= 1; i--){
            r_hash[i] = (r_hash[i + 1] * base + str[i - 1] + 1007) % mod;
        }
    }

    // inline: loads function at compile time, improves efficiency for light-weight functions

    inline int forward_hash(int l, int r){
    // return hash value of substring in - [l,r]
    // stored in 32 bits (int)

        int h = f_hash[r + 1] - ((long long)basepow[r - l + 1] * f_hash[l] % mod);
        return h < 0 ? h + mod : h;
    }

    inline int reverse_hash(int l, int r){;
    // return hash value of reverse substring in - [l,r]
    // reverse meaning positions sequence: r, (r-1) ... (l+1), l
    // stored in 32 bits (int)

        int h = r_hash[l + 1] - ((long long)basepow[r - l + 1] * r_hash[r + 2] % mod);
        return h < 0 ? h + mod : h;
    }
};

struct StringHash{
// Create hash value of a string by double hashing using the 'SingleHash' struct
// use this struct in main code

    SingleHash sh1, sh2;
    int base_1, mod_1, base_2, mod_2;

    StringHash(string str){
    // Use the SingleHash implementation by providing base & mod
    // base & mode with large prime numbers reduce hash value collision chances
    // randomely picking prime numbers reduce chances of getting hacked in live contests, targeted test cases

        unsigned int seed = chrono::system_clock::now().time_since_epoch().count();
        srand(seed);  /// to avoid getting hacked in CF, comment this line for easier debugging

        int q_len = (sizeof(PRIMES) / sizeof(PRIMES[0])) / 4;
        base_1 = PRIMES[rand() % q_len];
        mod_1  = PRIMES[rand() % q_len + q_len];
        base_2 = PRIMES[rand() % q_len + 2 * q_len];
        mod_2  = PRIMES[rand() % q_len + 3 * q_len];

        sh1 = SingleHash(str, base_1, mod_1);
        sh2 = SingleHash(str, base_2, mod_2);
    }

    StringHash(string str, int _base_1, int _mod_1, int _base_2, int _mod_2){
    // Use the SingleHash implementation with fixed base & mod
    // useful when multiple strings hash comparison is required
    // provide previous strings base and mod as parameters

        base_1 = _base_1;
        mod_1  = _mod_1;
        base_2 = _base_2;
        mod_2  = _mod_2;

        sh1 = SingleHash(str, base_1, mod_1);
        sh2 = SingleHash(str, base_2, mod_2);
    }

    /// returns the hash of the substring from indices l to r (inclusive)
    long long forward_hash(int l, int r){
    // Use implementation of SingleHash struct
    // both hashes are of 32 bits
    // shift left first hash by 32 bits and XOR with second hash
        return ((long long)sh1.forward_hash(l, r) << 32) ^ sh2.forward_hash(l, r);
    }

    /// returns the hash of the reversed substring from indices l to r (inclusive)
    long long reverse_hash(int l, int r){
    // Use implementation of SingleHash struct
    // both hashes are of 32 bits
    // shift left first hash by 32 bits and XOR with second hash
        return ((long long)sh1.reverse_hash(l, r) << 32) ^ sh2.reverse_hash(l, r);
    }
};

///---------------------------------------------------------  String Hashing end  ---------------------------------------------------------///


void exec(){
// execute the algorithm

    string s = "abcacba";

    StringHash s_hash = StringHash(s);

    bool isPalindrom = true;

    for(int i=0, j = s.size()-1; i<s.size()/2; i++, j--){

        if(s_hash.forward_hash(0, i)!=s_hash.reverse_hash(j, s.size()-1)){
            isPalindrom = false;
            break;
        }
    }

    if(isPalindrom)
        cout<<"palindrome!";
    else
        cout<<"error! not palindrome...";

}


int main()
{
    exec();

    return 0;
}
