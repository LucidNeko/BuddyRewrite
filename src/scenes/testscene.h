#ifndef TESTSCENE_H
#define TESTSCENE_H

#include <vector>

#include "entitycollection.h"
#include "scenes/scene.h"
#include "types.h"

#include "assets/assets.h"

class TestScene : public Scene
{
public:
    TestScene(AssetsHandle assets);
    ~TestScene();

    void onEnter() override;
    void onExit() override;

private:
};

#endif // TESTSCENE_H
