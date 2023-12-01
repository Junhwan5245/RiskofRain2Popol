#pragma once
#include "PerlinNoise.hpp"
class Terrain : public Actor
{
    struct InputDesc
    {
        UINT index;
        Vector3 v0, v1, v2;
    };
    struct OutputDesc
    {
        int picked;
        float u, v, distance;
    };
    struct RayDesc
    {
        Vector3 position;
        float size;
        Vector3 direction;
        float padding;
    };
	static ID3D11ComputeShader* computeShader;

public:
	static Terrain* Create(string name = "Terrain");
    static void		CreateStaticMember();
    static void		DeleteStaticMember();
protected:
	Terrain();
	~Terrain();
private:
    //compute Input
    InputDesc* inputArray;
    ID3D11Resource* input;
    ID3D11ShaderResourceView* srv = nullptr;//읽기전용
    //compute Output
    OutputDesc* outputArray;
    ID3D11Resource* output;
    ID3D11UnorderedAccessView* uav;//읽기쓰기 둘다가능
    //copy용
    ID3D11Resource* result;
    //ray
    RayDesc                     ray;
    ID3D11Buffer* rayBuffer;
public:
	int				size;
	float			uvScale;
	int				garo;

    double          baseFrequency{ 3.0 };            // 기본 주파수
    double          amplitude{ 3.0 };           // 진폭
    double          edgeSteepness{ 1.0 };            // 가장자리 경사의 가파름 조절
    double          distanceFactor{ 3 };             // 중앙과의 거리에 따른 높이 계수
    //CS            컴퓨트 쉐이더로 피킹할때만 만들기
    void            CreateStructuredBuffer();
    void            DeleteStructuredBuffer();

	void			CreateMesh(int   garo);
	void			LoadHeightRaw(string file);
	void			LoadHeightImage(string file);
	void			UpdateStructuredBuffer();
	void			UpdateNormal();
	void	        RenderDetail();
    void            PerlinNoise();
    double          IslandNoise(siv::PerlinNoise& perlin, double x, double y, double z, int i, int j);

    bool            ComPutePicking(Ray WRay, OUT Vector3& HitPoint);
};

