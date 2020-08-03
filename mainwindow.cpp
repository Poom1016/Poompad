#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setCentralWidget(ui->textEdit);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionNew_triggered()
{
    CurrentFile.clear();
    ui->textEdit->setText(QString());
}


void MainWindow::on_actionOpen_triggered()
{
    QString FileName = QFileDialog::getOpenFileName(this, "Open File");
    QFile File(FileName);
    if(!File.open(QIODevice::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "An Error Occurred While Opening File: " + File.errorString());
    }
    setWindowTitle(FileName);
    QTextStream in(&File);
    QString Text = in.readAll();
    ui->textEdit->setText(Text);
}

void MainWindow::on_actionSave_triggered()
{
    QString FileName = QFileDialog::getSaveFileName(this, "Save");
        QFile File(FileName);
        if (!File.open(QFile::WriteOnly | QFile::Text)) {
            QMessageBox::warning(this, "Warning", "Cannot save file: " + File.errorString());
            return;
        }
        CurrentFile = FileName;
        setWindowTitle(FileName);
        QTextStream out(&File);
        QString text = ui->textEdit->toPlainText();
        out << text;
        File.close();
}

void MainWindow::on_actionSave_As_triggered()
{
    QString FileName = QFileDialog::getSaveFileName(this, "Save as");
        QFile File(FileName);

        if (!File.open(QFile::WriteOnly | QFile::Text)) {
            QMessageBox::warning(this, "Warning", "Cannot save file: " + File.errorString());
            return;
        }

        CurrentFile = FileName;
        setWindowTitle(FileName);
        QTextStream out(&File);
        QString text = ui->textEdit->toPlainText();
        out << text;
        File.close();
}

void MainWindow::on_actionPrint_triggered()
{
    QPrinter Printer;

       Printer.setPrinterName("Printer Name");
       QPrintDialog pDialog(&Printer, this);

       if(pDialog.exec() == QDialog::Rejected){
           QMessageBox::warning(this, "Warning", "Cannot Access Printer");
           return;
       }

       ui->textEdit->print(&Printer);
}

void MainWindow::on_actionQuit_triggered()
{
    QApplication::quit();
}

void MainWindow::on_actionUndo_triggered()
{
    ui->textEdit->undo();
}

void MainWindow::on_actionRedo_triggered()
{
    ui->textEdit->redo();
}

void MainWindow::on_actionCpoy_triggered()
{
    ui->textEdit->copy();
}

void MainWindow::on_actionCut_triggered()
{
    ui->textEdit->cut();
}

void MainWindow::on_actionPaste_triggered()
{
    ui->textEdit->paste();
}

void MainWindow::on_actionFont_triggered()
{
    QFontComboBox fDialog;
}

void MainWindow::on_actionZoom_In_triggered()
{
    ui->textEdit->zoomIn();
}

void MainWindow::on_actionZoom_Out_triggered()
{
    ui->textEdit->zoomOut();
}

void MainWindow::on_actionAbout_Poom_Pad_triggered()
{

    QMessageBox msgBox;
    msgBox.setText("About Poompad");
    msgBox.setInformativeText("Poompad Version 11.01 Developer Beta");
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.setDefaultButton(QMessageBox::Ok);
    msgBox.exec();
}

void MainWindow::on_actionFind_triggered()
{
    bool Ok;
    FindText = "";
    FindText = QInputDialog::getText(this, tr("Find"),
                                             tr("Find text:"), QLineEdit::Normal,
                                             QDir::home().dirName(), &Ok);

    ui->textEdit->find(FindText);

}

void MainWindow::on_actionFind_Previous_triggered()
{

    ui->textEdit->find(FindText, QTextDocument::FindBackward | QTextDocument::FindCaseSensitively);

}

void MainWindow::on_actionFind_Next_triggered()
{
    ui->textEdit->find(FindText);
}

void replaceAll(std::string& str, const std::string& from, const std::string& to) {
    if(from.empty())
        return;
    size_t start_pos = 0;
    while((start_pos = str.find(from, start_pos)) != std::string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length();
    }
}

void MainWindow::on_actionReplace_triggered()
{
    bool Ok;
    QString ReplaceText = "";
    std::string utf8_text2 = FindText.toUtf8().constData();
    utf8_text2 = utf8_text2 + " to: ";
    ReplaceText = QInputDialog::getText(this, tr("Replace"),
                                             tr("Replace ",utf8_text2.c_str()), QLineEdit::Normal,
                                             QDir::home().dirName(), &Ok);
    QString Text = ui->textEdit->toPlainText();
    std::string utf8_text = Text.toUtf8().constData();
    std::string utf8_text3 = FindText.toUtf8().constData();
    std::string utf8_text4 = ReplaceText.toUtf8().constData();

    utf8_text = std::regex_replace(utf8_text, std::regex(utf8_text3),utf8_text4);
    QString ReplacedText =  QString::fromStdString(utf8_text);
    ui->textEdit->setText(ReplacedText);
}
