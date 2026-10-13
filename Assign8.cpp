#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

string removeLeadingZeros(string str) {
    int n = str.length();
    int i = 0;
    while (i < n - 1 && str[i] == '0') {
        i++;
    }
    return str.substr(i);
}

string add(string num1, string num2) {
    string result = "";
    int i = num1.length() - 1;
    int j = num2.length() - 1;
    int carry = 0;

    while (i >= 0 || j >= 0 || carry > 0) {
        int sum = carry;
        if (i >= 0) sum += num1[i--] - '0';
        if (j >= 0) sum += num2[j--] - '0';
        result += to_string(sum % 10);
        carry = sum / 10;
    }
    reverse(result.begin(), result.end());
    return result;
}

string subtract(string num1, string num2) {
    string result = "";
    int n1 = num1.length();
    int n2 = num2.length();
    
    if (n2 < n1) {
        num2 = string(n1 - n2, '0') + num2;
    }

    int borrow = 0;
    for (int i = n1 - 1; i >= 0; i--) {
        int diff = (num1[i] - '0') - (num2[i] - '0') - borrow;
        if (diff < 0) {
            diff += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }
        result += to_string(diff);
    }
    reverse(result.begin(), result.end());
    return removeLeadingZeros(result);
}

string multiply10(string str, int n) {
    if (str == "0") return "0";
    return str + string(n, '0');
}

string karatsuba(string X, string Y) {
    X = removeLeadingZeros(X);
    Y = removeLeadingZeros(Y);

    if (X.length() == 0) X = "0";
    if (Y.length() == 0) Y = "0";

    // Base Case: If the length is <= 9, it fits within C++'s long long range[cite: 1]
    // The maximum possible value for 9 digits (999,999,999^2) fits in a signed long long
    if (X.length() <= 9 && Y.length() <= 9) {
        long long x = stoll(X);
        long long y = stoll(Y);
        return to_string(x * y);
    }

    // Determine the length n, and pad the shorter string with leading zeros[cite: 1]
    int n = max(X.length(), Y.length());
    if (X.length() < n) X = string(n - X.length(), '0') + X;
    if (Y.length() < n) Y = string(n - Y.length(), '0') + Y;

    // Divide step: Split strings into high and low halves at midpoint m[cite: 1]
    int m = n / 2;
    int highLength = n - m;

    string X_high = X.substr(0, highLength); // 'a' in N = a*10^m + b
    string X_low = X.substr(highLength, m);  // 'b' in N = a*10^m + b
    string Y_high = Y.substr(0, highLength);
    string Y_low = Y.substr(highLength, m);

    // Conquer step: Perform the 3 sub-multiplications recursively[cite: 1]
    string P1 = karatsuba(X_high, Y_high);                         // P1 = a * a
    string P2 = karatsuba(X_low, Y_low);                           // P2 = b * b
    string P3 = karatsuba(add(X_high, X_low), add(Y_high, Y_low)); // P3 = (a+b) * (a+b)

    // Calculate middle term: M = P3 - P1 - P2[cite: 1]
    string M = subtract(subtract(P3, P1), P2);

    // Combine step: N^2 = P1 * 10^(2m) + M * 10^m + P2[cite: 1]
    string term1 = multiply10(P1, 2 * m);
    string term2 = multiply10(M, m);
    string term3 = P2;

    string result = add(add(term1, term2), term3);
    
    // Remove leading zeros before returning the final result[cite: 1]
    return removeLeadingZeros(result);
}

int main() {
    cout << "Enter a 20-digit number: ";
    string N;
    cin >> N;

    // Verify string length for exact assignment requirements (optional but recommended)
    if(N.length() != 20) {
        cout << "Warning: Number is not exactly 20 digits." << endl;
    }

    // Call Karatsuba function to square the 20-digit input N
    string N_squared = karatsuba(N, N);

    // Output formatting matching the sample output format provided[cite: 1]
    cout << "\nN   = " << N << endl;
    cout << "N^2 = " << N_squared << endl;
    cout << "Digits in N^2: " << N_squared.length() << endl;
    cout << "Method: Karatsuba Divide and Conquer\n";

    return 0;
}