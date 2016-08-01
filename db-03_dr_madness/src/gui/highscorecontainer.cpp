#include "gui/highscorecontainer.hpp"
#include "gamestate.hpp"
#include "stringutil.hpp"
#include "resourcehandler.hpp"

HighScoreContainer::HighScoreContainer()
: mState(VIEW),
mHash("dashda8s9dya89sd637h3nbcaut6752")
{
    mHighScoreLabel = new gcn::Label("HIGHSCORE");
	mHighScoreLabel->adjustSize();
	add(mHighScoreLabel, 
        160 - mHighScoreLabel->getWidth() / 2,
        50);

    for (unsigned int i = 0; i < 20; i++)
    {
        gcn::Label* label;
        if (i < 10)
        {
             label = new gcn::Label("FLUFFY LOVE");
             add(label, 95, 70 + i * label->getHeight());
        }
        else
        {
            label = new gcn::Label("10");
            add(label, 180, 70 + (i - 10) * label->getHeight());
        }

        mLabels.push_back(label);
    }

    mTextField = new DBSH07TextField("             ");
    mTextField->setVisible(false);
    mTextField->addActionListener(this);
    add(mTextField);

    mSample = ResourceHandler::getInstance()->getSample("shopbuy.wav");
}

HighScoreContainer::~HighScoreContainer()
{
    delete mTextField;
    delete mHighScoreLabel;
  
    for (unsigned int i = 0; i < 20; i++)
    {
        delete mLabels[i];
    }
}

void HighScoreContainer::setState(unsigned int state)
{
    mState = state;
}

void HighScoreContainer::setVisible(bool visible)
{
    Container::setVisible(visible);

    if (mState == ENTER_SCORE && !visible)
    {
        std::vector<GameState::HighScorePair> &highScores = GameState::getInstance()->getHighScores();

        for (int row = 0; row < highScores.size() && row < 10; row++)
	    {
            if (mState == ENTER_SCORE 
                && highScores[row].name == mHash
                && highScores[row].points == GameState::getInstance()->getPoints())
            {
               highScores[row].name = "";
            }
        }

        for (unsigned int i = 0; i < mLabels.size(); i++)
        {
            mLabels[i]->setVisible(true);
        }

        GameState::getInstance()->saveHighScore();
        GameState::getInstance()->setPoints(0);
        mState = VIEW;
       
        mTextField->setVisible(false);
        return;
    }
    else if (mState == ENTER_SCORE && visible)
    {
        GameState::getInstance()->addHighScore(mHash, GameState::getInstance()->getPoints());
        std::vector<GameState::HighScorePair> &highScores = GameState::getInstance()->getHighScores();

	    for (int row = 0; row < highScores.size() && row < 10; row++)
	    {
            mLabels[row]->setCaption(highScores[row].name);
            mLabels[row]->adjustSize();
            mLabels[row+10]->setCaption(toString(highScores[row].points));
            mLabels[row+10]->adjustSize();

            if (highScores[row].name == mHash
                && highScores[row].points == GameState::getInstance()->getPoints())
            {
                mTextFieldEnterRow = row;
            }
        }

        mLabels[mTextFieldEnterRow]->setVisible(false);
        mTextField->setText("");
        mTextField->setVisible(true);
        mTextField->setPosition(mLabels[mTextFieldEnterRow]->getX() - 1,
                                mLabels[mTextFieldEnterRow]->getY() - 1);
        mTextField->requestFocus();
    }
    else if (mState == VIEW && visible)
    {
        std::vector<GameState::HighScorePair> &highScores = GameState::getInstance()->getHighScores();

	    for (int row = 0; row < highScores.size() && row < 10; row++)
	    {
            mLabels[row]->setCaption(highScores[row].name);
            mLabels[row]->adjustSize();
            mLabels[row+10]->setCaption(toString(highScores[row].points));
            mLabels[row+10]->adjustSize();
        }
    }
}

void HighScoreContainer::action(const gcn::ActionEvent& actionEvent)
{
    if (actionEvent.getSource() == mTextField)
    {
        GameState::getInstance()->getHighScores()[mTextFieldEnterRow].name = mTextField->getText();
        GameState::getInstance()->saveHighScore();
        mTextField->setVisible(false);
        mLabels[mTextFieldEnterRow]->setCaption(mTextField->getText());
        mLabels[mTextFieldEnterRow]->adjustSize();
        mLabels[mTextFieldEnterRow]->setVisible(true);
        mState = VIEW;
        play_sample(mSample, 128, 128, 1000, 0);
        GameState::getInstance()->setPoints(0);
    }
}
