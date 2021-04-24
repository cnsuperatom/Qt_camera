/********************************************************************************
** Form generated from reading UI file 'EloamCamera.ui'
**
** Created by: Qt User Interface Compiler version 5.9.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ELOAMCAMERA_H
#define UI_ELOAMCAMERA_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_EloamCamera
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout_4;
    QVBoxLayout *verticalLayout_5;
    QWidget *widget_image;
    QTextEdit *textEdit_log;
    QVBoxLayout *verticalLayout_6;
    QVBoxLayout *verticalLayout_4;
    QVBoxLayout *verticalLayout;
    QLabel *label_deviceList;
    QComboBox *comboBox_deviceList;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_videoMode;
    QComboBox *comboBox_videoMode;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_resolution;
    QComboBox *comboBox_resolution;
    QPushButton *pushButton_openDev;
    QPushButton *pushButton_closeDev;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *pushButton_rotateLeft;
    QPushButton *pushButton_rotateRight;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *pushButton_leftRight;
    QPushButton *pushButton_upDown;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout;
    QLabel *label_photoPath;
    QLineEdit *lineEdit_photoPath;
    QPushButton *pushButton_browsePhoto;
    QPushButton *pushButton_snapshot;

    void setupUi(QWidget *EloamCamera)
    {
        if (EloamCamera->objectName().isEmpty())
            EloamCamera->setObjectName(QStringLiteral("EloamCamera"));
        EloamCamera->resize(800, 600);
        gridLayout = new QGridLayout(EloamCamera);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        widget_image = new QWidget(EloamCamera);
        widget_image->setObjectName(QStringLiteral("widget_image"));
        widget_image->setEnabled(false);

        verticalLayout_5->addWidget(widget_image);

        textEdit_log = new QTextEdit(EloamCamera);
        textEdit_log->setObjectName(QStringLiteral("textEdit_log"));

        verticalLayout_5->addWidget(textEdit_log);

        verticalLayout_5->setStretch(0, 3);
        verticalLayout_5->setStretch(1, 1);

        horizontalLayout_4->addLayout(verticalLayout_5);

        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label_deviceList = new QLabel(EloamCamera);
        label_deviceList->setObjectName(QStringLiteral("label_deviceList"));

        verticalLayout->addWidget(label_deviceList);

        comboBox_deviceList = new QComboBox(EloamCamera);
        comboBox_deviceList->setObjectName(QStringLiteral("comboBox_deviceList"));

        verticalLayout->addWidget(comboBox_deviceList);


        verticalLayout_4->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        label_videoMode = new QLabel(EloamCamera);
        label_videoMode->setObjectName(QStringLiteral("label_videoMode"));

        verticalLayout_2->addWidget(label_videoMode);

        comboBox_videoMode = new QComboBox(EloamCamera);
        comboBox_videoMode->setObjectName(QStringLiteral("comboBox_videoMode"));

        verticalLayout_2->addWidget(comboBox_videoMode);


        verticalLayout_4->addLayout(verticalLayout_2);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        label_resolution = new QLabel(EloamCamera);
        label_resolution->setObjectName(QStringLiteral("label_resolution"));

        verticalLayout_3->addWidget(label_resolution);

        comboBox_resolution = new QComboBox(EloamCamera);
        comboBox_resolution->setObjectName(QStringLiteral("comboBox_resolution"));

        verticalLayout_3->addWidget(comboBox_resolution);


        verticalLayout_4->addLayout(verticalLayout_3);

        pushButton_openDev = new QPushButton(EloamCamera);
        pushButton_openDev->setObjectName(QStringLiteral("pushButton_openDev"));

        verticalLayout_4->addWidget(pushButton_openDev);

        pushButton_closeDev = new QPushButton(EloamCamera);
        pushButton_closeDev->setObjectName(QStringLiteral("pushButton_closeDev"));

        verticalLayout_4->addWidget(pushButton_closeDev);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        pushButton_rotateLeft = new QPushButton(EloamCamera);
        pushButton_rotateLeft->setObjectName(QStringLiteral("pushButton_rotateLeft"));

        horizontalLayout_2->addWidget(pushButton_rotateLeft);

        pushButton_rotateRight = new QPushButton(EloamCamera);
        pushButton_rotateRight->setObjectName(QStringLiteral("pushButton_rotateRight"));

        horizontalLayout_2->addWidget(pushButton_rotateRight);


        verticalLayout_4->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        pushButton_leftRight = new QPushButton(EloamCamera);
        pushButton_leftRight->setObjectName(QStringLiteral("pushButton_leftRight"));

        horizontalLayout_3->addWidget(pushButton_leftRight);

        pushButton_upDown = new QPushButton(EloamCamera);
        pushButton_upDown->setObjectName(QStringLiteral("pushButton_upDown"));

        horizontalLayout_3->addWidget(pushButton_upDown);


        verticalLayout_4->addLayout(horizontalLayout_3);


        verticalLayout_6->addLayout(verticalLayout_4);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_6->addItem(verticalSpacer);


        horizontalLayout_4->addLayout(verticalLayout_6);

        horizontalLayout_4->setStretch(0, 4);
        horizontalLayout_4->setStretch(1, 1);

        gridLayout->addLayout(horizontalLayout_4, 0, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label_photoPath = new QLabel(EloamCamera);
        label_photoPath->setObjectName(QStringLiteral("label_photoPath"));

        horizontalLayout->addWidget(label_photoPath);

        lineEdit_photoPath = new QLineEdit(EloamCamera);
        lineEdit_photoPath->setObjectName(QStringLiteral("lineEdit_photoPath"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(lineEdit_photoPath->sizePolicy().hasHeightForWidth());
        lineEdit_photoPath->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(lineEdit_photoPath);

        pushButton_browsePhoto = new QPushButton(EloamCamera);
        pushButton_browsePhoto->setObjectName(QStringLiteral("pushButton_browsePhoto"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(pushButton_browsePhoto->sizePolicy().hasHeightForWidth());
        pushButton_browsePhoto->setSizePolicy(sizePolicy1);

        horizontalLayout->addWidget(pushButton_browsePhoto);

        pushButton_snapshot = new QPushButton(EloamCamera);
        pushButton_snapshot->setObjectName(QStringLiteral("pushButton_snapshot"));
        sizePolicy1.setHeightForWidth(pushButton_snapshot->sizePolicy().hasHeightForWidth());
        pushButton_snapshot->setSizePolicy(sizePolicy1);

        horizontalLayout->addWidget(pushButton_snapshot);


        gridLayout->addLayout(horizontalLayout, 1, 0, 1, 1);


        retranslateUi(EloamCamera);

        QMetaObject::connectSlotsByName(EloamCamera);
    } // setupUi

    void retranslateUi(QWidget *EloamCamera)
    {
        EloamCamera->setWindowTitle(QApplication::translate("EloamCamera", "Form", Q_NULLPTR));
        label_deviceList->setText(QApplication::translate("EloamCamera", "\350\256\276\345\244\207\345\210\227\350\241\250", Q_NULLPTR));
        label_videoMode->setText(QApplication::translate("EloamCamera", "\350\247\206\351\242\221\346\250\241\345\274\217", Q_NULLPTR));
        label_resolution->setText(QApplication::translate("EloamCamera", "\345\210\206\350\276\250\347\216\207", Q_NULLPTR));
        pushButton_openDev->setText(QApplication::translate("EloamCamera", "Open", Q_NULLPTR));
        pushButton_closeDev->setText(QApplication::translate("EloamCamera", "Close", Q_NULLPTR));
        pushButton_rotateLeft->setText(QApplication::translate("EloamCamera", "Rotate Left", Q_NULLPTR));
        pushButton_rotateRight->setText(QApplication::translate("EloamCamera", "Rotate Right", Q_NULLPTR));
        pushButton_leftRight->setText(QApplication::translate("EloamCamera", "Left-Right", Q_NULLPTR));
        pushButton_upDown->setText(QApplication::translate("EloamCamera", "Up-Down", Q_NULLPTR));
        label_photoPath->setText(QApplication::translate("EloamCamera", "Photo Path", Q_NULLPTR));
        pushButton_browsePhoto->setText(QApplication::translate("EloamCamera", "Browse", Q_NULLPTR));
        pushButton_snapshot->setText(QApplication::translate("EloamCamera", "Snapshot", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class EloamCamera: public Ui_EloamCamera {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ELOAMCAMERA_H
