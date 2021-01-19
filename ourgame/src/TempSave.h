//
// Created by Gebruiker on 19/01/2021.
//

#ifndef GBA_SPRITE_ENGINE_PROJECT_TEMPSAVE_H
#define GBA_SPRITE_ENGINE_PROJECT_TEMPSAVE_H


class TempSave {
private:
    int skin;
    int coins_temple = 0;
    int coins_islands = 0;
public:
    void setSkin(int i){this->skin = i;}
    int getSkin(){return this->skin;}
    void setCoinsTemple(int i){this->coins_temple = i;}
    void setCoinsIslands(int i){this->coins_islands = i;}
    int getCoins(){return (this->coins_islands + this->coins_temple);}
    void resetCoins(){this->coins_temple = 0; this->coins_islands = 0;}
};


#endif //GBA_SPRITE_ENGINE_PROJECT_TEMPSAVE_H
