//
// Created by Alyssa Foglia on 4/13/21.
//

#include "Tiles.h"
#include <fstream>


void Tiles::tileClicked(vector<vector<Tiles>>& boardvec, int x, int y){            //new
    int x2= (x/32);
    int y2 = y/32;
    boardvec[y2][x2].rightclick=true;
    //cout<< x << "--" << y << " -- " << x2 << " " << y2 << endl;
    if(boardvec[y2][x2].flag==false){
        boardvec[y2][x2].flag=true;
        this->flagCount++;

    }
    else if(boardvec[y2][x2].flag==true){
        boardvec[y2][x2].flag=false;
        this->flagCount--;

    }
    boardvec[y2][x2].areThereAdjacentMines=false;

}
void Tiles::revealClicked(vector<vector<Tiles>>& tiles, int x, int y){


    int x2= (x/32);
    int y2 = y/32;
    if(y2 > 15) return;
    tiles[y2][x2].areThereAdjacentMines=true;
    tiles[y2][x2].rightclick = false;
    tiles[y2][x2].leftclick = true;
    cout << "LEFT CLICK-------------------" <<endl;

    if(y2>15) return;           //added might stop crashing

   if (tiles[y2][x2].mine==true){
        endgamebool=true;
        tiles[y2][x2].endgameintiles=true;
       tiles[y2][x2].leftclick = true;
    }
   else{
       endgamebool=false;
       tiles[y2][x2].leftclick = true;
       tiles[y2][x2].endgameintiles=false;
   }
}

void Tiles::renderTile(sf::RenderWindow &window, int i,int j,vector<vector<Tiles>>& tiles, map<string, sf::Texture>& images) {           //new

    if (tiles[i][j].rightclick == true) {
        if (tiles[i][j].flag == true) {
            //cout<< "i --" << i << " "<<"j-- " <<j<<endl;
            flagSprite.setPosition((j * 32), (i * 32));
            window.draw(flagSprite);
            tiles[i][j].revealed=true;
        } else if (!flag) {
            front.setPosition(j * 32, i * 32);
            window.draw(front);
            tiles[i][j].revealed=true;
        }
    }
    else if(tiles[i][j].leftclick == true){
        if(endgamebool==true && tiles[i][j].endgameintiles==true){
            revealallmines(tiles,window);
        }

        else{
            /*if(tiles[i][j].adjacentMine==0){
                this->numberrevealed++;
                //recursion();
                for (int i = 0; i < tileNeighbor.size(); i++) {
                    if (tileNeighbor[i] != nullptr && !tileNeighbor[i]->item && !tileNeighbor[i]->mine && !tileNeighbor[i]->flag) {
                        if(tileNeighbor[i]->revealed==false) {
                            tileNeighbor[i]->setItem(images, tiles, window);
                            itemSprite.setPosition(j * 32, i * 32);
                            window.draw(itemSprite);
                            //tileNeighbor[i]->revealTile(tiles,images,window);

                            //call function to draw
                            //recursion();
                        }
                    }
                }

            }*/
            if(tiles[i][j].stoprevealing==true){
                recursion(i,j,window,tiles);
            }

            if(debugmode==true && tiles[i][j].mine==true){
                bomb.setPosition(j * 32, i * 32);
                window.draw(bomb);

                cout<< j << " " << i << " -----------------------" << endl;
            }
            else {
                //revealTile(tiles, images, window);
                itemSprite.setPosition(j * 32, i * 32);
                window.draw(itemSprite);
                checkwin(tiles);
                tiles[i][j].revealed = true;
            }

        }

    }

}

void Tiles::Tile(map<string, sf::Texture>& images, bool mine, int xcor, int ycor){
    this->xcor=xcor;
    this->ycor=ycor;
    this->mine=mine;
    this->debugmode=false;
    this->flag=false;
    this->revealed=false;
    this->item=false;
    this->adjacentMine=0;

    back.setPosition(sf::Vector2f(xcor, ycor));
    back.setTexture(images["tile_revealed.png"]);
    front.setPosition(sf::Vector2f(xcor, ycor));
    front.setTexture(images["tile_hidden.png"]);
    flagSprite.setPosition(sf::Vector2f(xcor, ycor));
    flagSprite.setTexture(images["flag"]);
    itemSprite.setPosition(sf::Vector2f(xcor, ycor));
    bomb.setTexture(images["mine"]);
    bomb.setPosition(sf::Vector2f(xcor, ycor));

    tileNeighbor.clear();
    for (int i = 0; i < 8; i++) {
        tileNeighbor.push_back(nullptr);
    }

}
void Tiles::setItem(map<string, sf::Texture>& images, vector<vector<Tiles>>& tiles, sf::RenderWindow &window)
{   //item=false;
    //tileNeighbor.clear();
    countNeighborMine();

    if (mine == true) {
        itemSprite.setTexture(images["mine"]);
        item = true;
        minecount++;
        stoprevealing = false;
    }

    else {
        if (adjacentMine == 0) {
            itemSprite.setTexture(images["tile_revealed.png"]);
            item = false;
            stoprevealing = true;
            this->numbertoberevealed++;
            //revealTile(tiles,images,window);
            //return;
        }
        else if (adjacentMine == 1) {
            itemSprite.setTexture(images["number_1"]);
            item = true;
            stoprevealing = false;

        }
        else if (adjacentMine == 2) {
            itemSprite.setTexture(images["number_2"]);
            item = true;
            stoprevealing = false;
        }
        else if (adjacentMine == 3) {
            itemSprite.setTexture(images["number_3"]);
            item = true;
            stoprevealing = false;
        }
        else if (adjacentMine == 4) {
            itemSprite.setTexture(images["number_4"]);
            item = true;
            stoprevealing = false;
        }
        else if (adjacentMine == 5) {
            itemSprite.setTexture(images["number_1"]);
            item = true;
            stoprevealing = false;
        }
        else if (adjacentMine == 6) {
            itemSprite.setTexture(images["number_6"]);
            item = true;
            stoprevealing = false;
        }
        else if (adjacentMine == 7) {
            itemSprite.setTexture(images["number_7"]);
            item = true;
            stoprevealing = false;
        }
        else if (adjacentMine == 8) {
            itemSprite.setTexture(images["number_8"]);
            item = true;
            stoprevealing = false;
        }

    }

}
void Tiles::countNeighborMine(){
    adjacentMine = 0;
    //tileNeighbor.clear();
    for (unsigned int i = 0; i < tileNeighbor.size(); i++) {
        if (tileNeighbor[i] != nullptr && tileNeighbor[i]->isMine() == true) {
            adjacentMine++;
            //tileNeighbor[i]->areThereAdjacentMines =true;
        }
    }
}

