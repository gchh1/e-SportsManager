/***************
 * 后台职员视图 *
 ***************/

#pragma once

#include "IView.h"
#include "BinaryStaffDataRepo.h"

class BackStageStaffView : public IView {
private:
    BinaryStaffDataRepo * repo;

public:
    BackStageStaffView() = default;
    BackStageStaffView(BinaryStaffDataRepo * repo) : repo(repo) {
    }
    
    ~BackStageStaffView() {
    }

    void initCtrl() override {}
    ViewState run() override;

    std::string nameGenerator();
    int attributeGenerator();
};