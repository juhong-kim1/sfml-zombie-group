#include "stdafx.h"
#include "SoundMgr.h"

void SoundMgr::Load(const std::string& id, const std::string& soundName)
{
	sf::SoundBuffer buffer;
	buffer.loadFromFile(soundName);
	buffers[id] = buffer;
	sounds[id].setBuffer(buffers[id]);
}

void SoundMgr::Play(const std::string& id)
{
	auto it = sounds.find(id);
	if (it != sounds.end())
	{
		it->second.play();
	}
}