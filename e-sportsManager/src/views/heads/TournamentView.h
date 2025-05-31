/***********
 * 赛事视图 *
 ***********/

#pragma once

#include <memory>
#include <iostream>

#include "IView.h"
#include "TournamentController.h"

class TournamentView : public IView {
private:
    TournamentController* controller;

public:
    TournamentView() = default;
    TournamentView(TournamentController* ctrl);
    
    void initCtrl() override;
    ViewState run() override;
};
