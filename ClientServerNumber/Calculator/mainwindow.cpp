#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    _formulaManager = FormulaManager();

    QColor c = QColor::fromRgb(240, 240, 240);
    QPalette p = ui->formulaTE->palette(); // define pallete for textEdit..
    p.setColor(QPalette::Base, c); // set color "Red" for textedit base
    p.setColor(QPalette::Text, Qt::black); // set text color which is selected from color pallete
    ui->formulaTE->setPalette(p);
    ui->logTE->setPalette(p);
    QPixmap pixmap("../Calculator/src/deletePicture.png");
    QIcon ButtonIcon(pixmap);
    ui->clearFormulaElementPB->setIcon(ButtonIcon);
    ui->clearFormulaElementPB->setIconSize(pixmap.rect().size());

    ui->accuracyLE->setVisible(false);
    ui->accuracyLE->setText("");
    ui->setAccuracyPB->setEnabled(false);

    ui->periodNumberLE->setVisible(false);
    ui->periodNumberLE->setText("");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_formulaCalculatePB_clicked()
{
    // Заблокируем кнопку Вычислить.
    ui->formulaCalculatePB->setEnabled(false);
    if(_formulaManager.HasFormula()){
        int accuracy = ui->accuracyLE->text().toInt();
        try{
            QString recalculateResult = QString::fromStdString(_formulaManager.GetIncreasedAccuracyResult(accuracy));
            QString formula = ui->formulaTE->toPlainText().split("=")[0];
            recalculateResult = recalculateResult.mid(0,recalculateResult.indexOf("Accuracy"));
            ui->formulaTE->setText(formula + " = " + recalculateResult);
            setAccuracyResultForFormula(formula, recalculateResult);
        }
        catch(const char* str){
            QString exceptionMessage = QString(str);
            showMessageBox("При вычислении формулы возникли ошибки: " + exceptionMessage);
            return;
        }
    }
    else{
        try{      
            QString formula = ui->formulaTE->toPlainText();
            QString result = QString::fromStdString(_formulaManager.Calculate(formula.toStdString()));
            result = result.mid(0,result.indexOf("Accuracy"));
            addToFormula(" = " + result);
            setAccuracyResultForFormula(formula, result);
        }
        catch(const char* str){
            QString exceptionMessage = QString(str);
            showMessageBox("При вычислении формулы возникли ошибки: " + exceptionMessage);
            return;
        }
    }

    _formulaManager.PrintTreeResult();
    // После вычисления разблокируем кнопку установления точности.
    ui->setAccuracyPB->setEnabled(true);
}

void MainWindow::on_setAccuracyPB_clicked()
{
    if(ui->setAccuracyPB->text() == "Установить точность"){
        ui->setAccuracyPB->setText("Подтвердить");
        ui->accuracyLE->setText("");
        ui->accuracyLE->setVisible(true);
    }
    else{
        ui->setAccuracyPB->setText("Установить точность");
        ui->accuracyLE->setVisible(false);
        ui->setAccuracyResultL->setText("Установленная точность: " + ui->accuracyLE->text());

        ui->formulaCalculatePB->setEnabled(true);
        //ui->accuracyLE->setText("");
    }
}

void MainWindow::on_periodNumberPB_clicked()
{
    if(ui->periodNumberPB->text() == "Задать в виде: a,b(c)"){
        ui->periodNumberPB->setText("Подтвердить");
        ui->periodNumberLE->setText("");
        ui->periodNumberLE->setVisible(true);
    }
    else{
        QRegExp correctPeriodNumber = QRegExp("^[0-9]+[,.]([0-9]+\\([0-9]+\\)|\\([0-9]+\\))$");
        if(!correctPeriodNumber.exactMatch(ui->periodNumberLE->text())){
            showMessageBox("Введенное периодическое число имеет некорректный формат!");
            return;
        }

        ui->periodNumberPB->setText("Задать в виде: a,b(c)");
        ui->periodNumberLE->setVisible(false);
        addToFormula(ui->periodNumberLE->text());
        ui->periodNumberLE->setText("");
    }
}

void MainWindow::addToFormula(QString additionToFormula)
{
    QString currentFormula = ui->formulaTE->toPlainText();
    ui->formulaTE->setText(currentFormula + additionToFormula);
}

void MainWindow::showMessageBox(QString message)
{
    QMessageBox msgBox;
    msgBox.setText(message);
    msgBox.exec();
}

