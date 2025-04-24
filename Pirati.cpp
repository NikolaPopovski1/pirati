#include <iostream>
#include <cstdio>
#include <vector>
#include <limits>
#include <tuple>
#include <algorithm>
#include <utility>

void print_array(const std::vector<std::pair<int, int>>& arr) {
    for (const auto& elem : arr) {
        std::cout << elem.first << " " << elem.second << std::endl;
    }
}
void print_array(const std::vector<int>& arr) {
    for (const auto& elem : arr) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;
}
void print_all_three(const std::vector<std::pair<int, int>>& arr1, const std::vector<std::pair<int, int>>& arr2, const std::vector<int>& arr3) {
    int i = 0;
    for (const auto& elem : arr1) {
        std::cout << i + 1 << ": " << arr1[i].first << " " << arr1[i].second << ", " << arr2[i].first << " " << arr2[i].second << ", " << arr3[i] << std::endl;
        i++;
    }
    std::cout << std::endl;
}


std::pair<int, int> min_num_with_place(std::vector<int> islands, int &m, int &numOfIslandsInRow, bool leftToRight) {
	std::pair<int, int> result = { std::numeric_limits<int>::max(), -1 }; // first is result, second is index
	int visitedIslands, tmp;
    if (leftToRight) {
        for (int i = 1; i <= numOfIslandsInRow; i++) {
            visitedIslands = 0, tmp = 0;
            for (int j = 0; j < m; j++) {
                if (j != 0) tmp++;
                if (islands[j] > 0) {
                    visitedIslands++;
                    if (visitedIslands == i && result.first > islands[j] + tmp) {
                        result.first = islands[j] + tmp;
                        result.second = j;
                        break;
                    }
                }
            }
        }
    }
    else {
		for (int i = 1; i <= numOfIslandsInRow; i++) {
			visitedIslands = 0, tmp = 0;
			for (int j = m - 1; j >= 0; j--) {
				if (j != m - 1) tmp++;
				if (islands[j] > 0) {
					visitedIslands++;
					if (visitedIslands == i && result.first > islands[j] + tmp) {
						result.first = islands[j] + tmp;
						result.second = j;
						break;
					}
				}
			}
		}
    }
	if (result.second == -1) {
		result.first = 0;
	}
	return result;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <filename>" << std::endl;
        return 1;
    }

    FILE* file = nullptr;
    if (fopen_s(&file, argv[1], "r") != 0 || file == nullptr) {
        std::cerr << "Error opening file: " << argv[1] << std::endl;
        return 1;
    }

	int n, m, k; // n = x, m = y, kjer sta x in y menjani oz. nista kot v tradicionalnem koordnatnem sistemu

    if (fscanf_s(file, "%d %d %d", &n, &m, &k) != 3 || n < 4 || m > 10000000 || k < 1 || k > 10000) {
        std::cerr << "Error reading n, m, k from file." << std::endl;
        fclose(file);
        return 1;
    }

	std::vector<int> result(k + 1, std::numeric_limits<int>::max());
    std::vector<std::pair<int, int>> A(k + 1, { std::numeric_limits<int>::max() / 2, std::numeric_limits<int>::max() / 2});

    A[0].first = 0;
	//std::vector<std::tuple<int, int, int>> islands(k);
    std::vector<std::vector<int>> islands(n, std::vector<int>(m, 0));
	std::vector<int> numOfIslandsInRow(n, 0);

	for (int i = 0; i < k; i++) {
		int x, y, h;
		if (fscanf_s(file, "%d %d %d", &x, &y, &h) != 3 || x > n || y > m) {
			std::cerr << "Error reading a, b, c from file." << std::endl;
			fclose(file);
			return 1;
		}
		//islands[i] = std::make_tuple(a, b, c);
		islands[x - 1][y - 1] = h;
		numOfIslandsInRow[x - 1]++;
	}

    std::vector<std::pair<int, int>> A_copy;
	int cumulative = 0, calc = 0, currentIslandsViseted; // cumulative of amount of islands in current and all previous rows, calc is for storing calculations
	result[0] = 0;
    A_copy = A;
    A[0].first = std::min(A_copy[0].first, A_copy[0].second + m - 1);
    A[0].second = std::min(A_copy[0].second, A_copy[0].first + m - 1);
	std::pair<int, int> left, right;
	for (int i = 0; i < n; i++) { // za vsako vrstico
		cumulative += numOfIslandsInRow[i];

		A_copy = A;

        std::cout << "Result before row " << i << std::endl;
        print_array(result);
        std::cout << "A before row " << i << std::endl;
        print_array(A);
        std::cout << std::endl;

		for (int j = 1; j < cumulative + 1; j++) {
			if (i == 0) {
                if (j == cumulative - 1) { // za zadnji element
                    left = min_num_with_place(islands[i], m, numOfIslandsInRow[i], true);

                    result[j] = std::min(result[j], A_copy[0].first + left.first);
                    A[j].first = std::min(A_copy[j].first, A_copy[0].first + left.first + left.second);
                    A[j].second = std::min(A_copy[j].second, A_copy[0].first + left.first + m - 1 - left.second);
                }
                else {
					left = min_num_with_place(islands[i], m, numOfIslandsInRow[i], true);

                    result[j] = std::min(result[j], A_copy[0].first + left.first);
                    A[j].first = std::min(A_copy[j].first, A_copy[0].first + left.first + left.second);
                    A[j].second = std::min(A_copy[j].second, A_copy[0].first + left.first + m - 1 - left.second);
                }
            }
            else {
                right = min_num_with_place(islands[i], m, numOfIslandsInRow[i], false);
                left = min_num_with_place(islands[i], m, numOfIslandsInRow[i], true);
                

                if (left.second != -1) {
                    result[j] = std::min({ result[j], A_copy[j - 1].first + left.first, A_copy[j - 1].second + right.first });
                    A[j].first = std::min({ A_copy[j].first, A_copy[j - 1].first + left.first + left.second, A_copy[j - 1].second + right.first + right.second });
                    A[j].second = std::min({ A_copy[j].second, A_copy[j - 1].first + left.first + m - 1 - left.second, A_copy[j - 1].second + right.first + m - 1 - right.second });
                }
            }
		}

        for (int i = 0; i < k + 1; i++) {
            if (A[i].first != std::numeric_limits<int>::max()) {
                A[i].first++;
            }
            if (A[i].second != std::numeric_limits<int>::max()) {
                A[i].second++;
            }
        }
	}

    print_array(result);

    fclose(file);
    return 0;
}