#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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
    void on_actionNOVO_triggered();

    void on_actionABRIR_triggered();

    void on_actionSALVAR_triggered();

    void on_actionSALVAR_COMO_triggered();

    void on_actionFECHAR_triggered();

    void on_actionCOPIAR_triggered();

    void on_actionRECORTAR_triggered();

    void on_actionCOLAR_triggered();

    void on_actionDESFAZER_triggered();

    void on_actionREFAZER_triggered();

    void on_actionFONTE_triggered();

    void on_actionCOR_triggered();

    void on_actionCOR_DE_FUNDO_triggered();

    void on_actionIMPRIMIR_triggered();

private:
    Ui::MainWindow *ui;
    QString local_arquivo;
    bool arquivoSalvo = false;
};
#endif // MAINWINDOW_H
