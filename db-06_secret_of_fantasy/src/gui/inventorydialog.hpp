#ifndef DB_INVENTORYDIALOG_HPP
#define DB_INVENTORYDIALOG_HPP

#include "guichan.hpp"
#include <allegro.h>

#include "gui/dbcontainer.hpp"
#include "gui/dblistbox.hpp"
#include "gui/dbscrollarea.hpp"
#include "inventory.hpp"

class InventoryListModel: public gcn::ListModel
{
public:
	InventoryListModel(Inventory* inventory);
	int getNumberOfElements();
	std::string getElementAt(int i);
private:
	Inventory* mInventory;
};

class InventoryDialog: public gcn::Container, public gcn::FocusListener, public gcn::ActionListener, public gcn::SelectionListener
{
public:
    InventoryDialog(Inventory* inventory);
    ~InventoryDialog();
	void focusGained(const gcn::Event& event);
	void action(const gcn::ActionEvent& event);
	void valueChanged (const gcn::SelectionEvent &event);
private:
	void updateInfo();
	DbContainer* mLabelContainer;
	gcn::Label* mLabel;
	DbContainer* mInfoContainer;
	DbContainer* mListContainer;
	DBListBox* mList;
	DbScrollArea* mScrollArea;
	gcn::TextBox* mInfo;
    InventoryListModel* mListModel;
	Inventory* mInventory;
};

#endif
