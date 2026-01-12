#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QMessageBox>
#include<QFile>
#include<QTextStream>
#include<QFileDialog>
#include<QFont>
#include<QFontDialog>
#include<QColorDialog>
#include<QColor>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
QString currentFile;

void MainWindow::on_textEdit_cursorPositionChanged()
{
    QTextCursor cursor = ui->textEdit->textCursor();
    int line = cursor.blockNumber()+1;
    int column = cursor.positionInBlock()+1;
    int charcount = ui->textEdit->toPlainText().length();


    QString status = QString("line: %1|column:%2| %3 character").arg(line).arg(column).arg(charcount);
    ui->statusbar->showMessage(status);
}


void MainWindow::on_actionNew_triggered()
{
    currentFile = "";
    ui->textEdit->setText("");
}


void MainWindow::on_actionOpen_triggered()
{
    bool isModified =false;
    if(!currentFile.isEmpty()){
        QFile file(currentFile);
        if(file.open(QIODevice::ReadOnly|QIODevice::Text)){
            QTextStream in(&file);
            QString savedContent = in.readAll();
            file.close();
            isModified = (savedContent!=ui->textEdit->toPlainText() );
        }else{
            isModified  =!ui->textEdit->toPlainText().isEmpty();
        }
        if(isModified){
            QMessageBox::StandardButton reply= QMessageBox::question(
                this,
                "unsaved changes",
                "you have unsaved.do you want to save before opening a new file ?",
                QMessageBox::Yes|QMessageBox::No|QMessageBox::Cancel
                );
            if(reply==QMessageBox::Cancel)return;
            if(reply==QMessageBox::Yes){
                on_actionSave_triggered();

            };
        }
    }else{
        if(isModified =false){
            QString fileName=QFileDialog::getOpenFileName(this,"open file ","","Text Files(*.txt);;All Files(*)");
            if(!fileName.isEmpty());
            QFile file(fileName);
            if(file.open(QIODevice::ReadOnly|QIODevice::Text)){
                QTextStream in(&file);
                QString content = in.readAll();
                ui->textEdit->setPlainText(content);
                file.close();
                currentFile=fileName;

                setWindowTitle(currentFile +"-Noteopad");
                ui->statusbar->showMessage(QFileInfo(currentFile).fileName(),3800);


            }


        }else{
            QMessageBox::warning(this,"error","could not open file");

        }
    }
}


void MainWindow::on_actionSave_triggered()
{
    if(currentFile.isEmpty()){
        on_actionSave_triggered();
        return;
    }
        QFile file(currentFile);
        if(file.open(QIODevice::WriteOnly|QIODevice::Text)){
            QTextStream out(&file);
            out<< ui->textEdit->toPlainText();
            file.close();

            setWindowTitle(currentFile + "-Noteopad");
            ui->statusbar->showMessage("File saved",3800);

        }else{
            QMessageBox::warning(this, "error","could not open file for writing" );
        }
    }



void MainWindow::on_actionSave_As_triggered()
{
    QString fileName=QFileDialog::getSaveFileName(this,"save file as","","Text Files(*.txt);;All Files(*)");
    if(!fileName.isEmpty()){
        currentFile =fileName;
        on_actionSave_As_triggered();
    }

}


void MainWindow::on_actioncut_triggered()
{
    ui->textEdit->cut();

}


void MainWindow::on_actioncopy_triggered()
{
    ui->textEdit->copy();
}


void MainWindow::on_actionpaste_triggered()
{
    ui->textEdit->paste();
}


void MainWindow::on_actionundo_triggered()
{
    ui->textEdit->undo();
}


void MainWindow::on_actionredo_triggered()
{
    ui->textEdit->redo();
}


void MainWindow::on_actionfont_triggered()
{
    bool ok;
    QFont font = QFontDialog::getFont(&ok,this);
    if(ok){
        ui->textEdit->setFont(font);

    }else{
        return;
    }


void MainWindow::on_actionfont_colour_triggered()
{
    QColor color = QColorDialog::getColor(Qt::white,this,"choose color");
    if(color.isValid()){
        ui->textEdit->setTextColor(color);
    }
}


void MainWindow::on_actionBG_colour_triggered()
{
    QColor color = QColorDialog::getColor(Qt::white,this,"choose color");
    if(color.isValid()){
        ui->textEdit->setTextBackgroundColor(color);
    }
};

