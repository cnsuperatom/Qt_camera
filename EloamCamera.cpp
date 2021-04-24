#include "EloamCamera.h"
#include "ui_EloamCamera.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QDateTime>
#include <QDebug>

#include "QUtilityBox.h"


EloamCamera::COMBOX_LIST mode_combox[] =
{
    {1, "YUY2"},
    {2, "MJPG"},
    {3, "YUY2,MJPG"},
    {4, "UYVY"},
    {5, "UYVY,YUY2"},
    {6, "UYVY,MJPG"},
    {7, "UYVY,MJPG,YUY2"}
};

EloamCamera::EloamCamera(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EloamCamera),
    widgetFontType("Arial"),
    widgetFontSize(16),
    logFile(new FileLog),
    logPath("./Log/"),
    m_eloamGlobal(NULL),
    m_eloamVideo(NULL),
    m_eloamAxWidget(NULL),
    m_devCnt(0),
    m_devCntLast(0),
    suffixName("jpg"),
    m_storagePath("./ScanImage/"),
    m_connectedFlag(false)
{
    ui->setupUi(this);

    // Default setting file
    currentSetting = new QSettings("config.ini", QSettings::IniFormat);

    // Load Settings from ini file
    loadSettingFromIniFile();

    // Init Widget Font type and size
    initWidgetFont();

    // Init Widget Style
    initWidgetStyle();

    m_detectEventTimer = new QTimer();
    connect(m_detectEventTimer, SIGNAL(timeout()), this, SLOT(pollingDevEvent()));

    // Init device
    //init();
}

EloamCamera::~EloamCamera()
{
    deInit();

    delete ui;
    delete logFile;
    delete currentSetting;
    delete m_detectEventTimer;
}

void EloamCamera::resizeEvent(QResizeEvent *e)
{
    Q_UNUSED(e);
    QWidget *pWidget = static_cast<QWidget*>(this->parent());

    if(pWidget != NULL)
    {
        this->resize(pWidget->size());
        qDebug() << "EloamCamera::resizeEvent pWidget->size()=" << pWidget->size();

        if(NULL != m_eloamAxWidget)
        {
            m_eloamAxWidget->resize(ui->widget_image->size());
            qDebug() << "EloamCamera::ui->widget_image->size()=" << ui->widget_image->size();
            m_eloamAxWidget->move(0, 0);
        }
    }
}

void EloamCamera::takeSnapShot()
{
    on_pushButton_snapshot_clicked();
}

bool EloamCamera::isConnected() const
{
    return m_connectedFlag;
}

bool EloamCamera::init()
{
    bool ret = false;

    m_detectEventTimer->start(1000);    // 1s

    if(NULL == m_eloamGlobal)
    {
        m_eloamGlobal = new QAxObject();
        m_eloamGlobal->setControl("EloamGlobal.Instance.1");
        //m_eloamGlobal->setControl("{52D1E686-D8D7-4DF2-9A74-8B8F4650BF73}");

        ret = m_eloamGlobal->dynamicCall("InitDevs()").toBool();

        if(ret)
        {
            pollingDevEvent();
        }
        else
        {
            qDebug() << "dynamicCall InitDevs() failed";
        }

    }

    if(NULL == m_eloamAxWidget)
    {
        m_eloamAxWidget = new QAxWidget();
        m_eloamAxWidget->setControl("EloamView.Instance.1");
        //m_eloamAxWidget->setControl("{26ba9e7f-78e9-4fb8-a05c-a4185d80d759}");

        m_eloamAxWidget->setParent(ui->widget_image);
        m_eloamAxWidget->dynamicCall("SetText(QString, QColor)", "Waiting...", QColor(255, 255, 255));
    }

    return ret;
}

void EloamCamera::deInit()
{
    on_pushButton_closeDev_clicked();

    if(NULL != m_eloamGlobal)
    {
        m_eloamGlobal->dynamicCall("DeinitDevs()");
        delete m_eloamGlobal;
        m_eloamGlobal = NULL;

        delete m_eloamAxWidget;
        m_eloamAxWidget = NULL;
    }
}

