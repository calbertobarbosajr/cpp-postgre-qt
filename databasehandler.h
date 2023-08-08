#ifndef DATABASEHANDLER_H
#define DATABASEHANDLER_H

#include <QSqlDatabase>

class DatabaseHandler
{
public:
    DatabaseHandler();
    bool openConnection();

private:
    QSqlDatabase db;
};

#endif // DATABASEHANDLER_H
