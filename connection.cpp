#include "connection.h"
#include <QString>

Connection::Connection()
{

}

bool Connection::createconnect()
{bool test=false;
QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("AssociationElWafa");
db.setUserName("nihed");//inserer nom de l'utilisateur
db.setPassword("esprit17");//inserer mot de passe de cet utilisateur

if (db.open())
test=true;





    return  test;
}