void EloamCamera::loadSettingFromIniFile()
{
    // Load Font type and size
    currentSetting->beginGroup("SystemSetting");

    if(currentSetting->contains("FontType"))
    {
        // Load FontType
        widgetFontType = currentSetting->value("FontType").toString();
    }
    else
    {
        // Init the default value
        currentSetting->setValue("FontType", widgetFontType);
    }

    if(currentSetting->contains("FontSize"))
    {
        // Load FontSize
        widgetFontSize = currentSetting->value("FontSize").toInt();
    }
    else
    {
        // Init the default value
        currentSetting->setValue("FontSize", widgetFontSize);
    }

    if(currentSetting->contains("LogPath"))
    {
        // Load Log Path
        logPath = currentSetting->value("LogPath").toString();
    }
    else
    {
        // Init the default value
        currentSetting->setValue("LogPath", logPath);
    }
    // Init Log File Path
    logFile->setLogPath(logPath);

    currentSetting->endGroup();


    currentSetting->beginGroup("CameraSetting");
    if(currentSetting->contains("SavePath"))
    {
        // Load storage path
        m_storagePath = currentSetting->value("SavePath").toString();
    }
    else
    {
        // Init the default value
        currentSetting->setValue("SavePath", m_storagePath);
    }
    ui->lineEdit_photoPath->setText(m_storagePath);
    QUtilityBox toolBox;
    toolBox.mkdir(m_storagePath);

    if(currentSetting->contains("Suffix"))
    {
        // Load storage path
        suffixName = currentSetting->value("Suffix").toString();
    }
    else
    {
        // Init the default value
        currentSetting->setValue("Suffix", suffixName);
    }

    currentSetting->endGroup();
}

void EloamCamera::initWidgetFont()
{
    // Init Font Size and bold
    ui->label_deviceList->setFont(QFont(widgetFontType, widgetFontSize, QFont::DemiBold));
    ui->label_videoMode->setFont(QFont(widgetFontType, widgetFontSize, QFont::DemiBold));
    ui->label_resolution->setFont(QFont(widgetFontType, widgetFontSize, QFont::DemiBold));

    ui->comboBox_deviceList->setFont(QFont(widgetFontType, widgetFontSize, QFont::Normal));
    ui->comboBox_videoMode->setFont(QFont(widgetFontType, widgetFontSize, QFont::Normal));
    ui->comboBox_resolution->setFont(QFont(widgetFontType, widgetFontSize, QFont::Normal));

    ui->label_photoPath->setFont(QFont(widgetFontType, widgetFontSize, QFont::Normal));

    ui->pushButton_openDev->setFont(QFont(widgetFontType, widgetFontSize, QFont::Normal));
    ui->pushButton_closeDev->setFont(QFont(widgetFontType, widgetFontSize, QFont::Normal));
    ui->pushButton_rotateLeft->setFont(QFont(widgetFontType, widgetFontSize, QFont::Normal));
    ui->pushButton_rotateRight->setFont(QFont(widgetFontType, widgetFontSize, QFont::Normal));
    ui->pushButton_leftRight->setFont(QFont(widgetFontType, widgetFontSize, QFont::Normal));
    ui->pushButton_upDown->setFont(QFont(widgetFontType, widgetFontSize, QFont::Normal));

    //ui->lineEdit_photoPath->setFont(QFont(widgetFontType, widgetFontSize, QFont::Normal));
    ui->pushButton_browsePhoto->setFont(QFont(widgetFontType, widgetFontSize, QFont::Normal));
    ui->pushButton_snapshot->setFont(QFont(widgetFontType, widgetFontSize, QFont::Normal));
}

