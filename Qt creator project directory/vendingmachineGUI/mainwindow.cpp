#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QProcess>
#include <QDebug>

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


void MainWindow::on_startButton_clicked()
{
    test();
}

void test(){

    QString program = "D:/C Interview project/project root/c project directory/vendingmachine.exe";
    QStringList arguments;
    arguments << "test";
    QProcess* process = new QProcess();

    // catch data output
    QObject::connect(process, &QProcess::readyRead, [process] () {
        QByteArray a = process->readAll();
        qDebug() <<  a;
    });

    // delete process instance when done, and get the exit status to handle errors.
    QObject::connect(process, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
                     [=](int exitCode, QProcess::ExitStatus /*exitStatus*/){
        qDebug()<< "process exited with code " << exitCode;
        process->deleteLater();
    });

    // start the process after making signal/slots connections
    process->start(program, arguments);
}
