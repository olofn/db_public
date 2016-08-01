#ifndef DBSH07_HIGHSCORECONTAINER_HPP
#define DBSH07_HIGHSCORECONTAINER_HPP

#include "guichan.hpp"
#include <vector>
#include "gui/dbsh07textfield.hpp"
#include "allegro.h"

class HighScoreContainer: public gcn::Container, gcn::ActionListener
{
public:
    HighScoreContainer();
    ~HighScoreContainer();
    void setVisible(bool visible);
    void setState(unsigned int state);
    void action(const gcn::ActionEvent& actionEvent);

    enum
    {
        VIEW,
        ENTER_SCORE
    };

protected:
    gcn::Label* mHighScoreLabel;
    unsigned int mState;
    std::vector<gcn::Label*> mLabels;
    DBSH07TextField* mTextField;
    unsigned int mTextFieldEnterRow;
    SAMPLE* mSample;
    std::string mHash;
};

#endif