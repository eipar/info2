/* ***** Botón Editar ***** */
#ifndef DIALOG3_H
#define DIALOG3_H

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
class Dialog3;
}

class Dialog3 : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog3(QWidget *parent = 0);
    ~Dialog3();

private slots:
    void on_comboBox_Ed_currentTextChanged(const QString &arg1);
    void on_buttonBox_Ed_accepted();

    void on_lineEdit_Ed_Luz_editingFinished();

    void on_lineEdit_Ed_RiegoDur_editingFinished();

private:
    Ui::Dialog3 *ui;
    void CargarDatos(void);                         //Cargo los distintos datos en los lineEdit
    void GuardarDatos(void);                        //Método para guardar los cambios en el archivo plantas.txt
};

#endif // DIALOG3_H
