#include "Animations.h"

Animation::Animation()
    : _frames({}), step(0)
{}

void Animation::addFrame(Texture* newF){
    _frames.push_back(newF);
}

Texture* Animation::operator[](int idx){
    return _frames[idx];
}

uint8_t Animation::numFrames(){
    return _frames.size();
}
