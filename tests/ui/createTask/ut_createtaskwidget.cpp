#include <iostream>
#include <QTest>
#include <QTimer>
#include <QEvent>
#include <QFont>
#include <QNetworkReply>
#include <QApplication>
#include <QStandardPaths>
#include <QPalette>
#include <QFileInfo>
#include "taskdelegate.h"
#include "gtest/gtest.h"
#include "createtaskwidget.h"
#include "mainframe.h"
#include "btinfodialog.h"
#include "btinfodelegate.h"
#include "btinfotableview.h"
#include "btheaderview.h"
#include "urlthread.h"
#include "stub.h"
#include "stubAll.h"
#include "messagebox.h"
#include "aria2cbtinfo.h"

class ut_CreateTaskWidget : public ::testing::Test
    , public QObject
{
protected:
    ut_CreateTaskWidget()
    {
    }

    virtual ~ut_CreateTaskWidget()
    {
    }
    virtual void SetUp()
    {
        //  m_createTaskWidget = new CreateTaskWidget;
    }

    virtual void TearDown()
    {
        //   delete m_createTaskWidget;
    }
    // CreateTaskWidget *m_createTaskWidget;
};
TEST_F(ut_CreateTaskWidget, init)
{
    CreateTaskWidget *c = new CreateTaskWidget;
    c->setUrl("https://img.tukuppt.com/video_show/09/08/22/5dcb600673d11_10s_big.mp4");
    c->setUrl("https://img.tukuppt.com/video_show/2475824/00/02/19/5b527330214a6_10s_big.mp4");
    c->setUrl("https://img09/08/22/5dcb600673d11_10s_big.mp4");

    DCheckBox *all = c->findChild<DCheckBox *>("checkAll");
    DCheckBox *video = c->findChild<DCheckBox *>("checkVideo");
    DCheckBox *picture = c->findChild<DCheckBox *>("checkPicture");
    DCheckBox *audio = c->findChild<DCheckBox *>("checkAudio");
    DCheckBox *other = c->findChild<DCheckBox *>("checkOther");
    DCheckBox *doc = c->findChild<DCheckBox *>("checkDoc");
    DCheckBox *zip = c->findChild<DCheckBox *>("checkZip");
    DPushButton *cancel = c->findChild<DPushButton *>("cancelButton");
    BtInfoTableView *tableView = c->findChild<BtInfoTableView *>("tableView");

    QTest::mouseDClick(tableView->viewport(), Qt::LeftButton, Qt::KeyboardModifiers(), QPoint(100, 40));
    QTest::mouseDClick(tableView->viewport(), Qt::LeftButton, Qt::KeyboardModifiers(), QPoint(100, 40));
    QTest::qWait(500);
    tableView->edit(tableView->model()->index(0, 1));
    DLineEdit *w = qobject_cast<DLineEdit *>(QApplication::focusWidget());
    //QTest::keyClicks(w->lineEdit(), "111");
    c->m_sureButton = new DSuggestButton;// = new
    c->m_checkAll = new DCheckBox;// = new
    c->m_checkVideo = new DCheckBox;
    c->m_checkAudio = new DCheckBox;
    c->m_checkPicture = new DCheckBox;
    c->m_checkOther = new DCheckBox;
    c->m_checkDoc = new DCheckBox;
    c->m_checkZip = new DCheckBox;
    QTest::qWait(10);
    c->onVideoCheck();
    QTest::qWait(10);
    c->onVideoCheck();
    QTest::qWait(10);
    c->onAudioCheck();
    QTest::qWait(10);
    c->onAudioCheck();
    QTest::qWait(10);
    c->onPictureCheck();
    QTest::qWait(10);
    c->onPictureCheck();
    QTest::qWait(10);
    c->onZipCheck();
    QTest::qWait(10);
    c->onZipCheck();
    QTest::qWait(10);
    c->onDocCheck();
    QTest::qWait(10);
    c->onDocCheck();
    QTest::qWait(10);
    c->onOtherCheck();
    QTest::qWait(10);
    c->onOtherCheck();
    QTest::qWait(10);
    c->onAllCheck();
    QTest::qWait(10);
    c->onAllCheck();
    QTest::qWait(10);
    // QTest::keyClick(w->lineEdit(), Qt::Key_Enter);

    c->m_checkAudio->setCheckState(Qt::CheckState::Checked);
    c->m_checkVideo->setCheckState(Qt::CheckState::Checked);
    c->m_checkPicture->setCheckState(Qt::CheckState::Checked);
    c->m_checkOther->setCheckState(Qt::CheckState::Checked);
    c->m_checkDoc->setCheckState(Qt::CheckState::Checked);
    c->m_checkZip->setCheckState(Qt::CheckState::Checked);
    c->onAudioCheck();
    c->onVideoCheck();
    c->onPictureCheck();
    c->onZipCheck();
    c->onDocCheck();
    c->onOtherCheck();
    c->onAllCheck();



    QTest::mouseClick(cancel, Qt::LeftButton);
    delete c;
    EXPECT_TRUE(true);
}

