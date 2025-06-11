/***************
 * 后台管理模块 *
 ***************/

#include <unordered_map>

#include "ViewState.h"
#include "BackStageMenuView.h"
#include "BackStageStaffView.h"
#include "BackStageTourView.h"
#include "BinaryStaffDataRepo.h"
#include "BinaryTournamentDataRepo.h"

int main() {

    BinaryStaffDataRepo * staffRepo = new BinaryStaffDataRepo();
    BinaryTournamentDataRepo * tourRepo = new BinaryTournamentDataRepo();

    staffRepo->load();
    tourRepo->load();

    std::unordered_map<ViewState, std::unique_ptr<IView>> views;
    views[ViewState::BackStageMenuView] = std::make_unique<BackStageMenuView>();
    views[ViewState::BackStageStaffView] = std::make_unique<BackStageStaffView>(staffRepo);
    views[ViewState::BackStageTourView] = std::make_unique<BackStageTourView>(tourRepo);

    ViewState state = ViewState::BackStageMenuView;
    while (state != ViewState::Exit) {
        state = views[state]->run();
    }
    
    staffRepo->save();
    tourRepo->save();

    delete staffRepo;
    delete tourRepo;
}