void EloamCamera::initWidgetStyle()
{

}
void EloamCamera::on_pushButton_openDev_clicked()
{
    QString logStr = tr("Open Camera");
    int devIndex = ui->comboBox_deviceList->currentIndex();
    int resIndex = ui->comboBox_resolution->currentIndex();
    int modeIndex = ui->comboBox_videoMode->currentIndex();
    int modeType = 0;

    if(devIndex < 0)
    {
        return;
    }

    if(resIndex < 0)
    {
        resIndex = 0;
    }

    if(modeIndex < 0)
    {
        modeType = 0;
    }
    else
    {
        modeType = findModeType(ui->comboBox_videoMode->currentText());
    }

    if(m_devCnt > 0)
    {
        on_pushButton_closeDev_clicked();

        m_eloamVideo =
                m_deviceList[ui->comboBox_deviceList->currentIndex()]->querySubObject("CreateVideo(int, int)", resIndex, modeType);

        if(NULL != m_eloamAxWidget)
        {
            m_eloamAxWidget->setParent(ui->widget_image);

            m_eloamAxWidget->dynamicCall("SelectVideo(IDispatch *)", m_eloamVideo->asVariant());

            QString openCameraStr = tr("Camera is open, please wait...");
            m_eloamAxWidget->dynamicCall("SetText(QString, QColor)", openCameraStr, QColor(255, 255, 255));
        }

        // Update Log
        updateLogData(logStr);
    }

}

void EloamCamera::on_pushButton_closeDev_clicked()
{
    QString logStr = tr("Close Camera");

    if(NULL != m_eloamAxWidget)
    {
        m_eloamAxWidget->dynamicCall("SetText(QString, QColor)", "", QColor(255, 255, 255));
    }

    if(NULL != m_eloamVideo)
    {
        m_eloamVideo->dynamicCall("Destroy()");
        m_eloamVideo = NULL;

        // Update Log
        updateLogData(logStr);
    }
}

void EloamCamera::on_pushButton_rotateLeft_clicked()
{
    bool ret = false;
    QString logStr = tr("Rotate Left");

    if(NULL == m_eloamVideo)
    {
        return;
    }

    ret = m_eloamVideo->dynamicCall("RotateLeft()").toBool();

    // Update Log
    updateLogData(logStr);
}

void EloamCamera::on_pushButton_rotateRight_clicked()
{
    bool ret = false;
    QString logStr = tr("Rotate Right");

    if(NULL == m_eloamVideo)
    {
        return;
    }

    ret = m_eloamVideo->dynamicCall("RotateRight()").toBool();

    // Update Log
    updateLogData(logStr);
}

void EloamCamera::on_pushButton_leftRight_clicked()
{
    bool ret = false;
    QString logStr = tr("Mirror");

    if(NULL == m_eloamVideo)
    {
        return;
    }

    ret = m_eloamVideo->dynamicCall("Mirror()").toBool();

    // Update Log
    updateLogData(logStr);
}

void EloamCamera::on_pushButton_upDown_clicked()
{
    bool ret = false;
    QString logStr = tr("Flip");

    if(NULL == m_eloamVideo)
    {
        return;
    }

    ret = m_eloamVideo->dynamicCall("Flip()").toBool();

    // Update Log
    updateLogData(logStr);
}

void EloamCamera::on_pushButton_browsePhoto_clicked()
{
    QString defaultLocalDir = ui->lineEdit_photoPath->text();

    QString directory = QFileDialog::getExistingDirectory( this,
                                                 tr("Select the Image storage Directory"),
                                                 defaultLocalDir,
                                                 QFileDialog::ShowDirsOnly
                                                 | QFileDialog::DontResolveSymlinks);
    if (!directory.isEmpty())
    {
        ui->lineEdit_photoPath->setText(directory);
        m_storagePath = directory;

        // Update the new path to ini setting file
        updateSavePathToIniFile();
    }
}

