#ifndef CONFIG_H
#define CONFIG_H

class Config {

    public: 
        static constexpr float CELL_SIZE = 20.0f;

        static constexpr float WIDTH = 1000;
        static constexpr int HEIGHT = 1000;

        static constexpr float GRAVITY = 9.81f;
        static constexpr float TIME_STEP = 0.1f; 

};


#endif // CONFIG_H