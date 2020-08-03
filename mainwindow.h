#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include <QPrinter>
#include <QPrintDialog>
#include <QFontComboBox>
#include <QStatusBar>
#include <QInputDialog>
#include <QTextDocument>
#include <regex>


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
    void on_actionNew_triggered();

    void on_actionOpen_triggered();

    void on_actionSave_triggered();

    void on_actionSave_As_triggered();

    void on_actionPrint_triggered();

    void on_actionQuit_triggered();

    void on_actionUndo_triggered();

    void on_actionRedo_triggered();

    void on_actionCpoy_triggered();

    void on_actionCut_triggered();

    void on_actionPaste_triggered();



    void on_actionFont_triggered();

    void on_actionZoom_In_triggered();

    void on_actionZoom_Out_triggered();

    void on_actionAbout_Poom_Pad_triggered();

    void on_actionFind_triggered();

    void on_actionFind_Previous_triggered();

    void on_actionFind_Next_triggered();

    void on_actionReplace_triggered();

private:
    Ui::MainWindow *ui;
    QString CurrentFile = nullptr;
    QString FindText = nullptr;
};
#endif // MAINWINDOW_H
