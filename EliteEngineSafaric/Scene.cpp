#include "Scene.h"
#include "Rigidbody.h"
#include "CircleCollider.h"
#include "RectangleCollider.h"
#include <iostream>
#include <fstream>

namespace Scene {
	void load(const char * Scene) {
		std::ifstream sceneFile;
		sceneFile.open("Debug/Assets/Scene.json", std::ios::in);
		if (!sceneFile) {
			std::cerr << "Error: cannot open scene." << std::endl;
			system("pause");
			exit(EXIT_FAILURE);
		}

		std::stringstream ss;
		ss << sceneFile.rdbuf();

		sceneFile.close();


		rapidjson::Document document;
		if (document.Parse(ss.str().c_str()).HasParseError()) {
			std::cerr << "Parsing Error: " << rapidjson::GetParseError_En(document.GetParseError()) << std::endl;
			system("pause");
			exit(EXIT_FAILURE);
		}
		if (!(document.HasMember("Entities") && document["Entities"].IsArray())) {
			std::cerr << "A .json Parse Error." << std::endl;
			system("Pause");
			exit(EXIT_FAILURE);
		}//Creates Entities
		for (auto entitiesIter = document["Entities"].Begin(); entitiesIter != document["Entities"].End(); ++entitiesIter) {
			Entities& newEntity = Entities::create();
			for (auto componentsIter = entitiesIter->MemberBegin(); componentsIter != entitiesIter->MemberEnd(); ++componentsIter) {
				std::string componentTypeName = componentsIter->name.GetString();
				if (componentTypeName == "Position") {
					Position& position = newEntity.addComponent<Position>();
					if (componentsIter->value.HasMember("x") && componentsIter->value["x"].IsNumber()) {
						position.X = (float)componentsIter->value["x"].GetDouble();
						printf("Position X%.2f\n", position.X);
					}
					if (componentsIter->value.HasMember("y") && componentsIter->value["y"].IsNumber()) {
						position.Y = (float)componentsIter->value["y"].GetDouble();
						printf("Position Y%.2f\n", position.Y);
					}
				}else if(componentTypeName == "Sprite"){
					Sprite& sprite = newEntity.addComponent<Sprite>();
					if (componentsIter->value.HasMember("texture") && componentsIter->value["texture"].IsString()) {
						sprite.Texture = componentsIter->value["texture"].GetString();
						sprite.isOriginCenter = componentsIter->value["OriginCenter"].GetBool();
						printf("Texture\n");
					}
				}
				else if (componentTypeName == "Rigidbody") {
					Rigidbody& rigidbody = newEntity.addComponent<Rigidbody>();
					
				}
				else if (componentTypeName == "CircleCollider") {
					CircleCollider& circleCollider = newEntity.addComponent< CircleCollider >(); 
					if (componentsIter->value.HasMember("radius") && componentsIter->value["radius"].IsNumber()) { 
						circleCollider.radius = (float)componentsIter->value["radius"].GetDouble(); 
					}
					if (componentsIter->value.HasMember("mass") && componentsIter->value["mass"].IsNumber()) {
						circleCollider.mass = (float)componentsIter->value["mass"].GetDouble();
					}
				}
				else if (componentTypeName == "RectangleCollider") {
					RectangleCollider& rectangleCollider = newEntity.addComponent< RectangleCollider >();       
					if (componentsIter->value.HasMember("width") && componentsIter->value["width"].IsNumber()) {
						rectangleCollider.width = (float)componentsIter->value["width"].GetDouble(); 
					}            
					if (componentsIter->value.HasMember("height") && componentsIter->value["height"].IsNumber()) {
						rectangleCollider.height = (float)componentsIter->value["height"].GetDouble(); 
					} 
				}
			}
		}
	}
}