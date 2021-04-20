//
// Created by Alyssa Foglia on 4/14/21.
//

#include "Board.h"

void Board::savePosition(sf::Event event){
     this->pos= Vector2i(event.mouseButton.x, event.mouseButton.y);
     this->xEvent = event.mouseButton.x/32;
     this->yEvent = event.mouseButton.y/32;
}

void Board::updateBoard(sf::Event event, Board& boardobj, sf::RenderWindow& window) {
    
    Tiles chosen1;
    window.draw(debugSprite);
    window.draw(test1Sprite);
    window.draw(test2Sprite);
    window.draw(test3Sprite);
    window.draw(SmileySprite);
    drawNumbers(flagCount, overallMineCount, window, images);

    sf::Texture backGroundTile;
    backGroundTile.loadFromFile("images/tile_revealed.png");
    sf::Sprite backGroundTileSprite(backGroundTile);
    sf::Texture coverTile;
    coverTile.loadFromFile("images/tile_hidden.png");
    sf::Sprite CoverTileSprite(coverTile);

    //for (int i = 0; i < (height - 88) / 32; i++) {
    //for (int j = 0; j < width / 32; j++) {
        for (int i = 0; i < boardvec.size(); i++) {
            for (int j = 0; j < boardvec[i].size(); j++) {

                backGroundTileSprite.setPosition(j * 32, i * 32);
                window.draw(backGroundTileSprite);
                CoverTileSprite.setPosition(j * 32, i * 32);
                window.draw(CoverTileSprite);
                
                boardvec[i][j].setItem(images, boardvec, window);
                boardvec[i][j].renderTile(window, i, j, boardvec, images);

                if (boardvec[i][j].endgameintiles == true) {
                    endgame(window);
                }

                if(boardvec[i][j].checkwin(boardvec)==true){
                    win(window);
                }

            }
        }

    //sf::FloatRect resetButton = SmileySprite.getGlobalBounds();
    //if(resetButton.contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y))){

    if(event.mouseButton.x>(width / 2) -16 &&  event.mouseButton.x<(width / 2) + 16 && event.mouseButton.y> height-88 && event.mouseButton.button == sf::Mouse::Left) {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
            resetbool = true;
            while(resetbool==true) {
                cout << "smiley" << endl;
                boardobj.reset(boardobj, window);
                cout << "RESEt in function" << endl;
            }
        }
    }

    sf::FloatRect test2button = test2Sprite.getGlobalBounds();
    if(test2button.contains(sf::Vector2f(event.mouseButton.x,event.mouseButton.y))){
        t12.clear();
            ifstream input("boards/testboard2.brd");
            while (!input.eof()) {
                vector<int> newvec;
                newvec.clear();
                string firstValueString;
                getline(input, firstValueString);
                for (unsigned int i = 0; i < firstValueString.length() + 1; i++) {
                    newvec.push_back((int) firstValueString[i] - 48);
                }
                t12.push_back(newvec);
            }
            input.close();
            overallMineCount = 0;
            for (unsigned int i = 0; i < boardvec.size(); i++) {
                for (int j = 0; j < boardvec[i].size(); j++) {
                    //boardvec[i][j].setItem(images, boardvec, window);
                    if (t12[i][j] == 0 && boardvec[i][j].item == true) {
                        boardvec[i][j].mine = false;
                        //boardvec[i][j].setItem(images, boardvec, window);
                        itemSprite.setTexture(images["tile_hidden.png"]);
                        itemSprite.setPosition(j * 32, i * 32);
                        //window.draw(itemSprite);
                    } else if (t12[i][j] == 1) {
                        boardvec[i][j].mine = true;
                        sf::Texture mine;
                        mine.loadFromFile("images/mine.png");
                        sf::Sprite mineSprite(mine);
                        mineSprite.setPosition(j * 32, i * 32);
                       // window.draw(mineSprite);
                        if (t12[i][j] == 1) {
                            overallMineCount++;
                        }

                    }
                }
            }

    }

    sf::FloatRect test1button = test1Sprite.getGlobalBounds();
    if (test1button.contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y))) {
        fortest2.clear();
        ifstream input2("boards/testboard1.brd");
        while (!input2.eof()) {
            vector<int> newvec2;
            string firstValueString2;
            getline(input2, firstValueString2);
            for (unsigned int i = 0; i < firstValueString2.length(); i++) {
                newvec2.push_back((int) firstValueString2[i] - 48);
            }
            fortest2.push_back(newvec2);
        }
        input2.close();
        overallMineCount=0;
        for (unsigned int i = 0; i < boardvec.size(); i++) {
            for (int j = 0; j < boardvec[i].size(); j++) {
                if (fortest2[i][j] == 1) {
                    boardvec[i][j].mine = true;
                    this->overallMineCount+=1;
                    sf::Texture mine;
                    mine.loadFromFile("images/mine.png");
                    sf::Sprite mineSprite(mine);
                    mineSprite.setPosition(j * 32, i * 32);
                    //window.draw(mineSprite);
                }
                if (fortest2[i][j] == 0) {
                    boardvec[i][j].mine = false;
                    itemSprite.setTexture(images["tile_hidden.png"]);
                    itemSprite.setPosition(j*32,i*32);
                    //window.draw(itemSprite);
                }
            }
        }
    }

    sf::FloatRect test3button = test3Sprite.getGlobalBounds();
    if (test3button.contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y))) {
        ifstream input3("boards/testboard3.brd");
        while (!input3.eof()) {
            vector<int> newvec3;
            string firstValueString3;
            getline(input3, firstValueString3);
            for (unsigned int i = 0; i < firstValueString3.length(); i++) {
                newvec3.push_back((int) firstValueString3[i] - 48);
            }
            fortest3.push_back(newvec3);
        }
        input3.close();
        overallMineCount=0;
        for (unsigned int i = 0; i < boardvec.size(); i++) {
            for (int j = 0; j < boardvec[i].size(); j++) {
                if (fortest3[i][j] == 1) {
                    boardvec[i][j].mine = true;
                    overallMineCount+=1;
                    sf::Texture mine;
                    mine.loadFromFile("images/mine.png");
                    sf::Sprite mineSprite(mine);
                    mineSprite.setPosition(j * 32, i * 32);
                    //window.draw(mineSprite);
                }
                if (fortest3[i][j] == 0) {
                    boardvec[i][j].mine = false;
                    itemSprite.setTexture(images["tile_hidden.png"]);
                    itemSprite.setPosition(j*32,i*32);
                    //window.draw(itemSprite);
                }
            }
        }
    }

    sf::FloatRect debugButton = debugSprite.getGlobalBounds();
    if (debugButton.contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y))){
       if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
           Tiles chosen;
           //chosen.debugbuttonPressed(boardvec, window);
           debugbool=true;
           while (debugbool == true) {
               for (unsigned int i = 0; i < boardvec.size(); i++) {
                   for (int j = 0; j < boardvec[i].size(); j++) {
                       if (boardvec[i][j].mine == true) {
                           boardvec[i][j].revealallmines(boardvec, window);
                       }
                   }
               }
                debugbool=false;
           }
       }

    }

    //drawNumbers(flagCount, overallMineCount, window, images);


    }


