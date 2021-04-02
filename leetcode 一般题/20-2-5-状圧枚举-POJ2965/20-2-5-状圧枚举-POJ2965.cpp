#include<stdio.h>
#include<string.h>
#include<iostream>
using namespace std;
const int maxn = 25;
const int INF = 0x3f3f3f3f;
int g[5][5];
int tmp_x[maxn];
int tmp_y[maxn];
int ans_pathx[maxn];
int ans_pathy[maxn];
int ans = INF;

void traverse(int pos){
    int tx = pos / 4, ty = pos % 4;
    g[tx][ty] = !g[tx][ty];
    for (int i = 0; i < 4; i++){
        g[i][ty] = !g[i][ty];
        g[tx][i] = !g[tx][i];
    }
}

bool ok(){
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++)
            if (g[i][j] == 0) {
                return false;
            }
    }
    return true;
}

//遍历到了第pos个, 翻转了traverse_num个
void dfs(int pos, int traverse_num){
    if (ok()){
        if (ans > traverse_num){
            ans = traverse_num;
            for (int i = 0; i < ans; i++){
                ans_pathx[i] = tmp_x[i], ans_pathy[i] = tmp_y[i];
            }
        }
        return;
    }
    if (pos >= 16) {
        return;
    }
    //第pos个不翻转
    dfs(pos + 1, traverse_num);

    //翻转存入g中
    traverse(pos);
    tmp_x[traverse_num] = pos / 4 + 1;
    tmp_y[traverse_num] = pos % 4 + 1;
    dfs(pos + 1, traverse_num + 1);
    traverse(pos);
}

int main(){
    char c;
    memset(g, 0, sizeof(g));
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++) {
            cin >> c;
            if (c == '-') {
                g[i][j] = 1;
            }
            else {
                g[i][j] = 0;
            }
        }
    }
    dfs(0, 0);
    cout << ans << "\n";
    for (int i = 0; i < ans; i++){
        printf("%d %d\n", ans_pathx[i], ans_pathy[i]);
    }
    return 0;
}