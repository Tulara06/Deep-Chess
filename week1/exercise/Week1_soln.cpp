#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>   // For reading files (ifstream)
#include <cctype>    // For isspace()
using namespace std;
// Helper function to calculate the maximum score difference 
// the current player can achieve starting from 'index'
long long getMaxDiff(int index, int n, const vector<long long>& a) {

    if (index >= n) {
        return 0;
    }
    
   
    if (index == n - 1) {
        return a[index];
    }

   
    long long option1 = a[index] - getMaxDiff(index + 1, n, a);
    long long option2 = a[index] + a[index + 1] - getMaxDiff(index + 2, n, a);
    return max(option1, option2);
}
string solve(int n, vector<long long> a) {

    long long final_diff = getMaxDiff(0, n, a);

    // Evaluate the final score difference for Player 1
    if (final_diff > 0) {
        return "Player 1"; // Player 1 got more points
    } else if (final_diff < 0) {
        return "Player 2"; // Player 2 got more points
    } else {
        return "Draw";     // It was a  tie
    }
    return "";
}

static string trim(const string &s) {
    int l = 0, r = (int)s.size() - 1;
    while (l <= r && isspace((unsigned char)s[l])) l++;
    while (r >= l && isspace((unsigned char)s[r])) r--;
    if (l > r) return "";
    return s.substr(l, r - l + 1);
}

static bool file_exists(const string &path) {
    ifstream f(path);
    return f.good();
}

int main() {
    const string folder = "testcases";

    int passed = 0;
    int total = 0;

    for (int tc = 0; ; tc++) {
        string in_path = folder + "/input" + to_string(tc) + ".txt";
        string out_path = folder + "/output" + to_string(tc) + ".txt";

        if (!file_exists(in_path) && !file_exists(out_path)) {
            break;
        }

        total++;

        if (!file_exists(in_path)) {
            cout << "Failed on testcase " << tc << ": missing " << in_path << '\n';
            continue;
        }
        if (!file_exists(out_path)) {
            cout << "Failed on testcase " << tc << ": missing " << out_path << '\n';
            continue;
        }

        ifstream fin(in_path);
        int n;
        fin >> n;
        vector<long long> a(n);
        for (int i = 0; i < n; i++) fin >> a[i];

        if (!fin) {
            cout << "Failed on testcase " << tc << ": invalid input format\n";
            continue;
        }

        string got = trim(solve(n, a));

        ifstream fout(out_path);
        string expected, line;
        while (getline(fout, line)) {
            if (!expected.empty()) expected += "\n";
            expected += line;
        }
        expected = trim(expected);

        if (got == expected) {
            cout << "OK testcase " << tc << '\n';
            passed++;
        } else {
            cout << "Failed on testcase " << tc << '\n';
            cout << "Expected: " << expected << '\n';
            cout << "Got     : " << got << '\n';
        }
    }

    if (total == 0) {
        cout << "No testcases found. Make sure there is a testcases folder with input0.txt and output0.txt.\n";
        return 1;
    }

    cout << "\nPassed " << passed << " / " << total << " testcases.\n";

    if (passed == total) {
        cout << "OK\n";
        return 0;
    } else {
        cout << "Failed\n";
        return 1;
    }
    


}
