#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QFontDialog>
#include <QFont>
#include <QColorDialog>
#include <QColor>
#include <QPrintDialog>
#include <QPrinter>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //caixa de texto para cobrir toda a tela
    this->setCentralWidget(ui->textEdit);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionNOVO_triggered()
{
    local_arquivo="";
    ui->textEdit->clear();
    ui->textEdit->setFocus();
}


void MainWindow::on_actionABRIR_triggered()
{
    QString filtro="Todos Arquivos (*.*);;Arquivos de texto (*.txt)";
    QString nome_arquivo= QFileDialog::getOpenFileName(this,"Abrir",QDir::homePath(),filtro);
    QFile arquivo(nome_arquivo);
    local_arquivo = nome_arquivo;
    if(!arquivo.open(QFile::ReadOnly | QFile::Text)){
        QMessageBox::warning(this,"","Arquivo não pode ser aberto");
        return;
    }
    QTextStream entrada(&arquivo);
    QString texto = entrada.readAll();
    ui->textEdit->setText(texto);
    arquivo.close();
}

void MainWindow::on_actionSALVAR_COMO_triggered()
{
    QString filtro="Todos Arquivos (*.*);;Arquivos de texto (*.txt)";
    QString nome_arquivo = QFileDialog::getSaveFileName(this,"Salvar como",QDir::homePath(),filtro);
    local_arquivo = nome_arquivo;
    QFile arquivo(nome_arquivo);
    if(!arquivo.open(QFile::WriteOnly | QFile::Text)){
        QMessageBox::warning(this,"","Arquivo não pode ser salvo");
        return;
    }
    QTextStream saida(&arquivo);
    QString texto = ui->textEdit->toPlainText();
    saida << texto;
    arquivo.flush();
    arquivo.close();
}

void MainWindow::on_actionSALVAR_triggered()
{
    if (!arquivoSalvo) {
        QString filtro = "Arquivos de texto (*.txt);;Todos Arquivos (*.*)";
        QString nome_arquivo = QFileDialog::getSaveFileName(this, "Salvar como", QDir::homePath(), filtro);

        if (!nome_arquivo.isEmpty()) {
            if (!nome_arquivo.endsWith(".txt", Qt::CaseInsensitive)) {
                nome_arquivo += ".txt";
            }

            local_arquivo = nome_arquivo;
            arquivoSalvo = true; // Marca o arquivo como salvo
        } else {
            return; // O usuário cancelou a operação
        }
    }

    QFile arquivo(local_arquivo);
    if (!arquivo.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, "", "Arquivo não pode ser salvo");
            return;
    }

    QTextStream saida(&arquivo);
    QString texto = ui->textEdit->toPlainText();
    saida << texto;
    arquivo.flush();
    arquivo.close();
}

void MainWindow::on_actionFECHAR_triggered()
{
    close();
}

void MainWindow::on_actionCOPIAR_triggered()
{
    ui->textEdit->copy();
}

void MainWindow::on_actionRECORTAR_triggered()
{
    ui->textEdit->cut();
}

void MainWindow::on_actionCOLAR_triggered()
{
    ui->textEdit->paste();
}

void MainWindow::on_actionDESFAZER_triggered()
{
    ui->textEdit->undo();
}

void MainWindow::on_actionREFAZER_triggered()
{
    ui->textEdit->redo();
}

void MainWindow::on_actionFONTE_triggered()
{
    bool fonte_ok;
    QFont fonte = QFontDialog::getFont(&fonte_ok,this);
    if(fonte_ok){
        ui->textEdit->setFont(fonte);
    }else{
        return;
    }
}

void MainWindow::on_actionCOR_triggered()
{
    QColor cor = QColorDialog::getColor(Qt::black,this,"Escolha uma cor");
    if(cor.isValid()){
        ui->textEdit->setTextColor(cor);
    }
}

void MainWindow::on_actionCOR_DE_FUNDO_triggered()
{
    QColor cor = QColorDialog::getColor(Qt::black,this,"Escolha uma cor");
    if(cor.isValid()){
        ui->textEdit->setTextBackgroundColor(cor);
    }
}

void MainWindow::on_actionIMPRIMIR_triggered()
{
    QPrinter imp;
    imp.setPrinterName("Impressora");
    QPrintDialog cx_imp(&imp,this);
    if(cx_imp.exec()==QDialog::Rejected){
        return;
    }else{
        ui->textEdit->print(&imp);
    }
}

