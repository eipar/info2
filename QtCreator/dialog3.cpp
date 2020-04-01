/* ***** Botón Editar ***** */
#include "dialog3.h"
#include "ui_dialog3.h"

Dialog3::Dialog3(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog3)
{
    ui->setupUi(this);

    CargarDatos();      //Cargo los datos de la planta seleccionada en el comboBox a los lineEdit

    connect(ui->buttonBox_Ed, SIGNAL(rejected()), this, SLOT(close()));     //Para cerrar la ventana
    connect(ui->buttonBox_Ed, SIGNAL(accepted()), this, SLOT(close()));     //Idem
}

Dialog3::~Dialog3()
{
    delete ui;
}

//Método para agregar al combobox_ListadoPlantas las plantas cargadas en el archivo plantas.txt
void Dialog3::CargarDatos(void){

    QFile Archivo("plantas.txt");                                           //Puntero al archivo
    QString Cultivo_Nombre;                                                 //Auxiliar para el nombre de la planta

    if(!Archivo.open(QFile::ReadOnly | QFile::Text)){                       //Abro el archivo en modo sólo lectura
        qDebug() << "Error al abrir archivo desde función LeerArchivo";
        return;
    }

    QTextStream in(&Archivo);                                               //Creo un flujo de datos

    while(!in.atEnd()){                                                     //Mientras no sea el final del archivo
        QString Renglon = in.readLine();                                    //Leo una linea
        //qDebug() << Renglon;
        if(Renglon == "<<"){                                                //Empezo bien la cadena
            Cultivo_Nombre = in.readLine();                                 //Leo el nombre de la planta
            ui->comboBox_Ed->addItem(Cultivo_Nombre);                       //Lo cargo al combobox
        }
    }

    Archivo.close();                                                        //Cierro el archivo
}

//Método para cambiar los datos mostrados en el lineEdit a medida que cambia la seleccion en el combobox
void Dialog3::on_comboBox_Ed_currentTextChanged(const QString &arg1)
{
    QFile Archivo("plantas.txt");                                                   //Abro el archivo

    if(!Archivo.open(QFile::ReadOnly | QFile::Text)){                               //Modo sólo lectura
        qDebug() << "Error al abrir archivo desde función LeerArchivo";
        return;
    }

    QTextStream in(&Archivo);                                                       //Flujo de datos de entrada

    while(!in.atEnd()){                                                             //Mientras no llegue al final
        QString Renglon = in.readLine();                                            //Leo una linea

        if(Renglon == arg1){                                                        //Si coincide con el nombre seleccionado en el combobox
                ui->lineEdit_Ed_Nombre->setText(Renglon);                           //Cargo todo a los lineEdit y sigo leyendo
                Renglon = in.readLine();
                ui->lineEdit_Ed_TempMax->setText(Renglon);
                Renglon = in.readLine();
                ui->lineEdit_Ed_TempMin->setText(Renglon);
                Renglon = in.readLine();
                ui->lineEdit_Ed_HumMax->setText(Renglon);
                Renglon = in.readLine();
                ui->lineEdit_Ed_HumMin->setText(Renglon);
                Renglon = in.readLine();
                ui->lineEdit_Ed_Luz->setText(Renglon);

                QString aux_hour, aux_minute;
                aux_hour = in.readLine();
                aux_minute = in.readLine();
                QTime time(aux_hour.toInt(), aux_minute.toInt());
                ui->timeEdit_Ed_RiegoInic->setTime(time);

                Renglon = in.readLine();
                ui->lineEdit_Ed_RiegoDur->setText(Renglon);
        }
    }

    Archivo.close();                                                            //Cierro el archivo
}

//Metodo para confirmar los cambios mediante un QMessageBox
void Dialog3::on_buttonBox_Ed_accepted()
{
    QMessageBox msgBox;

    //Creacion del messageBox
    msgBox.setText("Desea guardar los datos?");
    msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    msgBox.setIcon(QMessageBox::Critical);
    int Op = msgBox.exec();

    if(Op == QMessageBox::Ok){              //Si confirma los cambios, llamo a la funcion para guardarlos
        GuardarDatos();
    }
}

//Metodo para guardar los cambios al archivo
void Dialog3::GuardarDatos(void){
    QFile Archivo("plantas.txt");                               //Puntero al archivo plantas
    QFile Archivo_Copy("temp.txt");                             //Puntero a un archivo temporal

    if(!Archivo.open(QFile::ReadOnly | QFile::Text)){           //Abro el archivo plantas en sólo lectura
        qDebug() << "Error al abrir archivo plantas.txt";
        return;
    }

    if(!Archivo_Copy.open(QFile::WriteOnly | QFile::Text)){     //Abro el archivo temporal en sólo escritura
        qDebug() << "Error al abrir archivo aux.txt";
        return;
    }

    QTextStream in(&Archivo);                                       //Flujo de datos entrada
    QTextStream out(&Archivo_Copy);                                 //Flujo de datos salida

    while(!in.atEnd()){                                             //Mientras no llegue al final del archivo plantas
        QString Renglon;
        Renglon = in.readLine();                                    //Leo una linea

        if(Renglon == ui->comboBox_Ed->currentText()){              //Si coincide con la planta editada
            out << ui->lineEdit_Ed_Nombre->text()+"\n";             //Copio los nuevos datos, en vez de los viejos
            out << ui->lineEdit_Ed_TempMax->text()+"\n";
            out << ui->lineEdit_Ed_TempMin->text()+"\n";
            out << ui->lineEdit_Ed_HumMax->text()+"\n";
            out << ui->lineEdit_Ed_HumMin->text()+"\n";

            QString aux = ui->lineEdit_Ed_Luz->text();
            //qDebug() << aux;
            if(aux.toInt() < 10){
                if(aux.length() == 2){
                    aux.remove(0,1);
                }
               // qDebug() << aux;
                aux = "0"+aux;
            }
            out << aux+"\n";

            QString aux_time = ui->timeEdit_Ed_RiegoInic->time().toString();
            QString aux_hour = aux_time.remove(2,6);

            aux_time = ui->timeEdit_Ed_RiegoInic->time().toString();
            QString aux_minute = aux_time.remove(0,3);
            aux_minute = aux_time.remove(2,3);

            out << aux_hour+"\n";
            out << aux_minute+"\n";

            /*QTime aux_time;
            aux_time = ui->timeEdit_Ed_RiegoInic->time();
            out << aux_time.hour()+"\n";
            //qDebug() << aux_time.hour();
            out << aux_time.minute()+"\n";
            //qDebug() << aux_time.minute();
            */

            aux = ui->lineEdit_Ed_RiegoDur->text();
            //qDebug() << aux;
            if(aux.toInt() < 10){
                if(aux.length() == 2){
                    aux.remove(0,1);
                }
                //qDebug() << aux;
                aux = "0"+aux;
            }
            out << aux+"\n";

            for(int i = 0; i<8; i++)
                Renglon = in.readLine();                            //Me salteo los datos viejos de esa planta
        }else{                                                      //Sino, copio lo que estaba
            out << Renglon+"\n";
        }
    }

    in.flush();             //Limpio los flujos de datos
    out.flush();

    Archivo.close();        //Cierro los archivos
    Archivo_Copy.close();

    Archivo.remove();                                   //Elimino el plantaas.txt viejo, sin los cambios
    Archivo_Copy.rename("temp.txt", "plantas.txt");     //Renombro el archivo temporal
}
