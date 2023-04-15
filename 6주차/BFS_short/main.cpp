#include <iostream>
#include <queue>
#include <vector>

using namespace std;

const int MAX_N = 1000; // 적과 플레이어의 최대 위치
const int dx[4] = { 0, 0, 1, -1 }; // 이동 방향
const int dy[4] = { 1, -1, 0, 0 };

int playerX, playerY, enemyX, enemyY;
int N, M; // 적과 플레이어의 위치
int dist[MAX_N][MAX_N]; // 거리를 저장할 배열
bool visited[MAX_N][MAX_N]; // 방문 여부를 저장할 배열

struct Point {
    int x, y, d; // x좌표, y좌표, 거리
};

int bfs(int sx, int sy, int ex, int ey) {
    queue<Point> q;
    q.push({ sx, sy, 0 }); // 시작점을 큐에 삽입
    visited[sx][sy] = true; // 시작점 방문 표시

    while (!q.empty()) {
        Point cur = q.front();
        q.pop();

        if (cur.x == ex && cur.y == ey) { // 목적지에 도착한 경우 거리 반환
            return cur.d;
        }

        for (int i = 0; i < 4; i++) { // 이동 가능한 모든 경우를 고려
            int nx = cur.x + dx[i];
            int ny = cur.y + dy[i];

            if (nx < 0 || nx >= N || ny < 0 || ny >= M) continue; // 범위를 벗어나는 경우
            if (visited[nx][ny]) continue; // 이미 방문한 경우

            visited[nx][ny] = true; // 방문 표시
            dist[nx][ny] = cur.d + 1; // 거리 갱신
            q.push({ nx, ny, cur.d + 1 }); // 큐에 삽입
        }
    }
    return -1; // 도착하지 못한 경우
}

void printMap(int playerX, int playerY, int enemyX, int enemyY, const vector<vector<int>>& map) {
    int curX = playerX, curY = playerY;

       while (dist[curX][curY] != 0) { // 시작점까지 거슬러 올라감
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                if (i == playerX && j == playerY) { // 플레이어 위치
                    cout << "♥ ";
                }
                else if (i == enemyX && j == enemyY) { // 적 위치
                    cout << "★ ";
                }
                else if (map[i][j] == 1) { // 갈 수 없는 곳
                    cout << "▥ ";
                }
                else if (dist[i][j] == -1) { // 갈 수 없는 곳
                    cout << "▥ ";
                }
                else if (i == curX && j == curY) { // 최단 경로
                    cout << "■ ";
                }
                else { // 빈 칸
                    cout << "□ ";
                }

            }
            cout << endl;
            
        }

        for (int i = 0; i < 4; i++) { // 이동 가능한 모든 경우를 고려
            int nx = curX + dx[i];
            int ny = curY + dy[i];

            if (nx < 0 || nx >= N || ny < 0 || ny >= M) continue; // 범위를 벗어나는 경우
            if (dist[nx][ny] == -1) continue; // 갈 수 없는 곳
            if (map[nx][ny] == 1) continue; // 갈 수 없는 곳
            if (dist[nx][ny] < dist[curX][curY]) { // 이동한 경로일 경우
                curX = nx;
                curY = ny;
                break;
            }
        }
        cout << "====================" << endl;
    }
}


void Input() {
    cout << "모든 입력은 띄어쓰기로 구별합니다." << endl;
    cout << "맵의 크기를 입력하세요 (가로 세로): ";
    cin >> N >> M;
    cout << "플레이어의 위치를 입력하세요 (x좌표 y좌표): ";
    cin >> playerY >> playerX;
    cout << "적의 위치를 입력하세요 (x좌표 y좌표): ";
    cin >> enemyY >> enemyX;

    // 적과 플레이어의 위치를 인덱스로 변환
    enemyX--; enemyY--;
    playerX--; playerY--;
}

int main() {
    Input();

    // 맵 입력 받기
    vector<vector<int>> map(N, vector<int>(M));
    cout << "맵을 입력하세요 [길: 0 / 벽: 1]) " << endl;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            cin >> map[i][j];
            if (map[i][j] == 1) { // 갈 수 없는 곳이면 -1로 초기화
                dist[i][j] = -1;
            }
        }
    }

    int ans = bfs(enemyX, enemyY, playerX, playerY);

    printMap(playerX, playerY, enemyX, enemyY, map); // 2차원 맵 출력

    cout << "최단 거리: " << ans << endl;

    return 0;
}