#ifndef DB_LISTBOX_HPP
#define DB_LISTBOX_HPP

#include <guichan.hpp>
#include <allegro.h>

class DBListBox : public gcn::ListBox
{
public:
	DBListBox();
	~DBListBox();
	void draw(gcn::Graphics* graphics);
	void setSelected(int i);

private:
	BITMAP* mSelectedImage;
};

#endif
