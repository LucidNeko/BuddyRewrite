#include "io.h"

#include <cstdlib>
#include <cstring>

#include <QCoreApplication>
#include <QImage>
#include <QString>

#include "logging.h"

std::string IO::assetDirectory()
{
    static const QString assetDir = QCoreApplication::applicationDirPath()
                                              .append("/../../Buddy/assets/");
    return assetDir.toStdString();
}

//bool IO::loadImage(const char* fname, U32& width, U32& height, U8** bits)
//{
//    std::string fullpath(assetDirectory() + "textures/" + fname);
//    QImage image(fullpath.c_str());

//    if(image.isNull())
//    {
//        LOG_INFO("Loading texture \"%s\" from \"%s\" failed.", name.c_str(), fullpath.c_str());
//        return false;
//    }

//    image = image.convertToFormat(QImage::Format_RGBA8888);

//    width = image.width();
//    height = image.height();

//    *bits = std::malloc(sizeof(U8) * image.byteCount());

//    std::memcpy(*bits, image.bits(), image.byteCount());

//    return true;
//}
