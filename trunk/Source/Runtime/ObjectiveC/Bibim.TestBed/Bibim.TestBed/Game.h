#include <Bibim/GameFramework.h>

class Game : public Bibim::GameFramework
{
public:
    virtual void Initialize();
    virtual void Finalize();
    virtual void Update(float dt, int timestamp);
    virtual void Draw();
};