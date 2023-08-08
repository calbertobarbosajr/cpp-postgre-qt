#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlQuery> // Adicione esta linha
#include <QApplication>
#include <QStandardItemModel>
#include <QMessageBox>
#include <QInputDialog>

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
    void on_pushButtonSave_clicked();
    void on_pushButtonDelete_clicked();
    void on_pushButtonUpdate_clicked();
    void on_pushButtonShowDatabase_clicked();
    void clearFields();
    void recuperarDados();

private:
    Ui::MainWindow *ui;
    QStandardItemModel *model;
    QSqlQuery query;
};

#endif // MAINWINDOW_H
