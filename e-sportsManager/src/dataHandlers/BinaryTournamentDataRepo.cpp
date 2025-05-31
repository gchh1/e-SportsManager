#include "BinaryTournamentDataRepo.h"

void BinaryTournamentDataRepo::load() {
    std::ifstream in(filename, std::ios::binary);
    // 判断文件是否打开
    if (!in.is_open()) {
        return;
    }

    repo.clear();

    // 读取条目数量
    size_t count = 0;
    if (!in.read(reinterpret_cast<char*>(&count), sizeof(count)))
        return;

    // 精确循环count次
    for (size_t i = 0; i < count; ++i) {
        auto tournament = std::make_unique<Tournament>();
        if (!tournament->load(in)) {
            repo.clear();
            return;
        }
        repo.push_back(std::move(tournament));
    }   
}

void BinaryTournamentDataRepo::save() {
    std::ofstream out(filename, std::ios::binary | std::ios::trunc);
            
    if (out.is_open()) {
        // 写入条目数量
        size_t count = repo.size();
        out.write(reinterpret_cast<char*>(&count), sizeof(count));
                
        for(const auto & e : repo) {
            e->save(out);
        }
    }
}
