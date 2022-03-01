#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QTimer>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Port = NULL;    //indica que el objeto puerto no esta creado;
    //Portname = "";
    EnumerarPuertos();


}

MainWindow::~MainWindow()
{
    delete ui;
}

//---------------------------------------------------------------
//TAB1


void MainWindow::on_radioButton_Man_toggled(bool checked)
{
    if (checked==1){
    ui->lineEdit_Dist->setEnabled(1);
    ui->label_3->setEnabled(1);
    }else{
    ui->lineEdit_Dist->setEnabled(0);
    ui->label_3->setEnabled(0);
    }
}

//Start Botton Action
void MainWindow::on_pushButton_Srt_clicked()
{
    //Verifico si hay un Path especificado
    if(!(ui->lineEdit_Ruta->text().isEmpty())){
        //Verifico que modo se selecciono
        int state=NO_MODE;
        if(ui->radioButton_Scan->isChecked())
            state=SCN;
        if(ui->radioButton_Cal->isChecked())
            state=CAL;
        if(ui->radioButton_Man->isChecked())
            state=MAN;

        switch (state){
            case NO_MODE:
                QMessageBox::critical(this, "Error", "No se selecciono ningun modo");
            break;
            case SCN:
                if((ui->lineEdit_H->text().toDouble()) && (ui->lineEdit_Rot->text().toDouble())){
                    mode_started=SCANNING;
                    Scan_Action();
                }else
                    QMessageBox::critical(this, "Error -> Modo Scanner", "Falta especificar Altura y/o Rotacion de Avance");
            break;
            case CAL:
                Cal_Action();
            break;
            case MAN:
                if(ui->lineEdit_Dist->text().toDouble()){
                    Send_Signals(CHAR_MAN);
                    Send_ManParameters();
                    mode_started=MANUAL;
                    enabling_StartButton();
                }else
                    QMessageBox::critical(this, "Error -> Modo Manual", "Falta especificar Avance Manual");
            break;
        }
    }else
        QMessageBox::critical(this, "Error", "No hay ruta de guardado especificada");
}

void MainWindow::on_pushButton_Stp_clicked()
{
/*solo enviar si la señal vino de Qt */   Send_Signals(CHAR_STOP);
    switch(mode_started){
        case SCANNING:
            scan_file.close();
        break;
        case CALIBRATTING:
            cal_file.close();
        break;
    }
    //Habilitacion de botones
    ui->pushButton_Stp->setEnabled(0);
    ui->pushButton_Srt->setEnabled(1);
    ui->pushButton_Fwd->setEnabled(1);
    ui->pushButton_Bck->setEnabled(1);

    QMessageBox::information(this, "Informacion", "Proceso Finalizado",
                             ("Tiempo transcurrido:" + QString::number(timer/1000)));
}


void MainWindow::on_pushButton_Fwd_clicked(){
    Send_Signals(CHAR_FWD);
    //Deshabilitacion
    ui->pushButton_Srt->setEnabled(0);
    ui->pushButton_Bck->setEnabled(0);
}

void MainWindow::on_pushButton_Bck_clicked(){
    Send_Signals(CHAR_BCK);
    //Deshabilitacion
    ui->pushButton_Srt->setEnabled(0);
    ui->pushButton_Fwd->setEnabled(0);
}

void MainWindow::on_pushButton_Bck_released()
{
    Send_Signals(CHAR_BCKSTOP);
    //Deshabilitacion
    ui->pushButton_Srt->setEnabled(1);
    ui->pushButton_Fwd->setEnabled(1);
}

void MainWindow::on_pushButton_Fwd_released()
{
    Send_Signals(CHAR_FWDSTOP);
    //Deshabilitacion
    ui->pushButton_Srt->setEnabled(1);
    ui->pushButton_Bck->setEnabled(1);
}

