#include "gui/shopdialog.hpp"
#include "stringutil.hpp"

#include "entities/player.hpp"

#include "items/bomb.hpp"
#include "items/cure.hpp"
#include "items/shovel.hpp"
#include "items/calciumcrystal.hpp"
#include "resourcehandler.hpp"

int ShopListModel::getNumberOfElements()
{
    return 5;
}

std::string ShopListModel::getElementAt(int i)
{
    switch(i)
    {
    case 0:
        return std::string("CURE 20$");
	case 1:
        return std::string("BOMB 20$");
	case 2:
        return std::string("SHOVEL 10$");
	case 3:
        return std::string("CALCIUM CRYSTAL 400$");
    case 4:
        return std::string("EXIT");
    default: // Just to keep warnings away
      return std::string("");
    }
}

std::string ShopListModel::getDescription(int i)
{
    switch(i)
    {
    case 0:
        return std::string("HEAL STUFF!");
    case 1:
        return std::string("BLOW STUFF UP!");
	case 2:
        return std::string("DIG STUFF UP!");
	case 3:
        return std::string("A SHINY CRYSTAL!");
    default: // Just to keep warnings away
      return std::string("");
    }
}

ShopDialog::ShopDialog(Player* player)
{
	mPlayer = player;
	mIsDone = false;
	setSize(260, 180);
	setOpaque(false);
	setFocusable(true);
	addFocusListener(this);
	setEnabled(true);
	mDisableShopping = false;

	mLabelContainer = new DbContainer();
	mLabelContainer->setSize(260, 20);
	add(mLabelContainer);
	mLabel = new gcn::Label("SHOP");
	mLabel->adjustSize();
	mLabelContainer->add(mLabel, 
						 mLabelContainer->getWidth() / 2 - mLabel->getWidth() / 2,
						 mLabelContainer->getHeight() / 2 - mLabel->getHeight() / 2);

	
	mListContainer = new DbContainer();
	mListContainer->setSize(260, 110);
	mListContainer->setVisible(true);
	add(mListContainer, 0, 22);
	mList = new DBListBox();
	mList->addActionListener(this);
	mList->addSelectionListener(this);
	mListModel = new ShopListModel();
	mList->setListModel(mListModel);
	mList->setWidth(250);
	mScrollArea = new DbScrollArea();
	mScrollArea->setSize(250, 99);
	mScrollArea->setContent(mList);
	mListContainer->add(mScrollArea, 5, 5);

	mInfoContainer = new DbContainer();
	mInfoContainer->setSize(260, 30);
	mInfoContainer->setVisible(true);
	add(mInfoContainer, 0, 135);
	mInfo = new gcn::TextBox();
	mInfo->setOpaque(false);
	mInfo->setText("");
	mInfo->setEditable(false);
	mInfoContainer->add(mInfo, 5, 5);

	mUseItemSample = ResourceHandler::getInstance()->getSample("sound/useitem.wav");
}

ShopDialog::~ShopDialog()
{
	delete mInfo;
	delete mInfoContainer;
	delete mLabel;
	delete mLabelContainer;
	delete mListContainer;
	delete mList;
	delete mListModel;
}

void ShopDialog::focusGained(const gcn::Event& event)
{
	mList->requestFocus();
	mList->setSelected(0);
}

void ShopDialog::action(const gcn::ActionEvent& event)
{
	// Disable shopping at first action 
	// as a queued Guichan event is messing with our code.
	// (as the dialog is started with a key[KEY_ALT] check.
	if (mDisableShopping)
	{
		mDisableShopping = false;
		return;
	}

	int selectedIndex = mList->getSelected();
	if (selectedIndex == -1)
		return;

	switch(selectedIndex)
    {
    case 0:
		if (mPlayer->getCoins() >= 20)
		{
			mPlayer->getInventory()->add(new Cure());
			mPlayer->setCoins(mPlayer->getCoins() - 20);
			play_sample(mUseItemSample, 127, 127, 1000, 0);
		}
		break;
    case 1:
        if (mPlayer->getCoins() >= 20)
		{
			mPlayer->getInventory()->add(new Bomb());
			mPlayer->setCoins(mPlayer->getCoins() - 20);
			play_sample(mUseItemSample, 127, 127, 1000, 0);
		}
		break;
	case 2:
		if (mPlayer->getCoins() >= 10 && mPlayer->getInventory()->find("SHOVEL") == 0)
		{
			mPlayer->getInventory()->add(new Shovel());
			mPlayer->setCoins(mPlayer->getCoins() - 10);
			play_sample(mUseItemSample, 127, 127, 1000, 0);
		}
		break;
	case 3:
		if (mPlayer->getCoins() >= 400)
		{
			mPlayer->getInventory()->add(new CalciumCrystal());
			mPlayer->setCoins(mPlayer->getCoins() - 400);
			play_sample(mUseItemSample, 127, 127, 1000, 0);
		}
		break;
    }

	if (selectedIndex == mListModel->getNumberOfElements() - 1)
	{
		mIsDone = true;
	}
}

bool ShopDialog::isDone()
{
	return mIsDone;
}

void ShopDialog::setVisible(bool visible)
{
	if (visible)
	{
		mIsDone = false;
		mDisableShopping = true;
	}
	gcn::Container::setVisible(visible);
}

void ShopDialog::valueChanged(const gcn::SelectionEvent &event)
{
	updateInfo();
}

void ShopDialog::updateInfo()
{
	int selectedIndex = mList->getSelected();
	
	if (selectedIndex == -1)
	{
		mInfo->setText("");
	}
	else
	{
		mInfo->setText(mListModel->getDescription(selectedIndex));
	}
}