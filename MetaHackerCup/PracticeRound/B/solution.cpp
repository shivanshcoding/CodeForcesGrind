#include <bits/stdc++.h>
using namespace std;

struct Cell {
    int r, c;
};

int dr[4] = {-1, 1, 0, 0};
int dc[4] = {0, 0, -1, 1};

void solve() {
    int R, C, S;
    cin >> R >> C >> S;
    vector<string> grid(R);
    for (int i = 0; i < R; i++) cin >> grid[i];

    // Step 1: compute distance from walls/obstacles
    vector<vector<int>> dist(R, vector<int>(C, INT_MAX));
    queue<Cell> q;

    // push all walls (#) and boundary cells
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            if (grid[i][j] == '#') {
                dist[i][j] = 0;
                q.push({i,j});
            }
        }
    }
    // also consider boundaries as walls
    for(int i=0;i<R;i++){
        if(grid[i][0]=='.'){ dist[i][0]=1; q.push({i,0}); }
        if(grid[i][C-1]=='.'){ dist[i][C-1]=1; q.push({i,C-1}); }
    }
    for(int j=0;j<C;j++){
        if(grid[0][j]=='.'){ dist[0][j]=1; q.push({0,j}); }
        if(grid[R-1][j]=='.'){ dist[R-1][j]=1; q.push({R-1,j}); }
    }

    // BFS to compute shortest distance to nearest wall/obstacle
    while(!q.empty()){
        auto cur = q.front(); q.pop();
        int r = cur.r, c = cur.c;
        for(int k=0;k<4;k++){
            int nr = r + dr[k], nc = c + dc[k];
            if(nr>=0 && nr<R && nc>=0 && nc<C){
                if(dist[nr][nc] > dist[r][c]+1){
                    dist[nr][nc] = dist[r][c]+1;
                    q.push({nr,nc});
                }
            }
        }
    }

    // for(int i=0;i<R;i++){
    //     for(int j=0;j<C;j++){
    //         cout<<dist[i][j]<<" ";
    //     }
    //     cout<<"\n";
    // }
    // cout<<"\n";
    // Step 2: BFS to find largest connected safe zone (dist >= S)
    vector<vector<bool>> visited(R, vector<bool>(C,false));
    int max_safe = 0;

    for(int i=0;i<R;i++){
        for(int j=0;j<C;j++){
            if(!visited[i][j] && dist[i][j] > S){
                int cnt = 0;
                queue<Cell> qq;
                qq.push({i,j});
                visited[i][j] = true;
                while(!qq.empty()){
                    auto cur2 = qq.front(); qq.pop();
                    cnt++;
                    int r = cur2.r, c = cur2.c;
                    for(int k=0;k<4;k++){
                        int nr = r + dr[k], nc = c + dc[k];
                        if(nr>=0 && nr<R && nc>=0 && nc<C){
                            if(!visited[nr][nc] && dist[nr][nc] > S){
                                visited[nr][nc] = true;
                                qq.push({nr,nc});
                            }
                        }
                    }
                }
                max_safe = max(max_safe, cnt);
            }
        }
    }

    cout << max_safe << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    for(int tc=1; tc<=T; tc++){
        cout << "Case #" << tc << ": ";
        solve();
    }
    return 0;
}