void Board::loadWindow(string filename) {
    ifstream input(filename);
    //loadWindowSetup(input);
    int firstValueInt;
    int secondValueInt;
    int thirdValueInt;
    while(!input.eof()) {
        string firstValueString;
        getline(input, firstValueString);
        firstValueInt = stoi(firstValueString);
        string secondValueString;
        getline(input, secondValueString);
        secondValueInt = stoi(secondValueString);
        string thirdValueString;
        getline(input, thirdValueString);
        thirdValueInt = stoi(thirdValueString);
    }

    int width = firstValueInt*32;
    int height = (secondValueInt*32)+88;
    int mineCount = thirdValueInt;
    int tileCount= firstValueInt*secondValueInt;

    this->width=width;
    this->height=height;
    this->mineCount=mineCount;
    this-> tileCount=tileCount;
    this->overallMineCount=mineCount;


}
void Board::initializeBoard(sf::RenderWindow& window, Board boardobj) {
    LoadAllTextures();

    for (int i = 0; i < (height - 88) / 32; i++) {
        std::vector<Tiles> board2;
        for (int j = 0; j < width / 32; j++) {
            Tiles tile2;
            tile2.Tile(images, false, (j * width)/32, (i * height)/32);
            board2.push_back(tile2);
        }
        boardvec.push_back(board2);
    }

    //mineCount = 0;
    mineClicked = false;
    debugmode = false;
    numFlags = 0;
    revealedTiles = 0;
    randomizeMines(boardvec,boardobj);
    setNeighbors();

    

}

