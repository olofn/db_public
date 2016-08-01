#ifndef DB_SHOPDIALOG_HPP
#define DB_SHOPDIALOG_HPP

#include "guichan.hpp"
#include <allegro.h>

#include "gui/dbcontainer.hpp"
#include "gui/dblistbox.hpp"
#include "gui/dbscrollarea.hpp"

class Player;

class ShopListModel: public gcn::ListModel
{
public:
    int getNumberOfElements();
    std::string getElementAt(int i);
	std::string getDescription(int i);
};

class ShopDialog: public gcn::Container, public gcn::FocusListener, public gcn::ActionListener, public gcn::SelectionListener
{
public:
    ShopDialog(Player* player);
    ~ShopDialog();
	void focusGained(const gcn::Event& event);
	void action(const gcn::ActionEvent& event);
	void valueChanged (const gcn::SelectionEvent &event);
	bool isDone();
	void setVisible(bool visible);
private:
	void updateInfo();
	DbContainer* mLabelContainer;
	gcn::Label* mLabel;
	DbContainer* mInfoContainer;
	DbContainer* mListContainer;
	DBListBox* mList;
	DbScrollArea* mScrollArea;
	gcn::TextBox* mInfo;
    ShopListModel* mListModel;
	Player* mPlayer;
	bool mIsDone;
	bool mDisableShopping;
	SAMPLE* mUseItemSample;
};

#endif
