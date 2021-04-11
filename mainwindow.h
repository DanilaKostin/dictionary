#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "QWidget"
#include "QString"
#include "QDialog"
#include "QFileDialog"
#include "QListWidgetItem"
#include "QFile"
#include "QTextStream"
#include "QDebug"
#include "QMapIterator"
#include "QPair"
#include "QVector"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_okey_clicked();

    void on_load_clicked();

//    void on_list_pattern_itemActivated(QListWidgetItem *item);

    void on_list_pattern_itemDoubleClicked(QListWidgetItem *item);

    void on_reset_clicked();

private:
    Ui::MainWindow *ui;
    QDialog d;
    QString load(QString str, QMap<QString, QVector<QString>> *dict)
    {
        dict->clear();
        QFile dictionary(str);
        QFileInfo fileInfo(dictionary);
        QString namef(fileInfo.fileName());
        QTextStream infile(&dictionary);
        dictionary.open(QIODevice::ReadOnly);
        QString kluch =infile.readLine();
        QString resive;
        while (!infile.atEnd())
        {
            int line = 0;
            QVector<QString> copy;
            copy.insert(0, "");
            dict->insert(kluch, copy);
            auto t = dict->find(kluch);
            QString buf;
            QString translation;
            while (1)
            {
                buf = infile.readLine();

                if (buf.isEmpty())
                {
                    if (line)
                    t->push_back("\n");
                    buf = infile.readLine();
                    line = 1;
                }
                if (buf[0] != ' ')
                {
                    kluch = buf;
                    break;
                }
                QVector<QString> vec = *t;
                vec.push_back(buf);
                *t = vec;
            }
        }
        return namef;
    }

};
#endif // MAINWINDOW_H
