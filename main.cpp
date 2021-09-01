#include<iostream>
#include<math.h>
#include<string.h>
#include<stdlib.h>

using namespace std;

// Variables y Funciones
long int p, q, n, totient, flag, e[100], d[100], temp[100], j, m[100], en[100], i;
char message[100];

int primeNumber(long int);

void euler();

long int gcd(long int);

void encrypt();

void decrypt();

// This function allows to validate that two numbers n > 1 have de characteristics to be prime numbers
// The two numbers are going to be inserted by the user
int primeNumber(long int numPrime) {
    int i;
    j = sqrt(numPrime);
    for (i = 2; i <= j; i++) {
        if (numPrime % i == 0)
            return 0;
    }
    return 1;
}

int main() {

    // Enter of the two prime numbers
    cout << "\nFirst Prime Number\n";
    cin >> p;
    flag = primeNumber(p);
    if (flag == 0) {
        cout << "\nWrong Input!\n";
        exit(1);
    }
    cout << "\nSecond Prime Number\n";
    cin >> q;
    flag = primeNumber(q);
    if (flag == 0 || p == q) {
        cout << "\nWrong Input!\n";
        exit(1);
    }

    // Enter of the message to encrypt
    cout << "\nMessage\n";
    fflush(stdin);
    cin >> message;
    for (i = 0; message[i] != NULL; i++)
        m[i] = message[i];

    // Modulus of the two keys
    n = p * q;

    // Totient
    totient = (p - 1) * (q - 1);

    // Call of Functions
    euler();
    encrypt();
    decrypt();
    return 0;
}

// This function implements de logic of gcd (Greatest Common Divisor)
// The GDC of 'a' and 'b' is the largest positive integer which is a factor of both 'a' and 'b'
long int gcd(long int x) {
    long int k = 1;
    while (1) {
        k = k + totient;
        if (k % x == 0)
            return (k / x);
    }
}

// This function implements de Euler's Phi logic; counts the number of integers such that gcd(a,n)=1
void euler() {
    int k;
    k = 0;
    for (i = 2; i < totient; i++) {
        if (totient % i == 0)
            continue;
        flag = primeNumber(i);
        if (flag == 1 && i != p && i != q) {
            e[k] = i;
            flag = gcd(e[k]);
            if (flag > 0) {
                d[k] = flag;
                k++;
            }
            if (k == 99)
                break;
        }
    }
}


// This function Encrypt the message
void encrypt() {
    long int pt, ct, key = e[0], k, len;
    i = 0;
    len = strlen(message);
    while (i != len) {
        pt = m[i];
        pt = pt - 96;
        k = 1;
        for (j = 0; j < key; j++) {
            k = k * pt;
            k = k % n;
        }
        temp[i] = k;
        ct = k + 96;
        en[i] = ct;
        i++;
    }
    en[i] = -1;
    cout << "\nEncrypted Message:\n";
    for (i = 0; en[i] != -1; i++)
        printf("%c", en[i]);
}

// This function Decrypt the message
void decrypt() {
    long int pt, ct, key = d[0], k;
    i = 0;
    while (en[i] != -1) {
        ct = temp[i];
        k = 1;
        for (j = 0; j < key; j++) {
            k = k * ct;
            k = k % n;
        }
        pt = k + 96;
        m[i] = pt;
        i++;
    }
    m[i] = -1;
    cout << "\nDecrypted Message:\n";
    for (i = 0; m[i] != -1; i++)
        printf("%c", m[i]);
}

