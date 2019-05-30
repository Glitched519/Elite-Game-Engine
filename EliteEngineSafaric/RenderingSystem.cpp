#include "RenderingSystem.h"
#include "Entities.h"
#include "Position.h"
#include "Sprite.h"
#include <Windows.h>
#include <process.h>
#include <string>

RenderingSystem::RenderingSystem(sf::RenderWindow* window)
{
	
	componentMask = Position::getMask() | Sprite::getMask();
}

void RenderingSystem::update(sf::RenderWindow *window) 
{
	for (Entities&entity : Entities::getEntityList())
	{
		if ((entity.getComponentMask()&componentMask) == componentMask) {
			Position&pos = entity.getComponent<Position>();
			Sprite&sprite = entity.getComponent<Sprite>();
			//Add texture to pool
			if (_textureMap.count(sprite.Texture) < 1) {
				_textureMap[sprite.Texture] = _loadTexture(sprite.Texture);
			}
			//If there's not texture, add it
			if (sprite.sprite.getTexture() == NULL) {
				sprite.sprite.setTexture(*_textureMap[sprite.Texture]);
				sprite.width = sprite.sprite.getGlobalBounds().width;
				sprite.height = sprite.sprite.getGlobalBounds().height;
				if (sprite.isOriginCenter)
					sprite.sprite.setOrigin(sprite.width / 2, sprite.height / 2);
				
			}
			//Changes depending if we want origin centered or not
			if (!sprite.isOriginCenter)
				sprite.setPosition(pos.X - (sprite.width / 2), pos.Y - (sprite.height / 2));
			else
				sprite.setPosition(pos.X, pos.Y);
			window->draw(sprite.sprite);
		}
	}
}

sf::Texture* RenderingSystem::_loadTexture(std::string Texture) {
	sf::Texture* tex = new sf::Texture();
	if (!tex->loadFromFile(Texture)) {
		std::cerr << "Unable to load image." << Texture << ".\nIs this image in the correct directory? " << std::endl;
		std::cerr << "Error: " << std::endl;
		system("pause");
		exit(EXIT_FAILURE);
	}
	return tex;
}
RenderingSystem::~RenderingSystem(void)
{
}
