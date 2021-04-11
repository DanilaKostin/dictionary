#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QFile"
#include "QTextStream"
#include "QDebug"
#include "QMapIterator"
#include "QPair"
#include "QVector"
static QString str;
static QMap<QString, QVector<QString>> dict;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    load(":/mueller.dict", &dict);
    ui->setupUi(this);
    ui->cur_dict->setText("Mueller.dict (Стандартный словарь)");
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_okey_clicked()
{
    QString pattern = ui->pattern->text();
    ui->list_pattern->clear();
    int begin = 0, end = 0, j = 0;
    QString orig;
    for (int i = 0; i < pattern.length(); i++)
    {
        if (pattern[i] == '^' && i ==0)
        {
            begin = 1;
            continue;
        }
        if (pattern[i] == '$' && i == pattern.length()-1)
        {
            end = 1;
            continue;
        }
        orig[j] = pattern[i];
        j++;
    }
    QMap <QString, QVector<QString>>::iterator it = dict.begin();
    while(it != dict.end())
    {
        QString filter = it.key();
        if (begin == 0 && end == 0)
        {
            if (filter.contains(orig))
                ui->list_pattern->addItem(filter);
        }
        if (begin == 1 && end == 0)
        {
            if (filter.contains(orig) && filter.indexOf(orig) == 0)
                ui->list_pattern->addItem(filter);
        }
        if (begin == 0 && end == 1)
        {
            if (filter.contains(orig) && filter.indexOf(orig) == filter.length()-orig.length())
                ui->list_pattern->addItem(filter);
        }
        if (begin == 1 && end == 1)
        {
            if (filter.contains(orig) && filter.length()==orig.length())
                ui->list_pattern->addItem(filter);
        }

        it++;
    }
}



void MainWindow::on_load_clicked()
{
    str = QFileDialog::getOpenFileName(0, "Загрузить словарь", "", "*.dict");
    QString name = load(str, &dict);
    ui->cur_dict->setText(name);
    ui->display->clear();
    ui->list_pattern->clear();
    /*
    QFile dictionary(str);
    QTextStream infile(&dictionary);
    dictionary.open(QIODevice::ReadOnly);
    QString kluch =infile.readLine();
    QString resive;
    while (!infile.atEnd())
    {
        int line = 0;
        QVector<QString> copy;
        copy.insert(0, "");
        dict.insert(kluch, copy);
        auto t = dict.find(kluch);
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
    }*/
}

void MainWindow::on_list_pattern_itemDoubleClicked(QListWidgetItem *item)
{
    ui->display->clear();
    auto  t = dict.find(item->text());

    for ( auto k : t.value())
    {
        ui->display->append(k);

    }
}

void MainWindow::on_reset_clicked()
{
    ui->list_pattern->clear();
    ui->display->clear();
    load(":/mueller.dict", &dict);
    ui->cur_dict->setText("Mueller.dict (Стандартный словарь)");
}
