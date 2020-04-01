#ifndef MAINWINDOW_H
#define MAINWINDOW_H

//Librerias varias
#include <QMainWindow>
#include <QString>

//Libreria Manejo de Archivo
#include <QFile>
#include <QTextStream>

//Libreria para las ventanas
#include "dialog.h"
#include "dialog2.h"
#include "dialog3.h"

//Libreria para probar cosas por comando
#include <QDebug>

//Libreria Puerto Serie
#include <qextserialport.h>
#include <qextserialenumerator.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_PuertoSerie_Conectar_clicked();                          //Método de conexión en el puerto serie mediante el botón
    void onDatosRecibidos();                                                    //Recibo datos
    void on_comboBox_ListadoPlantas_currentTextChanged(const QString &arg1);    //Cargolos datos en el listWidget de la planta seleccionada
    void on_pushButton_AgregarPlanta_clicked();                                 //Abro la ventana para agregar plantas
    void on_pushButton_EliminarPlanta_clicked();                                //Abro la ventana eliminar plantas
    void on_pushButton_EditarPlanta_clicked();                                  //Abro la ventana edición plantas
    void on_pushButton_Prueba_clicked();                                        //Prueba del Hardware del Invernadero
    void on_pushButton_PuertoSerie_Enviar_clicked();

    void on_listWidget_ListadoPlantas_clicked(const QModelIndex &index);

private:
    Ui::MainWindow *ui;

    //Puerto Serie
    QextSerialPort  *Serial_Port;
    bool            Serial_Port_Conected;
    int             m_cant_bytes_recibidos;
    int             m_cant_bytes_enviados;
    QByteArray      Buffer_Recepcion;

    struct
    {
        BaudRateType    BaudRate;
        QString         Nombre;
    }Tipos_BaudRate[5];

    void EnumerarPuertos(void);
    void EnumerarVelocidades(void);
    void EnviarComando(QString );                       //Envia por Puerto Serie
    void ProcesarDatosRecibidos(QByteArray &bytes);     //Procesa datos recibidos por PS
    void CerrarPuerto();                                //Cierra el PS abierto
    void LeerArchivo_NombrePlantas(void);               //Carga desde archivo los nombres de las plantas para el combobox
    QString Trama(QString);                                //Crea la trama con los datos de la planta seleccionada
};

#endif // MAINWINDOW_H
