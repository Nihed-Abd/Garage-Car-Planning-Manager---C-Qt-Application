#ifndef PLANNING_H
#define PLANNING_H

#include <QString>
#include <QDate>
#include <QSqlQueryModel>
#include <QTableView>
#include <QList>

class planning
{
public:
    planning();
    planning(int, QDate, int, int, QString);
    QSqlQueryModel *afficher_calendar(QDate x); // Déclaration de la fonction
QList<planning> getEventData(QDate& date);

    int get_matricule();
    QDate get_date();
    int get_IDACTIVITE();
    int get_IDEMPLOYE();
    QString get_STATUS();

    void set_matricule(int);
    void set_IDACTIVITE(int);
    void set_IDEMPLOYE(int);
    void set_date(QDate);
    void set_STATUS(QString);

    bool ajouter();
    QSqlQueryModel* afficher();
    bool supprimer(int);
    bool modifier(int, QDate, int, int, QString);

private:
    int MATRICULE, IDACTIVITE, IDEMPLOYE;
    QString STATUS;
    QDate DATEE;
};

#endif // PLANNING_H
