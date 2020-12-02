#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

ifstream cin("input.txt");
ofstream cout("output.txt");

const int size = 1000;
bool graph[size][size];
bool used[size];
bool is_deleted[size];
int group[size];
int count_ = 0;
int dist[size][size];

void dfs(int v, int cur_group) {
    count_++;
    group[v] = cur_group;
    for (int i = 0; i < size; i++) {
        if (graph[v][i] && !used[i]) {
            used[i] = true;
            dfs(i, cur_group);
        }
    }
}

int max_distance = 0, first_edge, second_edge;
void work(int v) {
    queue<int> q;
    q.push(v);
    while (!q.empty()) {
        int cur = q.front();
        q.pop();
        for (int i = 0; i < size; i++) {
            if (dist[v][i] == 0 && i != v && graph[cur][i]) {
                dist[v][i] = dist[v][cur] + 1;
                if(dist[v][i] > max_distance) {
                    max_distance = dist[v][i];
                    first_edge = v;
                    second_edge = i;
                }
                q.push(i);
            }
        }
    }
}

void get(int first, int second){
    vector <int> ans;
    int cur = dist[first][second];
    int now = second;
    ans.push_back(second);
    while (cur > 0){
        cur--;
        for(int i = 0; i < size; i++){
            if(graph[now][i] && dist[first][i] == cur){
                ans.push_back(i);
                now = i;
                break;
            }
        }
    }
    reverse(ans.begin(), ans.end());
    cout << first << " " << second << " " << dist[first][second] << "\n";
    for(auto &x : ans) cout << x << " ";
    cout << "\n";
}

void edges_number(){
    int k = 0;
    for(int i = 0; i < size; i++){
        for(int j = i + 1; j < size; j++){
            if(graph[i][j]) k++;
        }
    }
    cout << "Количество ребер: " << k << "\n";
}

void get_alone_nodes(){
    int alone_nodes_number = 0;
    vector<int> ans_for_alone_nodes;
    for (int i = 0; i < size; i++) {
        bool ok = false;
        for (auto &x : graph[i]) ok |= x;
        if (!ok && !is_deleted[i]) {
            alone_nodes_number++;
            ans_for_alone_nodes.push_back(i);
        }
    }
    cout << "Количетсво изолятов: " << alone_nodes_number << "\n";
    cout << "Изоляты: ";
    for (auto &x : ans_for_alone_nodes) cout << x << " ";
    cout << "\n";
}

void find_max_pow(){
    unsigned int max_pow = 0;
    for (auto &i : graph) {
        int length = 0;
        for (auto &x : i) if (x) length++;
        if (length > max_pow) max_pow = length;
    }
    cout << "Максимальная степень вершины: " << max_pow << "\n";
    vector<int> ans_for_max_pow;
    for (int i = 0; i < size; i++) {
        int length = 0;
        for (auto &x : graph[i]) if (x) length++;
        if (length == max_pow) ans_for_max_pow.push_back(i);
    }
    cout << "Вершины с максимальной степенью: ";
    for (auto &x : ans_for_max_pow) cout << x << " ";
    cout << "\n";
}

void find_d(){
    int k = 0, max = -1;
    for (int i = 0; i < size; i++) {
        if (!used[i]) {
            used[i] = true;
            dfs(i, k);
            if (count_ > max) {
                max = count_;
            }
            k++;
            count_ = 0;
        }
    }
    for (int i = 0; i < size; i++) {
        work(i);
    }
    cout << max_distance << " " << first_edge << " " << second_edge << "\n";
}
void fix(){
    for(int i = 0; i < size; i++){
        used[i] = false;
        for(int j = 0; j < size; j++){
            dist[i][j] = 0;
        }
    }
}
int main() {


    int n, m;
    while (cin >> n >> m) {
        graph[n][m] = true;
        graph[m][n] = true;
    }
    edges_number();
    get_alone_nodes();
    find_max_pow();
    find_d();
   /*
    Вопрос 5. Найдите кратчайший путь от A до B. A: 389 B: 50
    Вопрос 6. Найдите кратчайший путь от C до D. C: 235 D: 32
    Вопрос 7. Найдите кратчайший путь от E до F. E: 588 F: 572
    */
    int A = 389, B = 50, C = 235, D = 32, E = 588, F = 572;
    get(A, B);
    get(C, D);
    get(E, F);
    /*
     * Удалите из графа следующие вершины: [225, 129, 227, 229, 424, 875, 465, 541]
     * 0, 17, 34, 51 и т.д.
     */
     vector<int> deleted = {225, 129, 227, 229, 424, 875, 465, 541};
     for(int i = 0; i < size; i += 17){
         deleted.push_back(i);
     }
     for(auto &x : deleted){
         is_deleted[x] = true;
         for(int i = 0; i < size; i++){
             graph[i][x] = false;
             graph[x][i] = false;
         }
     }
    fix();
    edges_number();
    get_alone_nodes();
    find_max_pow();
    find_d();
    get(A, B);
    get(C, D);
    get(E, F);
}
