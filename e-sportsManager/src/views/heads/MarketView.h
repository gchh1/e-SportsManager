/***********
 * 市场视图 *
 ***********/

#pragma once

#include <memory>
#include <iostream>

#include "IView.h"
#include "MarketController.h"

class MarketView : public IView {
private:
    MarketController* controller;

public:
    MarketView() = default;
    MarketView(MarketController* ctrl);
    
    void initCtrl() override;
    ViewState run() override;
};
