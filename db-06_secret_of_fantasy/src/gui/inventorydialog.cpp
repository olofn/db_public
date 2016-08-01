#include "gui/inventorydialog.hpp"
#include "stringutil.hpp"

InventoryListModel::InventoryListModel(Inventory* inventory)
{
	mInventory = inventory;
}

int InventoryListModel::getNumberOfElements()
{
	return mInventory->getNumberOfItems();
}

std::string InventoryListModel::getElementAt(int i)
{
	std::string result = mInventory->getEntry(i).item->getName();
	if (mInventory->getEntry(i).item->isStackable())
	{
		result += " *" + toString(mInventory->getEntry(i).amount);
	}

	if (mInventory->getEntry(i).equiped)
	{
		result += " &";
	}
	return result;
}

InventoryDialog::InventoryDialog(Inventory* inventory)
{
	mInventory = inventory;

	setSize(260, 180);
	setOpaque(false);
	setFocusable(true);
	addFocusListener(this);
	setEnabled(true);

	mLabelContainer = new DbContainer();
	mLabelContainer->setSize(260, 20);
	add(mLabelContainer);
	mLabel = new gcn::Label("ITEMS");
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
	mListModel = new InventoryListModel(mInventory);
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
}

InventoryDialog::~InventoryDialog()
{
	delete mInfo;
	delete mInfoContainer;
	delete mLabel;
	delete mLabelContainer;
	delete mListContainer;
	delete mList;
	delete mListModel;
}

void InventoryDialog::focusGained(const gcn::Event& event)
{
	mList->requestFocus();

	if (mInventory->getNumberOfItems() != 0)
	{
		mList->setSelected(0);
	}
}

void InventoryDialog::action(const gcn::ActionEvent& event)
{
	int selectedIndex = mList->getSelected();
	if (selectedIndex == -1)
		return;

	Item* item = mInventory->getEntry(selectedIndex).item;
	mInventory->useOrEquipe(item);
	
	if (selectedIndex >= mInventory->getNumberOfItems())
	{
		mList->setSelected(mList->getSelected() - 1);
		selectedIndex--;
	}
	updateInfo();
}

void InventoryDialog::valueChanged(const gcn::SelectionEvent &event)
{
	updateInfo();
}

void InventoryDialog::updateInfo()
{
	int selectedIndex = mList->getSelected();
	if (selectedIndex == -1 || mInventory->getNumberOfItems() == 0)
	{
		mInfo->setText("");
	}
	else
	{
		mInfo->setText(mInventory->getEntry(selectedIndex).item->getDescription() + "\n" +
					   mInventory->getEntry(selectedIndex).item->getHelp());
	}
}