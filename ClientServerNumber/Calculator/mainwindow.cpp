#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "../ClientServerNumbers/FormulaManager.h"

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    auto f = FormulaManager();
    string formula = "(42+(108/5)*12)/3";
    string result = f.Calculate(formula);
    auto qText = QString::fromStdString(result);
    ui->label->setText(ui->label->text() + qText);
}
