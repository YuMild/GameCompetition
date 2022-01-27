#pragma once

using namespace std;

class FontPurpleNumber : public IGameObject
{
public:

	FontPurpleNumber();
	~FontPurpleNumber();
	bool Start();

	/// <summary>
	/// �\�������������������
	/// </summary>
	/// <param name="number"></param>
	void Init(int number);

	/// <summary>
	/// �|�W�V�������w��ł���
	/// </summary>
	/// <param name="position"></param>
	void SetPosition(const Vector3& position)
	{
		m_position = position;
	}

	/// <summary>
	/// �T�C�Y���w��ł���
	/// </summary>
	/// <param name="scale"></param>
	void SetScale(const Vector3& scale)
	{
		m_scale = scale;
	}

	void Update();
	void Render(RenderContext& rc);

private:

	std::vector<std::unique_ptr<SpriteRender>>m_fontPurpleNumberList;		//�ϒ��z��

	Vector3 m_position;
	Vector3 m_scale;
};