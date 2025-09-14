#include<bits/stdc++.h>
using namespace std;


int main(){
	int T;
	cin >> T;
	while(T--){
		int n, m, x , y;
		cin >> n >> m;
		int px = 0, py = 0;
		int points = 0;
		while(n--){
			cin >> x >> y;
			points += x - px;
			if(((x - px + 2) % 2) != ((y - py + 2) % 2))points--;
			px = x;
			py = y;
		}
		if(px != m){
			points += m - px;
		}
		cout << points << endl;
	}
}