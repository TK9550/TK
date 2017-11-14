#include <cstdio>
#include <vector>
#define X first
#define Y second
#define dbg printf("OK on line %d\n", __LINE__ )

using namespace std;
typedef pair<int,int> pnt;

int r,s;
char polje[105][105];
bool visited[105][105];

int transX[] = {0,0,-1,1};
int transY[] = {1,-1,0,0};

inline bool valid(int x, int y){
    return x>=0 && y>=0 && x<=r && y<=s;
}

void set_f(){
    for(int i=0;i<r;++i)
        for(int j=0;j<s;++j)
            visited[i][j]=false;
}

bool is_ok(int x, int y){
    if(x==0) return true;
    visited[x][y]=true;
    for(int i=0;i<4;++i){
        if(valid(x+transX[i], y+transY[i]) && !visited[x+transX[i]][y+transY[i]] && polje[x+transX[i]][y+transY[i]]=='x'){
            if(is_ok(x+transX[i], y+transY[i])){
                return true;
            }
        }
    }
    return false;
}

void find_all(int x, int y, vector<pnt>& dio){
    dio.push_back(pnt(x,y));
    polje[x][y]='.';
    for(int i=0;i<4;++i)
        if(valid(x+transX[i], y+transY[i]) && polje[x+transX[i]][y+transY[i]]=='x')
            find_all(x+transX[i], y+transY[i], dio);
}

void fix(int x, int y){
    vector<pnt> dio;
    vector<pnt> dio2;
    find_all(x,y,dio2);
    bool done=false;
    while(!done){
        dio=vector<pnt>(move(dio2));
        for(pnt i:dio){
            if(polje[i.X-1][i.Y]=='x'){
                done=true;
                break;
            }
            dio2.push_back(pnt(i.X-1, i.Y));
        }

    }
    for(pnt i:dio){
        polje[i.X][i.Y]='x';
    }

}

void solve(int x, int y){
    polje[x][y]='.';
    for(int i=0;i<4;++i){
        if(valid(x+transX[i], y+transY[i]) && polje[x+transX[i]][y+transY[i]]=='x' && !is_ok(x+transX[i], y+transY[i])){
            fix(x+transX[i], y+transY[i]);
        }
        set_f();

    }

}


int main(){
    scanf("%d%d", &r,&s);
    for(int i=0;i<104;++i){
        polje[0][i]='x';
    }
    for(int i=r;i>=1;--i){
        scanf("%s", polje[i]);
    }
    int n;
    scanf("%d", &n);
    for(int i=0;i<n;++i){
        int tmp;
        scanf("%d", &tmp);
        if(i%2){
            for(int j=s-1;j>=0;--j){
                if(polje[tmp][j]=='x'){
                    solve(tmp,j);
                    break;
                }
            }
        }else{
            for(int j=0;j<s;++j){
                if(polje[tmp][j]=='x'){
                    solve(tmp,j);
                    break;
                }
            }
        }
    }
    for(int i=r;i>=1;--i){
        printf("%s\n", polje[i]);
    }
}
