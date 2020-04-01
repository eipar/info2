#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    Serial_Port_Conected = false;   //Mando por default que el PS está desconectado
    ui->setupUi(this);

    EnumerarPuertos();              //Método para enumerar los distintos puertos disponibles en el combobox
    EnumerarVelocidades();          //Método para enumerar las distintas velocidades de envio/recepcion
    LeerArchivo_NombrePlantas();    //Cargo en el combobox todas las plantas en el archivo plantas.txt
}

MainWindow::~MainWindow()
{
    delete ui;
}

/* ************ Puerto Serie ************ */

//Botón Conectar Puerto Serie
void MainWindow::on_pushButton_PuertoSerie_Conectar_clicked()
{
    if(Serial_Port_Conected == false)//Si no esta conectado
    {
        //Obtenemos el nombre del puerto
        QString sPort;

        int i = ui->comboBox_Puertos->currentIndex();

        if (i != -1 && ui->comboBox_Puertos->itemText(i) == ui->comboBox_Puertos->currentText())
            sPort = ui->comboBox_Puertos->itemData(i).toString();
        else
            sPort = ui->comboBox_Puertos->currentText();

        //sPort = ui->comboBox_Puertos->itemData(i).toString();

        Serial_Port = new QextSerialPort(sPort, QextSerialPort::EventDriven); //Crea el objeto del tipo PS

        //Seteo la configuración del PS
        Serial_Port->setBaudRate(BAUD9600); //Velocidad seleccionada en el combobox
        Serial_Port->setFlowControl(FLOW_OFF);  //Sin control de flujo
        Serial_Port->setParity(PAR_NONE);		//Sin paridad
        Serial_Port->setDataBits(DATA_8);		//8 bits de datos
        Serial_Port->setStopBits(STOP_1);		//1 bit de stop

        if (Serial_Port->open(QIODevice::ReadWrite) == true)	//Abrimos el puerto en modo lectura-escritura
        {
            //Conectamos las señales que nos interesen
            connect(Serial_Port, SIGNAL(readyRead()), this, SLOT(onDatosRecibidos()));

            Serial_Port_Conected = true;
            ui->plainTextEdit_PuertoSerie->appendPlainText("Conectado");
            ui->pushButton_PuertoSerie_Conectar->text() = "Desconectar";
        }else{
            //Hubo un error en abrir el Puerto
            ui->pushButton_PuertoSerie_Conectar->text() = "Conectar";
            ui->plainTextEdit_PuertoSerie->appendPlainText("ERROR");
            CerrarPuerto();
        }
    }else{
        //No se conecto
        ui->pushButton_PuertoSerie_Conectar->text() = "Conectar";
        ui->plainTextEdit_PuertoSerie->appendPlainText("Desconectado");
        Serial_Port_Conected = false;
        CerrarPuerto();
    }
}

//Método de lectura de los datos recibidos por Puerto Serie
void MainWindow::onDatosRecibidos()
{
    QByteArray bytes;
    int cant = Serial_Port->bytesAvailable();       //Determino la cantidad de bytes disponibles para envio
    bytes.resize(cant);                             //Vuelvo a determinar el tamaño del buffer según los bytes disponibles

    Serial_Port->read(bytes.data(), bytes.size());  //Leo el puerto

    ProcesarDatosRecibidos(bytes);                  //Llamo al método para procesar los datos recibidos
}

//Método para mostrar en el puerto serie los diferentes puertos disponibles
void MainWindow::EnumerarPuertos()
{
    ui->comboBox_Puertos->clear();

    QList<QextPortInfo> ports = QextSerialEnumerator::getPorts();       //Obtengo los puertod

    for (int i = 0; i < ports.size(); i++)
    {

    #ifdef Q_OS_WIN                                     //Los agrego según el sistema operativo
            ui->comboBox_Puertos->addItem(ports.at(i).friendName, ports.at(i).portName);
    #elif (defined Q_OS_UNIX)
            ui->comboBox_Puertos->addItem(ports.at(i).friendName, ports.at(i).physName);
    #endif

            /*qDebug() << "port name:" << ports.at(i).portName;
            qDebug() << "friendly name:" << ports.at(i).friendName;
            qDebug() << "physical name:" << ports.at(i).physName;
            qDebug() << "enumerator name:" << ports.at(i).enumName;
            qDebug() << "vendor ID:" << QString::number(ports.at(i).vendorID, 16);
            qDebug() << "product ID:" << QString::number(ports.at(i).productID, 16);*/
    }
}

