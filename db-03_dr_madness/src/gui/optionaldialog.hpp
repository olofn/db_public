#ifndef DBSH07_OPTIONALDIALOG_HPP
#define DBSH07_OPTIONALDIALOG_HPP

#include "guichan.hpp"
#include "gui/decoratedcontainer.hpp"
#include "gui/dbsh07button.hpp"

class OptionalDialog: public DecoratedContainer, public gcn::ActionListener
{
public:
    OptionalDialog();
    ~OptionalDialog();
    void setVisible(bool visible);
    void action(const gcn::ActionEvent& actionEvent);
    unsigned int getState();
    void setState(unsigned int state) { mState = state; }

    enum
    {
        BONUS_LEVEL,
        SHOP,
        NONE
    };

protected:
    gcn::Label* mQueryLabel;
    DBSH07Button* mBonusLevelButton;
    DBSH07Button* mShopButton;
    unsigned int mState;
};

#endif