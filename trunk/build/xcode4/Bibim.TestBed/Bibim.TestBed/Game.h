#include <Bibim/StandardGame.h>

class Game : public Bibim::StandardGame
{
public:
    virtual void Initialize();
    virtual void Finalize();
    virtual void Update(float dt, int timestamp);
    virtual void Draw();
    
    virtual void ReloadScripts() { }
};