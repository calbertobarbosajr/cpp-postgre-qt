#ifndef CONNECT_H
#define CONNECT_H

#endif // CONNECT_H


#include <QApplication>
#include <QLabel>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox> // Adicione esta linha
#include <QDebug>

int connectando()
{
    QApplication app(argc, argv);
    QLabel myLabel;

    // ... (configuração da conexão)

    if (db.open()) {
        // Conexão bem-sucedida
        QMessageBox::information(QApplication::activeWindow(), "Application", "Conectado com sucesso");
    } else {
        // Erro na conexão
        QMessageBox::information(QApplication::activeWindow(), "Application", "Erro");
    }

    myLabel.show();
    return app.exec();
}

