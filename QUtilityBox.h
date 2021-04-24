/**********************************************************************
PACKAGE:        Utility
FILE:           QUtilityBox.h
COPYRIGHT (C):  All rights reserved.

PURPOSE:        General tool box, provide buffer convert function and etc.
**********************************************************************/

#ifndef QUTILITYBOX_H
#define QUTILITYBOX_H
#include <QString>
#include <stdint.h>


class QUtilityBox
{
public:
    QUtilityBox();
    virtual ~QUtilityBox();

    // Convert Hex QString to data buffer
    // For example, "12 34 56" to 0x12, 0x34, 0x56, return 3
    uint32_t convertHexStringToDataBuffer(uint8_t *convertedDataBuffer, const QString &inputStr);

    // For example, "1234 5678" to 0x1234, 0x5678, return 2
    uint32_t convertHexStringToDataBuffer(uint16_t *convertedDataBuffer, const QString &inputStr);

    // Convert Decimal QString to data buffer
    // For example, "16 128" to 16, 128, return 2
    uint32_t convertDecStringToDataBuffer(uint8_t *convertedDataBuffer, const QString &inputStr);

    // For example, "1024 1280" to 1024, 1280, return 2
    uint32_t convertDecStringToDataBuffer(uint16_t *convertedDataBuffer, const QString &inputStr);

    // Convert data buffer to Hex QString
    // For example, data[0]=15 data[1]=32, return "0F 20 "
    QString convertDataToHexString(const QByteArray &data);
    QString convertDataToHexString(const uint8_t *data, int len);

    // If the path not exist, create folder for path
    void mkdir(QString path);
};

#endif // QUTILITYBOX_H
