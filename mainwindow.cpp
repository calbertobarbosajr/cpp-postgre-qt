#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QCoreApplication>
#include <QtSql>
#include <QTextStream>
#include <QDebug>
#include <QMessageBox>
#include <QInputDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Adicionando cabeçalho à tabela

    model = new QStandardItemModel();
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    model->setHorizontalHeaderItem(0, new QStandardItem(QString("ID")));
    model->setHorizontalHeaderItem(1, new QStandardItem(QString("Name")));
    model->setHorizontalHeaderItem(2, new QStandardItem(QString("Age")));

    ui->tableView->setModel(model);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButtonSave_clicked()
{
    QStandardItem *name = new QStandardItem(ui->lineEditName->text());
    QStandardItem *age = new QStandardItem(ui->lineEditAge->text());

    clearFields();

    QMessageBox::information(this, "Application", "Record has been saved");

    QSqlQuery query;
    query.exec("CREATE TABLE IF NOT EXISTS pessoa (id SERIAL PRIMARY KEY, nome VARCHAR(100), idade INTEGER)");

    QString nome = name->text();
    int idade = age->text().toInt();

    query.prepare("INSERT INTO pessoa (nome, idade) VALUES (:nome, :idade)");
    query.bindValue(":nome", nome);
    query.bindValue(":idade", idade);
    if (!query.exec()) {
        qDebug() << "Erro ao inserir dados na tabela:" << query.lastError().text();
    } else {
        qInfo() << "Dados inseridos com sucesso!";
        recuperarDados();
    }
}

void MainWindow::recuperarDados()
{
    query.prepare("SELECT * FROM pessoa");
    if (!query.exec()) {
        qDebug() << "Erro ao executar consulta:" << query.lastError().text();
        return;
    }

    model->removeRows(0, model->rowCount()); // Limpar os dados anteriores

    while (query.next()) {
        int id = query.value("id").toInt();
        QString nome = query.value("nome").toString();
        int idade = query.value("idade").toInt();
        model->appendRow({new QStandardItem(QString::number(id)), new QStandardItem(nome), new QStandardItem(QString::number(idade))});
    }
}

void MainWindow::on_pushButtonDelete_clicked()
{
    QModelIndexList selectedIndexes = ui->tableView->selectionModel()->selectedIndexes();

    if (!selectedIndexes.isEmpty()) {
        int rowIndex = selectedIndexes.at(0).row(); // Obter índice da linha selecionada
        int pessoaId = model->data(model->index(rowIndex, 0)).toInt(); // Obter ID da pessoa

        model->removeRow(rowIndex);

        QSqlQuery query;
        query.prepare("DELETE FROM pessoa WHERE id = :id");
        query.bindValue(":id", pessoaId);
        if (!query.exec()) {
            qDebug() << "Erro ao excluir dados da tabela:" << query.lastError().text();
        } else {
            qInfo() << "Dados excluídos com sucesso!";
        }
    }
}

void MainWindow::on_pushButtonUpdate_clicked()
{
    for (int row = 0; row < model->rowCount(); ++row) {
        int id = model->data(model->index(row, 0)).toInt();
        QString nome = model->data(model->index(row, 1)).toString();
        int idade = model->data(model->index(row, 2)).toInt();

        QSqlQuery query;
        query.prepare("UPDATE pessoa SET nome = :nome, idade = :idade WHERE id = :id");
        query.bindValue(":nome", nome);
        query.bindValue(":idade", idade);
        query.bindValue(":id", id);

        if (!query.exec()) {
            qDebug() << "Erro ao atualizar dados na tabela:" << query.lastError().text();
        } else {
            qInfo() << "Dados atualizados com sucesso!";
        }
    }

    QMessageBox::information(this, "Application", "Records have been updated");
}



void MainWindow::clearFields()
{
    ui->lineEditName->setText("");
    ui->lineEditAge->setText("");
}


void MainWindow::on_pushButtonShowDatabase_clicked()
{
    recuperarDados();
}

