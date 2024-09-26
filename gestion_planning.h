#ifndef GESTION_PLANNING_H
#define GESTION_PLANNING_H

#include <QMainWindow>
#include <QLabel>
#include <QNetworkReply>
#include "notification.h"


QT_BEGIN_NAMESPACE
namespace Ui { class gestion_planning; }
QT_END_NAMESPACE

class gestion_planning : public QMainWindow
{
    Q_OBJECT

public:
    gestion_planning(QWidget *parent = nullptr);
    ~gestion_planning();
    QVector<QString> chargerStatuts();
    void displayEventDetails(const QDate& date, QLabel* detailsWidget);

public slots:
    void onWeatherReply(QNetworkReply *reply);
private slots:

    void checkMatriculeLength(const QString &text);
    void checkActiviteLength(const QString &text);
    void checkEmployeLength(const QString &text);
    void on_M2_planning_3_clicked();
    void on_M4_planning_2_clicked();
    void on_M3_planning_2_clicked();
    void on_M1_planning_2_clicked();
    void on_M2_planning_2_clicked();
    void on_Chercher_planning_2_clicked();
    void on_Effacer_planning_2_clicked();
    void on_M2_planning_4_clicked();
//    QList<QPair<QDate, QString>>getEventDatesAndInfoFromDatabase();

    void on_Modifier_planning_2_clicked();
//void updateCalendar(const QDate &date);
    void on_Ajouter_planning_2_clicked();
    void on_affiche_tab_activated(const QModelIndex &index);

   // void on_calend_clicked(const QDate &date);

    void on_call_clicked();




    void on_calend_selectionChanged();

    void on_pushButton_clicked();

    void on_btnWeather_clicked();

private:
    Ui::gestion_planning *ui;
    notification n;

};


#endif // GESTION_PLANNING_H

