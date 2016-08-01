#include "gui/savedialog.hpp"
#include "gamestatemanager.hpp"

namespace nmc
{
    SaveDialog::SaveDialog()
    {
        setBackgroundColor(gcn::Color(0x000000));
        setSize(190, 50);

        mQueryLabel = new gcn::Label("Do you want to save your game?");
        mQueryLabel->adjustSize();
        add(mQueryLabel);

        mYesLabel = new gcn::Label("Yes");
        mYesLabel->adjustSize();
        add(mYesLabel, 20, mQueryLabel->getHeight() + 5);

        mNoLabel = new gcn::Label("No");
        mNoLabel->adjustSize();
        add(mNoLabel, 20, mQueryLabel->getHeight() + mYesLabel->getHeight() + 5);

        mMultiSelector = new MultiSelector();
        mMultiSelector->setSize(getWidth(), getHeight());
        mMultiSelector->addActionListener(this);
        add(mMultiSelector);
        mMultiSelector->addSelection(0, 
                                     mYesLabel->getY() + mYesLabel->getHeight() / 2 
                                     - mMultiSelector->getSelectorHeight() / 2);
        mMultiSelector->addSelection(0, 
                                     mNoLabel->getY() + mNoLabel->getHeight() / 2 
                                    - mMultiSelector->getSelectorHeight() / 2);
    }

    SaveDialog::~SaveDialog()
    {
        delete mMultiSelector;
        delete mNoLabel;
        delete mYesLabel;
        delete mQueryLabel;
    }

    void SaveDialog::setVisible(bool visible)
    {
        DecoratedContainer::setVisible(visible);

        if (visible)
        {
            mMultiSelector->requestFocus();
            mMultiSelector->setSelected(0);
        }
    }

    void SaveDialog::action(const gcn::ActionEvent& actionEvent)
    {
        if (mMultiSelector->getSelected() == 0)
        {
            GameStateManager::getInstance()->saveCurrent();
        }

         setVisible(false);
    }
}