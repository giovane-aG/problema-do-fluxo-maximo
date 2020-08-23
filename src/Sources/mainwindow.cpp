#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <string.h>
#include <sstream>
#include <iostream>
#include "FordFulkerson.h"
#include <QFile>
#include <QMessageBox>
#include <QDebug>
#include <QDir>

vector<vector<int>> matrix;
bool grafoCarregado = false;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->textEdit_2->setReadOnly(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    if(grafoCarregado){
        ui->textEdit_2->append("------------------------------------------------------");
        QString sink = ui ->DESTINO->text();
        int snk = sink.toInt();
        QString source = ui ->ORIGEM->text();
        int src = source.toInt();
    //////////////////////////////
        for (int j = src; j < snk; j++)
        {

            if (src == snk)
            {
                continue;
            }


            int n = maxFlux(j,snk,matrix);
            QString str = QString::number(n);

            ui->textEdit_2->append("FLUXO MAXIMO DE "+source+ " até " + QString::number(j) +" : " + str);
        }
        ui->textEdit_2->append("------------------------------------------------------");
    }
    else{
        QMessageBox::information(0, "Aviso!", "Favor carregar o grafo");
    }
}


void MainWindow::on_pushButton_2_clicked()
{

    ui->textEdit_2->append("------------------------------------------------------");
    QFile file(QDir::current().absolutePath()+"/graphmap/graph.txt");
    if(!file.open(QIODevice::ReadOnly)) {
        QMessageBox::information(0, "error", file.errorString());
    }
    QTextStream entrada(&file);
    QString line = entrada.readLine();

    int n = line.toInt();
    int v1[1024];
    int v2[1024];
    int peso[1024];
    int i = 0;
    int linhas = 0;

    while(!entrada.atEnd()){
        line = entrada.readLine();
        v1[i]= line.split(" ")[0].toInt();
        v2[i] = line.split(" ")[1].toInt();
        peso[i] = line.split(" ")[2].toInt();
        i++;
        ui->textEdit_2->append("Aresta ("+ line.split(" ")[0] +")"+"("+line.split(" ")[1]+")"+" COM PESO = "+ line.split(" ")[2] + " FOI ADICIONADA ");
        linhas++;
      }
    matrix = FormAdjMatrix(n,v1,v2,peso,linhas);

    file.close();
    grafoCarregado = true;
    ui->textEdit_2->append("------------------------------------------------------");
}

void MainWindow::on_pushButton_3_clicked()
{
    ui->textEdit_2->clear();
}