void EloamCamera::on_pushButton_snapshot_clicked()
{
    QString logStr;
    QDateTime time = QDateTime::currentDateTime();
    QString timeStr = time.toString("yyyyMMdd_hhmmss_zzz");  // Time format 20201111_093201_000 (2020-11-11 09:32:01.000)

    QString fileName = ui->lineEdit_photoPath->text();
    fileName.append("/");
    fileName.append(timeStr);

    fileName.append(".");
    fileName.append(suffixName); // Set image file format

    logStr = tr("Shot at ");
    logStr.append(fileName);
    qDebug() << logStr;

    if(NULL == m_eloamVideo)
    {
        QString logStr = tr("Video is not open!");

        // Update Log
        updateLogData(logStr);

        return;
    }

    int scanSize = 0x00;   // 0x00: default, 0x04:A3, 0x08:A4, 0x10:A5
    QAxObject *tempView = m_eloamAxWidget->querySubObject("GetView()");
    QAxObject *tempImage = m_eloamVideo->querySubObject("CreateImage(int, IDispatch *)",  scanSize, tempView->asVariant());

    if(NULL != tempImage)
    {
        tempImage->dynamicCall("Save(QString, int)", fileName, 0);

        if(NULL != m_eloamAxWidget)
        {
            m_eloamAxWidget->dynamicCall("PlayCaptureEffect()");
        }

        // Send signal out
        emit photoReady(fileName);
    }
    else
    {
        logStr = tr("Shot failed!");
    }

    // Update log
    updateLogData(logStr);
}

void EloamCamera::devChangeEvent(int devType, int devNo, int eventNo)
{

}

QString EloamCamera::findModeString(int modeNo)
{
    QString ret = "";

    for(uint32_t i = 0; i < (sizeof(mode_combox) / sizeof(COMBOX_LIST)); i++)
    {
        if(modeNo == mode_combox[i].value)
        {
            ret = QString(mode_combox[i].text);
            break;
        }
    }

    return ret;
}

int EloamCamera::findModeType(QString modeStr)
{
    int ret = -1;

    for(uint32_t i = 0; i < (sizeof(mode_combox) / sizeof(COMBOX_LIST)); i++)
    {
        if(modeStr == QString(mode_combox[i].text))
        {
            ret = mode_combox[i].value;
            break;
        }
    }

    return ret;
}

void EloamCamera::initModeComboBox(int devNo)
{
    qDebug() << "EloamCamera::initModeComboBox devNo=" << devNo;

    if(devNo < 0)
    {
        return;
    }

    ui->comboBox_videoMode->clear();

    int mode = m_deviceList.at(devNo)->dynamicCall("GetSubtype()").toInt();
    QString modeStr = findModeString(mode);
    QStringList modelist = modeStr.split(QRegExp("\\W+"), QString::SkipEmptyParts);;

    ui->comboBox_videoMode->addItems(modelist);

    // Init resolutuion comboBox
    initResolutionComboBox(mode);;
}

void EloamCamera::initResolutionComboBox(int modeType)
{
    qDebug() << "EloamCamera::initResolutionComboBox modeType=" << modeType;

    if(modeType < 0)
    {
        return;
    }

    ui->comboBox_resolution->clear();

    // Get resolution
    int devNo = ui->comboBox_deviceList->currentIndex();

    if(devNo >= 0)
    {
        int resCnt = m_deviceList.at(devNo)->dynamicCall("GetResolutionCountEx(int)", modeType).toInt();

        QStringList resList;
        resList.clear();

        for(int i = 0; i < resCnt; i++)
        {
            int width = m_deviceList.at(devNo)->dynamicCall("GetResolutionWidthEx(int, int)", modeType, i).toInt();
            int height = m_deviceList.at(devNo)->dynamicCall("GetResolutionHeightEx(int, int)", modeType, i).toInt();

            resList.append(QString::number(width) + "*" + QString::number(height));
        }

        ui->comboBox_resolution->addItems(resList);
    }
}

void EloamCamera::on_comboBox_videoMode_currentIndexChanged(int index)
{
    int modeType = findModeType(ui->comboBox_videoMode->currentText());
    initResolutionComboBox(modeType);
}

void EloamCamera::on_comboBox_deviceList_currentIndexChanged(int index)
{
    // ReInit comboBox of mode and resolution
    initModeComboBox(index);
}