//Método para enumerar las distintas velocidades del puerto en el combobox
void MainWindow::EnumerarVelocidades()
{
    Tipos_BaudRate[0].BaudRate = BAUD9600;
    Tipos_BaudRate[0].Nombre = "9600";
    Tipos_BaudRate[1].BaudRate = BAUD19200;
    Tipos_BaudRate[1].Nombre = "19200";
    Tipos_BaudRate[2].BaudRate = BAUD38400;
    Tipos_BaudRate[2].Nombre = "38400";
    Tipos_BaudRate[3].BaudRate = BAUD57600;
    Tipos_BaudRate[3].Nombre = "57600";
    Tipos_BaudRate[4].BaudRate = BAUD115200;
    Tipos_BaudRate[4].Nombre = "115200";

    for(int i = 0 ; i < 5 ; i++)
        ui->comboBox_BaudRate->addItem(Tipos_BaudRate[i].Nombre);
}

//Método de procesamiento de los datos recibidos por Puerto Serie
void MainWindow::ProcesarDatosRecibidos(QByteArray & bytes)
{
    int i;

    for( i = 0 ; i < bytes.size() ; i++)
    {
        if( (bytes.at(i) >= 32) && (bytes.at(i) <= 127) )
        {
            Buffer_Recepcion.append(bytes.at(i));
        }

        if(bytes.at(i) == 13 || bytes.at(i) == 10)
        {
            ui->plainTextEdit_PuertoSerie->appendPlainText(Buffer_Recepcion);

            m_cant_bytes_recibidos += Buffer_Recepcion.size();

            Buffer_Recepcion.clear();
        }
    }
}

//Método para enviar por puerto serie
void MainWindow::EnviarComando(QString comando)
{
    QByteArray send = comando.toLatin1();    //Convierte a Ascii solo que en el Qt5 es así
    send = comando.toLocal8Bit();
    char*pun = send.data();

    if (Serial_Port){                                   //Si existe el puerto
        //Serial_Port->write(send);                       //Escribo en el mismo
        for(int i=0; i<24; i++){
          Serial_Port->putChar(pun[i]);
          for(int j=0; j<10; j++);
        }
       /*   Serial_Port->putChar('<');
          Serial_Port->putChar('T');
          Serial_Port->putChar('8');
          Serial_Port->putChar('0');
          Serial_Port->putChar('6');
          Serial_Port->putChar('0');
          Serial_Port->putChar('H');
          Serial_Port->putChar('3');
          Serial_Port->putChar('0');
          Serial_Port->putChar('1');
          Serial_Port->putChar('0');
          Serial_Port->putChar('I');
          Serial_Port->putChar('0');
          Serial_Port->putChar('2');
          Serial_Port->putChar('R');
          Serial_Port->putChar('1');
          Serial_Port->putChar('8');
          Serial_Port->putChar('1');
          Serial_Port->putChar('5');
          Serial_Port->putChar('1');
          Serial_Port->putChar('4');
          Serial_Port->putChar('\r');
          Serial_Port->putChar('>');
          Serial_Port->putChar('>');
        */
        /*Serial_Port->putChar('>');
        Serial_Port->putChar('>');
        Serial_Port->putChar('p');
        Serial_Port->putChar('r');
        Serial_Port->putChar('u');
        Serial_Port->putChar('e');
        Serial_Port->putChar('b');
        Serial_Port->putChar('a');
        Serial_Port->putChar('<');
        Serial_Port->putChar('<');*/
    }
    m_cant_bytes_enviados += send.size();

    comando = "TX: " + comando;

    ui->plainTextEdit_PuertoSerie->appendPlainText(comando);
}

//Método para cerrar el puerto
void MainWindow::CerrarPuerto()
{
    Serial_Port->close();       //Cierro el puerto
    delete Serial_Port;         //Lo elimino
    Serial_Port = NULL;         //Mando a null la variable
}

/* ************ Manejo de Archivos ************ */

