/**************************************************
 *                    测试程序1                    *
 *------------------------------------------------*
 * 测试除 log 外所有功能                            *
 **************************************************/

#include <unordered_map>

#include "models/heads/Club.h"
#include "models/imp/Club.cpp"
#include "models/heads/Staff.h"
#include "models/imp/Staff.cpp"
#include "models/heads/Tournament.h"
#include "models/imp/Tournament.cpp"

#include "views/ClubInfoView.h"
#include "views/MainMenuView.h"
#include "views/MarketView.h"
#include "views/RankView.h"
#include "views/TournamentView.h"
#include "views/WelcomeView.h"

#include "dataHandlers/BinaryClubDataRepo.h"
#include "dataHandlers/BinaryStaffDataRepo.h"
#include "dataHandlers/BinaryTournamentDataRepo.h"

#include "controllers/heads/ClubController.h"
#include "controllers/imp/Clubcontroller.cpp"
#include "controllers/heads/MarketController.h"
#include "controllers/imp/MarketController.cpp"
#include "controllers/heads/TournamentController.h"
#include "controllers/imp/TournamentController.cpp"

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
    std::cout << "Initializing views..." << std::endl;
    std::unordered_map<ViewState, std::unique_ptr<IView>> views;

        views[ViewState::WelcomeView] = std::make_unique<WelcomeView>(clubCtrl);
        views[ViewState::MainMenuView] = std::make_unique<MainMenuView>(clubCtrl, marketCtrl, tourCtrl);
        views[ViewState::ClubInfoView] = std::make_unique<ClubInfoView>(clubCtrl);
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