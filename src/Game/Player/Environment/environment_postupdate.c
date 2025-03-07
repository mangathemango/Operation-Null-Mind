#include <environment.h>
#include <app.h>

void Environment_Update() {
    // Update environment logic here, including collision handling
    Environment_Render(app.setup.renderer);
}