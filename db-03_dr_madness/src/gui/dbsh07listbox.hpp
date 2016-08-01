#ifndef DBSH07_DBSH07LISTBOX_HPP
#define DBSH07_DBSH07LISTBOX_HPP

#include <guichan.hpp>
#include <allegro.h>

class DBSH07ListBox : public gcn::ListBox
{
public:
	DBSH07ListBox();
	~DBSH07ListBox();
	void draw(gcn::Graphics* graphics);
	void setSelected(int i);

private:
	BITMAP* mSelectedImage;
};

#endif
