#include <iostream>
#include <fstream>
#include <cstdint>


uint32_t my_ntohl(uint32_t net) {
    uint8_t data[4];
    data[0] = (net >> 24) & 0xFF;
    data[1] = (net >> 16) & 0xFF;
    data[2] = (net >> 8) & 0xFF;
    data[3] = net & 0xFF;
    return ((uint32_t)data[0] << 0) | ((uint32_t)data[1] << 8) | ((uint32_t)data[2] << 16) | ((uint32_t)data[3] << 24);
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <file1> <file2>\n";
        return 1;
    }

    std::ifstream file1(argv[1], std::ios::binary);
    std::ifstream file2(argv[2], std::ios::binary);

    if (!file1.is_open() || !file2.is_open()) {
        std::cerr << "Error opening files.\n";
        return 1;
    }

    uint32_t num1, num2;
    if (!file1.read(reinterpret_cast<char*>(&num1), sizeof(num1)) ||
        !file2.read(reinterpret_cast<char*>(&num2), sizeof(num2))) {
        std::cerr << "Error reading from files.\n";
        return 1;
    }


    num1 = my_ntohl(num1);
    num2 = my_ntohl(num2);

    uint32_t sum = num1 + num2;

    std::cout << std::dec << num1 << "(0x" << std::hex << num1 << ") + "
              << std::dec << num2 << "(0x" << std::hex << num2 << ") = "
              << std::dec << sum << "(0x" << std::hex << sum << ")\n";

    return 0;
}
