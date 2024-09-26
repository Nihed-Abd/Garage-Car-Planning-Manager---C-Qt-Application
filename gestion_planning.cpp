#include "gestion_planning.h"
#include "notification.h"
#include "ui_gestion_planning.h"
#include "planning.h"
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <QSqlError>
#include <QPixmap>
#include <iostream>
#include <QFileDialog>
#include <QMessageBox>
#include <QSqlQuery>
#include <QPdfWriter>
#include <QPainter>
#include <QDebug>
#include <QToolTip>
#include <QStackedWidget>
#include <QFileDialog>
#include <QMap>
#include <QFile>
#include <QString>
#include <QApplication>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>
#include <QtCharts>
#include <QFileDialog>
#include <QPrinter>
#include <QPainter>
#include <QRegularExpression>
#include<QSqlQueryModel>
#include <QTableView>
#include <QStandardItemModel>
#include <QTextDocument>
#include <QTextStream>
#include <QAbstractItemModel>
#include <QModelIndex>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QtCharts/QChartView>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QPieSeries>
#include <QImage>
#include <QCryptographicHash>
#include <QUrl>
#include <QJsonDocument>
#include <QJsonObject>
#include <QVariant>
#include <QtCore>
#include <QtGui>
#include <cstdlib>
#include <QByteArray>
#include <QPainter>
#include <QDesktopServices>
#include <QUrl>
#include <QAbstractItemModel>
#include <QFileDialog>
#include <QMessageBox>
#include <QSqlQuery>
#include <QtCharts/QPieSeries>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QLegend>
#include <QStringList>
#include <QVector>
#include <QHash>
#include <QPieSeries>
#include <QChart>
#include <QChartView>
#include <QMainWindow>
#include <QtGlobal> // Pour certaines macros comme QT_VERSION_CHECK
#include <QSqlQueryModel>
#include <QSqlRecord>
#include <QMessageBox> // Pour utiliser QMessageBox
#include <QPieSeries>
#include <QDebug>
#include <QSqlQuery>

#include <QVariant>

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>

// Ajoutez d'autres inclusions selon les besoins




gestion_planning::gestion_planning(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::gestion_planning)
{



    planning tr;
    ui->setupUi(this);      //affichage du tab des lentree
    ui->affiche_tab->setModel(tr.afficher());
    ui->affiche_tab_2->setModel(n.afficher());

    // Connexion du signal textChanged au slot checkMatriculeLength
    connect(ui->MATRICULE, &QLineEdit::textChanged, this, &gestion_planning::checkMatriculeLength);
    connect(ui->IDACTIVITE, &QLineEdit::textChanged, this, &gestion_planning::checkActiviteLength);
    connect(ui->IDEMPLOYE, &QLineEdit::textChanged, this, &gestion_planning::checkEmployeLength);
    connect(ui->M3_planning_2, &QPushButton::clicked, this, &gestion_planning::on_M3_planning_2_clicked);

    connect(ui->M2_planning_3, &QPushButton::clicked, this, &gestion_planning::on_M2_planning_3_clicked);

        //  calendarWidget->setToolTipText(DATE, tooltip);

}




gestion_planning::~gestion_planning()
{
    delete ui;
}
void gestion_planning::on_Chercher_planning_2_clicked()
{
    // Créer un objet planning pour récupérer les données
    planning tr;

    // Obtenir le modèle de données pour le tableau
    QSqlQueryModel* model = tr.afficher();

    // Afficher les données dans le tableau
    ui->affiche_tab->setModel(model);
}


