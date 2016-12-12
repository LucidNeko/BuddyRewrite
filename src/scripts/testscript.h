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
    void onUpdate(GameTime time) override;
    void onExit() override;

private:
    bool _first;
};

#endif // TESTSCRIPT_H
