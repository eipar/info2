/* ***** Botón Agregar ***** */
#ifndef DIALOG_H
#define DIALOG_H

//Libreria Manejo de Ventanas
#include <QDialog>

//Libreria Manejo de Archivo
#include <QFile>
#include <QTextStream>
#include <QString>

//Libreria Mensaje Pop Up
#include <QMessageBox>

//Libreria QTime para el TimeEdit
#include <QTime>
#include <QDateTime>
#include <QDateEdit>

//Librería de Prueba
#include <QDebug>

//Estructura Cultivo
typedef struct{
    QString Nombre;
    QString Temp_MAX;
    QString Temp_MIN;
    QString Humedad_MAX;
    QString Humedad_MIN;
    QString Luz_Horas_Dia;
    QString Riego_Hora_Inicio;
    QString Riego_Minu_Inicio;
    QString Riego_Duracion;
}Cultivo_Struct;

namespace Ui{
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();
    Cultivo_Struct aux;                                 //Declaro estructura auxiliar de cultivo para guardar datos

private slots:
    void on_buttonBox_accepted();

private:
    Ui::Dialog *ui;
    void EscribirArchivo(Cultivo_Struct);               //Escribimos el archivo plantas.txt}
    void Agregar(void);
};

#endif // DIALOG_H