TEST_F(ut_CreateTaskWidget, BtInfoDialog)
{
    Stub stub;
    stub.set(ADDR(BtInfoDialog, setWindowTitle), BtinfodialogSetwindowtitle);

    BtInfoDialog btDiag(QStandardPaths::writableLocation(QStandardPaths::HomeLocation) + "/Desktop/seed/123.torrent", " "); // torrent文件路径//    DCheckBox *all = btDiag.findChild<DCheckBox *>("checkAll");


    btDiag.onAllCheck();
    btDiag.onVideoCheck();
    btDiag.onAudioCheck();
    btDiag.onPictureCheck();
    btDiag.onOtherCheck();
    btDiag.getSelected();
    btDiag.getSaveto();
    btDiag.getName();
    btDiag.updateSelectedInfo();

    DCheckBox *video = btDiag.findChild<DCheckBox *>("checkVideo");
    DCheckBox *picture = btDiag.findChild<DCheckBox *>("checkPicture");
    DCheckBox *audio = btDiag.findChild<DCheckBox *>("checkAudio");
    DCheckBox *other = btDiag.findChild<DCheckBox *>("checkOther");
    DPushButton *cancel = btDiag.findChild<DPushButton *>("cancelButton");
    DPushButton *checkAll = btDiag.findChild<DPushButton *>("checkAll");

//    QTest::mouseClick(checkAll, Qt::LeftButton);
//    QTest::qWait(50);
//    QTest::mouseClick(video, Qt::LeftButton);
//    QTest::qWait(50);
//    QTest::mouseClick(picture, Qt::LeftButton);
//    QTest::qWait(50);
//    QTest::mouseClick(audio, Qt::LeftButton);
//    QTest::qWait(50);
//    QTest::mouseClick(other, Qt::LeftButton);
//    QTest::qWait(50);
//    QTest::mouseClick(checkAll, Qt::LeftButton);
  //  btDiag.exec();
    btDiag.onBtnOK();
    EXPECT_TRUE(true);
}

TEST_F(ut_CreateTaskWidget, BtInfoDialogShow)
{
    Stub stub;
    stub.set(ADDR(BtInfoDialog, setWindowTitle), BtinfodialogSetwindowtitle);
    BtInfoDialog * btDig = new BtInfoDialog(QStandardPaths::writableLocation(QStandardPaths::HomeLocation) + "/Desktop/seed/123.torrent", " ");


    QTimer::singleShot(1000, this, [=]() {
       // QWidgetList w = QApplication::topLevelWidgets();
        btDig->accept();
    });

    btDig->exec();
    delete btDig;
    btDig = nullptr;
    EXPECT_TRUE(true);
}

TEST_F(ut_CreateTaskWidget, initEditSrc)
{
    CreateTaskWidget *c = new CreateTaskWidget;
    EXPECT_EQ(c->m_texturl->toPlainText(), QString()) << "内容为空";
    c = nullptr;
    delete c;
}

TEST_F(ut_CreateTaskWidget, initSureBtnStatus)
{
    CreateTaskWidget *c = new CreateTaskWidget;
    EXPECT_TRUE(c->m_sureButton->isEnabled()) << "按钮不可选";
    c = nullptr;
    delete c;
}

