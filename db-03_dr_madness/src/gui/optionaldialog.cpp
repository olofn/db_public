#include "gui/optionaldialog.hpp"

OptionalDialog::OptionalDialog()
:mState(NONE)
{
    setBackgroundColor(gcn::Color(0x000000));
    setSize(190, 50);

    mQueryLabel = new gcn::Label("Where do you want to go?");
    mQueryLabel->adjustSize();
    add(mQueryLabel);

    mBonusLevelButton = new DBSH07Button("To the bonus level");
    mBonusLevelButton->addActionListener(this);
    add(mBonusLevelButton, 20, mQueryLabel->getHeight() + 5);

    mShopButton = new DBSH07Button("To the shop");
    mShopButton->addActionListener(this);
    add(mShopButton, 20, mQueryLabel->getHeight() + mBonusLevelButton->getHeight() + 5);
}

OptionalDialog::~OptionalDialog()
{
    delete mBonusLevelButton;
    delete mShopButton;
    delete mQueryLabel;
}

void OptionalDialog::setVisible(bool visible)
{
    DecoratedContainer::setVisible(visible);

    if (visible)
    {
        mState = NONE;
    }
}

void OptionalDialog::action(const gcn::ActionEvent& actionEvent)
{
    if (actionEvent.getSource() == mBonusLevelButton)
    {
        mState = BONUS_LEVEL;
    }
    else if (actionEvent.getSource() == mShopButton)
    {
        mState = SHOP;
    }

    generateAction();
}

unsigned int OptionalDialog::getState()
{
    return mState;
}