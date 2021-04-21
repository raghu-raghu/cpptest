//#include <__bit_reference>
//
// Created by Alyssa Foglia on 4/14/21.
//
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;
#include <fstream>
using namespace sf;
#include "Tiles.h"
#pragma once
//#ifndef PROJECT3MINESWEEPER_BOARD_H
//#define PROJECT3MINESWEEPER_BOARD_H


class Board {
public:
    int height;
    int width;
    int mineCount;
    int tileCount=0;
    int overallMineCount=0;
    int xEvent;
    int yEvent;
    void updateBoard(sf::RenderWindow& window);
    void savePosition(sf::Event event);
    int flagCount=0;
    vector<sf::Sprite> flags;
    int bombCount=0;
    vector<sf::Sprite> bombs;
    vector<vector<Tiles>> boardvec;
    void loadWindow(string filename);
    void initializeBoard(sf::RenderWindow& window);
    map<string, sf::Texture> images;
    bool mineClicked=false;
    bool debugmode = false;
    vector<int> boardNums;
    void setUpBoard(int x);
    void LoadAllTextures();
    void drawDigits(int a, sf::RenderWindow& window);
    void loadDigits(sf::RenderWindow& window);
    sf::Vector2i pos;
    int revealedTiles = 0;
    int numFlags =0;
    vector<int> t1;
    vector<int> t2;
    vector<int> t3;
    void randomizeMines( vector<vector<Tiles>>& tiles);
    void getNumber(string number, vector<string> &numdraw);
    void drawNumbers(int flagCount, int overallMineCount, sf::RenderWindow &window,map<string,sf::Texture> &images);
    void setNeighbors();
    void endgame(sf::RenderWindow &window);
    vector<vector<int>> t12;
    vector<vector<int>> fortest2;
    vector<vector<int>> fortest3;
    void reset(sf::RenderWindow &window);
    void win(sf::RenderWindow & window);
    bool resetbool = false;
    bool debugbool = false;
    void bottomButtons(int x, int y, sf::RenderWindow &window);
    void draw(sf::RenderWindow &window);
    bool test2=false;
    bool test1=false;
    bool test3=false;
    void debugBoard(sf::RenderWindow &window);


    sf::Sprite back;
    sf::Sprite front;
    sf::Sprite flagSprite;
    sf::Sprite itemSprite;
    sf::Sprite debugSprite;
    sf::Sprite test1Sprite;
    sf::Sprite test2Sprite;
    sf::Sprite test3Sprite;
    sf::Sprite SmileySprite;
    sf::Sprite sadSprite;
    sf::Sprite winningFace;
    sf:: Sprite digits;
    sf::Sprite bomb;
};


//#endif //PROJECT3MINESWEEPER_BOARD_H
