#ifndef TESTSCRIPT_H
#define TESTSCRIPT_H

#include "components/script.h"
#include "types.h"

class TestScript : public Script
{
public:
    TestScript(EntityHandle entity = nullptr);
    virtual ~TestScript();

    void onStart() override;
    void onEnter() override;
    void onUpdate(GameTime time, const class Input& input) override;
    void onExit() override;

private:
    bool _first;
    F32 _elapsed;
    I32 _dir;
};

#endif // TESTSCRIPT_H
