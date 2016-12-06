#ifndef TESTSCENE_H
#define TESTSCENE_H

#include <vector>

#include "entitycollection.h"
#include "scenes/scene.h"
#include "types.h"

class TestScene : public Scene
{
public:
    TestScene();
    ~TestScene();

    void onEnter() override;
    void onExit() override;
};

#endif // TESTSCENE_H
