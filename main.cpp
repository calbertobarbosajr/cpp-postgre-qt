#include "mainwindow.h"

#include <QApplication>
#include <QLabel>
#include <QMessageBox>
#include "databasehandler.h" // Inclui o cabeçalho para o manipulador do banco de dados

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    DatabaseHandler dbHandler; // Cria uma instância do manipulador do banco de dados
    QString message;

    if (dbHandler.openConnection()) {
        message = "Conectado com sucesso";
    } else {
        message = "Erro ao conectar";
    }

    QMessageBox::information(nullptr, "Status da Conexão", message);
        //return 0;


        MainWindow w;
        w.show();
        return app.exec();
}
