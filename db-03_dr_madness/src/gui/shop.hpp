#ifndef DBSH07_SHOP_HPP
#define DBSH07_SHOP_HPP

#include "guichan.hpp"
#include "gui/dbsh07button.hpp"
#include "gui/dialog.hpp"

class Shop: public gcn::Container, public gcn::ActionListener
{
public:
    Shop();
    ~Shop();
    void action(const gcn::ActionEvent& actionEvent);
    void setVisible(bool visible);

protected:
    static const int CANNON_UPGRADE_COST = 15;
    static const int POD_COST = 10;
    static const int LIFE_COST = 3;
    static const int MEGA_BLAST_COST = 4;

    gcn::Label* mItemLabel;
    gcn::Label* mCostLabel;
    gcn::Label* mYouHaveLabel;
    gcn::Label* mShopLabel;
    DBSH07Button* mLeaveButton;
    DBSH07Button* mBuyLifeButton;
    DBSH07Button* mBuyPodButton;
    DBSH07Button* mBuyCannonUpgradeButton;
    DBSH07Button* mBuyMegaBlastButton;
    gcn::Label* mLifeCostLabel;
    gcn::Label* mLivesEquipedLabel;
    gcn::Label* mPodCostLabel;
    gcn::Label* mPodsEquipedLabel;
    gcn::Label* mEnergyOrbsLabel;
    gcn::Label* mCannonUpgradeEquipedLabel;
    gcn::Label* mCannonUpgradeCostLabel;
    gcn::Label* mMegaBlastsEquippedLabel;
    gcn::Label* mMegaBlastCostLabel;
    Dialog* mDialog;
    SAMPLE* mBuySample;
};

#endif