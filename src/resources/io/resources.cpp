#include "resources/io/resources.h"

#include <QCoreApplication>
#include <QString>

Resources::Resources()
    : _d()
{
    QString assetDir = QCoreApplication::applicationDirPath().append("/../../../assets/");

    _d.reset(new FileBackedResources(assetDir.toStdString()));
}

void Resources::unloadFreeResources()
{
    // TODO: resources that reference other resources prevent resources higher in the tree from being deleted.
    // texture <- spritesheet. need to delete spritesheet before texture can be removed.
    _d->unloadFreeResources();
    _d->unloadFreeResources();
    _d->unloadFreeResources();
}
