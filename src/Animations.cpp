#include "Animations.h"

Animation::Animation()
    : frames_({}), step_(0)
{}

void Animation::addFrame(SDL_Texture* newF){
    frames_.push_back(newF);
}

SDL_Texture* Animation::operator[](int idx){
    return frames_[idx];
}

uint8_t Animation::numFrames(){
    return frames_.size();
}

// uint8_t Animation::getStep(){
//     return step_;
// }