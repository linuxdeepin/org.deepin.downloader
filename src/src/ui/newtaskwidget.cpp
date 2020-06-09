/**
 * @copyright 2020-2020 Uniontech Technology Co., Ltd.
 *
 * @file newtaskwidget.cpp
 *
 * @brief 新建任务类
 *
 * @date 2020-06-09 10:52
 *
 * Author: bulongwei  <bulongwei@uniontech.com>
 *
 * Maintainer: bulongwei  <bulongwei@uniontech.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "newtaskwidget.h"
#include "btinfodialog.h"
#include <QHBoxLayout>
#include <QSizePolicy>
#include <QDropEvent>
#include <QMimeData>
#include <QDebug>
#include <QStandardPaths>

newTaskWidget::newTaskWidget(DDialog *parent):
    DDialog(parent)
{
    m_savePath = Settings::getInstance()->getDownloadSavePath();
    initUi();

}

newTaskWidget::~newTaskWidget()
{

}

void newTaskWidget::initUi()
{
    setCloseButtonVisible(true);
    setAcceptDrops(true);

    QIcon tryIcon=QIcon(QIcon::fromTheme(":/icons/icon/downloader2.svg"))  ;
    this->setIcon(tryIcon);
    this->setWindowFlags(this->windowFlags()&~Qt::WindowMinMaxButtonsHint);
    this->setTitle(tr("New Task"));

    QString _msg = tr("When adding download links, please enter one URL in each line");
    this->addSpacing(15);
    DLabel * _msgLab= new DLabel(this);
    _msgLab->setText(_msg);
    this->addContent(_msgLab,Qt::AlignHCenter);
    this->addSpacing(15);
    m_texturl= new DTextEdit(this);

    m_texturl->setReadOnly(false);
    m_texturl->setAcceptDrops(false);
    m_texturl->setPlaceholderText(tr("Enter download links or drag torrent file here"));
    m_texturl->setFixedSize(QSize(454,154));
    QPalette _pal;
    _pal.setColor(QPalette::Base, QColor(0,0,0,20));
    m_texturl->setPalette(_pal);
    this->addContent(m_texturl);
    this->addSpacing(15);


    QWidget *_boxBtn= new QWidget(this);
    QHBoxLayout *layout=new QHBoxLayout(_boxBtn);
    layout->setMargin(0);
    layout->setContentsMargins(0,0,10,0);
    DIconButton *_iconBtn= new DIconButton(_boxBtn);
    QIcon _tryIcon=QIcon(QIcon::fromTheme("dcc_bt"));
    _iconBtn->setIcon(_tryIcon);
    _iconBtn->setIconSize(QSize(18,15));
    _iconBtn->setFixedSize(QSize(40,35));
    connect(_iconBtn,&DIconButton::clicked,this,&newTaskWidget::openfileDialog);
    layout->addWidget(_iconBtn);

    QWidget *_rightBox= new QWidget(_boxBtn);
    QHBoxLayout *layout_right=new QHBoxLayout(_rightBox);
    layout->setSpacing(10);
    layout_right->setContentsMargins(0,0,0,0);

    DPushButton *cancel_button = new DPushButton(_boxBtn);
    QSizePolicy _policy;
    _policy = cancel_button->sizePolicy();
    _policy.setHorizontalPolicy(QSizePolicy::Expanding);
    cancel_button->setSizePolicy(_policy);
    cancel_button->setText(tr("Cancel"));
    connect(cancel_button,&DPushButton::clicked,this,&newTaskWidget::onCancelBtnClicked);
    layout_right->addWidget(cancel_button);



    DSuggestButton *sure_button = new DSuggestButton(_boxBtn);
    sure_button->setText(tr("Confirm"));
    _policy = sure_button->sizePolicy();
    _policy.setHorizontalPolicy(QSizePolicy::Expanding);
    sure_button->setSizePolicy(_policy);
    connect(sure_button,&DPushButton::clicked,this,&newTaskWidget::onSureBtnClicked);
    layout_right->addSpacing(20);
    layout_right->addWidget(sure_button);
    layout->addWidget(_rightBox);
    this->addContent(_boxBtn);
}


void newTaskWidget::openfileDialog()
{
    QString _btFile = DFileDialog::getOpenFileName(this, tr("Choose Torrent File"), QDir::homePath(), "*.torrent");
    if(_btFile != "") {
        BtInfoDialog *_dialog = new BtInfoDialog(_btFile,m_savePath);//torrent文件路径
        if(_dialog->exec() == QDialog::Accepted) {
            QMap<QString,QVariant> opt;
            QString _infoName;
            QString _infoHash;
            _dialog->getBtInfo(opt, _infoName, _infoHash);
            emit newDownLoadTorrent(_btFile,opt,_infoName,_infoHash);
            this->close();
        }
        delete _dialog;
    }
}

void newTaskWidget::onCancelBtnClicked()
{
    this->close();
}

void newTaskWidget::onSureBtnClicked()
{
    QString _strUrl = m_texturl->toPlainText();
    if(_strUrl.isEmpty())
    {
        qDebug()<<"url is NUll";
        return;
    }

    emit NewDownload_sig(_strUrl,m_savePath);
    this->close();
}

void newTaskWidget::dragEnterEvent(QDragEnterEvent *event)
{
    if(event->mimeData()->hasUrls()) //数据中是否包含URL
    {
        event->acceptProposedAction(); //如果是则接受动作
    }
    else
        event->ignore();
}


void newTaskWidget::dropEvent(QDropEvent *event)
{

    const QMimeData *mineData=event->mimeData();//获取MIME数据
    if(mineData->hasUrls())                     //如数据中包含URL
    {
        QList<QUrl>urlList=mineData->urls();    //获取URL列表
        if(urlList.isEmpty())return ;
        QString fileName;
        for(int i=0;i<urlList.size();++i)
        {
            fileName=urlList.at(i).toString();


        if(fileName.isEmpty())return;

        if(!fileName.isEmpty())                 //若文件路径不为空
        {
            if(fileName.startsWith("file:")&&fileName.endsWith(".torrent"))
            {
                fileName=fileName.right(fileName.length()-6);

                BtInfoDialog *_dialog = new BtInfoDialog(fileName,m_savePath);//torrent文件路径
                int ret = _dialog->exec();
                if(ret == QDialog::Accepted) {
                    QMap<QString,QVariant> opt;
                    QString _infoName;
                    QString _infoHash;
                    _dialog->getBtInfo(opt, _infoName, _infoHash);
                    emit newDownLoadTorrent(fileName,opt,_infoName,_infoHash);
                    this->close();
                }
                delete _dialog;
             }
            else
            {
                 //textBrowser->append(fileName);
            }
        }
       }
    }
}

void newTaskWidget::setUrl(QString url)
{
    m_texturl->clear();
    m_texturl->setText(url);
}
