/* ***** Botón Agregar ***** */
#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(close()));        //Para cerrar la ventana cuando se presiona el botón Ok
    connect(ui->buttonBox, SIGNAL(rejected()), this, SLOT(close()));        //Idem boton cancel
}

Dialog::~Dialog()
{
    delete ui;
}

//Método para escribir en el Archivo "plantas.txt" la nueva planta a agregar
void Dialog::EscribirArchivo(Cultivo_Struct Data_In){
    QFile Archivo("plantas.txt");                                               //Puntero al archivo

    if(!Archivo.open(QFile::Append | QFile::WriteOnly | QFile::Text)){          //Abro el archivo en sólo escritura y para adherir al final del mismo
        qDebug() << "Error al abrir archivo desde función EscribirArchivo";
        return;
    }

    QTextStream out(&Archivo);                              //Flujo de datos
    out << "<<\n";                                        //Escribo el indicador del comienzo de una planta
    out << Data_In.Nombre+"\n";
    out << Data_In.Temp_MAX+"\n";
    out << Data_In.Temp_MIN+"\n";
    out << Data_In.Humedad_MAX+"\n";
    out << Data_In.Humedad_MIN+"\n";
    out << Data_In.Luz_Horas_Dia+"\n";
    out << Data_In.Riego_Hora_Inicio+"\n";
    out << Data_In.Riego_Minu_Inicio+"\n";
    out << Data_In.Riego_Duracion+"\n";

    out.flush();                                    //Limpio el flujo de datos
    Archivo.close();                                //Cierro el archivo
}

void Dialog::on_buttonBox_accepted()
{
    QMessageBox msgBox;

    msgBox.setText("Se agregará la planta:\t"+ui->lineEdit_AP_Nombre->text());   //Cargo texto junto con el nombre de la planta seleccionada
    msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);            //Tendra dos botones Ok y Cancel
    msgBox.setIcon(QMessageBox::Information);                                    //Icono info
    int Op = msgBox.exec();                 //La funcion .exec devuelve cuál de los dos botones fueron presionados además de ejecutar la ventana

    if(Op == QMessageBox::Ok){              //Si apreto el botón ok, agrego la planta
        Agregar();
    }
}

void Dialog::Agregar(void){
    //QTime aux_time;         //Auxiliar para el TimeEdit

    //Cargo en la auxiliar de la clase los datos cargados en la venta
    aux.Nombre = ui->lineEdit_AP_Nombre->text();
    aux.Temp_MAX = ui->lineEdit_AP_TempMax->text();
    aux.Temp_MIN = ui->lineEdit_AP_TempMin->text();
    aux.Humedad_MAX = ui->lineEdit_AP_HumMax->text();
    aux.Humedad_MIN = ui->lineEdit_AP_HumMin->text();

    QString aux_LD = ui->lineEdit_AP_Luz->text();
   // qDebug() << aux_LD;
    if(aux_LD.toInt() < 10){
        if(aux_LD.length() == 2){
            aux_LD.remove(0,1);
        }
        //qDebug() << aux_LD;
        aux_LD = "0"+aux_LD;
    }
    aux.Luz_Horas_Dia = aux_LD;

    QString aux_time = ui->timeEdit_AP_RiegoInic->time().toString();
    aux.Riego_Hora_Inicio = aux_time.remove(2,6);

    aux_time = ui->timeEdit_AP_RiegoInic->time().toString();
    aux.Riego_Minu_Inicio = aux_time.remove(0,3);
    aux.Riego_Minu_Inicio = aux_time.remove(2,3);

    aux_LD = ui->lineEdit_AP_RiegoDur->text();
    //qDebug() << aux_LD;
    if(aux_LD.toInt() < 10){
        if(aux_LD.length() == 2){
            aux_LD.remove(0,1);
        }
        //qDebug() << aux_LD;
        aux_LD = "0"+aux_LD;
    }
    aux.Riego_Duracion = aux_LD;

    EscribirArchivo(aux);   //Llamo a la función para escribir archivo
}
