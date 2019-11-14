/*
 * Copyright (C) 2019 ~ 2019 Deepin Technology Co., Ltd.
 *
 * Author:     liurui <liurui_cm@deepin.com>
 *
 * Maintainer: liurui <liurui_cm@deepin.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef INSTALLDRIVERWINDOW_H
#define INSTALLDRIVERWINDOW_H
#include "zdevicemanager.h"

#include <DMainWindow>
DWIDGET_USE_NAMESPACE
DWIDGET_BEGIN_NAMESPACE
class DIconButton;
class DSpinner;
class DListView;
class DLineEdit;
class DSpinner;
DWIDGET_END_NAMESPACE

QT_BEGIN_NAMESPACE
class QLineEdit;
class QComboBox;
class QPushButton;
class QWidget;
class QLabel;
class QStandardItemModel;
class QStackedWidget;
QT_END_NAMESPACE
class InstallDriverWindow : public DMainWindow
{
    Q_OBJECT
public:
    explicit InstallDriverWindow(QWidget *parent = nullptr);
    virtual ~InstallDriverWindow() override;

    /**
    * @projectName   Printer
    * @brief         传入设备信息
    * @author        liurui
    * @date          2019-10-26
    */
    void setDeviceInfo(const TDeviceInfo &device);
    /**
    * @projectName   Printer
    * @brief         传入上级窗口指针.方便返回上级窗口
    * @author        liurui
    * @date          2019-10-28
    */
    void setPreWidget(QWidget *parent);
private:
    void initUI();
    void initConnections();
    void initMakerAndType();
    /**
    * @projectName   Printer
    * @brief         重复打开时清空用户输入的信息
    * @author        liurui
    * @date          2019-11-05
    */
    void clearUserInfo();
protected:
    void showEvent(QShowEvent *event) override;
    /**
    * @projectName   Printer
    * @brief         事件过滤，监控外部的文件拖拽事件
    * @author        liurui
    * @date          2019-10-28
    */
    bool eventFilter(QObject *watched, QEvent *event) override;
private slots:
    // 响应左侧tab列表切换
    void tabCurrentIndexChanged();
    /**
    * @projectName   Printer
    * @brief         厂商下拉框切换
    * @author        liurui
    * @date          2019-10-26
    */
    void currentMakerChangedSlot(const QString &maker);
    /**
    * @projectName   Printer
    * @brief         型号下拉框切换
    * @author        liurui
    * @date          2019-10-26
    */
    void currentModelChangedSlot(const QString &model);
    // 从文件选择PPD文件
    void getPPDFileFromLocalSlot();
    /**
    * @projectName   Printer
    * @brief         安装驱动
    * @author        liurui
    * @date          2019-10-26
    */
    void installDriverSlot();
    /**
    * @projectName   Printer
    * @brief         通过厂商型号查找驱动
    * @author        liurui
    * @date          2019-10-26
    */
    void searchDriverSlot();
    /**
    * @projectName   Printer
    * @brief         获取驱动查找结果
    * @author        liurui
    * @date          2019-10-26
    */
    void driverSearchedSlot();
    // 响应本地驱动初始化完成
    void driverReflushSlot(int id, int iState);

signals:
    void updatePrinterList();
private:
    // 左侧选项列表
    DListView *m_pTabListView;
    QStandardItemModel *m_pTabListModel;

    QLabel *m_pRightTitleLabel;
    // 本地驱动
    QComboBox *m_pManufacturerCombo;
    QComboBox *m_pTypeCombo;
    QComboBox *m_pDriverCombo;
    // 本地PPD
    QLabel *m_pPPDPath;
    QPushButton *m_pSelectPPDBtn;

    // 设置打印信息搜索
    QLineEdit *m_pManuAndTypeLineEdit;
    QPushButton *m_pSearchBtn;
    QComboBox *m_pDriverManualCombo;
    // 安装驱动
    QPushButton *m_pInstallBtn;
    DSpinner *m_pSpinner;
    // 切换打印机
    QStackedWidget *m_pStackWidget;
    // 返回上级按钮
    DIconButton *m_pPreBtn;
    // 上级界面
    QWidget *m_pParentWidget;

private:
    TDeviceInfo m_device;
};

#endif // INSTALLDRIVERWINDOW_H
