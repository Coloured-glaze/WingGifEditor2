/*==============================================================================
** Copyright (C) 2024-2027 WingSummer
**
** This program is free software: you can redistribute it and/or modify it under
** the terms of the GNU Affero General Public License as published by the Free
** Software Foundation, version 3.
**
** This program is distributed in the hope that it will be useful, but WITHOUT
** ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
** FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for more
** details.
**
** You should have received a copy of the GNU Affero General Public License
** along with this program. If not, see <https://www.gnu.org/licenses/>.
** =============================================================================
*/

#include "confirmdialog.h"
#include <QDialogButtonBox>
#include <QLabel>
#include <QVBoxLayout>

ConfirmDialog::ConfirmDialog(const QString &currentFile, const QString &newFile, QWidget *parent)
    : FramelessDialogBase(parent) {
    setWindowTitle(tr("Confirm"));

    auto layout = new QVBoxLayout(this);

    // 创建消息文本
    QString message = tr("You have already opened a GIF file:\n%1\n\n"
                        "Do you want to open the new file?\n%2")
                        .arg(currentFile, newFile);
    
    auto label = new QLabel(message, this);
    label->setWordWrap(true);
    layout->addWidget(label);

    // 添加"不再询问"复选框
    dontAskAgainCheckBox = new QCheckBox(tr("Don't ask again"), this);
    layout->addWidget(dontAskAgainCheckBox);

    // 添加按钮
    auto buttonBox = new QDialogButtonBox(
        QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
        this);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &ConfirmDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &ConfirmDialog::reject);
    layout->addWidget(buttonBox);

    setLayout(layout);
    
    // 设置对话框的最小大小
    setMinimumSize(400, 200);
    resize(450, 250);
}

bool ConfirmDialog::isDontAskAgainChecked() const {
    return dontAskAgainCheckBox->isChecked();
}