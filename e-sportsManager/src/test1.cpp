/**************************************************
 *                    测试程序1                    *
 *------------------------------------------------*
 * 测试除 log 外所有功能                            *
 **************************************************/

#include <unordered_map>

#include "Club.h"
#include "Staff.h"
#include "Tournament.h"

#include "ClubInfoView.h"
#include "ClubLogView.h"
#include "MainMenuView.h"
#include "MarketView.h"
#include "RankView.h"
#include "TournamentView.h"
#include "WelcomeView.h"

#include "BinaryClubDataRepo.h"
#include "BinaryStaffDataRepo.h"
#include "BinaryTournamentDataRepo.h"

#include "ClubController.h"
#include "MarketController.h"
#include "TournamentController.h"

int main() {
    
    // 数据仓库
    auto clubRepo = std::make_shared<BinaryClubDataRepo>();
    auto staffRepo = std::make_shared<BinaryStaffDataRepo>();
    auto tourRepo = std::make_shared<BinaryTournamentDataRepo>();

    clubRepo->load();
    staffRepo->load();
    tourRepo->load();


    //  控制器
    auto clubCtrl = new ClubController(clubRepo, staffRepo);
    auto marketCtrl = new MarketController(staffRepo, clubRepo);
    auto tourCtrl = new TournamentController(tourRepo, clubRepo);


    // 视图
    std::unordered_map<ViewState, std::unique_ptr<IView>> views;

        views[ViewState::WelcomeView] = std::make_unique<WelcomeView>(clubCtrl);
        views[ViewState::MainMenuView] = std::make_unique<MainMenuView>(clubCtrl, marketCtrl, tourCtrl);
        views[ViewState::ClubInfoView] = std::make_unique<ClubInfoView>(clubCtrl);
        views[ViewState::ClubLogView] = std::make_unique<ClubLogView>(clubCtrl);
        views[ViewState::MarketView] = std::make_unique<MarketView>(marketCtrl);
        views[ViewState::TournamentView] = std::make_unique<TournamentView>(tourCtrl);
        views[ViewState::RankView] = std::make_unique<RankView>(clubCtrl);

    ViewState state = ViewState::WelcomeView;

    // 程序主循环
    while (state != ViewState::Exit) {
        if (state == ViewState::InitMainMenu) {
            views[ViewState::MainMenuView]->initCtrl();
            state = ViewState::MainMenuView;
        }
        state = views[state]->run();
    }

    //  保存数据
    clubRepo->save();
    staffRepo->save();
    tourRepo->save();

    return 0;
}