void Board::LoadAllTextures() {
    images["debug"].loadFromFile("images/debug.png");
    images["digits"].loadFromFile("images/digits.png");
    images["face_happy"].loadFromFile("images/face_happy.png");
    images["face_lose"].loadFromFile("images/face_lose.png");
    images["face_win"].loadFromFile("images/face_win.png");
    images["flag"].loadFromFile("images/flag.png");
    images["mine"].loadFromFile("images/mine.png");
    images["number_1"].loadFromFile("images/number_1.png");
    images["number_2"].loadFromFile("images/number_2.png");
    images["number_3"].loadFromFile("images/number_3.png");
    images["number_4"].loadFromFile("images/number_4.png");
    images["number_5"].loadFromFile("images/number_5.png");
    images["number_6"].loadFromFile("images/number_6.png");
    images["number_7"].loadFromFile("images/number_7.png");
    images["number_8"].loadFromFile("images/number_8.png");
    images["test_1"].loadFromFile("images/test_1.png");
    images["test_2"].loadFromFile("images/test_2.png");
    images["test_3"].loadFromFile("images/test_3.png");
    images["tile_hidden.png"].loadFromFile("images/tile_hidden.png");
    images["tile_revealed.png"].loadFromFile("images/tile_revealed.png");
    images["digits0"].loadFromFile("images/digits.png",sf::IntRect(0,0,21,32));
    images["digits1"].loadFromFile("images/digits.png",sf::IntRect(21,0,21,32));
    images["digits2"].loadFromFile("images/digits.png",sf::IntRect(42,0,21,32));
    images["digits3"].loadFromFile("images/digits.png",sf::IntRect(63,0,21,32));
    images["digits4"].loadFromFile("images/digits.png",sf::IntRect(84,0,21,32));
    images["digits5"].loadFromFile("images/digits.png",sf::IntRect(105,0,21,32));
    images["digits6"].loadFromFile("images/digits.png",sf::IntRect(126,0,21,32));
    images["digits7"].loadFromFile("images/digits.png",sf::IntRect(147,0,21,32));
    images["digits8"].loadFromFile("images/digits.png",sf::IntRect(168,0,21,32));
    images["digits9"].loadFromFile("images/digits.png",sf::IntRect(189,0,21,32));
    images["digits-"].loadFromFile("images/digits.png",sf::IntRect(210,0,21,32));


    debugSprite.setPosition((width / 2) + 112, height - 88);
    debugSprite.setTexture(images["debug"]);


    test1Sprite.setPosition((width / 2) + 176, height - 88);
    test1Sprite.setTexture(images["test_1"]);

    test2Sprite.setTexture(images["test_2"]);
    test2Sprite.setPosition((width / 2) + 240, height - 88);

    test3Sprite.setTexture(images["test_3"]);
    test3Sprite.setPosition((width / 2) + 304, height - 88);

    SmileySprite.setTexture(images["face_happy"]);
    SmileySprite.setPosition((width / 2) - 16, height - 88);

    sadSprite.setTexture(images["face_lose"]);
    sadSprite.setPosition((width / 2) - 16, height - 88);

    winningFace.setTexture(images["face_win"]);
    winningFace.setPosition((width / 2) - 16, height - 88);

    digits.setTexture(images["digits"]);
    digits.setPosition(32, height - 88);

}