bool Tiles::isMine(){
    return mine;
}

bool Tiles::getflag(){
    return flag;
}
int Tiles::getFlagCount() {
    return this->flagCount;
}
void Tiles::revealallmines(vector<vector<Tiles>>& tiles,sf::RenderWindow &window){
    for(int i=0; i<tiles.size();i++){
        for(int j=0;j<tiles[i].size();j++){
            if(tiles[i][j].mine==true){
                bomb.setPosition(j*32,i*32);
                window.draw(bomb);
                cout << "MINE REVEALED" <<endl;
            }
        }
    }
    debugmode=false;

}
void Tiles::revealTile(vector<vector<Tiles>>& tiles,map<string, sf::Texture>& images, sf::RenderWindow &window) {

        for (int i = 0; i < tileNeighbor.size(); i++) {
            if (tileNeighbor[i] != nullptr && !tileNeighbor[i]->item && !tileNeighbor[i]->mine && !tileNeighbor[i]->flag) {
                if(tileNeighbor[i]->revealed==false) {
                    //tileNeighbor[i]->setItem(images, tiles, window);
                    itemSprite.setTexture(images["tile_revealed.png"]);
                    window.draw(itemSprite);
                    //tileNeighbor[i]->revealTile(tiles,images,window);

                }
            }
        }

}
void Tiles:: recursion(int a, int j,sf::RenderWindow &window ,vector<vector<Tiles>>& boardvec){
    bool recursionfuncbool = boardvec[a][j].stoprevealing;
    if(recursionfuncbool==false) {
        return;
    }
    else {
        for (int i = 0; i <boardvec[a][j].tileNeighbor.size(); i++) { // i <tileneighbor.size()
            if (boardvec[a][j].tileNeighbor[i] != nullptr && boardvec[a][j].tileNeighbor[i]->revealed == false && boardvec[a][j].tileNeighbor[i]->item==false) {
                if(i > 7){
                    return;
                }
                cout <<" IN RECURSIOM " << i <<endl;
                cout << a<< "= a  " << j << "= j" <<endl;

                int x = boardvec[a][j].tileNeighbor[i]->xcor;
                int y = boardvec[a][j].tileNeighbor[i]->ycor;

                cout << x/32 << "   " << y/32 << " x-y " <<endl;

                itemSprite.setPosition(x/32,y);
                window.draw(itemSprite);

                //call function to draw
                //recursion(a,j,window, boardvec);
            }
        }
    }
    tileNeighbor.clear();
}
void Tiles::debugbuttonPressed(vector<vector<Tiles>>& tiles,sf::RenderWindow &window) {
    revealallmines(tiles,window);
}
void Tiles::resetInTiles(vector<vector<Tiles>>& tiles,sf::RenderWindow &window) {
    this->reset2=true;
    //sf::Texture backGroundTile;
    //backGroundTile.loadFromFile("images/tile_revealed.png");
    //sf::Sprite backGroundTileSprite(backGroundTile);
    sf::Texture coverTile;
    coverTile.loadFromFile("images/tile_hidden.png");
    sf::Sprite CoverTileSprite(coverTile);
    //for (int i = 0; i < (height - 88) / 32; i++) {
    //for (int j = 0; j < width / 32; j++) {
    for (int i = 0; i < tiles.size(); i++) {
        for (int j = 0; j < tiles[i].size(); j++) {
            tiles[i][j].mine=false;
            tiles[i][j].flag=false;
            //tiles[i][j].revealed=false;

            //backGroundTileSprite.setPosition(j * 32, i * 32);
            //window.draw(backGroundTileSprite);
            CoverTileSprite.setPosition(j * 32, i * 32);
            window.draw(CoverTileSprite);
            //boardvec[i][j].setItem(images, boardvec, window);
            //boardvec[i][j].renderTile(window, i, j, boardvec, images);
        }
    }
    this->reset2=true;
}
bool Tiles::checkwin(vector<vector<Tiles>>& boardvec) {
    int overalltileNum;
    for(int i=0;i<boardvec.size();i++){
        for(int j=0; j<boardvec[i].size();j++){
            overalltileNum++;
        }
    }

    if(numbertoberevealed==0){
        return false;
    }
    if(overalltileNum-(numberrevealed+minecount) ==0){
        return true;
    }
    return false;
}
void Tiles::getXY() {
    //return xcor,ycor;
}