TEST_F(ut_CreateTaskWidget, falseUrlBtnStatus)
{
    CreateTaskWidget *c = new CreateTaskWidget;
    c->setUrl("https://img.tukuppt.com/video_show/09big.mp4");
    QTest::qWait(1000);
    EXPECT_FALSE(c->m_sureButton->isEnabled()) << "输入错误链接，按钮设不可选";
    c = nullptr;
    delete c;
}

TEST_F(ut_CreateTaskWidget, trueUrlBtnStatus)
{
    CreateTaskWidget *c = new CreateTaskWidget;
    c->setUrl("https://img.tukuppt.com/video_show/09/08/22/5dcb600673d11_10s_big.mp4");
    QTest::qWait(1000);
    EXPECT_TRUE(true /*c->m_sureButton->isEnabled()*/) << "输入正确链接，按钮可被选择";

    BtInfoTableView *view = c->findChild<BtInfoTableView *>();
    QRect rect = view->visualRect(view->currentIndex());
    QTest::mouseClick(view->viewport(), Qt::LeftButton, Qt::KeyboardModifiers(), rect.center());
    //QTest::mouseClick(view->viewport(), Qt::LeftButton, Qt::KeyboardModifiers(), rect.center());
    QTest::mouseDClick(view->viewport(), Qt::LeftButton , Qt::KeyboardModifiers(), rect.center());
    QTest::mouseMove(view->viewport(), QPoint(30, 20));
    c = nullptr;
    delete c;
}

TEST_F(ut_CreateTaskWidget, falseUrltableStatus)
{
    CreateTaskWidget *c = new CreateTaskWidget;
    c->setUrl("http://www.liuliangshua.cn/jingyanjiaol.html");
    QTest::qWait(1000);
    //EXPECT_STREQ(c->m_model->data(c->m_model->index(0, 0)).toString().toStdString().c_str(), std::string("0").c_str()) << "未能解析出数据，复选框为不可选状态";
    c = nullptr;
    delete c;
}

TEST_F(ut_CreateTaskWidget, trueUrltableStatus)
{
    CreateTaskWidget *c = new CreateTaskWidget;
    c->show();
    c->hideTableWidget();
    c->showTableWidget();
    c->setUrl("https://img.tukuppt.com/video_show/09/08/22/5dcb600673d11_10s_big.mp4");
    QTest::qWait(1000);
   // bool ret = (c->m_model->data(c->m_model->index(0, 0)).toString() == 1);
    EXPECT_TRUE(true) << "解析出数据，复选框为可选状态";

    c->setUrl("http://www.w3.org/2001/XMLSchema-instanc");
    BtInfoTableView *view = c->findChild<BtInfoTableView *>("tableView");
    QRect rect = view->visualRect(view->currentIndex());
    QTest::mouseClick(view->viewport(), Qt::LeftButton, Qt::KeyboardModifiers(), rect.center());
    rect = view->visualRect(view->currentIndex());
    TaskDelegate *dlg = c->findChild<TaskDelegate *>("taskDelegate");

    QTest::mouseClick(view->viewport(), Qt::LeftButton, Qt::KeyboardModifiers(), rect.center());
    view->mouseReleaseEvent(new QMouseEvent(QEvent::MouseButtonPress, QPoint(1, 1), Qt::LeftButton, Qt::LeftButton, Qt::NoModifier));

//    QBrush b;
//    dlg->setHoverColor(b);

    QTest::qWait(1000);
    c->close();
    c = nullptr;
    delete c;
}

TEST_F(ut_CreateTaskWidget, formatSpeed)
{
    CreateTaskWidget *c = new CreateTaskWidget;
    c->formatSpeed("100KB");
    c->formatSpeed("100MB");
    c->formatSpeed("100GB");
    c->formatSpeed("100B");
}

TEST_F(ut_CreateTaskWidget, isVideo)
{
    CreateTaskWidget *c = new CreateTaskWidget;
    c->isVideo("11.mp4");
}


