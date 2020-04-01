/* ***** Botón Eliminar ***** */
#ifndef DIALOG2_H
#define DIALOG2_H

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

namespace Ui {
class Dialog2;
}

class Dialog2 : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog2(QWidget *parent = 0);
    ~Dialog2();

private slots:
    void on_pushButton_EP_clicked();

private:
    Ui::Dialog2 *ui;
    void CargarWidget(void);                //Cargo los distintos nombres de las plantas a eliminar
    void EliminarPlanta(void);              //Método para eliminar dicha planta del archivo plantas.txt
};

#endif // DIALOG2_H
