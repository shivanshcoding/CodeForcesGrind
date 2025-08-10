#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

#define sab(a) (a).begin(), (a).end()
#define suchi vector
#define joda pair<int, int>
#define dusra second
#define pahla first
#define jodo push_back
#define adhiktam_tatva(v) *max_element((v).begin(), (v).end())
#define nyuntam_tatva(v) *min_element((v).begin(), (v).end())

void samasya_halo(){
    ll lambai;
    cin >> lambai;
    string pehli, dusri;
    cin >> pehli >> dusri;

    // prefix sum pehli string ka
    suchi<ll> pehli_ginti(lambai+1, 0);
    suchi<ll> dusri_ginti(lambai+1, 0);
    for(int i=0; i<lambai; i++){
        pehli_ginti[i+1] = pehli_ginti[i] + (pehli[i] - '0');
        dusri_ginti[i+1] = dusri_ginti[i] + (dusri[i] - '0');
    }

    // har index ka vishesh maan nikalna
    suchi<ll> pehli_moolya(lambai);
    suchi<ll> dusri_moolya(lambai);
    for(int i=0; i<lambai; i++){
        pehli_moolya[i] = 2 * pehli_ginti[i+1] - (i+1);
        dusri_moolya[i] = 2 * dusri_ginti[i+1] - (i+1);
    }

    // dusri_moolya ko sort karna
    sort(sab(dusri_moolya));

    // prefix sum dusri_moolya ka
    suchi<ll> dusri_moolya_jod(lambai+1, 0);
    for(int i=0; i<lambai; i++){
        dusri_moolya_jod[i+1] = dusri_moolya_jod[i] + dusri_moolya[i];
    }

    ll kul_jod_dusri = dusri_moolya_jod[lambai];
    ll kul_absolute_jod = 0;

    // kul absolute sum nikalna
    for(ll maan : pehli_moolya){
        ll sthiti = lower_bound(sab(dusri_moolya), -maan) - dusri_moolya.begin();
        kul_absolute_jod += maan * (lambai - 2*sthiti) + kul_jod_dusri - 2 * dusri_moolya_jod[sthiti];
    }

    ll kul_xy_samyukt = lambai * lambai * (lambai + 1);
    ll uttar = (kul_xy_samyukt - kul_absolute_jod) / 2;

    cout << uttar << endl;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int parikshan;
    cin >> parikshan;
    while(parikshan--){
        samasya_halo();
    }
    return 0;
}
