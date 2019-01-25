#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMap>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_comboBoxRegione_currentIndexChanged(const QString &arg1);

private:
    Ui::MainWindow *ui;
    QMap<QString, QMap<QString,QMap<QString,int>>> values;
};

#endif // MAINWINDOW_H