void Board::drawDigits(int a, sf::RenderWindow& window){
    if (a >= 0) {
        int hundDigit = (a / 10) / 10;
        int tensDigit = (a / 10 )% 10;
        int onesDigit = a % 10;

        digits.setPosition(sf::Vector2f(0, 16*height));
        digits.setTextureRect(sf::IntRect(21*hundDigit, 0, 21, 32));
        window.draw(digits);
        digits.setPosition(sf::Vector2f(21, 16 * height));
        digits.setTextureRect(sf::IntRect(21 * tensDigit, 0, 21, 32));
        window.draw(digits);
        digits.setPosition(sf::Vector2f(42, 16 * height));
        digits.setTextureRect(sf::IntRect(21 * onesDigit, 0, 21, 32));
        window.draw(digits);
    }
    else if (a < 0) {
        int hundDigit = (-a / 10) / 10;
        int tensDigit = (-a / 10) % 10;
        int onesDigit = -a % 10;
        digits.setPosition(sf::Vector2f(0, 16 * height));
        digits.setTextureRect(sf::IntRect(21 * 10 ,0, 21, 32));
        window.draw(digits);
        digits.setPosition(sf::Vector2f(21, 16 * height));
        digits.setTextureRect(sf::IntRect(21 * hundDigit, 0, 21, 32));
        window.draw(digits);
        digits.setPosition(sf::Vector2f(42, 16 * height));
        digits.setTextureRect(sf::IntRect(21 * tensDigit, 0, 21, 32));
        window.draw(digits);
        digits.setPosition(sf::Vector2f(63, 16 * height));
        digits.setTextureRect(sf::IntRect(21 * onesDigit, 0, 21, 32));
        window.draw(digits);
    }
}
void Board::loadDigits(sf::RenderWindow& window){
    drawDigits(overallMineCount-flagCount, window);
}

void Board::randomizeMines(vector<vector<Tiles>>& tiles, Board boardobj){
    cout<< "mine count " << this->mineCount<<endl;

    for(int a=0; a< this->mineCount ; a++) {

        // srand((unsigned) time(0));
        int i = (rand() % (boardobj.width / 32)) + 0;
        //srand((unsigned) time(0));
        int j=(rand() % ((boardobj.height -88) /32)) + 0;

        cout << "bomb at " << a << ":" << j <<" " << i <<endl;

        tiles[j][i].mine = true;
    }

}

void Board:: getNumber(string number, vector<string> &numdraw){
    for(unsigned int i=0; i<number.size();i++){
        switch(number.at(i)) {
            case '0':
                numdraw.push_back("digits0");
                break;
            case '1':
                numdraw.push_back("digits1");
                break;
            case '2':
                numdraw.push_back("digits2");
                break;
            case '3':
                numdraw.push_back("digits3");
                break;
            case '4':
                numdraw.push_back("digits4");
                break;
            case '5':
                numdraw.push_back("digits5");
                break;
            case '6':
                numdraw.push_back("digits6");
                break;
            case '7':
                numdraw.push_back("digits7");
                break;
            case '8':
                numdraw.push_back("digits8");
                break;
            case '9':
                numdraw.push_back("digits9");
                break;
            //case '-':
             //   numdraw.push_back("digits-");
             //   break;
        }
    }
}

void Board::drawNumbers(int flagCount, int overallMineCount, sf::RenderWindow &window, map<string, sf::Texture> &images) {

    string drawCount= to_string(overallMineCount-flagCount);
    // y cor x cor?
    int xcor =0;
    int ycor=512;
    vector<string> numDraw;
    if((overallMineCount-flagCount)>=0){
        switch(drawCount.size()){
            case 1:
                numDraw.push_back("digits0");
                numDraw.push_back("digits0");
                getNumber(drawCount, numDraw);
                break;
            case 2:
                numDraw.push_back("digits0");
                getNumber(drawCount, numDraw);
                break;
            case 3:
                getNumber(drawCount, numDraw);
                break;
        }
    }
    if((overallMineCount-flagCount)<0){
        switch(drawCount.size()){
            case 1:
                numDraw.push_back("digits-");
                numDraw.push_back("digits0");
                numDraw.push_back("digits0");
                getNumber(drawCount, numDraw);
                break;
            case 2:
                numDraw.push_back("digits-");
                numDraw.push_back("digits0");
                getNumber(drawCount, numDraw);
                break;
            case 3:
                numDraw.push_back("digits-");
                getNumber(drawCount, numDraw);
                break;

        }
    }

    for (unsigned int i = 0; i < numDraw.size(); i++){
        sf::Sprite number (images.find(numDraw.at(i))->second);
        number.setPosition(xcor,ycor);
        xcor+=21; //pdf each digit 21x32 pixels
        window.draw(number);
    }

}

