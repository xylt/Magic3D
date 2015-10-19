#include "PointShopAppUI.h"
#include "../Common/ResourceManager.h"
#include "../Common/ToolKit.h"
#include "../Common/RenderSystem.h"
#include "AppManager.h"
#include "PointShopApp.h"

namespace MagicApp
{
    PointShopAppUI::PointShopAppUI()
    {
    }

    PointShopAppUI::~PointShopAppUI()
    {
    }

    void PointShopAppUI::Setup()
    {
        MagicCore::ResourceManager::LoadResource("../../Media/PointShopApp", "FileSystem", "PointShopApp");
        mRoot = MyGUI::LayoutManager::getInstance().loadLayout("PointShopApp.layout");
        mRoot.at(0)->findWidget("But_ImportPointCloud")->castType<MyGUI::Button>()->eventMouseButtonClick += MyGUI::newDelegate(this, &PointShopAppUI::ImportPointCloud);
        mRoot.at(0)->findWidget("But_ExportPointCloud")->castType<MyGUI::Button>()->eventMouseButtonClick += MyGUI::newDelegate(this, &PointShopAppUI::ExportPointCloud);
        mRoot.at(0)->findWidget("But_SmoothPointCloud")->castType<MyGUI::Button>()->eventMouseButtonClick += MyGUI::newDelegate(this, &PointShopAppUI::SmoothPointCloud);
        mRoot.at(0)->findWidget("But_SamplePointCloud")->castType<MyGUI::Button>()->eventMouseButtonClick += MyGUI::newDelegate(this, &PointShopAppUI::SamplePointCloud);
        mRoot.at(0)->findWidget("But_DoSamplePointCloud")->castType<MyGUI::Button>()->eventMouseButtonClick += MyGUI::newDelegate(this, &PointShopAppUI::DoSamplePointCloud);
        mRoot.at(0)->findWidget("But_Normal")->castType<MyGUI::Button>()->eventMouseButtonClick += MyGUI::newDelegate(this, &PointShopAppUI::PointCloudNormal);
        mRoot.at(0)->findWidget("But_CalNormal")->castType<MyGUI::Button>()->eventMouseButtonClick += MyGUI::newDelegate(this, &PointShopAppUI::CalculatePointCloudNormal);
        mRoot.at(0)->findWidget("But_FlipNormal")->castType<MyGUI::Button>()->eventMouseButtonClick += MyGUI::newDelegate(this, &PointShopAppUI::FlipPointCloudNormal);
        mRoot.at(0)->findWidget("But_Reconstruction")->castType<MyGUI::Button>()->eventMouseButtonClick += MyGUI::newDelegate(this, &PointShopAppUI::ReconstructMesh);
        mRoot.at(0)->findWidget("But_BackToHomepage")->castType<MyGUI::Button>()->eventMouseButtonClick += MyGUI::newDelegate(this, &PointShopAppUI::BackToHomepage);
        mRoot.at(0)->findWidget("But_Contact")->castType<MyGUI::Button>()->eventMouseButtonClick += MyGUI::newDelegate(this, &PointShopAppUI::Contact);
    }

    void PointShopAppUI::Shutdown()
    {
        MyGUI::LayoutManager::getInstance().unloadLayout(mRoot);
        mRoot.clear();
        MagicCore::ResourceManager::UnloadResource("PointShopApp");
    }

    void PointShopAppUI::ImportPointCloud(MyGUI::Widget* pSender)
    {
        PointShopApp* pointShop = dynamic_cast<PointShopApp* >(AppManager::Get()->GetApp("PointShopApp"));
        if (pointShop != NULL)
        {
            pointShop->ImportPointCloud();
        }
    }

    void PointShopAppUI::ExportPointCloud(MyGUI::Widget* pSender)
    {
        PointShopApp* pointShop = dynamic_cast<PointShopApp* >(AppManager::Get()->GetApp("PointShopApp"));
        if (pointShop != NULL)
        {
            pointShop->ExportPointCloud();
        }
    }

    void PointShopAppUI::SmoothPointCloud(MyGUI::Widget* pSender)
    {
        PointShopApp* pointShop = dynamic_cast<PointShopApp* >(AppManager::Get()->GetApp("PointShopApp"));
        if (pointShop != NULL)
        {
            pointShop->SmoothPointCloud();
        }
    }

