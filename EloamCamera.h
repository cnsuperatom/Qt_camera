#ifndef ELOAMCAMERA_H
#define ELOAMCAMERA_H

#include <QWidget>
#include <QSettings>
#include <ActiveQt/QAxObject>
#include <QAxWidget>
#include <QTimer>
#include "FileLog.h"

namespace Ui {
class EloamCamera;
}

class EloamCamera : public QWidget
{
    Q_OBJECT
    
public:
    explicit EloamCamera(QWidget *parent = 0);
    ~EloamCamera();

    // Init & deInit
    bool init();
    void deInit();

    // Load setting from ini file
    void loadSettingFromIniFile();

    // Take photo
    void takeSnapShot();

    // true: if camera is connected
    // false: camera is disconnected
    bool isConnected() const;

public:
    struct COMBOX_LIST
    {
        int value;
        char text[50];
    };

signals:
    void photoReady(QString);

protected:
    void resizeEvent(QResizeEvent *e);

private slots:
    bool pollingDevEvent();

    void on_pushButton_openDev_clicked();

    void on_pushButton_closeDev_clicked();

    void on_pushButton_rotateLeft_clicked();

    void on_pushButton_rotateRight_clicked();

    void on_pushButton_leftRight_clicked();

    void on_pushButton_upDown_clicked();

    void on_pushButton_browsePhoto_clicked();

    void on_pushButton_snapshot_clicked();

    void devChangeEvent(int devType, int devNo, int eventNo);

    void on_comboBox_videoMode_currentIndexChanged(int index);

    void on_comboBox_deviceList_currentIndexChanged(int index);

private:
    Ui::EloamCamera *ui;

    QSettings *currentSetting;  // Store current setting with ini file
    QString widgetFontType; // Store the font type of widget
    int widgetFontSize;     // Store the font size of widget

    FileLog *logFile;   // Log File
    QString logPath;    // Log Path

    QAxObject *m_eloamGlobal;
    QAxObject *m_eloamVideo;
    QAxWidget *m_eloamAxWidget;

    QList<QAxObject *> m_deviceList;    // device list

    int m_devCnt; // connected device count
    int m_devCntLast; // connected device count

    QTimer *m_detectEventTimer; // Timer used to polling the device status(connected, disconnected)

    QString suffixName;     // photo suffix name, such as .jpg .png
    QString m_storagePath;  // Store image path

    bool m_connectedFlag;   // Camera connected flag

    // Init the Font type and size of the widget
    void initWidgetFont();

    // Init Icon of the widget
    void initWidgetStyle();

    // Update Log to file and log display buffer
    void updateLogData(QString logStr);

    // Find mode string according to modeNo.
    QString findModeString(int modeNo);

    // Find mode subtype according to mode string
    int findModeType(QString modeStr);

    // Init comboBox of mode according to device index
    void initModeComboBox(int devNo);

    // Init comboBox of resolution according to Mode Subtype.
    void initResolutionComboBox(int modeType);

    // Enable/Disable some function UIs
    void setFunctionUIEnable(bool flag);

    // Update storage path to ini file
    void updateSavePathToIniFile();

};

#endif // ELOAMCAMERA_H
