#include "../headers/animations.h"
#include <math.h>
#include <stdio.h>

void PulsateAnimation_Btn(AnimatableButton *btn, float minWidth, float minHeight, float maxWidth, float maxHeight, float minFontSize, float maxFontSize, float speed){
    float wave = (sin(GetTime() * speed) + 1.0f) / 2.0f;

    btn->currentSize.x = minWidth + ((maxWidth - minWidth) * wave);
    btn->currentSize.y = minHeight + ((maxHeight - minHeight) * wave);

    btn->btnText.currentFontSize = minFontSize + ((maxFontSize - minFontSize) * wave);
}

void ChangeSize_OverTime(AnimatableText *text, float targetSize, float speed){
    
    if(targetSize < 0){
        printf("\n[animations.h] WARNING: targetSize CAN'T BE A NEGATIVE NUMBER!");
        return;
    }

    text->currentFontSize -= GetFrameTime() * speed;
    if(text->currentFontSize <= targetSize){
        text->currentFontSize = targetSize;
    }
}