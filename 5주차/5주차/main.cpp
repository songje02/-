#include <iostream>
#include <queue>
#include <vector>
#include <climits>

using namespace std;

const int MAX_N = 1000; // 맵의 최대 크기
const int dx[4] = { 1, -1, 0, 0 }; // x 좌표 이동 값
const int dy[4] = { 0, 0, 1, -1 }; // y 좌표 이동 값

int n, m; // 맵의 크기
char map[MAX_N][MAX_N]; // 맵 정보
int dist_player[MAX_N][MAX_N]; // 플레이어로부터의 거리
int dist_enemy[MAX_N][MAX_N]; // 적으로부터의 거리
pair<int, int> player_pos, enemy_pos; // 플레이어와 적의 위치

void bfs(int dist[MAX_N][MAX_N], pair<int, int> start) {
    queue<pair<int, int>> q; // BFS를 위한 큐
    q.push(start);
    dist[start.first][start.second] = 0;

    while (!q.empty()) {
        pair<int, int> cur = q.front(); q.pop();

        for (int i = 0; i < 4; i++) { // 4방향 탐색
            int nx = cur.first + dx[i];
            int ny = cur.second + dy[i];

            if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue; // 맵을 벗어나는 경우
            if (map[nx][ny] == '#') continue; // 벽인 경우
            if (dist[nx][ny] != INT_MAX) continue; // 이미 방문한 경우

            dist[nx][ny] = dist[cur.first][cur.second] + 1;
            q.push({ nx, ny });
        }
    }
}

void print_map() { // 맵 출력 함수
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (i == player_pos.first && j == player_pos.second) {
                cout << 'P'; // 플레이어 위치
            }
            else if (i == enemy_pos.first && j == enemy_pos.second) {
                cout << 'E'; // 적 위치
            }
            else {
                cout << map[i][j]; // 빈 공간 또는 벽
            }
        }
        cout << endl;
    }
}

int main() {
    cin >> n;
    cin >> m;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> map[i][j];

            if (map[i][j] == 'P') {
                player_pos = { i, j };
            }
            else if (map[i][j] == 'E') {
                enemy_pos = { i, j };
            }

            dist_player[i][j] = dist_enemy[i][j] = INT_MAX;
        }
    }

    bfs(dist_player, player_pos);
    bfs(dist_enemy, enemy_pos);

    int min_dist = INT_MAX;
    // 플레이어와 적 사이의 최단거리 구하기
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (map[i][j] != '.') continue; // 빈 공간이 아닌 경우

            if (dist_player[i][j] < dist_enemy[i][j] && dist_player[i][j] < min_dist) {
                min_dist = dist_player[i][j];
            }
        }
    }

    if (min_dist == INT_MAX) { // 플레이어와 적이 서로 도달할 수 없는 경우
        cout << "불가능한 상황입니다." << endl;
    }
    else {
        cout << "최단거리: " << min_dist << endl;
    }

    // 플레이어 이동하기
    cout << "플레이어 이동" << endl;
    for (int i = 0; i < 4; i++) {
        int nx = player_pos.first + dx[i];
        int ny = player_pos.second + dy[i];

        if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue; // 맵을 벗어나는 경우
        if (map[nx][ny] == '#') continue; // 벽인 경우
        if (dist_player[nx][ny] >= INT_MAX) continue; // 도달할 수 없는 경우

        // 이동 가능한 경우
        map[player_pos.first][player_pos.second] = '.';
        player_pos = { nx, ny };
        map[nx][ny] = 'P';

        print_map(); // 맵 출력
        cout << endl;

        break; // 이동 후 더 이상 탐색하지 않음
    }

    // 적 이동하기
    cout << "적 이동" << endl;
    int min_dist_dir = -1; // 최단거리를 찾은 방향
    for (int i = 0; i < 4; i++) {
        int nx = enemy_pos.first + dx[i];
        int ny = enemy_pos.second + dy[i];

        if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue; // 맵을 벗어나는 경우
        if (map[nx][ny] == '#') continue; // 벽인 경우
        if (dist_enemy[nx][ny] >= INT_MAX) continue; // 도달할 수 없는 경우

        // 이동 가능한 경우
        if (dist_player[nx][ny] < dist_player[enemy_pos.first][enemy_pos.second]) {
            // 플레이어에게 더 가까워지는 경우
            min_dist_dir = i;
            break;
        }
    }

    if (min_dist_dir == -1) {
        // 플레이어에게 더 가까워지지 않는 경우 랜덤 이동
        vector<int> candidate_dirs; // 이동 가능한 방향 후보
        for (int i = 0; i < 4; i++) {
            int nx = enemy_pos.first + dx[i];
            int ny = enemy_pos.second + dy[i];

            if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue; // 맵을 벗어나는 경우
            if (map[nx][ny] == '#') continue; // 벽인 경우
            if (dist_enemy[nx][ny] >= INT_MAX) continue; // 도달할 수 없는 경우

            // 이동 가능한 경우
            if (dist_player[nx][ny] >= dist_player[enemy_pos.first][enemy_pos.second]) {
                // 플레이어와 같거나 더 멀어지는 경우
                candidate_dirs.push_back(i);
            }
        }

        if (candidate_dirs.empty()) {
            // 모든 방향이 막혔을 경우
            cout << "이동할 수 없습니다." << endl;
        }
        else {
            // 이동 가능한 방향 중 랜덤으로 선택
            int idx = rand() % candidate_dirs.size();
            int dir = candidate_dirs[idx];
            int nx = enemy_pos.first + dx[dir];
            int ny = enemy_pos.second + dy[dir];

            // 이동
            map[enemy_pos.first][enemy_pos.second] = '.';
            enemy_pos = { nx, ny };
            map[nx][ny] = 'E';

            print_map(); // 맵 출력
            cout << endl;
        }
    }
}