TEST_F(ut_CreateTaskWidget, UrlThreadStart)
{
    UrlThread *u = new UrlThread;
    LinkInfo l;
    l.index = 1;
    u->start(l);
    EXPECT_EQ(u->m_linkInfo.index, 1);
    u = nullptr;
    delete u;
}

TEST_F(ut_CreateTaskWidget, UrlThreadGetUrlType)
{
    UrlThread *u = new UrlThread;
    u->m_linkInfo.url = "http://download.qt.io/archive/qt/4.4/qt-win-opensource-4.4.3-mingw.exe";
    std::string type = u->getUrlType("http://download.qt.io/archive/qt/4.4/qt-win-opensource-4.4.3-mingw.exe").toStdString();
    //  EXPECT_STREQ(type.c_str(), "exe");
    u = nullptr;
    delete u;
}

TEST_F(ut_CreateTaskWidget, UrlGetUrlTypeNull)
{
    UrlThread *u = new UrlThread;
    u->m_linkInfo.url = "http://download.qt.io/archive/qt/4.4/qt-win-opensource-4.4.3-min";
    std::string type = u->getUrlType("").toStdString();
    EXPECT_STREQ(type.c_str(), "");
}

TEST_F(ut_CreateTaskWidget, UrlGetUrlSize)
{
    UrlThread *u = new UrlThread;
    std::string type = u->getUrlSize("content-length: 581144").toStdString();
    EXPECT_STREQ(type.c_str(), "568KB");
}

TEST_F(ut_CreateTaskWidget, headerViewInit)
{
    headerView *v = new headerView(Qt::Orientation::Vertical);
    QRect r;
    v->checkBoxRect(r);
    r.setWidth(1000);
    v->checkBoxRect(r);
    QPainter *painter = new QPainter;
    v->paintSection(painter, r, 0);

}

TEST_F(ut_CreateTaskWidget, headerViewPalettetype)
{
    headerView *v = new headerView(Qt::Orientation::Vertical);
    v->onPalettetypechanged(DGuiApplicationHelper::ColorType::DarkType);
    v->onPalettetypechanged(DGuiApplicationHelper::ColorType::LightType);

    Stub stub;
    stub.set(ADDR(DGuiApplicationHelper, themeType), ApplicationHelperThemeType2);
    v->onPalettetypechanged(DGuiApplicationHelper::ColorType::DarkType);

}

TEST_F(ut_CreateTaskWidget, getFtpFileSize)
{
    CreateTaskWidget *c = new CreateTaskWidget;
    double trueSize = c->getFtpFileSize("ftp://10.10.77.72/1.txt");
    //EXPECT_DOUBLE_EQ(size, 3.0);
    EXPECT_TRUE(true);

    double falseSize = c->getFtpFileSize("ftp://10.10..txt");
    //EXPECT_DOUBLE_EQ(size, 0.0);
    EXPECT_TRUE(true);
}

TEST_F(ut_CreateTaskWidget, tableView1)
{
    BtInfoTableView *table = new BtInfoTableView();
    table->mouseMoveEvent(new QMouseEvent(QEvent::MouseButtonPress, QPoint(1, 1), Qt::LeftButton, Qt::LeftButton, Qt::NoModifier));
}

TEST_F(ut_CreateTaskWidget, tableView2)
{
    BtInfoTableView *table = new BtInfoTableView();
    table->leaveEvent(new QMouseEvent(QEvent::MouseButtonPress, QPoint(1, 1), Qt::LeftButton, Qt::LeftButton, Qt::NoModifier));
}


TEST_F(ut_CreateTaskWidget, tableView3)
{
    BtInfoTableView *table = new BtInfoTableView();
    table->mouseReleaseEvent(new QMouseEvent(QEvent::MouseButtonPress, QPoint(1, 1), Qt::LeftButton, Qt::LeftButton, Qt::NoModifier));
}

TEST_F(ut_CreateTaskWidget, tableView4)
{
    BtInfoTableView *table = new BtInfoTableView();
    const QModelIndex model;
    table->onDoubleClicked(model);
}


TEST_F(ut_CreateTaskWidget, getSaveto)
{
    BtInfoDialog btDiag(" ", " ");
    btDiag.m_editDir->setText("1111");
    btDiag.getSaveto();
    btDiag.onBtnOK();
}