/*Esta funcion es invocada en caso de que presionemos alguna tecla. Esta programada para hacer algo
si se aprietan A,W,S,D , las cuales serian las teclas de movimiento para la aspiradora. En caso de
que se presione alguna de las teclas anteriores se hará click en un boton IZQUIERDA,ARRIBA,ABAJO o
DERECHA respectivamente.*/
 void MainWindow::keyPressEvent(QKeyEvent *evento)
 {
            if(evento->key() == Qt::Key_A){
              ui->pushButton_Fwd->click();
            }
            else if(evento->key() == Qt::Key_D){
              ui->pushButton_Bck->click();
            }
 }
 void MainWindow::keyReleaseEvent(QKeyEvent *evento){
     if(evento->isAutoRepeat())
        evento->ignore();
     else{
     if(evento->key() == Qt::Key_A)
        ui->pushButton_Fwd->released();
     else if(evento->key() == Qt::Key_D)
        ui->pushButton_Bck->released();
    }
 }

 void MainWindow::on_pushButtonConectar_clicked()
 {
     if (!Port)
     {
         Port = new QextSerialPort("COM3");
         Port->setBaudRate(BAUD128000);
         Port->setFlowControl(FLOW_OFF);
         Port->setParity(PAR_NONE);
         Port->setDataBits(DATA_8);
         Port->setStopBits(STOP_1);
         if(!Port->open(QIODevice::ReadWrite))
         {
             QMessageBox::critical(this,tr("Error"),tr("No se puede abrir el puerto ")+Port->portName());
             delete Port;
             Port = NULL;
         }
         else
         {
             ui->pushButtonConectar->setText("Desconectar");
             connect(Port,SIGNAL(readyRead()),this,SLOT(on_Port_rx()));
         }
     }
     else
     {
         delete Port;
         Port = NULL;
         ui->pushButtonConectar->setText("Conectar");
     }
 }


//--    -------------------------------------------------------------
//TAB2

//Text Input Transform -> Tab2

void MainWindow::on_lineEdit_Rot_editingFinished()
{
    rot_setted=ui->lineEdit_Rot->text().toFloat();
}
void MainWindow::on_lineEdit_H_editingFinished()
{
    hgt_setted=ui->lineEdit_H->text().toFloat();
}
void MainWindow::on_lineEdit_Ruta_editingFinished()
{
    path=ui->lineEdit_Ruta->text();
}

//Configuration
void MainWindow::on_pushButton_OpRuta_clicked()
{
    path=QFileDialog::getExistingDirectory(this,"Elegi una carpeta","C://");
    ui->lineEdit_Ruta->setText(path);
}

void MainWindow::on_pushButton_Sv_clicked()
{
    QString cfg_path="C:/Users/adrie/Documents/00_PATONEITOR/GUI_Scanner/config.dat";
    QFile file(cfg_path);
    if (file.open(QIODevice::ReadWrite | QIODevice::Text | QIODevice::Truncate)){
        QTextStream stream;
        stream.setDevice(&file);
        stream<<path;
        stream<<" ";
        stream<<rot_setted;
        stream<<" ";
        stream<<hgt_setted;
        stream<<" ";
        file.close();

        QMessageBox::information(this, "Informacion", "Archivo de configuración creado");
    }
}
void MainWindow::on_pushButton_Upld_clicked()
{
    QString cfg_path="C:/Users/adrie/Documents/00_PATONEITOR/GUI_Scanner/config.dat";
    QFile file(cfg_path);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)){
        QTextStream stream;
        stream.setDevice(&file);
        stream>>path;
        stream.read(1);
        stream>>rot_setted;
        stream.read(1);
        stream>>hgt_setted;

        file.close();
        ui->lineEdit_Ruta->setText(path);
        ui->lineEdit_Rot->setText(QString::number(rot_setted));
        ui->lineEdit_H->setText(QString::number(hgt_setted));
    }
}

//-----------------------------------------------------------------
//Funciones

void MainWindow::enabling_StartButton(){
    ui->pushButton_Stp->setEnabled(1);
//    ui->pushButton_P->setEnabled(1);
    ui->pushButton_Srt->setEnabled(0);
    ui->pushButton_Fwd->setEnabled(0);
    ui->pushButton_Bck->setEnabled(0);
}

void MainWindow::Scan_Action(){

    //Abro el path donde se guardara el archivo de scan
    QString scan_archive=path+"/scan.csv";
    QTimer *cronometro = new QTimer(this);
    timer=0;
    connect(cronometro, SIGNAL(timeout()),this,SLOT(fTimer()));
    cronometro->start(1);
    scan_file.setFileName(scan_archive);
    if( scan_file.open(QIODevice::ReadWrite | QIODevice::Text | QIODevice::Truncate) ){
        stream.setDevice(&scan_file);
        stream<<"0;";
        //Convierto los parametros a steps del motor
        height_Step=round(hgt_setted*2048/8);
        hgt_real=8*height_Step/2048;
        angle_Step=rot_setted*2048/360;
        rot_real=360*float(angle_Step)/2048;
        Send_Signals(CHAR_SCAN);
        Send_ScanParameters();
        enabling_StartButton();
        QMessageBox::information(this, "Parametros",
                                 ("Eje:\n   [mm]: "+QString::number(hgt_real,'g',3)+"\n   [steps]: "+QString::number(height_Step)+
                                  "\nMesa:\n   [degree]: "+QString::number(rot_real,'g',3)+"\n   [steps]: "+QString::number(angle_Step)));
    }
}

