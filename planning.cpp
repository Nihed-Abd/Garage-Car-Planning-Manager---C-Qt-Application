#include "planning.h"
#include <QDate>
#include <QSqlQuery>
#include <QtDebug>
#include <QSqlQueryModel>
#include <QSqlError>
#include <string>
#include <QPdfWriter>
#include <QPainter>
planning::planning()
{
     MATRICULE=0;
             IDACTIVITE=0;
             IDEMPLOYE=0;
             DATEE=QDate::currentDate();;
              STATUS="";

}

planning::planning(int MATRICULE,QDate DATE,int IDACTIVITE,int IDEMPLOYE,QString STATUS)
{
    this->MATRICULE=MATRICULE;
    this-> DATEE=DATE;
    this->IDACTIVITE=IDACTIVITE;
    this->IDEMPLOYE=IDEMPLOYE;
     this->STATUS=STATUS;
}

int planning::get_matricule(){return MATRICULE;}
QDate planning::get_date(){return DATEE;}
int planning::get_IDACTIVITE(){return IDACTIVITE; }
int planning::get_IDEMPLOYE(){return IDEMPLOYE;}
QString planning::get_STATUS(){return STATUS;}

void planning::set_matricule(int MATRICULE){this->MATRICULE=MATRICULE;}
void planning::set_IDACTIVITE(int IDACTIVITE){this->IDACTIVITE=IDACTIVITE;}
void planning::set_IDEMPLOYE(int IDEMPLOYE){this->IDEMPLOYE=IDEMPLOYE;}
void planning::set_date(QDate DATEE){this-> DATEE=DATEE;}
void planning::set_STATUS(QString STATUS){this-> STATUS=STATUS;}

bool planning::ajouter()
{
    QSqlQuery query;
    QString CMATRICULE=QString::number(MATRICULE);


         query.prepare("INSERT INTO PLANING (MATRICULE,DATEE,IDACTIVITE,IDEMPLOYE,STATUS) "
                       "VALUES (:MATRICULE,:DATEE,:IDACTIVITE,:IDEMPLOYE,:STATUS)");
         query.bindValue(":MATRICULE",CMATRICULE);
         query.bindValue(":DATEE",DATEE);
         query.bindValue(":IDACTIVITE",IDACTIVITE);
         query.bindValue(":IDEMPLOYE",IDEMPLOYE);
            query.bindValue(":STATUS",STATUS);
         return query.exec();

}
QSqlQueryModel* planning::afficher()
{
    QSqlQueryModel* model=new QSqlQueryModel();


          model->setQuery("SELECT* FROM PLANING");
          model->setHeaderData(0, Qt::Horizontal, QObject::tr("MATRICULE"));
          model->setHeaderData(1, Qt::Horizontal, QObject::tr("DATEE"));
          model->setHeaderData(2, Qt::Horizontal, QObject::tr("IDACTIVITE"));
          model->setHeaderData(3, Qt::Horizontal, QObject::tr("IDEMPLOYE"));
               model->setHeaderData(4, Qt::Horizontal, QObject::tr("STATUS"));

    return model;
};
bool planning::supprimer(int MATRICULE){
    QSqlQuery query;
    QString res = QString::number(MATRICULE);
    query.prepare("DELETE FROM PLANING WHERE MATRICULE=:MATRICULE");
    query.bindValue(":MATRICULE", res);
    if (!query.exec()) {
        return false;  // Failed to execute the query
    }
    if (query.numRowsAffected() == 0) {
        return false;
    }
    return true;
}





bool planning::modifier(int MATRICULE,QDate DATEE,int IDACTIVITE,int IDEMPLOYE,QString STATUS)
{
    QSqlQuery query;
       query.prepare("SELECT COUNT(*) FROM PLANING WHERE MATRICULE = :MATRICULE");
         query.bindValue(":MATRICULE", MATRICULE);
         query.exec();
         query.next();
         int count = query.value(0).toInt();
         if (count == 0) {

             return false;
         }

         QString id_m_string = QString::number(MATRICULE);
         QString id_a_string = QString::number(IDACTIVITE);
         QString id_e_string = QString::number(IDEMPLOYE);
         query.prepare("UPDATE PLANING SET DATEE=:DATEE,IDACTIVITE =:IDACTIVITE,IDEMPLOYE =:IDEMPLOYE,STATUS=:STATUS WHERE MATRICULE = :MATRICULE");
         query.bindValue(":MATRICULE", id_m_string);
         query.bindValue(":IDACTIVITE", id_a_string);
           query.bindValue(":IDEMPLOYE", id_e_string);
         query.bindValue(":DATEE",DATEE);
          query.bindValue(":STATUS",STATUS);

         return query.exec();
}
QSqlQueryModel * planning:: afficher_calendar(QDate x)
{
    QSqlQueryModel * model= new QSqlQueryModel();
QString x1=QString::number(x.month()),x2=QString::number(x.day()),x3=QString::number(x.year());
model->setQuery("select * from PLANING where(extract(day  from DATEE)='"+x2+"' and extract(month  from DATEE)='"+x1+"' and extract(year  from DATEE)='"+x3+"')");
model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
model->setHeaderData(1,Qt::Horizontal,QObject::tr("DATE"));
model->setHeaderData(4,Qt::Horizontal,QObject::tr("ETAT"));
model->setHeaderData(5,Qt::Horizontal,QObject::tr("TYPE"));
model->setHeaderData(6,Qt::Horizontal,QObject::tr("DATE"));

    return model;
}



