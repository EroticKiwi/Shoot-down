#include "../lib/raylib6/include/raylib.h"
#include "../utils/structs.h"

void PulsateAnimation_Btn(AnimatableButton *btn, float minWidth, float minHeight, float maxWidth, float maxHeight, float minFontSize, float maxFontSize, float speed);
void ChangeSize_OverTime(AnimatableText *text, float targetSize, float speed);