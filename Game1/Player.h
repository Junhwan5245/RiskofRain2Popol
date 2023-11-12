#pragma once

/**
player Animation
Commando

애니메이션 #115933  == #1074766 == #1076287 == 1139078
선택창 #115885
앉아서 쉬기? #272820

// 이동상태
2번 앞으로 걷기
3번 뒤로 가기
4번 가만히 있기
5번 왼쪽
6번 오른쪽

7번 가만히 있기..

// 달리기 상태
8번 앞으로 뛰기

// 슬라이딩 및 구르기 상태
9번 슬라이딩

// 쉬프트 스킬
10번 좌로구르기
11번 우로구르기
12번 앞으로 구르기
13번 뒤로 구르기

// 공중에 떠있는 상태
14번 점프 시작 모션
15번 공중에 잠깐 떠있는 모션
16번 점프
17번 착지 (높은곳에서 떨어질때도 이모션)

// 공격?
18번 장전?
19번 뭔가를 던지고 있는데 모르겠음?
20번 한팔로 뭔가를 하네?
21번 팔을 내리는 모션
22번 공격모션인가?
23번 정면 보면서 팔벌리는중
24번 우측 보면서 팔벌리는중
25번 정면 보고 팔벌리면서 안움직음
26번 정면 보고 팔벌리면서 상체만 까딱
27번 정면 보고 팔벌리면서 상체만 좀 더 빠르게 까딱

28번 두팔을 아래 정면 위로 하는 모션
29번 좌에서 우로 뭔가를 쏘는거같은 모션
30번 오른팔 가만히 왼팔로만 뭔가를 쏜다?
31번 왼팔 가만히 오른팔로만 뭔가를 쏘기
32번 뭔가 피격모션인듯
33번 ? 그냥 상체를 우측으로 까딱
34번 ? 상테를 좌측으로 까딱
*/


enum class PlayerState
{
    // 움직임
    IDLE,       // 가만히 있기
    WALK,       // 걷기
    RUN,        // 뛰기
    ROLL,       // 구르기
    SLIDE,      // 슬라이딩
};

enum class PlayerAttackState
{
    IDLE,
    ATTACK,
};

enum class Attack
{
    NONE,
    LBUTTON,
    RBUTTON,
    R,
};


class Player : public Unit
{
public:
    static Player* Create(string name = "Player");

private:
    // Player는 몸통메쉬 + 이동 애니메이션만, playerGun은 총메쉬 + 공격 애니메이션만
    //Actor* playerGun;   //고민중..
    vector<class Bullet*>   bullet;     // 총알


    PlayerState         playerState;    // 플레이어 이동상태
    PlayerAttackState   attackState;    // 플레이어 공격상태
    Attack              attack;         // 공격

    Vector3             dir;            // 대체, 나중에 Unit클래스를 상속 받을 친구
    Vector3             fixDir;         // 굴렀을때의 고정된 방향값
    
    float               lastRot;
    float               attackStopTime; // 공격 멈춘 시간 (4초가 되면 isAttack = false)

    bool                isRight;
    bool                isRoll;         // 구르고 있는지
    bool                isLButton;      // 좌클릭이 눌렸는지
    bool                isRButton;      // 우클릭이 눌렸는지
    bool                isRSkill;       // R이 눌렸는지
    
    float               attackSpeed = 0.1f;    // 공속
    float               LButtonFireTime;// 좌클릭 발사타임

    /** 임시스텟*/
    float               velocity;       // 이동속도


    Player();
    virtual ~Player();
public:
    void	Update() override;
    void	Render(shared_ptr<Shader> pShader = nullptr) override;

    void    FSM();
    void    AttackMotion(Attack state);
    void    AinmChange(PlayerState state);
    void    Move(Vector3 Target);

    void    Fire(Vector3 dest, float power);
    void    WolrdUpdate();
    void    PlayerRenderHierarchy();


    /** Get함수*/
    //Vector3 GetLast() { return last; };
    PlayerState     GetPlayerState() { return playerState; }
};

