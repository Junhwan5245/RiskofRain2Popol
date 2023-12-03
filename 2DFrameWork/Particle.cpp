#include "framework.h"

//��ã��,��ƼŬ


//���ݻ繰����
//���۵巻����
//�����
//�׼����̼�

void Particle::UpdateParticle()
{
	if (isPlaying)
	{
		playTime += DELTA;
		if (playTime > duration)
		{
			Stop();
		}
	}
}

void Particle::Gui()
{
	if (ImGui::Button("Play"))
	{
		Play();
	}
	ImGui::SameLine();
	if (ImGui::Button("Stop"))
	{
		Stop();
	}
	//���� ��� �ð�
	ImGui::Text("Playtime : %f", PlayTime());
	//�� ����� �ð�
	ImGui::SliderFloat("duration", &duration, 0.0f, 100.0f);
}



