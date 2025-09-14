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

#include "exportdialog.h"

#include <QDialogButtonBox>
#include <QDir>
#include <QLabel>
#include <QPushButton>
#include <QShortcut>
#include <QStandardPaths>
#include <QVBoxLayout>

ExportDialog::ExportDialog(QWidget *parent) : FramelessDialogBase(parent) {
    auto widget = new QWidget(this);
    auto layout = new QVBoxLayout(widget);
    layout->addWidget(new QLabel(tr("ChooseFolder"), this));
    layout->addSpacing(3);

    folder = new QPathEdit(this);
    folder->setAllowEmptyPath(false);
    folder->setEditable(false);
    folder->setPathMode(QPathEdit::ExistingFolder);
    QDir dir(
        QStandardPaths::writableLocation(QStandardPaths::PicturesLocation));
    dir.mkdir("WingGifEditor");
    connect(folder, &QPathEdit::pathChanged, folder, &QPathEdit::setToolTip);
    folder->setPath(dir.absolutePath() + "/" + "WingGifEditor");

    layout->addWidget(folder);
    layout->addSpacing(10);

    auto group = new QButtonGroup(this);
    group->setExclusive(true);

    auto btnBox = new QWidget(this);
    auto buttonLayout = new QHBoxLayout(btnBox);
    buttonLayout->setSpacing(0);

    int id = 0;

    auto b = new QPushButton(QStringLiteral("PNG"), this);
    b->setCheckable(true);
    connect(b, &QPushButton::toggled, this, [=](bool b) {
        if (b) {
            res.type = ExportImageType::PNG;
        }
    });
    group->addButton(b, id++);
    buttonLayout->addWidget(b);

    b = new QPushButton(QStringLiteral("JPG"), this);
    b->setCheckable(true);
    connect(b, &QPushButton::toggled, this, [=](bool b) {
        if (b) {
            res.type = ExportImageType::JPG;
        }
    });
    group->addButton(b, id++);
    buttonLayout->addWidget(b);

    b = new QPushButton(QStringLiteral("TIFF"), this);
    b->setCheckable(true);
    connect(b, &QPushButton::toggled, this, [=](bool b) {
        if (b) {
            res.type = ExportImageType::TIFF;
        }
    });
    group->addButton(b, id++);
    buttonLayout->addWidget(b);

    b = new QPushButton(QStringLiteral("WEBP"), this);
    b->setCheckable(true);
    connect(b, &QPushButton::toggled, this, [=](bool b) {
        if (b) {
            res.type = ExportImageType::WEBP;
        }
    });
    group->addButton(b, id++);
    buttonLayout->addWidget(b);

    group->button(0)->setChecked(true);
    layout->addWidget(btnBox);
    layout->addSpacing(20);

    auto dbbox = new QDialogButtonBox(
        QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    connect(dbbox, &QDialogButtonBox::accepted, this, &ExportDialog::on_accept);
    connect(dbbox, &QDialogButtonBox::rejected, this, &ExportDialog::on_reject);
    auto key = QKeySequence(Qt::Key_Return);
    auto s = new QShortcut(key, this);
    connect(s, &QShortcut::activated, this, &ExportDialog::on_accept);
    layout->addWidget(dbbox);

    buildUpContent(widget);

    // 设置对话框的最小大小
    setMinimumSize(400, 200);
    resize(450, 250);

    setWindowTitle(tr("Export"));
}

ExportResult ExportDialog::getResult() { return res; }

void ExportDialog::on_accept() {
    res.path = folder->path();
    done(1);
}

void ExportDialog::on_reject() { done(0); }

void ExportDialog::closeEvent(QCloseEvent *event) {
    Q_UNUSED(event);
    done(0);
}