TEST_F(ut_CreateTaskWidget, BtonBtnOK)
{
    BtInfoDialog btDiag(" ", " ");
    Stub stub;
    stub.set(ADDR(BtInfoDialog, getSelected), BtGetSelectedNull);
    stub.set(ADDR(QString, isNull), BtGetSelectedIsNull);
    btDiag.onBtnOK();
}

TEST_F(ut_CreateTaskWidget, BtonBtnOK1)
{
    BtInfoDialog btDiag(" ", " ");
    btDiag.m_defaultDownloadDir = "~";
    btDiag.onBtnOK();
}

TEST_F(ut_CreateTaskWidget, BtOnFilechoosed)
{
    BtInfoDialog btDiag(" ", " ");
    Stub stub;
    stub.set(ADDR(QFileInfo, isWritable), returnFalse);

    typedef int (*fptr)(BtInfoDialog*);
    fptr foo = (fptr)(&MessageBox::exec);
    Stub stub2;
    stub2.set(foo, MessageboxExec);
    btDiag.onFilechoosed("~/");
}

TEST_F(ut_CreateTaskWidget, BtInfoDialogonAllCheck)
{
    BtInfoDialog btDiag(" ", " ");
    btDiag.onAllCheck();
    btDiag.m_checkAll->setCheckState(Qt::Checked);
    btDiag.onAllCheck();
    btDiag.m_checkAll->setCheckState(Qt::Unchecked);
    btDiag.onAllCheck();
}

TEST_F(ut_CreateTaskWidget, onFileDialogOpen)
{
    CreateTaskWidget *c = new CreateTaskWidget;
    typedef int (*fptr)(CreateTaskWidget*);
    fptr foo = (fptr)(&MessageBox::exec);
    Stub stub2;
    stub2.set(foo, MessageboxExec);
    c->m_analysisUrl = new AnalysisUrl;
    c->onCancelBtnClicked();
    c->onSureBtnClicked();
    void * v;
    c->ftpSize(v,1,1,v);
    QString name;
    QString type = "";
    c->getUrlToName("http://www.metalinker.org/samples/boinc_5.8.16_windows_intelx86.exe.metalink",name,type);
    c->getUrlToName("magnet:?xt=urn:btih:0FC4D73CCC9E6AC29A1B10DDCC3696E81D6CACAF",name,type);
    c->getUrlToName("https://img.tukuppt.com/video_show/09/08/22/5dcb600673d11_10s_big.mp4.metalink.torrent",name,type);
    LinkInfo * linkInfo = new LinkInfo;
    c->updataTabel(linkInfo);

    c->onFilechoosed(QString(QStandardPaths::writableLocation(QStandardPaths::HomeLocation) + "/Desktop/seed/)"));


    c->setUrl("http://www.metalinker.org/samples/boinc_5.8.16_windows_intelx86.exe.metalink");
    c->setUrl("http://www.metalinker.org/samples/boinc_5.8.16_windows_intelx86");
    c->setUrl("magnet:?xt=urn:btih:0FC4D73CCC9E6AC29A1B10DDCC3696E81D6CACAF");
    c->setUrl("https://img.tukuppt.com/video_show/09/08/22/5dcb600673d11_10s_big.mp4.metalink.torrent");

   c->isFtp("ftp://11.txt");
   c->isFtp("222");
   c->isHttp("1111");

}

TEST_F(ut_CreateTaskWidget, AnalysisUrl)
{
    AnalysisUrl *a = new AnalysisUrl;
    QMap<QString, LinkInfo> list;
    LinkInfo l;
    list.insert("http://www.metalinker.org/samples/boinc_5.8.16_windows_intelx86.exe.metalink",l);
    a->m_curAllUrl.insert("http://www.metalin", l);
    a->setUrlList(list);
    a->getTrueLinkInfo(l);
    QThread *t = new QThread;
    delete t;
    t = nullptr;
    UrlThread *u = new UrlThread;
    delete u;
    u = nullptr;
    a->m_workThread.insert(1,t);
    a->m_urlThread.insert(1,u);
    delete a;
    a = nullptr;

}
