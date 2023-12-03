#pragma once

class Particle : public Actor
{
protected:

    //현재 재생중인 시간
    float playTime = 0.0f;
    //재생중인가?
   
public:
    //총 재생시간
    bool isPlaying = false;
    bool isErasing = false;
    float duration = 1.0f;
    virtual void    Play()
    {
        playTime = 0.0f;
        isPlaying = true;
    };
    virtual void    Stop()
    {
        isErasing = true;
        /*isPlaying = false; */
    };
    void            UpdateParticle();
    void            Gui();
    float           PlayTime() { return playTime / duration; } //재생시간 비율
    bool            IsPlaying() { return isPlaying; } //재생중인가?
};



