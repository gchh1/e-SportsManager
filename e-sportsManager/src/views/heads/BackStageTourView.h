/***************
 * 后台赛事视图 *
 ***************/

#pragma once

#include "IView.h"
#include "BinaryTournamentDataRepo.h"

class BackStageTourView : public IView {
private:
    BinaryTournamentDataRepo* repo;
public:
    BackStageTourView(BinaryTournamentDataRepo* repo) : repo(repo) {
    }

    ~BackStageTourView() {
    }
    
    ViewState run() override;
    void initCtrl() override {}

    
};