/*void MainWindow::EscribirArchivo(QString Data_In){
    QFile Archivo("plantas.txt");

    if(!Archivo.open(QFile::WriteOnly | QFile::Text)){
        qDebug() << "Error al abrir archivo desde función EscribirArchivo";
        return;
    }

    QTextStream out(&Archivo);
    out << "<<";
    out << Data_In;
    out << Data_In.Temp_MAX;
    out << Data_In.Temp_MIN;
    out << Data_In.Humedad_MAX;
    out << Data_In.Humedad_MIN;
    out << Data_In.Luz_Horas_Dia;
    out << Data_In.Riego_Hora_Inicio;
    out << Data_In.Riego_Minu_Inicio;
    out << Data_In.Riego_Duracion;

    Archivo.flush();
    Archivo.close();
}*/

//Método para agregar al combobox_ListadoPlantas las plantas cargadas en el archivo plantas.txt
void MainWindow::LeerArchivo_NombrePlantas(void){
    QFile Archivo("plantas.txt");                                           //Puntero al archivo
    QString Cultivo_Nombre;

    ui->comboBox_ListadoPlantas->clear();                                   //Limpio el combobox

    if(!Archivo.open(QFile::ReadOnly | QFile::Text)){                       //Lo abro en sólo lectura
        qDebug() << "Error al abrir archivo desde función LeerArchivo";
        return;
    }

    QTextStream in(&Archivo);                                               //Flujo de datos

    while(!in.atEnd()){                                                     //Mientras no llegue al final de la linea
        QString Renglon = in.readLine();                                    //Leo una linea
        //qDebug() << Renglon;
        if(Renglon == "<<"){                                                //Empezo bien la cadena
            Cultivo_Nombre = in.readLine();                                 //Leo el nombre
            ui->comboBox_ListadoPlantas->addItem(Cultivo_Nombre);           //Lo agrego al combobox
        }
    }

    Archivo.close();                                                        //Cierro el archivo
}

//Método para cargar en el listWidget_ListadoPlantas los datos de la planta seleccionado en el combobox_ListadoPlantas
void MainWindow::on_comboBox_ListadoPlantas_currentTextChanged(const QString &arg1)
{
    QFile Archivo("plantas.txt");           //Puntero a archivo
    Cultivo_Struct Cultivo_Aux;
    QString aux1, aux2;

    if(!Archivo.open(QFile::ReadOnly | QFile::Text)){                       //Sólo lectura
        qDebug() << "Error al abrir archivo desde función LeerArchivo";
        return;
    }

    QTextStream in(&Archivo);                                               //Flujo de datos de entrada

    while(!in.atEnd()){
        QString Renglon = in.readLine();                                    //Leo una linea

        if(Renglon == arg1){                                                //Coincide el nombre buscado con el leido en la linea
            //Limpio el widget
            ui->listWidget_ListadoPlantas->clear();

            //Voy leyendo y cargando los datos
            Cultivo_Aux.Temp_MAX = in.readLine();
            ui->listWidget_ListadoPlantas->addItem("Temperatura Máx: "+Cultivo_Aux.Temp_MAX);

            Cultivo_Aux.Temp_MIN = in.readLine();
            ui->listWidget_ListadoPlantas->addItem("Temperatura Mín: "+Cultivo_Aux.Temp_MIN);

            Cultivo_Aux.Humedad_MAX = in.readLine();
            ui->listWidget_ListadoPlantas->addItem("Humedad Máx: "+Cultivo_Aux.Humedad_MAX);

            Cultivo_Aux.Humedad_MIN = in.readLine();
            ui->listWidget_ListadoPlantas->addItem("Humedad Mín: "+Cultivo_Aux.Humedad_MIN);

            Cultivo_Aux.Luz_Horas_Dia = in.readLine();
            ui->listWidget_ListadoPlantas->addItem("Cantidad de Luz x Día: "+Cultivo_Aux.Luz_Horas_Dia);

            aux1 = in.readLine();
            Cultivo_Aux.Riego_Hora_Inicio = aux1.toInt();
            aux2 = in.readLine();
            Cultivo_Aux.Riego_Hora_Inicio = aux2.toInt();
            ui->listWidget_ListadoPlantas->addItem("Riego Inicio: "+aux1+":"+aux2);

            Cultivo_Aux.Riego_Duracion = in.readLine();
            ui->listWidget_ListadoPlantas->addItem("Riego Duracion: "+Cultivo_Aux.Riego_Duracion);
        }
    }

    Archivo.close();            //Cierro el archivo
}

