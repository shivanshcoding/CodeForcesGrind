#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int pariksha; // test cases ka count
    cin >> pariksha;

    while (pariksha--) {
        int gintiElement, maxValue; 
        cin >> gintiElement >> maxValue;

        vector<int> sankhya(gintiElement); // array of numbers
        for (int i = 0; i < gintiElement; i++) {
            cin >> sankhya[i];
        }

        // yahaan hum un pairs ko store karenge jinka gcd 1 hai
        vector<pair<int, int>> coprimeJode;

        // sabhi pairs check karo jab tak 50 tak gcd=1 wale pairs na mil jayein
        for (int i = 0; i < gintiElement && (int)coprimeJode.size() < 50; i++) {
            for (int j = i + 1; j < gintiElement && (int)coprimeJode.size() < 50; j++) {
                if (gcd(sankhya[i], sankhya[j]) == 1) {
                    coprimeJode.push_back({i + 1, j + 1}); // 1-based index
                }
            }
        }

        bool milGaya = false; // kya answer mil gaya?

        // agar kam se kam 2 coprime pairs mil gaye to unko check karo ki kya disjoint hain
        if (coprimeJode.size() >= 2) {
            for (size_t i = 0; i < coprimeJode.size(); i++) {
                for (size_t j = i + 1; j < coprimeJode.size(); j++) {
                    auto [p1, q1] = coprimeJode[i];
                    auto [p2, q2] = coprimeJode[j];
                    milGaya = true;
                    cout<<p1<<" "<<q1<<" "<<p2<<" "<<q2<<"\n";
                    break;
                }
                if (milGaya) break;
            }
            
        }

        // agar kuch nahi mila to 0 print karo
        if (!milGaya) {
            cout << 0 << "\n";
        }
    }

    return 0;
}