void Board::setNeighbors() {
    for(int r=0; r<boardvec.size();r++){
        for(int c=0; c<boardvec[r].size();c++){
            if(r!=0 && c!=0){
                boardvec[r][c].tileNeighbor[0] = &boardvec[r-1][c-1];
            }
            if(r!=0){
                boardvec[r][c].tileNeighbor[1] = &boardvec[r-1][c];
            }
            if(r!=0 && c!=boardvec[r].size()){
                boardvec[r][c].tileNeighbor[2]=&boardvec[r-1][c+1];
            }
            if(c!=0){
                boardvec[r][c].tileNeighbor[3]=&boardvec[r][c-1];
            }
            if(c!=boardvec[r].size()){
                boardvec[r][c].tileNeighbor[4]=&boardvec[r][c+1];
            }
            if(r!=boardvec.size() && c!=0){
                boardvec[r][c].tileNeighbor[5]=&boardvec[r+1][c-1];
            }
            if(r!=boardvec.size()){
                boardvec[r][c].tileNeighbor[6]=&boardvec[r+1][c];
            }
            if(r!=boardvec.size() && c!=boardvec[r].size()){
                boardvec[r][c].tileNeighbor[7]=&boardvec[r+1][c+1];
            }

            if(r == boardvec.size() -1 ){
                boardvec[r][c].tileNeighbor[5]=NULL;
                boardvec[r][c].tileNeighbor[6]=NULL;
                boardvec[r][c].tileNeighbor[7]=NULL;
            }
            if(r == 0 ){
                boardvec[r][c].tileNeighbor[0]=NULL;
                boardvec[r][c].tileNeighbor[1]=NULL;
                boardvec[r][c].tileNeighbor[2]=NULL;
            }
        }
    }

}
/*
Tile* tileNeighbor[7]
0:r-1,c-1
1: r-1
2:r-1, c+1
3:    c-1
4:     c+1
5: r+1, c-1
6: r+1
7: r+1, c+1

            c-1     c       c+1
       r-1    0  |   1    |   2
       ---------------------------
       r      3  |   *    |   4
       ---------------------------
       r+1    5  |   6    |   7


 */
void Board::endgame(sf::RenderWindow &window) {
    window.draw(sadSprite);
}
void Board::reset(Board boardobj, sf::RenderWindow &window) {
    Tiles chosen;
    //chosen.resetInTiles(boardvec,window);

    sf::Texture coverTile;
    coverTile.loadFromFile("images/tile_hidden.png");
    sf::Sprite CoverTileSprite(coverTile);
    sf::Texture backGroundTile;
    backGroundTile.loadFromFile("images/tile_revealed.png");
    sf::Sprite backGroundTileSprite(backGroundTile);

    boardvec.clear();
    for (int i = 0; i < (height - 88) / 32; i++) {
    for (int j = 0; j < width / 32; j++) {
            boardvec[i][j].mine=false;
            boardvec[i][j].flag=false;
            boardvec[i][j].revealed=false;
            boardvec[i][j].tileNeighbor.clear();
            backGroundTileSprite.setPosition(j * 32, i * 32);
            window.draw(backGroundTileSprite);
            CoverTileSprite.setPosition(j * 32, i * 32);
            window.draw(CoverTileSprite);
            //boardvec[i][j].setItem(images, boardvec, window);
            //boardvec[i][j].renderTile(window, i, j, boardvec, images);
        }
    }
    cout << "RESET" <<endl;
    mineClicked = false;
    debugmode = false;
    numFlags = 0;
    revealedTiles = 0;
    randomizeMines(boardvec,boardobj);
    setNeighbors();
    overallMineCount=mineCount;
    drawNumbers(flagCount,overallMineCount,window,images);
    window.draw(SmileySprite);

    resetbool = false;
}
void Board:: win(sf::RenderWindow & window){
    window.draw(winningFace);
}









