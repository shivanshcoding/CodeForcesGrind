#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct AnkPrakriya {   // "Digit Processing"
    vector<ll> dasmala; // "powers of 10" (dasmala = decimal)

    AnkPrakriya() {
        dasmala.resize(20, 1);
        for (int i = 1; i < 20; i++) dasmala[i] = dasmala[i - 1] * 10;
    }

    // yog of digits from 1..ant
    ll ankYog(ll ant) {
        if (ant <= 0) return 0;
        ll yog = 0;
        for (ll sthaan = 1; sthaan <= ant; sthaan *= 10) {
            ll bada = ant / (sthaan * 10);
            ll vartman = (ant / sthaan) % 10;
            ll chhota = ant % sthaan;

            yog += bada * sthaan * 45;                        // poore chakr
            yog += (vartman * (vartman - 1) / 2) * sthaan;    // adhoora yog
            yog += vartman * (chhota + 1);                    // shesh

            if (sthaan > ant / 10) break; // overflow se bachaav
        }
        return yog;
    }

    // ek prashn ka uttar
    ll samadhan(ll k) {
        ll uttar = 0;
        for (int lambai = 1; lambai < 20 && k > 0; lambai++) {
            ll kitne = 9LL * dasmala[lambai - 1];       // itne sankhya is lambai ki
            ll kulAnk = kitne * lambai;                 // unke total digits
            ll shuru = dasmala[lambai - 1];             // pratham sankhya is lambai ki

            if (k >= kulAnk) {
                // poora block le lo
                uttar += ankYog(dasmala[lambai] - 1) - ankYog(shuru - 1);
                k -= kulAnk;
            } else {
                ll poore = k / lambai;
                ll bache = k % lambai;

                if (poore > 0) {
                    uttar += ankYog(shuru + poore - 1) - ankYog(shuru - 1);
                }

                if (bache > 0) {
                    string sankhya = to_string(shuru + poore);
                    uttar += accumulate(sankhya.begin(), sankhya.begin() + bache, 0LL,
                                        [](ll yog, char ch) { return yog + (ch - '0'); });
                }
                break;
            }
        }
        return uttar;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int pariksha;
    cin >> pariksha;

    AnkPrakriya yantra;
    vector<ll> pratyuttar;
    pratyuttar.reserve(pariksha);

    while (pariksha--) {
        ll k;
        cin >> k;
        pratyuttar.push_back(yantra.samadhan(k));
    }

    for (ll u : pratyuttar) cout << u << "\n";
    return 0;
}
