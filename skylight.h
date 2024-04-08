#include <iostream>
#include <filesystem>
#include <fstream>
#include <cstring>
#include <algorithm>
#include <iomanip>
using namespace std;

// byte reordering algorithms
uint32_t tobe32(uint32_t value) {
    return  ((value & 0xFF) << 24) |
            ((value & 0xFF00) << 8) |
            ((value & 0xFF0000) >> 8) |
            ((value & 0xFF000000) >> 24);
}
uint64_t tobe64(uint64_t value) {
    return ((value & 0xFFULL) << 56) |
           ((value & 0xFF00ULL) << 40) |
           ((value & 0xFF0000ULL) << 24) |
           ((value & 0xFF000000ULL) << 8) |
           ((value & 0xFF00000000ULL) >> 8) |
           ((value & 0xFF0000000000ULL) >> 24) |
           ((value & 0xFF000000000000ULL) >> 40) |
           ((value & 0xFF00000000000000ULL) >> 56);
}

// the byte reading magic
uint64_t magic64(ifstream* File, int pos, bool invendian = true) {
    File -> seekg(pos);
    uint64_t data;
    File -> read(reinterpret_cast<char*>(&data), 8);
    if (invendian) return tobe64(data);
    else return data;
}
uint32_t magic32(ifstream* File, int pos, bool invendian = true) {
    File -> seekg(pos);
    uint32_t data;
    File -> read(reinterpret_cast<char*>(&data), 4);
    if (invendian) return tobe32(data);
    else return data;
}
uint16_t magic16(ifstream* File, int pos) {
    File -> seekg(pos);
    uint16_t data;
    File -> read(reinterpret_cast<char*>(&data), 2);
    return data;
}
uint8_t magic8(ifstream* File, int pos) {
    File -> seekg(pos);
    uint8_t data;
    File -> read(reinterpret_cast<char*>(&data), 1);
    return data;
}

string getData(string fileName, string name) {
    stringstream buffer;
    ifstream skyFile(fileName, ios::binary);
    buffer  << "{\"" << name << "\", {" << magic16(&skyFile, 0x10) << ", 0x" << hex << magic16(&skyFile, 0x1C);
    buffer  << "}},\n\n";
    buffer  << "------BFIM------\n\n";
    buffer  << "{\"" << name << "\",\n";
    buffer  << "    {\n";
    buffer  << hex
            << "        0x"  << setw(8) << setfill('0') << magic32(&skyFile, 0) << ",\n"
            << "        {0x" << setw(16) << setfill('0') << magic64(&skyFile, 0x20)  << ", 0x" << setw(16) << setfill('0') << magic64(&skyFile, 0x28) << "},\n"
            << "        {0x" << setw(16) << setfill('0') << magic64(&skyFile, 0x40)  << ", 0x" << setw(16) << setfill('0') << magic64(&skyFile, 0x48) << "},\n"
            << "        {0x" << setw(16) << setfill('0') << magic64(&skyFile, 0x220) << ", 0x" << setw(16) << setfill('0') << magic64(&skyFile, 0x228) << "},\n"
            << "        {0x" << setw(16) << setfill('0') << magic64(&skyFile, 0x3E0) << ", 0x" << setw(16) << setfill('0') << magic64(&skyFile, 0x3E8) << "},\n";
    buffer  << "        {0x" << (uint16_t)magic8(&skyFile, 0x9)   << ", 0x" << (uint16_t)magic8(&skyFile, 0xF) << "}\n"
            << "    }\n},";
    return buffer.str();
}