void MainWindow::Cal_Action(){
    cal_file.setFileName(path+"/calibration.csv");
    if(scan_file.open(QIODevice::ReadWrite | QIODevice::Text | QIODevice::Truncate)){
        Send_Signals(CHAR_CAL);
    enabling_StartButton();
    }
}

void MainWindow::Send_ManParameters(){
    if(Port){
        QByteArray aux;
        aux=NULL;
        aux.append(CHAR_INIT);
        aux.append(ui->lineEdit_Dist->text().toDouble());
        aux.append(CHAR_FIN);
        Port->write(aux);
    }else
        QMessageBox::critical(this, "Error", QString::fromUtf8("No hay conexion"));

}
void MainWindow::Send_ScanParameters(){
    if(Port){
        QByteArray aux;
        aux=NULL;
        aux.append(CHAR_INIT);
        aux.append(round(hgt_setted*10));
        aux.append(CHAR_FIN);
        Port->write(aux);

        aux=NULL;
        aux.append(CHAR_INIT);
        aux.append(round(rot_setted));
        aux.append(CHAR_FIN);
        Port->write(aux);

    }else
        QMessageBox::critical(this, "Error", QString::fromUtf8("No hay conexion"));

}

void MainWindow::Send_Signals(int signal){
   if(Port){
       QByteArray aux;
       aux=NULL;
       aux.append(CHAR_INIT);
       aux.append(signal);
       aux.append(CHAR_FIN);
       Port->write(aux);
   }else
       QMessageBox::critical(this, "Error", QString::fromUtf8("No hay conexion"));
}

void MainWindow::EnumerarPuertos()
{
    ui->comboBoxPort->clear();

    QList<QextPortInfo> ports = QextSerialEnumerator::getPorts();

    for (int i = ports.size(); i > 0; i--)
    {
    #ifdef Q_OS_WIN
       ui->comboBoxPort->addItem(ports.at(i-1).portName);
   #elif (defined Q_OS_UNIX)
           ui->comboBoxPort->addItem(ports.at(i).physName);
   #endif

    }
}


void MainWindow::on_Port_rx()
{
    static int k=0,altura=0,angulo=0;
    QByteArray aux;
    aux.resize(Port->bytesAvailable());
    Port->read(aux.data(),aux.size());
    std::string  data=aux.toStdString();
    if (k==MEDxP){
        angulo+=rot_setted;
        if (angulo>359){//vuelta completa
            angulo=0;
            altura+=hgt_setted;
        }stream<<";"<<altura<<"\0"<<angulo<<";";
    }
    //Determina que hacer con la información
    switch (mode_started) {
    case SCANNING:
        //stream.setDevice(&scan_file);
        for (int i=0;i<data.size();i++){
            Serial_Trama(uint8_t (data[i]));
            if ((uint8_t(data[i])==10))
                Scan_manage_data();
            else if((uint8_t(data[i])>47) && (uint8_t(data[i])<58))
                stream<<data[i];

        }break;
    case CALIBRATTING:
            stream.setDevice(&cal_file);
        for (int i=0;i<data.size();i++){
            Serial_Trama(uint8_t (data[i]));
            if((uint8_t(data[i])>47) && (uint8_t(data[i])<58) || (uint8_t(data[i])==10)){
                stream<<data[i];
            }
        }break;
    case MANUAL:
        for (int i=0;i<data.size();i++){
            Serial_Trama(uint8_t (data[i]));
        }break;
    }
}

void MainWindow::Serial_Trama(uint8_t data){
    static int state=0;

    switch(state){
    case 0:
        if(data==CHAR_INIT)
            state=1;
        break;
    case 1:
        if(data==CHAR_STOP)
            state=2;
        else state=0;
        break;
    case 2:
        if (data==CHAR_FIN){
            state=0;
            ui->pushButton_Stp->click();
        }else state=0;
    }
}

void MainWindow::Scan_manage_data(){
    static int k=0;
    stream<<";"<<hgt_write<<"\n";
    k++;
    if (k==MEDxP){
        k=0;
        //angle_write+=rot_real;
        angle_write+=0.1757;
        if (angle_write>359){//vuelta completa
            angle_write=0;
            hgt_write+=hgt_setted;
        }
    }stream<<angle_write<<";";
}

void MainWindow::fTimer(){
    timer++;
}
