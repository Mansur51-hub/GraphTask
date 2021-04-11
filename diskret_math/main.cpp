#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <vector>

const int size = 47;

int main() {

    std::ifstream fin("list.txt");

    std::map<std::string, int> key;
    std::map<int, std::string> value;
    std::string s;

/*
 * Вводим список стран
 */
    for (int i = 0; i < size; i++) {
        fin >> s;
        key[s] = i;
        value[i] = s;
    }

/*
 * Вводим список соседних стран
 */

    std::vector<std::vector<int> > graph(size);

    std::fstream land_in("land.txt");

    for (int i = 0; i < 88; i++) {
        std::string v1, v2;
        land_in >> v1 >> v2;

        graph[key[v1]].push_back(key[v2]);
        graph[key[v2]].push_back(key[v1]);
    }

    std::vector<bool> used(size, false);

    std::vector<std::vector<int> > a(size, std::vector<int>(size, 0));
    for (int i = 0; i < size; i++) {
        for (auto &x : graph[i]) {
            a[i][x] = 1;
        }
    }
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
           std::cout << a[i][j] << " ";
        }
        std::cout << "\n";
    }
}
