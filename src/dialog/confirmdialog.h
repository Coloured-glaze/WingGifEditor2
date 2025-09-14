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

#ifndef CONFIRMDIALOG_H
#define CONFIRMDIALOG_H

#include "framelessdialogbase.h"
#include <QCheckBox>
#include <QDialogButtonBox>
#include <QLabel>
#include <QVBoxLayout>

class ConfirmDialog : public FramelessDialogBase {
    Q_OBJECT

public:
    explicit ConfirmDialog(const QString &currentFile, const QString &newFile, QWidget *parent = nullptr);
    
    bool isDontAskAgainChecked() const;

private:
    QCheckBox *dontAskAgainCheckBox;
};

#endif // CONFIRMDIALOG_H