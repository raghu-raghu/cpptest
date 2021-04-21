//
// Created by Alyssa Foglia on 4/13/21.
//

//#ifndef PROJECT3MINESWEEPER_TILES_H
#define PROJECT3MINESWEEPER_TILES_H
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;
#include <fstream>
#include <vector>
using namespace sf;
#pragma once
#include <ctime>
//#include "Board.h"

struct Tiles {
    public:
        void tileClicked(vector<vector<Tiles>>& tiles, int x, int y);
        int xcor;
        int ycor;
        int adjacentMine;
        int flagCount;
        int minecount;
        int numberrevealed;
        int numbertoberevealed;
        bool flag=false;
        bool mine;
        bool clickedMine;
        bool debugmode=false;
        bool revealed=false;
        bool noMineReveal;
        bool thesearetrue;
        bool item = false;
        bool isMine();
        bool getflag();
        bool checkwin(vector<vector<Tiles>>& boardvec);
        void renderTile(sf::RenderWindow &window,int i , int j,vector<vector<Tiles>>& tiles,map<string, sf::Texture>& images);
        void Tile(map<string, sf::Texture>& images, bool mine, int xcor, int ycor);
        vector<Tiles*> tileNeighbor;
        void setItem(map<string, sf::Texture>& images,vector<vector<Tiles>>& tiles, sf::RenderWindow &window);
        void countNeighborMine();
        void revealClicked(vector<vector<Tiles>>& tiles, int x, int y);
        int getFlagCount();
        void endgame();
        bool endgamebool;
        bool endgameintiles;
        void recursion(int i, int j,sf::RenderWindow &window,vector<vector<Tiles>>& boardvec);
        int bottomoftheboard(int x, int y);
    bool reset2;
    void resetInTiles(vector<vector<Tiles>>& tiles,sf::RenderWindow &window);
    void revealTile(vector<vector<Tiles>>& tiles,map<string, sf::Texture>& images, sf::RenderWindow &window);
        void revealallmines(vector<vector<Tiles>>& tiles,sf::RenderWindow &window);
        void debugbuttonPressed(vector<vector<Tiles>>& tiles,sf::RenderWindow &window);
    bool clickedabomb;
    bool leftclick=false;
    bool areThereAdjacentMines;
    bool drawhiddentile;
    bool rightclick;
    bool stoprevealing;
    void getXY();


        sf::Sprite back;
        sf::Sprite front;
        sf::Sprite flagSprite;
        sf::Sprite itemSprite;
        sf::Sprite bomb;
        sf::Sprite sadSprite;

    };






//#endif //PROJECT3MINESWEEPER_TILES_H
