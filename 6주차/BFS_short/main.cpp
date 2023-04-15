#include <iostream>
#include <queue>
#include <vector>

using namespace std;

const int MAX_N = 1000; // ���� �÷��̾��� �ִ� ��ġ
const int dx[4] = { 0, 0, 1, -1 }; // �̵� ����
const int dy[4] = { 1, -1, 0, 0 };

int playerX, playerY, enemyX, enemyY;
int N, M; // ���� �÷��̾��� ��ġ
int dist[MAX_N][MAX_N]; // �Ÿ��� ������ �迭
bool visited[MAX_N][MAX_N]; // �湮 ���θ� ������ �迭

struct Point {
    int x, y, d; // x��ǥ, y��ǥ, �Ÿ�
};

int bfs(int sx, int sy, int ex, int ey) {
    queue<Point> q;
    q.push({ sx, sy, 0 }); // �������� ť�� ����
    visited[sx][sy] = true; // ������ �湮 ǥ��

    while (!q.empty()) {
        Point cur = q.front();
        q.pop();

        if (cur.x == ex && cur.y == ey) { // �������� ������ ��� �Ÿ� ��ȯ
            return cur.d;
        }

        for (int i = 0; i < 4; i++) { // �̵� ������ ��� ��츦 ���
            int nx = cur.x + dx[i];
            int ny = cur.y + dy[i];

            if (nx < 0 || nx >= N || ny < 0 || ny >= M) continue; // ������ ����� ���
            if (visited[nx][ny]) continue; // �̹� �湮�� ���

            visited[nx][ny] = true; // �湮 ǥ��
            dist[nx][ny] = cur.d + 1; // �Ÿ� ����
            q.push({ nx, ny, cur.d + 1 }); // ť�� ����
        }
    }
    return -1; // �������� ���� ���
}

void printMap(int playerX, int playerY, int enemyX, int enemyY, const vector<vector<int>>& map) {
    int curX = playerX, curY = playerY;

       while (dist[curX][curY] != 0) { // ���������� �Ž��� �ö�
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                if (i == playerX && j == playerY) { // �÷��̾� ��ġ
                    cout << "�� ";
                }
                else if (i == enemyX && j == enemyY) { // �� ��ġ
                    cout << "�� ";
                }
                else if (map[i][j] == 1) { // �� �� ���� ��
                    cout << "�� ";
                }
                else if (dist[i][j] == -1) { // �� �� ���� ��
                    cout << "�� ";
                }
                else if (i == curX && j == curY) { // �ִ� ���
                    cout << "�� ";
                }
                else { // �� ĭ
                    cout << "�� ";
                }

            }
            cout << endl;
            
        }

        for (int i = 0; i < 4; i++) { // �̵� ������ ��� ��츦 ���
            int nx = curX + dx[i];
            int ny = curY + dy[i];

            if (nx < 0 || nx >= N || ny < 0 || ny >= M) continue; // ������ ����� ���
            if (dist[nx][ny] == -1) continue; // �� �� ���� ��
            if (map[nx][ny] == 1) continue; // �� �� ���� ��
            if (dist[nx][ny] < dist[curX][curY]) { // �̵��� ����� ���
                curX = nx;
                curY = ny;
                break;
            }
        }
        cout << "====================" << endl;
    }
}


void Input() {
    cout << "��� �Է��� ����� �����մϴ�." << endl;
    cout << "���� ũ�⸦ �Է��ϼ��� (���� ����): ";
    cin >> N >> M;
    cout << "�÷��̾��� ��ġ�� �Է��ϼ��� (x��ǥ y��ǥ): ";
    cin >> playerY >> playerX;
    cout << "���� ��ġ�� �Է��ϼ��� (x��ǥ y��ǥ): ";
    cin >> enemyY >> enemyX;

    // ���� �÷��̾��� ��ġ�� �ε����� ��ȯ
    enemyX--; enemyY--;
    playerX--; playerY--;
}

int main() {
    Input();

    // �� �Է� �ޱ�
    vector<vector<int>> map(N, vector<int>(M));
    cout << "���� �Է��ϼ��� [��: 0 / ��: 1]) " << endl;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            cin >> map[i][j];
            if (map[i][j] == 1) { // �� �� ���� ���̸� -1�� �ʱ�ȭ
                dist[i][j] = -1;
            }
        }
    }

    int ans = bfs(enemyX, enemyY, playerX, playerY);

    printMap(playerX, playerY, enemyX, enemyY, map); // 2���� �� ���

    cout << "�ִ� �Ÿ�: " << ans << endl;

    return 0;
}