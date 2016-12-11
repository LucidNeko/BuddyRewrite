#include "uuid.h"

#include <vector>

#include <QByteArray>
#include <QString>
#include <QUuid>

Uuid::Uuid()
{
    QUuid uuid = QUuid::createUuid();

    QByteArray bytes = uuid.toRfc4122();

    for(I32 i = 0; i < 16; i++)
    {
        _uuid.bytes[i] = bytes.at(i);
    }
}

Uuid::Uuid(const std::string& string)
{
    QUuid uuid(QString::fromStdString(string));

    if(uuid.isNull())
    {
        _uuid.number.first = 0;
        _uuid.number.second = 0;
    }
    else
    {
        QByteArray bytes = uuid.toRfc4122();

        for(I32 i = 0; i < 16; i++)
        {
            _uuid.bytes[i] = bytes.at(i);
        }
    }
}

std::string Uuid::toString() const
{
    std::vector<char> uuidBytes(_uuid.bytes, _uuid.bytes + 16);

    QByteArray bytes(&uuidBytes[0], 16);

    QUuid uuid = QUuid::fromRfc4122(bytes);

    return uuid.toString().toStdString();
}