void gestion_planning::on_Effacer_planning_2_clicked()
{
    planning f;
       int MATRICULE = ui->MATRICULE->text().toInt();
       bool test = f.supprimer(MATRICULE);
       if (test) {
           // Add notification after modifying planning
           QString notif = "Planning with ID = " + QString::number(MATRICULE) + " Added";
           notification n;
           n.setDate(QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss"));
           n.setNotif(notif);
           n.ajouter();
           QMessageBox::information(nullptr, QObject::tr("Ok"),
                                    QObject::tr("Suppression effectuée.\n"
                                                "Click Ok to exit."), QMessageBox::Ok);
       } else {
           QMessageBox::critical(nullptr, QObject::tr("Not ok"),
                                 QObject::tr("Échec de la suppression.\n"
                                             "Le fournisseur n'existe pas dans la base de données."),
                                 QMessageBox::Cancel);
       }
       ui->affiche_tab->setModel(f.afficher());
       ui->affiche_tab_2->setModel(n.afficher());


}



void gestion_planning::on_Modifier_planning_2_clicked()
{
    // Récupérer les valeurs des champs texte
    QString matriculeString = ui->MATRICULE->text();
    QString idActiviteString = ui->IDACTIVITE->text();
    QString idEmployeString = ui->IDEMPLOYE->text();
    QDate date = ui->DATE->date();
    QString status = ui->STATUS->currentText();

    // Vérifier si les champs ne sont pas vides
    if (matriculeString.isEmpty() || idActiviteString.isEmpty() || idEmployeString.isEmpty()) {
        QMessageBox::warning(this, "Champs vides", "Veuillez remplir tous les champs.");
        return;
    }

    // Convertir les valeurs en entiers
    bool matriculeOk, idActiviteOk, idEmployeOk;
    int matricule = matriculeString.toInt(&matriculeOk);
    int idActivite = idActiviteString.toInt(&idActiviteOk);
    int idEmploye = idEmployeString.toInt(&idEmployeOk);

    // Vérifier si les champs ID Activité et ID Employé sont des entiers
    if (!idActiviteOk || !idEmployeOk) {
        QMessageBox::warning(this, "Erreur de saisie", "Les champs ID Activité et ID Employé doivent être des entiers.");
        return;
    }

    // obj
    planning f(matricule, date, idActivite, idEmploye, status);

    if (f.modifier(matricule, date, idActivite, idEmploye, status)) {
        // Add notification after modifying planning
        QString notif = "Planning with ID = " + QString::number(matricule) + " Added";
        notification n;
        n.setDate(QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss"));
        n.setNotif(notif);
        n.ajouter();
        ui->affiche_tab->setModel(f.afficher());
        ui->affiche_tab_2->setModel(n.afficher());

        QMessageBox::information(this, "Modification réussie", "Les données ont été modifiées avec succès.");

    } else {
        QMessageBox::critical(this, "Erreur de modification", "Échec de la modification des données.");
    }

}



void gestion_planning::on_Ajouter_planning_2_clicked()
{

    QString id_MATRICULE_string = ui->MATRICULE->text();
    QString id_IDACTIVITE_string = ui->IDACTIVITE->text();
    QString id_IDEMPLOYE_string = ui->IDEMPLOYE->text();
    QDate DATE = ui->DATE->date();
    QString STATUS = ui->STATUS->currentText();

    if (id_MATRICULE_string.isEmpty() || id_IDACTIVITE_string.isEmpty() || id_IDEMPLOYE_string.isEmpty() || DATE.isNull()) {
        QMessageBox::warning(this, "Champs vides", "Veuillez remplir tous les champs.");
        return;
    }

    bool idActiviteOk, idEmployeOk;
    int IDACTIVITE = id_IDACTIVITE_string.toInt(&idActiviteOk);
    int IDEMPLOYE = id_IDEMPLOYE_string.toInt(&idEmployeOk);

    if (!idActiviteOk || !idEmployeOk) {
        QMessageBox::warning(this, "Erreur de saisie", "Les champs ID Activité et ID Employé doivent être des entiers.");
        return;
    }

    // Vérifier si la longueur de la matricule est inférieure à 8
    if (id_MATRICULE_string.length() < 8) {
        QMessageBox::warning(this, "Erreur de saisie", "La matricule doit comporter au moins 8 chiffres.");
        return;
    }

    // Convertir la matricule en entier
    bool matriculeOk;
    int MATRICULE = id_MATRICULE_string.toInt(&matriculeOk);

    // Vérifier si la conversion en entier a réussi et si la matricule est valide
    if (!matriculeOk) {
        QMessageBox::warning(this, "Erreur de saisie", "La matricule doit être un entier.");
        return;
    }

    // Vérifier si la matricule ne dépasse pas 8 chiffres
    if (MATRICULE > 99999999) {
        QMessageBox::warning(this, "Erreur de saisie", "La matricule ne doit pas dépasser 8 chiffres.");
        return;
    }


    QDate dateTime =DATE;
    if (!dateTime.isValid()) {
        QMessageBox::warning(this, "Erreur de saisie", "Veuillez entrer une date et une heure valides au format 'dd/MM/yyyy'.");
        return;
    }

    // Création de l'objet planning avec les données saisies
    planning tr(MATRICULE, DATE, IDACTIVITE, IDEMPLOYE, STATUS);

    // Ajout de l'objet à la base de données et affichage d'un message approprié
    if (tr.ajouter()) {

        // Add notification after modifying planning
        QString notif = "Planning with ID = " + QString::number(MATRICULE) + " Added";
        notification n;
        n.setDate(QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss"));
        n.setNotif(notif);
        n.ajouter();

        QMessageBox::information(this, "Ajout réussi", "Ajout avec succès.");
        ui->IDACTIVITE->clear();
        ui->IDEMPLOYE->clear();
        ui->DATE->clear();
        ui->MATRICULE->clear();
        ui->STATUS->clear();
    } else {
        QMessageBox::critical(this, "Erreur d'ajout", "Échec de l'ajout.");
    }

    // Affichage des données mises à jour dans le tableau
    ui->affiche_tab->setModel(tr.afficher());
    ui->affiche_tab_2->setModel(n.afficher());


}
void gestion_planning::checkMatriculeLength(const QString &text)
{

    if (text.length() >= 8) {

        ui->MATRICULE->setText(text.left(8));


    }
}

void gestion_planning::on_affiche_tab_activated(const QModelIndex &index)
{

        QString val=ui->affiche_tab->model()->data(index).toString();
        QSqlQuery qry;
        qry.prepare("select * from PLANING where MATRICULE='"+val+"'");
        if(qry.exec())
        {
         while(qry.next())
         {ui->MATRICULE->setText(qry.value(0).toString());
          ui->DATE->setDate(qry.value(1).toDate());
          ui->IDACTIVITE->setText(qry.value(2).toString());
          ui->IDEMPLOYE->setText(qry.value(3).toString());
          ui->STATUS->addItem(qry.value(4).toString());

         }
        }
        else
        {
         QMessageBox::critical(this,tr("error::"),qry.lastError().text());
        }






}


// Slot pour le contrôle de saisie de la longueur du champ ID Activité
void gestion_planning::checkActiviteLength(const QString &text)
{
    if (text.length() > 8) {
        ui->IDACTIVITE->setText(text.left(8));
    }
}

// Slot pour le contrôle de saisie de la longueur du champ ID Employé
void gestion_planning::checkEmployeLength(const QString &text)
{
    if (text.length() > 8) {
        ui->IDEMPLOYE->setText(text.left(8));
    }
}

// Connecter les signaux des champs ID Activité et ID Employé aux slots de contrôle de saisie


void gestion_planning::on_M1_planning_2_clicked()
{
    // Récupérer le matricule à rechercher
    QString matriculeString = ui->MATRICULE->text();

    // Vérifier si le champ du matricule n'est pas vide
    if (matriculeString.isEmpty()) {
        QMessageBox::warning(this, "Champ vide", "Veuillez saisir un matricule.");
        return;
    }

    // Convertir le matricule en entier
    bool matriculeOk;
    int matricule = matriculeString.toInt(&matriculeOk);

    // Vérifier si le matricule est valide
    if (!matriculeOk) {
        QMessageBox::warning(this, "Erreur de saisie", "Le matricule doit être un entier.");
        return;
    }

    // Créer un objet planning pour effectuer la recherche
    planning tr;

    // Effectuer la recherche dans la base de données
    QSqlQueryModel* model = tr.afficher(); // Obtenir le modèle actuel
    model->setQuery("SELECT * FROM PLANING WHERE MATRICULE = " + QString::number(matricule));

    // Vérifier si la recherche a retourné des résultats
    if (model->rowCount() > 0) {
        // Afficher les résultats dans le tableau
        ui->affiche_tab->setModel(model);

        // Afficher un message de succès
        QMessageBox::information(this, "Recherche réussie", "La recherche a retourné des résultats.");
    } else {
        // Aucun résultat trouvé, afficher un message d'erreur
        QMessageBox::information(this, "Aucun résultat", "Aucun résultat trouvé pour ce matricule.");
    }
}
void gestion_planning::on_M2_planning_2_clicked()
{
    // Créer un objet planning pour effectuer le tri
    planning tr;

    // Obtenir le modèle actuel
    QSqlQueryModel* model = tr.afficher();

    // Définir la requête SQL pour trier les entrées par statut (confirmé en premier, puis refusé)
    QString queryString = "SELECT * FROM PLANING ORDER BY CASE WHEN STATUS='CONFIRMER' THEN 1 WHEN STATUS='REFUSER' THEN 2 ELSE 3 END";
    qDebug() << "Query: " << queryString;
    model->setQuery(queryString);

    // Vérifier les éventuelles erreurs lors de l'exécution de la requête
    if (model->lastError().isValid()) {
        qDebug() << "Database error: " << model->lastError().text();
    }

    // Afficher les résultats triés dans le tableau
    ui->affiche_tab->setModel(model);
}
void gestion_planning::on_M2_planning_3_clicked()
{
    // Créer un objet planning pour effectuer le tri
    planning tr;

    // Obtenir le modèle actuel
    QSqlQueryModel* model = tr.afficher(); // Assurez-vous que cette fonction retourne un modèle de données valide

    // Définir la requête SQL pour trier les entrées par DATEE (croissant)
    QString queryString = "SELECT * FROM PLANING ORDER BY DATEE ASC";
    qDebug() << "Query: " << queryString;
    model->setQuery(queryString);

    // Vérifier les éventuelles erreurs lors de l'exécution de la requête
    if (model->lastError().isValid()) {
        qDebug() << "Database error: " << model->lastError().text();
    }

    // Afficher les résultats triés dans le tableau
    ui->affiche_tab->setModel(model);
}

void gestion_planning::on_M4_planning_2_clicked()
{
    // Créer un objet planning pour accéder aux données
    planning tr;

    // Calculer les statistiques
    int totalStatus = 0;
    int confirmerCount = 0;
    int refuserCount = 0;

    // Obtenir le modèle actuel
    QSqlQueryModel* model = tr.afficher();

    // Parcourir les données pour compter les occurrences de chaque status
    for (int i = 0; i < model->rowCount(); ++i) {
        QString STATUS = model->record(i).value("STATUS").toString();
        if (STATUS == "CONFIRMER") {
            confirmerCount++;
        } else if (STATUS == "REFUSER") {
            refuserCount++;
        }
        totalStatus++;
    }

    // Calculer les pourcentages
    qreal confirmerPercentage = (qreal)confirmerCount / totalStatus * 100;
    qreal refuserPercentage = (qreal)refuserCount / totalStatus * 100;

    // Créer le diagramme circulaire (camembert)
    QPieSeries *series = new QPieSeries();
          series->append(QString("CONFRIMER (%1%)").arg(confirmerPercentage), confirmerPercentage);
          series->append(QString("REFUSER  (%1%)").arg(refuserPercentage), refuserPercentage);



    // Définir les couleurs des segments du diagramme
    series->slices().at(0)->setColor(Qt::green);  // Couleur pour CONFIRMER
    series->slices().at(1)->setColor(Qt::red);    // Couleur pour REFUSER

    // Créer le diagramme et le visualiser dans une vue
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Répartition des Status");

    // Créer la vue du diagramme
    QChartView *chartView = new QChartView(chart);
         chartView->setRenderHint(QPainter::Antialiasing);

    // Générer un PDF contenant le diagramme

    QMainWindow *statWindow = new QMainWindow();
           statWindow->setCentralWidget(chartView);
           statWindow->resize(400, 300);
           statWindow->show();


}


void gestion_planning::on_M3_planning_2_clicked()
{
    // Récupérer le matricule
    QString matriculeString = ui->MATRICULE->text();

    // Vérifier si le champ du matricule n'est pas vide
    if (matriculeString.isEmpty()) {
        QMessageBox::warning(this, "Champ vide", "Veuillez choisir une matricule.");
        return;
    }

    // Convertir le matricule en entier
    bool matriculeOk;
    int matricule = matriculeString.toInt(&matriculeOk);

    // Créer un nom de fichier unique
    QString fileName = QString("monplanning_") + QString::number(matricule) + ".pdf";

    // Créer un objet QPdfWriter pour écrire dans le fichier PDF
    QPdfWriter writer(fileName);
    writer.setPageSize(QPageSize(QPageSize::A4)); // Définir la taille de la page A4
    writer.setPageOrientation(QPageLayout::Portrait); // Définir l'orientation de la page en portrait
    QPainter painter(&writer);

    // Définir la police et la taille du texte
    QFont font;
    font.setPointSize(12);
    font.setBold(true);
    painter.setFont(font);

    // Position Y initiale
    int yPos = 20;

    // Commencer à dessiner sur le PDF
    painter.drawText(20, yPos, "ID Activite: " + ui->IDACTIVITE->text());
    yPos += 400; // Espacement entre les lignes
    painter.drawText(20, yPos, "ID Planning: " + ui->MATRICULE->text());
    yPos += 400; // Espacement entre les lignes
    painter.drawText(20, yPos, "Date: " + ui->DATE->text());
    yPos += 400; // Espacement entre les lignes
    painter.drawText(20, yPos, "Statut: " + ui->STATUS->currentText());



    // Terminer de dessiner et finaliser le PDF
    painter.end();

    QMessageBox::information(this, "PDF généré", "Le PDF a été généré avec succès.");

    // Ouvrir le PDF dans l'application par défaut
    QDesktopServices::openUrl(QUrl::fromLocalFile(fileName));
}
void gestion_planning::on_M2_planning_4_clicked()
{
    // Créer un objet planning pour effectuer le tri
    planning tr;

    // Obtenir le modèle actuel
    QSqlQueryModel* model = tr.afficher(); // Assurez-vous que cette fonction retourne un modèle de données valide

    // Définir la requête SQL pour trier les entrées par DATEE (décroissant)
    QString queryString = "SELECT * FROM PLANING ORDER BY DATEE DESC"; // Utiliser DESC pour le tri décroissant
    qDebug() << "Query: " << queryString;
    model->setQuery(queryString);

    // Vérifier les éventuelles erreurs lors de l'exécution de la requête
    if (model->lastError().isValid()) {
        qDebug() << "Database error: " << model->lastError().text();
    }

    // Afficher les résultats triés dans le tableau
    ui->affiche_tab->setModel(model);
}


void gestion_planning::on_call_clicked()
{
     ui->stackedWidget->setCurrentIndex(1);

   }


        void gestion_planning::on_calend_selectionChanged()
        {

            QDate x1=ui->calend->selectedDate();
            planning m;
           ui->ttw->setModel(m.afficher_calendar(x1));
        }

void gestion_planning::on_pushButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}


void gestion_planning::on_btnWeather_clicked()
{
    QString apiKey = "YOUR_API_KEY";

    // Replace LOCATION with the location you want to fetch weather for (e.g., city name or lat/long)
    QString location = "LOCATION";

    // Construct the API URL
    QString apiUrl = "https://www.googleapis.com/calendar/v3/calendars/" + location + "/weather?key=" + apiKey;

    // Create a network access manager to send the request
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    connect(manager, &QNetworkAccessManager::finished, this, &gestion_planning::onWeatherReply);

    // Send a GET request to the API URL
    manager->get(QNetworkRequest(QUrl(apiUrl)));
}

void gestion_planning::onWeatherReply(QNetworkReply *reply)
{
    // Check for errors in the network reply
    if (reply->error() != QNetworkReply::NoError) {
        QMessageBox::warning(this, "Network Error", "Failed to fetch weather information.");
        return;
    }

    // Read the response data
    QByteArray responseData = reply->readAll();
    reply->deleteLater();

    // Parse the JSON response
    QJsonDocument jsonResponse = QJsonDocument::fromJson(responseData);
    QJsonObject jsonObject = jsonResponse.object();

    // Extract weather information from the JSON object
    if (jsonObject.contains("items")) {
        QJsonArray itemsArray = jsonObject.value("items").toArray();
        if (!itemsArray.isEmpty()) {
            QJsonObject itemObject = itemsArray.first().toObject();
            if (itemObject.contains("summary")) {
                QString weatherSummary = itemObject.value("summary").toString();
                // Display the weather summary in a QMessageBox or update a label on your UI
                QMessageBox::information(this, "Weather Information", weatherSummary);
                return;
            }
        }
    }

    // Display an error message if weather information couldn't be retrieved
    QMessageBox::warning(this, "Weather Error", "Failed to retrieve weather information.");
}
