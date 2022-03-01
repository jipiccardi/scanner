#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QMessageBox>
#include <QFileDialog>
#include <QTextStream>
#include <cmath>
#include <QKeyEvent>
#include <qextserialport.h>
#include <qextserialenumerator.h>

#define NO_MODE 0
#define SCN 1
#define CAL 2
#define MAN 3

#define SCANNING 0
#define CALIBRATTING 1
#define MANUAL 3

//caracteres especiales para la comunicacion serie
#define CHAR_INIT   254
#define CHAR_FIN    253
#define CHAR_STOP   252
#define CHAR_SCAN   249
#define CHAR_CAL    248
#define CHAR_MAN    247
#define CHAR_BCK    246
#define CHAR_FWD    245
#define CHAR_BCKSTOP    244
#define CHAR_FWDSTOP    243
#define CHAR_FNSH_FROM_MICRO 242

#define MEDxP 534 //cantidada de mediciones por angulo

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_radioButton_Man_toggled(bool checked);

    void on_pushButton_Srt_clicked();

    void on_pushButton_Sv_clicked();

    void on_lineEdit_Rot_editingFinished();

    void on_lineEdit_H_editingFinished();

    void on_lineEdit_Ruta_editingFinished();

    void on_pushButton_Upld_clicked();

    void on_pushButtonConectar_clicked();

    void on_pushButton_OpRuta_clicked();

    void on_pushButton_Stp_clicked();

    void on_pushButton_Fwd_clicked();

    void on_pushButton_Bck_clicked();

    void on_pushButton_Bck_released();

    void on_pushButton_Fwd_released();

    void on_Port_rx();

    void fTimer();


private:
    Ui::MainWindow *ui;

    float hgt_setted,rot_setted;
    float height_Step;
    int angle_Step;
    float hgt_real,rot_real;
    int hgt_write=0;
    float angle_write=0;
    int mode_started;
    int timer=0;
    bool boton_apretado=false;
    QString path;
    QFile scan_file,cal_file;
    QextSerialPort *Port;
    QTextStream stream;

    void EnumerarPuertos();
    void keyPressEvent(QKeyEvent *);
    void keyReleaseEvent(QKeyEvent *);
    void enabling_StartButton(void);
    void Scan_Action(void);
    void Cal_Action(void);

    void Send_Signals(int);


    void Send_ManParameters(void);
    void Send_ScanParameters(void);
    void Serial_Trama(uint8_t);
    void Scan_manage_data(void);




};
#endif // MAINWINDOW_H
