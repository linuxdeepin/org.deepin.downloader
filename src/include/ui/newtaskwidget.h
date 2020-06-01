/**
* @file newtaskwidget.h
* @brief 新建任务类
* @author bulongwei  <bulongwei@uniontech.com>
* @version 1.0.0
* @date 2020-06-01 16:01
* @copyright 2020-2020 Uniontech Technology Co., Ltd.
*/

#ifndef NEWTASKWIDGET_H
#define NEWTASKWIDGET_H

#include <DMainWindow>
#include <QObject>
#include <DPushButton>
#include <DDialog>
#include <DLabel>
#include <DTextEdit>
#include <QHBoxLayout>
#include <DSuggestButton>
#include <DFileDialog>
#include <QSizePolicy>
#include <QDropEvent>
#include <QMimeData>
#include "btinfodialog.h"
#include "settings.h"

DWIDGET_USE_NAMESPACE

class  newTaskWidget :public DDialog
{
    Q_OBJECT
public:
    explicit newTaskWidget(DDialog *parent=0);
    ~newTaskWidget();

    void setUrl(QString url);
private:
    /**
     * @brief 初始化ui
     */
    void initUi();

private slots:
    /**
     * @brief 打开选择文件窗口按钮
     */
    void openfileDialog();
    /**
     * @brief 关闭窗口按钮
     */
    void onCancelBtnClicked();
    /**
     * @brief 确定下载按钮
     */
    void onSureBtnClicked();
protected:
    /**
     * @brief 拖拽处理函数
     * @param event 拖拽事件
    */
    void dragEnterEvent(QDragEnterEvent *event);
    /**
     * @brief 拖拽释放处理函数
     * @param event 拖拽事件
    */
    void dropEvent(QDropEvent *event);

signals:
    void NewDownload_sig(QString url,QString save_path);
    void newDownLoadTorrent(QString btPath,QMap<QString,QVariant> opt,QString infoName, QString infoHash);

private:
    QString m_savePath;                 //当前保存文件路径

    DTextEdit *m_texturl;               //url文本框

};


#endif // NEWTASKWIDGET_H
