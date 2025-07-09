#pragma once
#include "Singleton.h"

class SoundMgr : public Singleton<SoundMgr>
{
	friend class Singleton<SoundMgr>;

private:
	SoundMgr() = default;
	~SoundMgr() = default;

	std::unordered_map<std::string, sf::SoundBuffer> buffers;
	std::unordered_map<std::string, sf::Sound> sounds;

public:
	void Load(const std::string& id, const std::string& filename);
	void Play(const std::string& id);
};