    void PointShopAppUI::SamplePointCloud(MyGUI::Widget* pSender)
    {
        bool isVisible = mRoot.at(0)->findWidget("But_DoSamplePointCloud")->castType<MyGUI::Button>()->isVisible();
        isVisible = !isVisible;
        mRoot.at(0)->findWidget("But_DoSamplePointCloud")->castType<MyGUI::Button>()->setVisible(isVisible);
        mRoot.at(0)->findWidget("Edit_SampleTargetPointCount")->castType<MyGUI::EditBox>()->setVisible(isVisible);
        if (isVisible)
        {
            int pointCount = 0;
            PointShopApp* pointShop = dynamic_cast<PointShopApp* >(AppManager::Get()->GetApp("PointShopApp"));
            if (pointShop != NULL)
            {
                pointCount = pointShop->GetPointCount();
            }
            std::stringstream ss;
            std::string textString;
            ss << pointCount;
            ss >> textString;
            mRoot.at(0)->findWidget("Edit_SampleTargetPointCount")->castType<MyGUI::EditBox>()->setOnlyText(textString);
            mRoot.at(0)->findWidget("Edit_SampleTargetPointCount")->castType<MyGUI::EditBox>()->setTextSelectionColour(MyGUI::Colour::Black);
        }
    }

    void PointShopAppUI::DoSamplePointCloud(MyGUI::Widget* pSender)
    {
        PointShopApp* pointShop = dynamic_cast<PointShopApp* >(AppManager::Get()->GetApp("PointShopApp"));
        if (pointShop != NULL)
        {
            int pointCount = pointShop->GetPointCount();
            std::string textString = mRoot.at(0)->findWidget("Edit_SampleTargetPointCount")->castType<MyGUI::EditBox>()->getOnlyText();
            int targetPointCount = std::atoi(textString.c_str());
            if (targetPointCount > pointCount || pointCount < 1)
            {
                std::stringstream ss;
                std::string textString;
                ss << pointCount;
                ss >> textString;
                mRoot.at(0)->findWidget("Edit_SampleTargetPointCount")->castType<MyGUI::EditBox>()->setOnlyText(textString);
            }
            else
            {
                pointShop->SamplePointCloud(targetPointCount);
            }            
        }
    }

    void PointShopAppUI::PointCloudNormal(MyGUI::Widget* pSender)
    {
        bool isVisible = mRoot.at(0)->findWidget("But_CalNormal")->castType<MyGUI::Button>()->isVisible();
        mRoot.at(0)->findWidget("But_CalNormal")->castType<MyGUI::Button>()->setVisible(!isVisible);
        mRoot.at(0)->findWidget("But_FlipNormal")->castType<MyGUI::Button>()->setVisible(!isVisible);     
    }

    void PointShopAppUI::CalculatePointCloudNormal(MyGUI::Widget* pSender)
    {
        PointShopApp* pointShop = dynamic_cast<PointShopApp* >(AppManager::Get()->GetApp("PointShopApp"));
        if (pointShop != NULL)
        {
            pointShop->CalculatePointCloudNormal();
        }
    }

    void PointShopAppUI::FlipPointCloudNormal(MyGUI::Widget* pSender)
    {
        PointShopApp* pointShop = dynamic_cast<PointShopApp* >(AppManager::Get()->GetApp("PointShopApp"));
        if (pointShop != NULL)
        {
            pointShop->FlipPointCloudNormal();
        }
    }

    void PointShopAppUI::ReconstructMesh(MyGUI::Widget* pSender)
    {
        PointShopApp* pointShop = dynamic_cast<PointShopApp* >(AppManager::Get()->GetApp("PointShopApp"));
        if (pointShop != NULL)
        {
            pointShop->ReconstructMesh();
        }
    }

    void PointShopAppUI::BackToHomepage(MyGUI::Widget* pSender)
    {
        AppManager::Get()->SwitchCurrentApp("Homepage");
    }

    void PointShopAppUI::Contact(MyGUI::Widget* pSender)
    {
        MagicCore::ToolKit::OpenWebsite(std::string("http://threepark.net/geometryplusplus/about"));
    }
}
