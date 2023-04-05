#include <iostream>
#include <queue>
#include <vector>
#include <climits>

using namespace std;

const int MAX_N = 1000; // ���� �ִ� ũ��
const int dx[4] = { 1, -1, 0, 0 }; // x ��ǥ �̵� ��
const int dy[4] = { 0, 0, 1, -1 }; // y ��ǥ �̵� ��

int n, m; // ���� ũ��
char map[MAX_N][MAX_N]; // �� ����
int dist_player[MAX_N][MAX_N]; // �÷��̾�κ����� �Ÿ�
int dist_enemy[MAX_N][MAX_N]; // �����κ����� �Ÿ�
pair<int, int> player_pos, enemy_pos; // �÷��̾�� ���� ��ġ

void bfs(int dist[MAX_N][MAX_N], pair<int, int> start) {
    queue<pair<int, int>> q; // BFS�� ���� ť
    q.push(start);
    dist[start.first][start.second] = 0;

    while (!q.empty()) {
        pair<int, int> cur = q.front(); q.pop();

        for (int i = 0; i < 4; i++) { // 4���� Ž��
            int nx = cur.first + dx[i];
            int ny = cur.second + dy[i];

            if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue; // ���� ����� ���
            if (map[nx][ny] == '#') continue; // ���� ���
            if (dist[nx][ny] != INT_MAX) continue; // �̹� �湮�� ���

            dist[nx][ny] = dist[cur.first][cur.second] + 1;
            q.push({ nx, ny });
        }
    }
}

void print_map() { // �� ��� �Լ�
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (i == player_pos.first && j == player_pos.second) {
                cout << 'P'; // �÷��̾� ��ġ
            }
            else if (i == enemy_pos.first && j == enemy_pos.second) {
                cout << 'E'; // �� ��ġ
            }
            else {
                cout << map[i][j]; // �� ���� �Ǵ� ��
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
    // �÷��̾�� �� ������ �ִܰŸ� ���ϱ�
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (map[i][j] != '.') continue; // �� ������ �ƴ� ���

            if (dist_player[i][j] < dist_enemy[i][j] && dist_player[i][j] < min_dist) {
                min_dist = dist_player[i][j];
            }
        }
    }

    if (min_dist == INT_MAX) { // �÷��̾�� ���� ���� ������ �� ���� ���
        cout << "�Ұ����� ��Ȳ�Դϴ�." << endl;
    }
    else {
        cout << "�ִܰŸ�: " << min_dist << endl;
    }

    // �÷��̾� �̵��ϱ�
    cout << "�÷��̾� �̵�" << endl;
    for (int i = 0; i < 4; i++) {
        int nx = player_pos.first + dx[i];
        int ny = player_pos.second + dy[i];

        if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue; // ���� ����� ���
        if (map[nx][ny] == '#') continue; // ���� ���
        if (dist_player[nx][ny] >= INT_MAX) continue; // ������ �� ���� ���

        // �̵� ������ ���
        map[player_pos.first][player_pos.second] = '.';
        player_pos = { nx, ny };
        map[nx][ny] = 'P';

        print_map(); // �� ���
        cout << endl;

        break; // �̵� �� �� �̻� Ž������ ����
    }

    // �� �̵��ϱ�
    cout << "�� �̵�" << endl;
    int min_dist_dir = -1; // �ִܰŸ��� ã�� ����
    for (int i = 0; i < 4; i++) {
        int nx = enemy_pos.first + dx[i];
        int ny = enemy_pos.second + dy[i];

        if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue; // ���� ����� ���
        if (map[nx][ny] == '#') continue; // ���� ���
        if (dist_enemy[nx][ny] >= INT_MAX) continue; // ������ �� ���� ���

        // �̵� ������ ���
        if (dist_player[nx][ny] < dist_player[enemy_pos.first][enemy_pos.second]) {
            // �÷��̾�� �� ��������� ���
            min_dist_dir = i;
            break;
        }
    }

    if (min_dist_dir == -1) {
        // �÷��̾�� �� ��������� �ʴ� ��� ���� �̵�
        vector<int> candidate_dirs; // �̵� ������ ���� �ĺ�
        for (int i = 0; i < 4; i++) {
            int nx = enemy_pos.first + dx[i];
            int ny = enemy_pos.second + dy[i];

            if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue; // ���� ����� ���
            if (map[nx][ny] == '#') continue; // ���� ���
            if (dist_enemy[nx][ny] >= INT_MAX) continue; // ������ �� ���� ���

            // �̵� ������ ���
            if (dist_player[nx][ny] >= dist_player[enemy_pos.first][enemy_pos.second]) {
                // �÷��̾�� ���ų� �� �־����� ���
                candidate_dirs.push_back(i);
            }
        }

        if (candidate_dirs.empty()) {
            // ��� ������ ������ ���
            cout << "�̵��� �� �����ϴ�." << endl;
        }
        else {
            // �̵� ������ ���� �� �������� ����
            int idx = rand() % candidate_dirs.size();
            int dir = candidate_dirs[idx];
            int nx = enemy_pos.first + dx[dir];
            int ny = enemy_pos.second + dy[dir];

            // �̵�
            map[enemy_pos.first][enemy_pos.second] = '.';
            enemy_pos = { nx, ny };
            map[nx][ny] = 'E';

            print_map(); // �� ���
            cout << endl;
        }
    }
}


