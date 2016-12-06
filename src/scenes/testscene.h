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
    TestScene();
    ~TestScene();

    void onEnter() override;
    void onExit() override;

private:
    Assets _assets;
};

#endif // TESTSCENE_H