bool EloamCamera::pollingDevEvent()
{
    bool ret = false;
    static int cnt = 0;
    QString logStr = "";

    if(NULL == m_eloamGlobal)
    {
        return ret;
    }

    m_devCnt = m_eloamGlobal->dynamicCall("GetDevCount(int)", 1).toInt();

    // If m_devCnt > m_devCntLast , which means new device incoming
    // If m_devCnt < m_devCntLast , which means device disconnected
    if(m_devCntLast != m_devCnt)
    {
        if(m_devCnt > m_devCntLast)
        {
            logStr = tr("New Camera connected");

            // Enable some UIs
            setFunctionUIEnable(true);

            m_connectedFlag = true;
        }
        else
        {
            logStr = tr("Camera disconnected");

            on_pushButton_closeDev_clicked();

            m_connectedFlag = false;
        }

        // Update log
        updateLogData(logStr);
    }

    if(0 == m_devCnt)
    {
        // Disable some UIs
        setFunctionUIEnable(false);

        QString warningStr = "No device found";

        // Only the 1st time prompt out the warning dialogue
        if(++cnt == 1)
        {
            QMessageBox::warning(0, tr("Warning"), warningStr);
        }

        qDebug() << warningStr;

        ret = false;
    }
    else if(m_devCnt > 0)
    {
        //cnt = 0;

        // If m_devCntLast != m_devCnt, which means new device incoming
        // Refresh the UIs(comboBox)
        if(m_devCntLast != m_devCnt)
        {
            m_deviceList.clear();
            ui->comboBox_deviceList->clear();

            // Get device list
            for(int i = 0; i < m_devCnt; i++)
            {
                QAxObject *dev = m_eloamGlobal->querySubObject("CreateDevice(int, int)", 1, i);

                if(!dev->isNull())
                {
                    m_deviceList.append(dev);
                    QString devName = dev->dynamicCall("GetFriendlyName()").toString();
                    ui->comboBox_deviceList->addItem(devName);
                }
            }


            // Get mode
            initModeComboBox(ui->comboBox_deviceList->currentIndex());

            // Get resolution
            int modeType = findModeType(ui->comboBox_videoMode->currentText());
            initResolutionComboBox(modeType);
        }

        ret = true;
    }

    m_devCntLast = m_devCnt;

    return ret;
}

void EloamCamera::setFunctionUIEnable(bool flag)
{
    if(false == flag)
    {
        // Clear ComboBox
        ui->comboBox_deviceList->clear();
        ui->comboBox_videoMode->clear();
        ui->comboBox_resolution->clear();

        ui->pushButton_openDev->setEnabled(false);
        ui->pushButton_closeDev->setEnabled(true);
    }
    else
    {
        ui->pushButton_openDev->setEnabled(true);
        ui->pushButton_closeDev->setEnabled(true);
    }

    ui->pushButton_rotateLeft->setEnabled(flag);
    ui->pushButton_rotateRight->setEnabled(flag);
    ui->pushButton_leftRight->setEnabled(flag);
    ui->pushButton_upDown->setEnabled(flag);
}


void EloamCamera::updateLogData(QString logStr)
{
    QDateTime time = QDateTime::currentDateTime();
    QString timeStr = time.toString("[yyyy-MM-dd hh:mm:ss:zzz] ");

    // Add time stamp
    logStr.prepend(timeStr);

    logFile->addLogToFile(logStr);
    ui->textEdit_log->insertPlainText(logStr.append("\n")); //Display the log in the textBrowse
    ui->textEdit_log->moveCursor( QTextCursor::End, QTextCursor::MoveAnchor );
}

void EloamCamera::updateSavePathToIniFile()
{
    currentSetting->beginGroup("CameraSetting");
    if(currentSetting->contains("SavePath"))
    {
        if(!m_storagePath.isEmpty())
        {
            currentSetting->setValue("SavePath", m_storagePath);
        }
    }

    currentSetting->endGroup();
}
