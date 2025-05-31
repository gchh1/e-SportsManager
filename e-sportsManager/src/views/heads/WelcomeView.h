/***********
 * 欢迎界面 *
 ***********/

#pragma once

#include <memory>

#include "IView.h"
#include "ClubController.h"

class WelcomeView : public IView {
private:
    ClubController* controller;

public:
    WelcomeView() = default;
    WelcomeView(ClubController* ctrl);
    
    void initCtrl() override;
    ViewState run() override;
};
