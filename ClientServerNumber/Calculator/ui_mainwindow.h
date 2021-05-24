/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.0.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QPushButton *sevenPB;
    QTextEdit *formulaTE;
    QPushButton *eightPB;
    QPushButton *ninePB;
    QPushButton *sixPB;
    QPushButton *fourPB;
    QPushButton *fivePB;
    QPushButton *threePB;
    QPushButton *onePB;
    QPushButton *twoPB;
    QPushButton *zerroPB;
    QPushButton *openBracketPB;
    QPushButton *closeBracketPB;
    QPushButton *clearFormulaElementPB;
    QPushButton *changeSignPB;
    QPushButton *dividePB;
    QPushButton *multiplicationPB;
    QPushButton *minusPB;
    QPushButton *plusPB;
    QPushButton *periodNumberPB;
    QPushButton *formulaCalculatePB;
    QPushButton *setAccuracyPB;
    QLabel *logTitleLabel;
    QTextEdit *logTE;
    QPushButton *clearFormulaPB;
    QPushButton *clearLogPB;
    QLabel *logTitleLabel_2;
    QLabel *setAccuracyResultL;
    QLineEdit *accuracyLE;
    QLineEdit *periodNumberLE;
    QLabel *accuracyResultL;

    void setupUi(QWidget *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 600);
        sevenPB = new QPushButton(MainWindow);
        sevenPB->setObjectName(QString::fromUtf8("sevenPB"));
        sevenPB->setGeometry(QRect(110, 290, 61, 51));
        formulaTE = new QTextEdit(MainWindow);
        formulaTE->setObjectName(QString::fromUtf8("formulaTE"));
        formulaTE->setGeometry(QRect(110, 80, 541, 81));
        formulaTE->setFrameShape(QFrame::StyledPanel);
        formulaTE->setFrameShadow(QFrame::Plain);
        formulaTE->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        formulaTE->setLineWrapColumnOrWidth(1);
        formulaTE->setReadOnly(true);
        eightPB = new QPushButton(MainWindow);
        eightPB->setObjectName(QString::fromUtf8("eightPB"));
        eightPB->setGeometry(QRect(170, 290, 61, 51));
        ninePB = new QPushButton(MainWindow);
        ninePB->setObjectName(QString::fromUtf8("ninePB"));
        ninePB->setGeometry(QRect(230, 290, 61, 51));
        sixPB = new QPushButton(MainWindow);
        sixPB->setObjectName(QString::fromUtf8("sixPB"));
        sixPB->setGeometry(QRect(230, 340, 61, 51));
        fourPB = new QPushButton(MainWindow);
        fourPB->setObjectName(QString::fromUtf8("fourPB"));
        fourPB->setGeometry(QRect(110, 340, 61, 51));
        fivePB = new QPushButton(MainWindow);
        fivePB->setObjectName(QString::fromUtf8("fivePB"));
        fivePB->setGeometry(QRect(170, 340, 61, 51));
        threePB = new QPushButton(MainWindow);
        threePB->setObjectName(QString::fromUtf8("threePB"));
        threePB->setGeometry(QRect(230, 390, 61, 51));
        onePB = new QPushButton(MainWindow);
        onePB->setObjectName(QString::fromUtf8("onePB"));
        onePB->setGeometry(QRect(110, 390, 61, 51));
        twoPB = new QPushButton(MainWindow);
        twoPB->setObjectName(QString::fromUtf8("twoPB"));
        twoPB->setGeometry(QRect(170, 390, 61, 51));
        zerroPB = new QPushButton(MainWindow);
        zerroPB->setObjectName(QString::fromUtf8("zerroPB"));
        zerroPB->setGeometry(QRect(170, 440, 61, 51));
        openBracketPB = new QPushButton(MainWindow);
        openBracketPB->setObjectName(QString::fromUtf8("openBracketPB"));
        openBracketPB->setGeometry(QRect(110, 240, 61, 51));
        openBracketPB->setCursor(QCursor(Qt::ArrowCursor));
        closeBracketPB = new QPushButton(MainWindow);
        closeBracketPB->setObjectName(QString::fromUtf8("closeBracketPB"));
        closeBracketPB->setGeometry(QRect(170, 240, 61, 51));
        closeBracketPB->setCursor(QCursor(Qt::ArrowCursor));
        clearFormulaElementPB = new QPushButton(MainWindow);
        clearFormulaElementPB->setObjectName(QString::fromUtf8("clearFormulaElementPB"));
        clearFormulaElementPB->setGeometry(QRect(230, 240, 61, 51));
        changeSignPB = new QPushButton(MainWindow);
        changeSignPB->setObjectName(QString::fromUtf8("changeSignPB"));
        changeSignPB->setGeometry(QRect(110, 440, 61, 51));
        dividePB = new QPushButton(MainWindow);
        dividePB->setObjectName(QString::fromUtf8("dividePB"));
        dividePB->setGeometry(QRect(290, 240, 61, 51));
        multiplicationPB = new QPushButton(MainWindow);
        multiplicationPB->setObjectName(QString::fromUtf8("multiplicationPB"));
        multiplicationPB->setGeometry(QRect(290, 290, 61, 51));
        minusPB = new QPushButton(MainWindow);
        minusPB->setObjectName(QString::fromUtf8("minusPB"));
        minusPB->setGeometry(QRect(290, 340, 61, 51));
        plusPB = new QPushButton(MainWindow);
        plusPB->setObjectName(QString::fromUtf8("plusPB"));
        plusPB->setGeometry(QRect(290, 390, 61, 51));
        periodNumberPB = new QPushButton(MainWindow);
        periodNumberPB->setObjectName(QString::fromUtf8("periodNumberPB"));
        periodNumberPB->setGeometry(QRect(350, 440, 161, 51));
        formulaCalculatePB = new QPushButton(MainWindow);
        formulaCalculatePB->setObjectName(QString::fromUtf8("formulaCalculatePB"));
        formulaCalculatePB->setGeometry(QRect(230, 440, 121, 51));
        setAccuracyPB = new QPushButton(MainWindow);
        setAccuracyPB->setObjectName(QString::fromUtf8("setAccuracyPB"));
        setAccuracyPB->setGeometry(QRect(350, 340, 161, 51));
        logTitleLabel = new QLabel(MainWindow);
        logTitleLabel->setObjectName(QString::fromUtf8("logTitleLabel"));
        logTitleLabel->setGeometry(QRect(600, 210, 121, 31));
        logTE = new QTextEdit(MainWindow);
        logTE->setObjectName(QString::fromUtf8("logTE"));
        logTE->setGeometry(QRect(540, 240, 251, 241));
        logTE->setReadOnly(true);
        clearFormulaPB = new QPushButton(MainWindow);
        clearFormulaPB->setObjectName(QString::fromUtf8("clearFormulaPB"));
        clearFormulaPB->setGeometry(QRect(350, 240, 161, 51));
        clearLogPB = new QPushButton(MainWindow);
        clearLogPB->setObjectName(QString::fromUtf8("clearLogPB"));
        clearLogPB->setGeometry(QRect(600, 490, 151, 51));
        logTitleLabel_2 = new QLabel(MainWindow);
        logTitleLabel_2->setObjectName(QString::fromUtf8("logTitleLabel_2"));
        logTitleLabel_2->setGeometry(QRect(150, 10, 481, 31));
        QFont font;
        font.setPointSize(14);
        font.setBold(true);
        logTitleLabel_2->setFont(font);
        setAccuracyResultL = new QLabel(MainWindow);
        setAccuracyResultL->setObjectName(QString::fromUtf8("setAccuracyResultL"));
        setAccuracyResultL->setEnabled(true);
        setAccuracyResultL->setGeometry(QRect(110, 170, 231, 21));
        accuracyLE = new QLineEdit(MainWindow);
        accuracyLE->setObjectName(QString::fromUtf8("accuracyLE"));
        accuracyLE->setEnabled(true);
        accuracyLE->setGeometry(QRect(350, 290, 161, 51));
        QFont font1;
        font1.setKerning(false);
        accuracyLE->setFont(font1);
        accuracyLE->setCursor(QCursor(Qt::ArrowCursor));
        accuracyLE->setFocusPolicy(Qt::StrongFocus);
        accuracyLE->setInputMethodHints(Qt::ImhDigitsOnly);
        accuracyLE->setInputMask(QString::fromUtf8(""));
        accuracyLE->setMaxLength(32767);
        accuracyLE->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        accuracyLE->setClearButtonEnabled(true);
        periodNumberLE = new QLineEdit(MainWindow);
        periodNumberLE->setObjectName(QString::fromUtf8("periodNumberLE"));
        periodNumberLE->setEnabled(true);
        periodNumberLE->setGeometry(QRect(350, 390, 161, 51));
        periodNumberLE->setFont(font1);
        periodNumberLE->setCursor(QCursor(Qt::ArrowCursor));
        periodNumberLE->setFocusPolicy(Qt::StrongFocus);
        periodNumberLE->setInputMethodHints(Qt::ImhNone);
        periodNumberLE->setMaxLength(32767);
        periodNumberLE->setAlignment(Qt::AlignCenter);
        periodNumberLE->setClearButtonEnabled(true);
        accuracyResultL = new QLabel(MainWindow);
        accuracyResultL->setObjectName(QString::fromUtf8("accuracyResultL"));
        accuracyResultL->setEnabled(true);
        accuracyResultL->setGeometry(QRect(110, 200, 231, 21));

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QWidget *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        sevenPB->setText(QCoreApplication::translate("MainWindow", "7", nullptr));
        formulaTE->setHtml(QCoreApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:7.8pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p></body></html>", nullptr));
        eightPB->setText(QCoreApplication::translate("MainWindow", "8", nullptr));
        ninePB->setText(QCoreApplication::translate("MainWindow", "9", nullptr));
        sixPB->setText(QCoreApplication::translate("MainWindow", "6", nullptr));
        fourPB->setText(QCoreApplication::translate("MainWindow", "4", nullptr));
        fivePB->setText(QCoreApplication::translate("MainWindow", "5", nullptr));
        threePB->setText(QCoreApplication::translate("MainWindow", "3", nullptr));
        onePB->setText(QCoreApplication::translate("MainWindow", "1", nullptr));
        twoPB->setText(QCoreApplication::translate("MainWindow", "2", nullptr));
        zerroPB->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        openBracketPB->setText(QCoreApplication::translate("MainWindow", "(", nullptr));
        closeBracketPB->setText(QCoreApplication::translate("MainWindow", ")", nullptr));
        clearFormulaElementPB->setText(QString());
        changeSignPB->setText(QCoreApplication::translate("MainWindow", "+/-", nullptr));
        dividePB->setText(QCoreApplication::translate("MainWindow", "/", nullptr));
        multiplicationPB->setText(QCoreApplication::translate("MainWindow", "*", nullptr));
        minusPB->setText(QCoreApplication::translate("MainWindow", "-", nullptr));
        plusPB->setText(QCoreApplication::translate("MainWindow", "+", nullptr));
#if QT_CONFIG(tooltip)
        periodNumberPB->setToolTip(QString());
#endif // QT_CONFIG(tooltip)
        periodNumberPB->setText(QCoreApplication::translate("MainWindow", "\320\227\320\260\320\264\320\260\321\202\321\214 \320\262 \320\262\320\270\320\264\320\265: a,b(c)", nullptr));
        formulaCalculatePB->setText(QCoreApplication::translate("MainWindow", "\320\222\321\213\321\207\320\270\321\201\320\273\320\270\321\202\321\214", nullptr));
        setAccuracyPB->setText(QCoreApplication::translate("MainWindow", "\320\243\321\201\321\202\320\260\320\275\320\276\320\262\320\270\321\202\321\214 \321\202\320\276\321\207\320\275\320\276\321\201\321\202\321\214", nullptr));
        logTitleLabel->setText(QCoreApplication::translate("MainWindow", "\320\226\321\203\321\200\320\275\320\260\320\273 \320\264\320\265\320\271\321\201\321\202\320\262\320\270\320\271", nullptr));
        logTE->setHtml(QCoreApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:7.8pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p></body></html>", nullptr));
        clearFormulaPB->setText(QCoreApplication::translate("MainWindow", "\320\241\321\202\320\265\321\200\320\265\321\202\321\214 \321\204\320\276\321\200\320\274\321\203\320\273\321\203", nullptr));
        clearLogPB->setText(QCoreApplication::translate("MainWindow", "\320\236\321\207\320\270\321\201\321\202\320\270\321\202\321\214 \320\266\321\203\321\200\320\275\320\260\320\273", nullptr));
        logTitleLabel_2->setText(QCoreApplication::translate("MainWindow", "\320\232\320\260\320\273\321\214\320\272\321\203\320\273\321\217\321\202\320\276\321\200 \321\201 \321\203\320\277\321\200\320\260\320\262\320\273\321\217\320\265\320\274\320\276\320\271 \321\202\320\276\321\207\320\275\320\276\321\201\321\202\321\214\321\216", nullptr));
        setAccuracyResultL->setText(QString());
        accuracyLE->setPlaceholderText(QCoreApplication::translate("MainWindow", "\320\222\320\262\320\265\320\264\320\270\321\202\320\265 \321\202\320\276\321\207\320\275\320\276\321\201\321\202\321\214", nullptr));
        periodNumberLE->setInputMask(QString());
        periodNumberLE->setPlaceholderText(QCoreApplication::translate("MainWindow", "\320\222\320\262\320\265\320\264\320\270\321\202\320\265 \320\262 \320\262\320\270\320\264\320\265 a,b(c)", nullptr));
        accuracyResultL->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