void MainWindow::setEnableAllPBsExceptClearLogAndClearFormulaPB(bool enabled)
{
    // Меняем доступность всех цифр.
    ui->zerroPB->setEnabled(enabled);
    ui->onePB->setEnabled(enabled);
    ui->twoPB->setEnabled(enabled);
    ui->threePB->setEnabled(enabled);
    ui->fourPB->setEnabled(enabled);
    ui->fivePB->setEnabled(enabled);
    ui->sixPB->setEnabled(enabled);
    ui->sevenPB->setEnabled(enabled);
    ui->eightPB->setEnabled(enabled);
    ui->ninePB->setEnabled(enabled);
    // Меняем доступность всех арифметических операций.
    ui->openBracketPB->setEnabled(enabled);
    ui->closeBracketPB->setEnabled(enabled);
    ui->dividePB->setEnabled(enabled);
    ui->multiplicationPB->setEnabled(enabled);
    ui->minusPB->setEnabled(enabled);
    ui->plusPB->setEnabled(enabled);
    ui->changeSignPB->setEnabled(enabled);
    // Меняем доступность всех дополнительных кнопок.
    ui->clearFormulaElementPB->setEnabled(enabled);
    ui->setAccuracyPB->setEnabled(enabled);
   // ui->formulaCalculatePB->setEnabled(enabled);
    ui->periodNumberPB->setEnabled(enabled);
}

void MainWindow::setAccuracyResultForFormula(QString formula, QString formulaResult)
{
    int realAccuracyResult = _formulaManager.GetRealAccuracyResult();
    QString setUserAccuracy = ui->accuracyLE->text();
    if(setUserAccuracy.trimmed() != ""){
        if(realAccuracyResult > setUserAccuracy.toInt()){
            showMessageBox("Для данного выражения не удалось достигнуть заданной точности: " + setUserAccuracy + " . Но удалось достигнуть большей точности.");
        }
    }
    auto accuracyString = QString::fromStdString(to_string(realAccuracyResult));
    ui->accuracyResultL->setText("Получившаяся точность результата: " + accuracyString);
    QString previousLog = ui->logTE->toPlainText();
    formulaResult = formulaResult.mid(0,formulaResult.indexOf("Accuracy"));
    ui->logTE->setText(previousLog + "\n" + formula + " = " + formulaResult + "\nТочность " + accuracyString + "\n");
}

void MainWindow::on_openBracketPB_clicked()
{
    addToFormula(" ( ");
}

void MainWindow::on_closeBracketPB_clicked()
{
    addToFormula(" ) ");
}

void MainWindow::on_dividePB_clicked()
{
    addToFormula(" / ");
}

void MainWindow::on_multiplicationPB_clicked()
{
    addToFormula(" * ");
}

void MainWindow::on_minusPB_clicked()
{
    addToFormula(" - ");
}

void MainWindow::on_plusPB_clicked()
{
    addToFormula(" + ");
}

void MainWindow::on_zerroPB_clicked()
{
    addToFormula("0");
}

void MainWindow::on_onePB_clicked()
{
    addToFormula("1");
}

void MainWindow::on_twoPB_clicked()
{
    addToFormula("2");
}

void MainWindow::on_threePB_clicked()
{
    addToFormula("3");
}

void MainWindow::on_fourPB_clicked()
{
    addToFormula("4");
}

void MainWindow::on_fivePB_clicked()
{
    addToFormula("5");
}

void MainWindow::on_sixPB_clicked()
{
    addToFormula("6");
}

void MainWindow::on_sevenPB_clicked()
{
    addToFormula("7");
}

void MainWindow::on_eightPB_clicked()
{
    addToFormula("8");
}

void MainWindow::on_ninePB_clicked()
{
    addToFormula("9");
}

void MainWindow::on_clearFormulaElementPB_clicked()
{
    QString currentFormula = ui->formulaTE->toPlainText();
    int countClearedSymbols = 1;
    if(currentFormula[currentFormula.length() - 1] == ' '){
        countClearedSymbols++;
    }
    ui->formulaTE->setText(currentFormula.mid(0, currentFormula.length() - countClearedSymbols));
}

void MainWindow::on_clearFormulaPB_clicked()
{
    ui->formulaTE->setText("");
    ui->setAccuracyResultL->setText("");
    ui->accuracyResultL->setText("");
    // Разблокируем все кнопки, кроме установить точность.
    ui->formulaCalculatePB->setEnabled(true);
    setEnableAllPBsExceptClearLogAndClearFormulaPB(true);
    ui->setAccuracyPB->setEnabled(false);
    _formulaManager = FormulaManager();
}

void MainWindow::on_formulaCalculatePB_pressed()
{
    // На время вычислений блокируем все кнопки, кроме стереть формулу и очистить журнал.
    setEnableAllPBsExceptClearLogAndClearFormulaPB(false);
}

void MainWindow::on_clearLogPB_clicked()
{
    ui->logTE->setText("");
}