/* ************ Manejo de Ventanas ************ */

//Método para abrir la ventana Agregar una planta
void MainWindow::on_pushButton_AgregarPlanta_clicked()
{
    Dialog wAgregarPlanta;

    wAgregarPlanta.setModal(true);
    wAgregarPlanta.exec();

    LeerArchivo_NombrePlantas();
}

//Método para abrir la ventada de Eliminar Planta
void MainWindow::on_pushButton_EliminarPlanta_clicked()
{
    Dialog2 wEliminarPlanta;

    wEliminarPlanta.setModal(true);
    wEliminarPlanta.exec();

    LeerArchivo_NombrePlantas();
}

//Método para abrir la ventada de Editar Planta
void MainWindow::on_pushButton_EditarPlanta_clicked()
{
    Dialog3 wEditarPlanta;

    wEditarPlanta.setModal(true);
    wEditarPlanta.exec();

    LeerArchivo_NombrePlantas();
}

/* ************ Prueba Hardware ************ */

//Método que envia una trama especial por puerto serie para indicar que haga la rutina de prueba de hardware
void MainWindow::on_pushButton_Prueba_clicked()
{
    /* Trama a enviar ||prueba||    */
    EnviarComando("||prueba||");
}

void MainWindow::on_pushButton_PuertoSerie_Enviar_clicked()
{
    QMessageBox msg;

    msg.setText("Desea enviar los datos de la planta: "+ui->comboBox_ListadoPlantas->currentText());
    msg.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    msg.setIcon(QMessageBox::Information);
    int Op = msg.exec();

    if(Op == QMessageBox::Ok){
        QString trama = Trama(ui->comboBox_ListadoPlantas->currentText());
        //qDebug() << "trama clicked"+trama;
        EnviarComando(trama);
    }


    LeerArchivo_NombrePlantas();
}

QString MainWindow::Trama(QString Nombre_Planta){
    QFile Archivo("plantas.txt");                                           //Puntero al archivo
    Cultivo_Struct Aux_Cultivo;

    ui->comboBox_ListadoPlantas->clear();                                   //Limpio el combobox

    if(!Archivo.open(QFile::ReadOnly | QFile::Text)){                       //Lo abro en sólo lectura
        qDebug() << "Error al abrir archivo desde función LeerArchivo";
        return 0;
    }

    QTextStream in(&Archivo);                                               //Flujo de datos

    while(!in.atEnd()){                                                     //Mientras no llegue al final de la linea
        QString Renglon = in.readLine();                                    //Leo una linea
        //qDebug() << Renglon;
        if(Renglon == Nombre_Planta){
            Aux_Cultivo.Temp_MAX = in.readLine();
            Aux_Cultivo.Temp_MIN = in.readLine();
            Aux_Cultivo.Humedad_MAX = in.readLine();
            Aux_Cultivo.Humedad_MIN = in.readLine();
            Aux_Cultivo.Luz_Horas_Dia = in.readLine();
            Aux_Cultivo.Riego_Hora_Inicio = in.readLine();
            Aux_Cultivo.Riego_Minu_Inicio = in.readLine();
            Aux_Cultivo.Riego_Duracion = in.readLine();
        }
    }
    /* Trama a enviar:
     * <<T,temp_max,temp_min,H,hum_max,hum_min,I,horas al dia,R,hora_deinicio,mins_deinicio,duracion(en minutos)>> */
    QString trama = "<<T"+Aux_Cultivo.Temp_MAX+Aux_Cultivo.Temp_MIN+"H"+Aux_Cultivo.Humedad_MAX+Aux_Cultivo.Humedad_MIN+"I"+Aux_Cultivo.Luz_Horas_Dia+"R"+Aux_Cultivo.Riego_Hora_Inicio+Aux_Cultivo.Riego_Minu_Inicio+Aux_Cultivo.Riego_Duracion+">>";
    //qDebug() << trama;
    Archivo.close();

    return trama;
}
