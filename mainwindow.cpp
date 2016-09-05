#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    db = QSqlDatabase::addDatabase("QPSQL", "first");
    db.setHostName("localhost");
    db.setDatabaseName("rtpq");
    db.setUserName("postgres");
    db.setPassword("tr0561");
    db.setPort(5432);



    // Connect from another window
    // QSqlDatabase defaultDB = QSqlDatabase::database("first");




}

MainWindow::~MainWindow()
{

    if (dbOk)
        db.close();

    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    dbOk = db.open();


    if(dbOk != true)
    {
        qDebug("Connection Failed!") ;
    }
    else
    {
        qDebug("Connection OK!") ;

    }
}

void MainWindow::on_pushButton_2_clicked()
{

   QSqlQuery query(db);
   QSqlDatabase defaultDB = QSqlDatabase::database("first");

    query.exec("select * from pqd");


    if( !query.exec("select * from pqd") )
    {
               qDebug() <<"Error = " << db.lastError().text();

    }
    else
    {

        if (defaultDB.driver()->hasFeature(QSqlDriver::QuerySize))
            qDebug("Record Count: %d", query.size());

        if (query.size()>0)
        {

            while (query.next())
            {
                  QByteArray dataUnsigned = query.value(3).toByteArray();

                  qDebug("Byte Array Size: %d", dataUnsigned.size());

                  short *values = (short *)dataUnsigned.data();

                  qDebug("Value : %d", values[0]);
                  qDebug("Value : %d", values[1]);
                  qDebug("Value : %d", values[2]);
            }

        }


    }



}

void MainWindow::on_pushButton_3_clicked()
{
    short data[3] = {728, 633, -25};

    QByteArray ba((char*)data, sizeof(data));

    // qDebug("Sizeof: %d" ,sizeof(data));


    QSqlQuery sql(db);

    QString query = "INSERT INTO pqd(type, raw_data) VALUES(:type,:raw_data)";


    sql.prepare(query);

    sql.bindValue(":raw_data", ba);
    sql.bindValue(":type", 1);


     if( !sql.exec() ) {
         qDebug("Error while Insert");

          qDebug() <<"Error = " << db.lastError().text();


     }







}
