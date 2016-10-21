/*
Copyright (c) 2013, Ronie P. Martinez <ronmarti18@gmail.com>
All rights reserved.

Permission to use, copy, modify, and/or distribute this software for any purpose
with or without fee is hereby granted, provided that the above copyright notice
and this permission notice appear in all copies.

THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH
REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND
FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT,
OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA
OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION,
ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
*/

#ifndef CSVREADER_H
#define CSVREADER_H

#include <QMainWindow>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QDebug>
#include <QString>
#include <QStandardItemModel>

namespace Ui {
class CsvReader;
}

class CsvReader : public QMainWindow
{
    Q_OBJECT

public:
    explicit CsvReader();
    ~CsvReader();

    void readCSV(QString fileName, QStandardItemModel* m = 0);

private:
    void checkString(QString &temp, QStandardItemModel* model, QChar character = 0);

    QList<QStringList> csv;
    QList<QStandardItem*> standardItemList;

};

#endif // CSVREADER_H
