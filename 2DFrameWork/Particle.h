#pragma once

class Particle : public Actor
{
protected:

    //���� ������� �ð�
    float playTime = 0.0f;
    //������ΰ�?
   
public:
    //�� ����ð�
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
    float           PlayTime() { return playTime / duration; } //����ð� ����
    bool            IsPlaying() { return isPlaying; } //������ΰ�?
};



