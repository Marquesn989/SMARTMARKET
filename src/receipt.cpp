#include "../include/receipt.h"
#include <fstream>
#include <chrono>
#include <iomanip>
#include <filesystem>

std::string saveReceipt(const Cart &cart, const Catalog &catalog) {
    using namespace std::chrono;
    auto now = system_clock::now();
    auto t = system_clock::to_time_t(now);
    std::tm tm;
#ifdef _WIN32
    localtime_s(&tm, &t);
#else
    localtime_r(&t, &tm);
#endif
    std::ostringstream name;
    name << "output/receipt_" << std::put_time(&tm, "%Y%m%d_%H%M%S") << ".txt";
    std::string filename = name.str();
    // ensure output dir exists
    try {
        std::filesystem::create_directories("output");
    } catch (...) {}
    std::ofstream out(filename);
    if (!out.is_open()) return std::string();
    out << "SMARTMARKET - Recibo\n";
    out << "====================\n";
    const auto &items = cart.items();
    float total = 0.0f;
    for (const auto &kv : items) {
        const Product *p = catalog.findById(kv.first);
        if (!p) continue;
        out << p->name << " x" << kv.second << " - € " << (p->price * kv.second) << "\n";
        total += p->price * kv.second;
    }
    out << "--------------------\n";
    out << "Total: € " << total << "\n";
    out.close();
    return filename;
}
