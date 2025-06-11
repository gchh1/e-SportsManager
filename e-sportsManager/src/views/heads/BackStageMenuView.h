/***************
 * 后台菜单视图 *
 ***************/

#pragma once

#include "IView.h"


class BackStageMenuView : public IView {
public:
    ViewState run() override;
    void initCtrl() override {}

};