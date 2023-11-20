#pragma once

/**
player Animation
Commando

�ִϸ��̼� #115933  == #1074766 == #1076287 == 1139078
����â #115885
�ɾƼ� ����? #272820

// �̵�����
2�� ������ �ȱ�
3�� �ڷ� ����
4�� ������ �ֱ�
5�� ����
6�� ������

7�� ������ �ֱ�..

// �޸��� ����
8�� ������ �ٱ�

// �����̵� �� ������ ����
9�� �����̵�

// ����Ʈ ��ų
10�� �·α�����
11�� ��α�����
12�� ������ ������
13�� �ڷ� ������

// ���߿� ���ִ� ����
14�� ���� ���� ���
15�� ���߿� ��� ���ִ� ���
16�� ����
17�� ���� (���������� ���������� �̸��)

// ����?
18�� ����?
19�� ������ ������ �ִµ� �𸣰���?
20�� ���ȷ� ������ �ϳ�?
21�� ���� ������ ���
22�� ���ݸ���ΰ�?
23�� ���� ���鼭 �ȹ�������
24�� ���� ���鼭 �ȹ�������
25�� ���� ���� �ȹ����鼭 �ȿ�����
26�� ���� ���� �ȹ����鼭 ��ü�� ���
27�� ���� ���� �ȹ����鼭 ��ü�� �� �� ������ ���

28�� ������ �Ʒ� ���� ���� �ϴ� ���
29�� �¿��� ��� ������ ��°Ű��� ���
30�� ������ ������ ���ȷθ� ������ ���?
31�� ���� ������ �����ȷθ� ������ ���
32�� ���� �ǰݸ���ε�
33�� ? �׳� ��ü�� �������� ���
34�� ? ���׸� �������� ���
*/

/**
�̹��� �۾��ؾ��Ұ�
- ĳ���� ����â �� �Ϸ�
    - ���� ĳ���� ����, ��ų �� ĳ���� ����
    - ��ų ���� ����
    - -> ������ ĳ����, ������ ��ų, ������ ���̵��� ĳ���� ���� �� ���Ӿ� ����

- �÷��̾� �Ϸ�
    - ����, ��Ŭ��, R��ų ����
    - ���� ����

- ���Ӿ� UI ?
    - UI ��ġ �� ĳ���� ���� or ü�¹� UI
*/


enum class PlayerState
{
    // ������
    IDLE,       // ������ �ֱ�
    WALK,       // �ȱ�
    RUN,        // �ٱ�
    ROLL,       // ������
    SLIDE,      // �����̵�
};

enum class PlayerAttackState
{
    IDLE,
    ATTACK,
};

enum class SkillState
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
    

    PlayerState         playerState;    // �÷��̾� �̵�����
    PlayerAttackState   attackState;    // �÷��̾� ���ݻ��� // ���ݻ��³� �ƴϸ� 
    SkillState          skillState;         // ����       // ��Ŭ���̳� ��Ŭ���̳� R�̳�

    //Vector3             dir;            // ��ü, ���߿� UnitŬ������ ��� ���� ģ��
    Vector3             fixDir;         // ���������� ������ ���Ⱚ
    Vector3             mouseDir;       // ���콺�� ����


    float               lastRot;
    float               lastRot_root;
    float               attackStopTime; // ���� ���� �ð� (4�ʰ� �Ǹ� isAttack = false)

    bool                isRight;
    bool                isRoll;         // ������ �ִ���
    bool                isLButton;      // ��Ŭ���� ���ȴ���
    bool                isRButton;      // ��Ŭ���� ���ȴ���
    bool                isRSkill;       // R�� ���ȴ���
    
    float               attackSpeed = 0.2f;    // ����
    float               LButtonFireTime;// ��Ŭ�� �߻�Ÿ��

    /** �ӽý���*/
    float               velocity;       // �̵��ӵ�
           //���ݷ�

    Player();
    virtual ~Player();
public:
    float               attack = 10;
    void	Update() override;
    void	Render(shared_ptr<Shader> pShader = nullptr) override;

    void    FSM();
    void    AinmChange(PlayerState state);
    void    Move(Vector3 Target);

    void    Fire(Vector3 dest, float power);
    void    WolrdUpdate();
    void    PlayerRenderHierarchy();


    /** Get�Լ�*/
    //Vector3 GetLast() { return last; };
    PlayerState     GetPlayerState() { return playerState; }
};

