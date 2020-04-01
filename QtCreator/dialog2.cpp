/* ***** Botón Eliminar ***** */
#include "dialog2.h"
#include "ui_dialog2.h"

Dialog2::Dialog2(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog2)
{
    ui->setupUi(this);

    CargarWidget();                                                         //Cargo los nombres de las plantas a eliminar en el ListWidget

    connect(ui->buttonBox_EP, SIGNAL(accepted()), this, SLOT(close()));     //Cierra la ventana cuando apreto Ok
}

Dialog2::~Dialog2()
{
    delete ui;
}

//Método para cargar las diferentes plantas en el ListWidget
void Dialog2::CargarWidget(void){
    QFile Archivo("plantas.txt");                           //Puntero a archivo
    QString Cultivo_Nombre;                                 //Auxiliar para cargar los nombres

    ui->listWidget_EP_Listado->clear();                     //Limpio el widget

    if(!Archivo.open(QFile::ReadOnly | QFile::Text)){       //Abro el archivo en sólo lectura
        qDebug() << "Error al abrir archivo desde función LeerArchivo";
        return;
    }

    QTextStream in(&Archivo);           //Flujo de datos de entrada

    while(!in.atEnd()){                                         //Mientras no llegue al final del archivo
        QString Renglon = in.readLine();                        //Leo una linea
        //qDebug() << Renglon;
        if(Renglon == "<<"){                                    //Empezo bien la cadena
            Cultivo_Nombre = in.readLine();                     //Leo el nombre
            ui->listWidget_EP_Listado->addItem(Cultivo_Nombre); //Adhiero en el listWidget el nombre de la planta
        }
    }

    Archivo.close();            //Cierro el archivo
}

//Al presionar el botón abro una ventana para confirmar la solicitud de eliminar planta
void Dialog2::on_pushButton_EP_clicked()
{
    QMessageBox msgBox;

    msgBox.setText("Se eliminará la planta:\t"+ui->listWidget_EP_Listado->currentItem()->text());   //Cargo texto junto con el nombre de la planta seleccionada
    msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);                               //Tendra dos botones Ok y Cancel
    msgBox.setIcon(QMessageBox::Critical);                                                          //Icono crítico
    int Op = msgBox.exec();                 //La funcion .exec devuelve cuál de los dos botones fueron presionados además de ejecutar la ventana

    if(Op == QMessageBox::Ok){              //Si apreto el botón ok, elimino la planta
        EliminarPlanta();
    }

    CargarWidget();                         //Actualizo el ListWidget
}

//Método para eliminar la planta seleccionada del archivo
void Dialog2::EliminarPlanta(void){
    QFile Archivo("plantas.txt");                               //Puntero al archivo
    QFile Archivo_Copy("temp.txt");                             //Puntero a un archivo temporal

    if(!Archivo.open(QFile::ReadOnly | QFile::Text)){           //Abro el archivo plantas.txt en modo sólo lectura
        qDebug() << "Error al abrir archivo plantas.txt";
        return;
    }

    if(!Archivo_Copy.open(QFile::WriteOnly | QFile::Text)){     //Abro el archivo temporal en modo sólo escritura
        qDebug() << "Error al abrir archivo aux.txt";
        return;
    }

    QTextStream in(&Archivo);                                   //Flujo de datos de entrada del archivo plantas
    QTextStream out(&Archivo_Copy);                             //Flujo de datos de salida del archivo temporal

    while(!in.atEnd()){                                         //Mientras no llegue al final del archivo
        QString Renglon;
        Renglon = in.readLine();                                //Leo una linea

        if(Renglon == ui->listWidget_EP_Listado->currentItem()->text()){    //Verifico si es la planta seleccionada
            for(int i = 0; i<9; i++){                           //Si lo es, la salteo. Muevo el puntero del flujo in
                Renglon = in.readLine();
            }
        }else{
            out << Renglon+"\n";                                //Si no lo es, copio los datos de plantas a temp
        }
    }

    in.flush();                 //Vacio el flujo de datos
    out.flush();

    Archivo.close();            //Cierro ambos archivos
    Archivo_Copy.close();

    Archivo.remove();           //Elimino el archivo plantas.txt CON la planta a eliminar
    Archivo_Copy.rename("temp.txt", "plantas.txt"); //Renombro el archivos temp a plantas SIN la planta a eliminar
}
