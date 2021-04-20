#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;
#include <fstream>
using namespace sf;
#include "Tiles.h"
#include "Board.h"
#pragma once



int main() {
    //Tiles board;
    Board boardobj;
    boardobj.loadWindow("boards/config.cfg");
    sf::RenderWindow window(sf::VideoMode(boardobj.width, boardobj.height), "Minesweeper!");

    boardobj.initializeBoard(window, boardobj);

    while (window.isOpen()) {
        sf::Event event;
        Tiles chosen1;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Right) {
                    cout << "Right mouse clicked" << endl;
                    cout << "mouse x: " << event.mouseButton.x << endl;
                    cout << "mouse y: " << event.mouseButton.y << endl;
                    chosen1.tileClicked(boardobj.boardvec, event.mouseButton.x, event.mouseButton.y); //new
                    cout << "end of right mouse click" << endl;
                    if(boardobj.boardvec[event.mouseButton.y/32][event.mouseButton.x/32].flag) {
                        boardobj.flagCount++;
                    }
                    else{
                        boardobj.flagCount--;
                    }


                }
                if (event.mouseButton.button == sf::Mouse::Left) {
                    cout << "Left mouse clicked" << endl;
                    cout << "mouse x: " << event.mouseButton.x << endl;
                    cout << "mouse y: " << event.mouseButton.y << endl;
                    chosen1.revealClicked(boardobj.boardvec, event.mouseButton.x, event.mouseButton.y);

                }
            }
            //boardobj.savePosition(event);
       }

        //event then clear draw display
        window.clear(sf::Color::Black);
        boardobj.updateBoard(event,boardobj,window);
        window.display(); // comment this line to see the flag..
    }

    return 0;
}
