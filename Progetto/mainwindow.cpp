#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMap>
#include <QFile>
#include <QtDebug>
#include <QFileDialog>
#include <QMessageBox>
#include <QStringList>
#include <QtCharts>

using namespace QtCharts;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    QFile file("./dataset/data.txt");
    if(!file.open(QIODevice::ReadOnly)) {
        QMessageBox::information(nullptr, "error", file.errorString());
    }
    QTextStream in(&file);

    QStringList cb_values;

    while(!in.atEnd()) {
        QString line = in.readLine();
        QStringList fields = line.split(" ");

        if(line!="<END>") {
            if(!cb_values.contains(fields[0]))
                cb_values.append(fields[0]);

            values[fields[0]][fields[1]]["F"] = fields[2].toInt();
            values[fields[0]][fields[1]]["M"] = fields[3].toInt();
        }
    }
    file.close();

    ui->setupUi(this);
    ui->comboBoxRegione->addItems(cb_values);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_comboBoxRegione_currentIndexChanged(const QString &arg1)
{
    int riga = 1;
    int colonna = 0;

    ui->labelRegione->setText(arg1);
    QMap<QString,QMap<QString,int>> dati = values[arg1];
    ui->tableRegione->setRowCount(dati.count()+2);          //intestazione + riga totale

    QMap<QString,QMap<QString,int>>::const_iterator i = dati.begin(), ie = dati.end();
    QString eta;
    int maschi=0, femmine=0, tot_maschi=0, tot_femmine=0;
    QString key;

    for(;i!=ie;i++) {
        key = i.key();
        if(key!="100+" && key!="5-9") {                                   //Problema di ordinamento lessicografico con 5-9,100+
            eta = key;
            maschi = dati[key]["M"];
            tot_maschi += maschi;
            femmine = dati[key]["F"];
            tot_femmine += femmine;

            ui->tableRegione->setItem(riga,colonna,new QTableWidgetItem(eta));
            colonna++;
            ui->tableRegione->setItem(riga,colonna,new QTableWidgetItem(QString::number(maschi)));
            colonna++;
            ui->tableRegione->setItem(riga,colonna,new QTableWidgetItem(QString::number(femmine)));
            colonna++;

            if(colonna>=2)
                colonna=0;
            riga++;

            if(key=="0-4")
                riga++;
        }
    }
    if(dati.keys().contains("100+")) {
        eta = "100+";
        maschi = dati["100+"]["M"];
        tot_maschi += maschi;
        femmine = dati["100+"]["F"];
        tot_femmine += femmine;

        ui->tableRegione->setItem(riga,colonna,new QTableWidgetItem(eta));
        colonna++;
        ui->tableRegione->setItem(riga,colonna,new QTableWidgetItem(QString::number(maschi)));
        colonna++;
        ui->tableRegione->setItem(riga,colonna,new QTableWidgetItem(QString::number(femmine)));
        colonna++;

        if(colonna>=2)
            colonna=0;

        riga++;
    }
    if(dati.keys().contains("5-9")) {
        eta = "5-9";
        maschi = dati["5-9"]["M"];
        tot_maschi += maschi;
        femmine = dati["5-9"]["F"];
        tot_femmine += femmine;

        ui->tableRegione->setItem(2,colonna,new QTableWidgetItem(eta));
        colonna++;
        ui->tableRegione->setItem(2,colonna,new QTableWidgetItem(QString::number(maschi)));
        colonna++;
        ui->tableRegione->setItem(2,colonna,new QTableWidgetItem(QString::number(femmine)));
        colonna++;

        if(colonna>=2)
            colonna=0;

    }

    //Riga finale
    ui->tableRegione->setItem(riga,colonna,new QTableWidgetItem("Totale"));
    colonna++;
    ui->tableRegione->setItem(riga,colonna,new QTableWidgetItem(QString::number(tot_maschi)));
    colonna++;
    ui->tableRegione->setItem(riga,colonna,new QTableWidgetItem(QString::number(tot_femmine)));
    colonna++;

    //Grafico a torta
    QPieSeries *series_maschi = new QPieSeries(), *series_femmine = new QPieSeries();   //inizializzo le serie per il grafico

    for(i=dati.begin();i!=ie;i++) {
            key = i.key();
            series_maschi->append(key,(dati[key]["M"]));
            series_femmine->append(key,(dati[key]["F"]));
    }

    //Imposto le percentuali
    series_maschi->setLabelsVisible();
    series_maschi->setLabelsPosition(QPieSlice::LabelInsideNormal);

    series_femmine->setLabelsVisible();
    series_femmine->setLabelsPosition(QPieSlice::LabelInsideNormal);

    for(QPieSlice *slice : series_maschi->slices())
        slice->setLabel(QString(slice->label()+": %1%").arg(100*slice->percentage(), 0, 'f', 1));

    for(QPieSlice *slice : series_femmine->slices())
        slice->setLabel(QString(slice->label()+": %1%").arg(100*slice->percentage(), 0, 'f', 1));

    QChart *chart_maschi = new QChart(), *chart_femmine = new QChart();
    chart_maschi->setTitle("Maschi");
    chart_maschi->addSeries(series_maschi);

    chart_femmine->setTitle("Femmine");
    chart_femmine->addSeries(series_femmine);

    chart_maschi->legend()->setAlignment(Qt::AlignRight);
    ui->graphicsView_maschi->setChart(chart_maschi);

    chart_femmine->legend()->setAlignment(Qt::AlignRight);
    ui->graphicsView_femmine->setChart(chart_femmine);

}
