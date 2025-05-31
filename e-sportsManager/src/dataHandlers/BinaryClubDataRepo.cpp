#include "BinaryClubDataRepo.h"

void BinaryClubDataRepo::load() {
    std::ifstream in(filename, std::ios::binary);
    if (!in) return;
    
    repo.clear();
    
    // 读取条目数量
    size_t count = 0;
    if (!in.read(reinterpret_cast<char*>(&count), sizeof(count)))
        return;
    
    // 精确循环count次
    for (size_t i = 0; i < count; ++i) {
        auto club = std::make_unique<Club>();
        if (!club->load(in)) {
            repo.clear();
            return;
        }
        repo.push_back(std::move(club));
    }
}


void BinaryClubDataRepo::save() {
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


Club * BinaryClubDataRepo::getClub(int ID) {
    for (const auto & e : repo) {
        if (e->getID() == ID) {
            return e.get();
        }
    }
    return nullptr;
}

std::vector<int> BinaryClubDataRepo::getRepoID() {
    std::vector<int> ids;
    for (const auto & e : repo) {
        ids.push_back(e->getID());
    }
    return ids;
}
