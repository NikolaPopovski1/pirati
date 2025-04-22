#include <iostream>
#include <cstdio>
#include <vector>
#include <limits>

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

    int n, m, k;

    if (fscanf_s(file, "%d %d %d", &n, &m, &k) != 3 || n < 4 || m > 10000000 || k < 1 || k > 10000) {
        std::cerr << "Error reading n, m, k from file." << std::endl;
        fclose(file);
        return 1;
    }

    std::vector<int> result(k + 1, {std::numeric_limits<int>::max()});
    std::vector<std::pair<int, int>> A(k + 1, { std::numeric_limits<int>::max(), std::numeric_limits<int>::max() });
    std::vector<std::pair<int, int>> A_copy(k + 1, { std::numeric_limits<int>::max(), std::numeric_limits<int>::max() });

	for (int i = 0; i < k; i++) {
		int a, b, c;
		if (fscanf_s(file, "%d %d %d", &a, &b, &c) != 3 || a > n || b > m) {
			std::cerr << "Error reading a, b, c from file." << std::endl;
			fclose(file);
			return 1;
		}
	}

    fclose(file);
    return 0;
}