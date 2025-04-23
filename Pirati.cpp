#include <iostream>
#include <cstdio>
#include <vector>
#include <limits>
#include <tuple>

void print_array(const std::vector<std::pair<int, int>>& arr) {
    for (const auto& elem : arr) {
        std::cout << elem.first << " " << elem.second << " ";
    }
    std::cout << std::endl;
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

	std::vector<int> result(k + 1, { std::numeric_limits<int>::max() });
    std::vector<std::pair<int, int>> A(k + 1, { std::numeric_limits<int>::max(), std::numeric_limits<int>::max() });
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
	for (int i = 0; i < n; i++) { // za vsako vrstico
		cumulative += numOfIslandsInRow[i];

		A_copy = A;

        A[0].first = std::min(A_copy[0].first, A_copy[0].second + m);
        A[0].second = std::min(A_copy[0].second, A_copy[0].first + m);

		for (int j = 1; j < cumulative + 1; j++) {
			if (n == 0) {
                if (j == cumulative) { // za zadnji element

                }
                else {




                    //???????????????????????????????????????????
                    //TUKI OSTAU BUKI
                    //???????????????????????????????????????????
                    for (int l = 1; l < m; l++) {
                        calc++;
						if (islands[i][l] > 0) {
                            currentIslandsViseted++;
							calc += islands[i][l];
							if (currentIslandsViseted > j) break;
						}
					}
                    //???????????????????????????????????????????
                    //???????????????????????????????????????????
                    //???????????????????????????????????????????












                    result[j] = std::min(result[j], A_copy[j - 1].first + calc, A_copy[j - 1].first + 99990000000000000000000000000000000);
                    A[j].first = std::min(A_copy[j].first, A_copy[j - 1].first + 9999999999999999999999999999999999999, A_copy[j - 1].first + 99999999999999999999999999999999);
                    A[j].second = std::min(A_copy[j].second, A_copy[j - 1].first + 9999999999999999999999999999999999999, A_copy[j - 1].first + 99999999999999999999999999999999);
                }
            }
            else {

            }
		}
	}

    print_all_three(A, A_copy, result);

    fclose(file);
    return 0;
}