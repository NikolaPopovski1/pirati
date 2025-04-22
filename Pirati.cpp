#include <iostream>
#include <cstdio>

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

    if (fscanf_s(file, "%d %d %d", &n, &m, &k) != 3) {
        std::cerr << "Error reading n, m, k from file." << std::endl;
        fclose(file);
        return 1;
    }

	for (int i = 0; i < k; ++i) {
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