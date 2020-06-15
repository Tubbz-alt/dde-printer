/*
 * Copyright (C) 2019 ~ 2020 Uniontech Software Co., Ltd.
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
#include "renameprinterwindow.h"

#include <DPushButton>
#include <DTitlebar>
#include <DLineEdit>
#include <DWidgetUtil>

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QCloseEvent>

RenamePrinterWindow::RenamePrinterWindow(QWidget *parent)
    : DMainWindow(parent)
    , m_ret(0)
{
    initUI();
    initConnections();
}

RenamePrinterWindow::~RenamePrinterWindow()
{
}

int RenamePrinterWindow::result()
{
    return m_ret;
}

QString RenamePrinterWindow::getName()
{
    return m_pNameEdit->text();
}

void RenamePrinterWindow::setName(const QString &name)
{
    m_pNameEdit->setText(name);
}

QString RenamePrinterWindow::getLocation()
{
    return m_pLocationEdit->text();
}

void RenamePrinterWindow::setLocation(const QString &location)
{
    m_pLocationEdit->setText(location);
}

QString RenamePrinterWindow::getDescription()
{
    return m_pDescriptionEdit->text();
}

void RenamePrinterWindow::setDescription(const QString &description)
{
    m_pDescriptionEdit->setText(description);
}

void RenamePrinterWindow::initUI()
{
    titlebar()->setMenuVisible(false);
    titlebar()->setTitle(tr("Rename Printer"));
    titlebar()->setIcon(QIcon(":/images/dde-printer.svg"));
    // 去掉最大最小按钮
    setWindowFlags(windowFlags() & ~Qt::WindowMinMaxButtonsHint);
    setWindowModality(Qt::ApplicationModal);
    resize(380, 270);

    QLabel *pNameLabel = new QLabel(tr("Name"));
    m_pNameEdit = new DLineEdit();
    QLabel *pLocationLabel = new QLabel(tr("Location"));
    m_pLocationEdit = new DLineEdit();
    QLabel *pDescriptionLabel = new QLabel(tr("Description"));
    m_pDescriptionEdit = new DLineEdit();

    QGridLayout *pGridLayout = new QGridLayout();
    pGridLayout->addWidget(pNameLabel, 0, 0);
    pGridLayout->addWidget(m_pNameEdit, 0, 1);
    pGridLayout->addWidget(pLocationLabel, 1, 0);
    pGridLayout->addWidget(m_pLocationEdit, 1, 1);
    pGridLayout->addWidget(pDescriptionLabel, 2, 0);
    pGridLayout->addWidget(m_pDescriptionEdit, 2, 1);

    m_pCancelBtn = new DPushButton(tr("Cancel"));
    m_pOKBtn = new DPushButton(tr("Confirm"));
    QHBoxLayout *pHLayout = new QHBoxLayout();
    pHLayout->addWidget(m_pCancelBtn);
    pHLayout->addWidget(m_pOKBtn);

    QVBoxLayout *pMainLayout = new QVBoxLayout();
    pMainLayout->addLayout(pGridLayout);
    pMainLayout->addLayout(pHLayout);

    QWidget *widget = new QWidget();
    widget->setLayout(pMainLayout);
    takeCentralWidget();
    setCentralWidget(widget);

    Dtk::Widget::moveToCenter(this);
}

void RenamePrinterWindow::initConnections()
{
    connect(m_pCancelBtn, &DPushButton::clicked, this, &RenamePrinterWindow::btnClickedSlot);
    connect(m_pOKBtn, &DPushButton::clicked, this, &RenamePrinterWindow::btnClickedSlot);
}

void RenamePrinterWindow::btnClickedSlot()
{
    if (sender() == m_pCancelBtn) {
        m_ret = 0;
    } else if (sender() == m_pOKBtn) {
        m_ret = 1;
    }
    close();
}

void RenamePrinterWindow::closeEvent(QCloseEvent *event)
{
    emit accepted(m_ret);
    event->accept();
}
