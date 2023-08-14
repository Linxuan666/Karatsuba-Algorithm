#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

// School Method for integer addition
string add(string I1, string I2, int B) {
    int len = max(I1.size(), I2.size());
    int c = 0;
    int s;
    string sum;
    for (int i = 0; i < len || c; i++) {
        if (i < I1.size()) c += I1[I1.size() - i - 1] - '0';
        if (i < I2.size()) c += I2[I2.size() - i - 1] - '0';
        s = c % B;
        c = c / B;
        sum.push_back(s + '0');
    }
    reverse(sum.begin(), sum.end());
    return sum;
}

// subtract two numbers
string subtract(string I1, string I2, int B) {
    int len = max(I1.size(), I2.size());
    int c = 0;
    int s;
    string sub;
    for (int i = 0; i < len; i++) {
        if (i < I1.size()) c += I1[I1.size() - i - 1] - '0';
        if (i < I2.size()) c -= I2[I2.size() - i - 1] - '0';
        if (i == len - 1 && c < 0) return "-"+subtract(I2, I1, B);
        if (c >= 0) {
            s = c;
            c = 0;

        }
        else {
            s = B + c;
            c = -1;
        }
        sub.push_back(s + '0');
    }
    reverse(sub.begin(), sub.end()); 
    while (sub[0] == '0' && sub.size() > 1) sub.erase(0,1);
    return sub;
}

// School Method for integer multiplication
string school_mul(string I1, string I2, int B) {
    int m = I1.size();
    int len2 = I2.size();
    string sch_mul = "0";
    for (int j = 0; j < len2; j++) {
        int c = 0;
        int a_b, d;
        std::string sum;
        for (int i = 0; i < m; i++) {
            a_b = (I1[m - i - 1] - '0') * (I2[len2 - j - 1] - '0');
            d = (a_b + c) % B;
            c = (a_b + c) / B;
            sum = std::to_string(d) + sum;
            if (i == m - 1) {
                sum = std::to_string(c) + sum;
                sum.append(j, '0');
            }
        }
        sch_mul = add(sch_mul, sum, B);
    }
    while (sch_mul[0] == '0' && sch_mul.size() > 1) sch_mul.erase(0, 1);
    return sch_mul;
}

// Karatsuba Algorithm for integer multiplication 
string multiply(string I1, string I2, int B) {
    if (I1 == "0" || I2 == "0") return "0";
    int len1 = I1.size();
    int len2 = I2.size();
    if (len1 < len2) return multiply(I2, I1, B);
    int m = len1;
    if (m < 4) return school_mul(I1, I2, B); 
    int k = m / 2;
    string a1, a0, b1, b0;
    if (len1-k >= len2) {
        a1 = I1.substr(0, k);
        a0 = I1.substr(k);
        b1 = "0";
        b0 = I2;
    }
    else {
        a1 = I1.substr(0, k);
        a0 = I1.substr(k);
        b1 = I2.substr(0, len2 - len1 + k);
        b0 = I2.substr(len2 - len1 + k);
    }
    string p2 = multiply(a1, b1, B);
    string p0 = multiply(a0, b0, B);
    string p1 = subtract(multiply(add(a1,a0,B),add(b1,b0,B),B), add(p2, p0, B), B);
    string product = add(add(p2+string((m-k)*2,'0'),p1 + string(m-k,'0'), B), p0, B);
    while (product[0] == '0' && product.size() > 1) product.erase(0, 1);
    return product;
}

// tool: add 0 to the behind of the string
string addZeroBottom(string I1, int num)
{
    if (I1 == "0")
    {
        return I1;
    }
    for (long int i = 0; i < num; i++)
    {
        I1 += "0";
    }
    return I1;
}

// tool: compare the length of two numbers
int compareLength(string I1, string I2)
{
    long int len1 = I1.length();
    long int len2 = I2.length();
    if (len1 > len2)
    {
        return 1;
    }
    else if (len1 < len2)
    {
        return -1;
    }
    for (long int i = 0; i < len1; i++)
    {
        if (I1.at(i) > I2.at(i))
        {
            return 1;
        }
        if (I1.at(i) < I2.at(i))
        {
            return -1;
        }
    }
    return 0;
}

// integer division 
string divide(string I1, string I2, int B) {
    int len1 = I1.size();
    int len2 = I2.size();
    std::string div;

    if (len2 > len1 || I1 == "0") return "0";
    if ((len1 == len2) || (len1 == len2+1)) {
        int count = 0;
        string diff = I1;
        for (int i = 0; ; i++) {
            diff = subtract(diff, I2, B);
            if (diff[0] != '-') count = i + 1;
            else break;
        }
        //transform count to B-based
        int s;
        do {
            s = count % B;
            count = count / B;
            div = std::to_string(s) + div;
        } while (count != 0);
        return div;
    }
    string num1 = I1;
    string s;
    for (int i = len1 - len2; i >= 0; i--) {
        string num2 = addZeroBottom(I2, i);
        s = divide(num1, num2, B);
        div += s;
        num1 = subtract(num1, multiply(num2, s, B), B);
    }
    while (div[0] == '0' && div.size() > 1) div.erase(0, 1);
    return div;
}

// add, multiply and divide the input number of user
int main() {
    string I1, I2;
    int B;
    cin >> I1 >> I2 >> B;
    cout << add(I1, I2, B) << ' ' << multiply(I1, I2, B) << ' ' << divide(I1, I2, B) << endl;
    return 0;
}
