//
// Created by Alyssa Foglia on 4/14/21.
//

#include "TextureManager.h"

unordered_map<string, sf::Texture> TextureManager::textures;

void TextureManager::LoadTexture(const char *fileName) {
    string filePath = "images/";
    filePath += fileName;
    filePath += ".png";

    textures[fileName].loadFromFile(filePath);
}

sf::Texture &TextureManager::GetTexture(const char *texKey) {
    if(textures.find(texKey) == textures.end()){
        LoadTexture(texKey);
    }
    return textures[texKey];
}

void TextureManager::LoadAllTextures() {
    LoadTexture("debug");
    LoadTexture("digits");
    LoadTexture("face_happy");
    LoadTexture("face_lose");
    LoadTexture("face_win");
    LoadTexture("flag");
    LoadTexture("mine");
    LoadTexture("number_1");
    LoadTexture("number_2");
    LoadTexture("number_3");
    LoadTexture("number_4");
    LoadTexture("number_5");
    LoadTexture("number_6");
    LoadTexture("number_7");
    LoadTexture("number_8");
    LoadTexture("test_1");
    LoadTexture("test_2");
    LoadTexture("test_3");
    LoadTexture("tile_revealed");
}