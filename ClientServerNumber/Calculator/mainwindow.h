#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QRegExp>
#include <QRegularExpressionValidator>
#include <QMessageBox>
#include "../ClientServerNumbers/FormulaManager.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_formulaCalculatePB_clicked();

    void on_setAccuracyPB_clicked();

    void on_periodNumberPB_clicked();

    void on_openBracketPB_clicked();

    void on_closeBracketPB_clicked();

    void on_dividePB_clicked();

    void on_multiplicationPB_clicked();

    void on_minusPB_clicked();

    void on_plusPB_clicked();

    void on_zerroPB_clicked();

    void on_onePB_clicked();

    void on_twoPB_clicked();

    void on_threePB_clicked();

    void on_fourPB_clicked();

    void on_fivePB_clicked();

    void on_sixPB_clicked();

    void on_sevenPB_clicked();

    void on_eightPB_clicked();

    void on_ninePB_clicked();

    void on_clearFormulaElementPB_clicked();

    void on_clearFormulaPB_clicked();

    void on_formulaCalculatePB_pressed();

    void on_clearLogPB_clicked();

private:
    Ui::MainWindow *ui;

    FormulaManager _formulaManager;

    void addToFormula(QString formulaElement);
    void showMessageBox(QString message);
    void setEnableAllPBsExceptClearLogAndClearFormulaPB(bool enabled);
    void setAccuracyResultForFormula(QString formula, QString formulaResult);
};
#endif // MAINWINDOW_H
