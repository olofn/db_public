#ifndef NMC_SAVEDIALOG_HPP
#define NMC_SAVEDIALOG_HPP

#include "guichan.hpp"
#include "gui/decoratedcontainer.hpp"
#include "gui/multiselector.hpp"

namespace nmc
{
    class SaveDialog: public DecoratedContainer, public gcn::ActionListener
    {
    public:
        SaveDialog();
        ~SaveDialog();
        void setVisible(bool visible);
        void action(const gcn::ActionEvent& actionEvent);

    protected:
        gcn::Label* mQueryLabel;
        gcn::Label* mNoLabel;
        gcn::Label* mYesLabel;
        MultiSelector* mMultiSelector;
    };
}

#endif