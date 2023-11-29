#pragma once
class Water : public Actor
{
private:
    float uvScale = 20.0f;
    struct WaterBuffer
    {
        Vector2 velocity;
        float time;
        float padding;
        Vector4 plane;
    }waterBufferDesc;
    ID3D11Buffer* waterBuffer;

    //반사될 상 그려줄 렌더타겟
    CubeRenderTarget* reflection;


public:
    static Water* Create(string name = "Water");
    Water();

    void Update();
    virtual void Render(shared_ptr<Shader> pShader = nullptr);
    void RenderDetail();

    void SetReflectionTarget();

};


