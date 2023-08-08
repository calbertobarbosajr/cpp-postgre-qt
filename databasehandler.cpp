#include "databasehandler.h"

DatabaseHandler::DatabaseHandler()
{
    db = QSqlDatabase::addDatabase("QPSQL");
    db.setHostName("localhost"); // ou o endereço IP do servidor PostgreSQL
    db.setDatabaseName("postgres");
    db.setUserName("postgres");
    db.setPassword("123");
}

bool DatabaseHandler::openConnection()
{
    if (db.open()) {
        return true;
    } else {
        // Aqui, você pode adicionar código para lidar com erros, se necessário
        return false;
    }
}
