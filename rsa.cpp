/*
 * RSA Encryption and Decryption Program
 *
 * The RSA Algorithm:
 * Public key is used to encrypt the messages and the private key is used to
 * decrypt the messages.
 * User1 => User2   uses User2's key pair.
 * 1. To generate a pair of keys, two large prime numbers are used, since
 *    factoring numbers is a hard problem.
 * 2. Here we can use sieve to generate prime. However, today it is recommended
 *    that the numbers should be atleast 1024 bits.
 * 3. Then take the product of those two numbers, say p and q, and store it in n.
 * 4. Then calculate (p-1)*(q-1) and store it in m.
 * 5. Find e that is relatively prime or co-prime to m and less than m.
 * 6. Find d that satisfies => d*e = 1 (mod m) using extended Euclidean Algo.
 * 7. Now, the public key will be the pair (e, n).
 * 8. And the private key will be the pair (d, n).
 *
 * Note: We can break our message M in smaller chunks, all smaller than n and
 *       then encrypt each of those chunks.
 *       For example: string "abcd" can be divided into four chunks a, b, c, d
 *
 * 9. We are going to use the ascii values of string chunks to encrypt them.
 * 10. Let the cipher be c, then => c = M^e (mod n). (M is the message.)
 * 11. Decryption is done using => c^d(mod n).
*/

#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

ll extendedEA(ll e, ll m);

int main(void)
{
    ll p, q, e, d;
    printf("RSA: Encryption\n");

    // Take two prime numbers from user.
    printf("Enter the first prime number: ");
    cin >> p;
    printf("Enter the second prime number: ");
    cin >> q;

    // n is modulus.
    ll n = p * q;
    // euler's totient
    ll m = (p-1)*(q-1);

    // Setting e = 2 as p and q are already prime.
    e = 101;

    // Finding d using extended Euclidean Algorithm.
    d = extendedEA(e, m);

    cout << "Encryption Pair is: (" << n << ", " << e << ")" << endl;

    // Open the file containing the plain text.
    FILE* fin = fopen("plain.txt", "r");

    // Open the file that will contain the cipher text.
    FILE* fout = fopen("cipher.txt", "w");

    // Variable to hold one character from plain text at a time.
    char c;
    // Variable storing the ascii value of character stored in c.
    int M;

    // Reading the plain text file untill EOF occurs.
    // Calculating the value of c = M ^ e(mod n).
    while(fscanf(fin, "%c", &c) != EOF)
    {
        M = c;
        ll temp = e;
        ll prod = 1;
        while(temp--)
        {
            prod *= M;
            if(prod > n)
                prod %= n;
        }
        fprintf(fout, "%lld\n", prod);
    }

    // Close the opened files.
    fclose(fin);
    fclose(fout);

    cout << "Decryption Pair is: (" << n << ", " << d << ")" << endl;

    // Take the file containing the cipher text.
    fin = fopen("cipher.txt", "r");
    fout = fopen("decrypt.txt", "w");

    // Stores the number from cipher text in the form of string.
    char s[100];

    // Reading the cipher text file untill the EOF occurs.
    // Calculating the value of m = c ^ d(mod n).
    while(fscanf(fin, "%s", s) != EOF)
    {
        int x = atoi(s);
        int temp = d;
        ll prod = 1;
        while(temp--)
        {
            prod *= x;
            if(prod > n)
                prod %= n;
        }
        char c = prod;
        fprintf(fout, "%c", c);
    }

    // Closing the opened files.
    fclose(fin);
    fclose(fout);
}

ll extendedEA(ll e, ll m)
{
    ll temp;
    struct pa
    {
        ll x, y, d, k;
    } p1, p2;

    p1.x = 1, p1.y = 0, p1.d = e, p1.k = 0;
    p2.x = 0, p2.y = 1, p2.d = m, p2.k = 0;

    while(p2.d != 1 && p1.k != p2.d)
    {
        p2.k = p1.d / p2.d;
        temp = p2.x;
        p2.x = p1.x - temp*(p2.k);
        p1.x = temp;
        temp = p2.y;
        p2.y = p1.y - temp*(p2.k);
        p1.y = temp;
        temp = p2.d;
        p2.d = p1.d - temp*(p2.k);
        p1.d = temp;
        p1.k = p2.k;
    }
    if(p2.x < 0)
        return p2.x + m;
    return p2.x;
}
