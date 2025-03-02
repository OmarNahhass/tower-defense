#include "game.h"
#include "Map.h"
#include "Critter.h"
#include "Tower.h"
#include "CritterGroupGenerator.h"
#include "SpecialTowers.h"
#include "CritterView.h"


#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>


// images for grass, path, towers, and critters
sf::Texture grassTextureGame, pathTextureGame, damageTowerTextureGame, critterTexture;

std::vector<Critter> critters;  // List of critters
std::vector<Tower> towers;      // List of towers

std::vector<sf::Vector2i> directDamageTowerPositions;


std::vector<Critter> activeCritters; 
int currentWave = 1;
bool waitingForNextWave = false;    // Indicates if we are waiting to start a new wave
float waveDelayTimer = 0.0f;        // Timer for delay between waves

std::vector<Critter> spawnQueue;  // Queue of critters waiting to be spawned
float critterSpawnTimer = 0.0f;   // Timer to control spawning intervals
int crittersSpawned = 0;          // Track number of critters spawned in current wave

int cellSize = WINDOWSIZE / ROWS;

int numberOfCrittersPerWave = 10;
int numberOfCrittersRemaining = numberOfCrittersPerWave;

void spawnCritter() {
    critters.emplace_back(currentWave, critterTexture); // Construct directly in place
    std::cerr << "Spawned a critter! Current size: " << critters.size() << std::endl;
}

void storeTowerPositions() {
    directDamageTowerPositions.clear(); // Reset before scanning

    for (int j = 0; j < COLS; j++) {  // 
        for (int i = 0; i < ROWS; i++) {  
            if (grid[i][j] == 2) { // 
                directDamageTowerPositions.emplace_back(j, i); // Store cell coordinates correctly
            }
        }
    }
}


// spawn towners at their corresponding location on the map
void spawnTowers() {
    towers.clear(); // Clear old towers before spawning new ones

    for (const auto& pos : directDamageTowerPositions) {
        towers.emplace_back(DirectDamageTower(pos.x, pos.y, damageTowerTextureGame));
    }
}


// Draw towers
void drawTowers(sf::RenderWindow& window) {
    for (const auto& tower : towers) {
        sf::Sprite towerSprite = tower.sprite;
        towerSprite.setPosition(tower.position.x * cellSize, tower.position.y * cellSize);

        towerSprite.setScale(
            static_cast<float>(cellSize) / towerSprite.getTexture()->getSize().x,
            static_cast<float>(cellSize) / towerSprite.getTexture()->getSize().y
        );
        window.draw(towerSprite);
    }
}

// Update towers to shoot at critters
void updateTowers(float currentTime) {
    for (auto& tower : towers) {
        tower.shoot(activeCritters, currentTime);
    }
}

// Update critters movement and remove dead ones
void updateCritters(float deltaTime, float currentTime) {
    for (auto critter = activeCritters.begin(); critter != activeCritters.end();) {
        critter->move(deltaTime);
      
        if (critter->takeDamage(0, currentTime)) { // Remove if dead
            critter = activeCritters.erase(critter);
        }
        else {
            ++critter;
        }
    }
}


void startWave(CritterView& critterView) {
    std::cerr << "Starting wave " << currentWave << std::endl;

    activeCritters.clear();   // Clear old critters
    spawnQueue.clear();       // Reset spawn queue

    // Generate 10 critters and store them in the spawn queue
    spawnQueue = CritterGroupGenerator::generateWaveCritters(currentWave, critterTexture, critterView);

    crittersSpawned = 0;       // Reset spawn count
    critterSpawnTimer = 0.0f;  // Reset spawn timer
    waitingForNextWave = false;
}



void updateWave(float deltaTime, float currentTime, CritterView& critterView) {
    // Check if the wave is completed
    if (spawnQueue.empty() && activeCritters.empty() && !waitingForNextWave) {
        std::cerr << "Wave " << currentWave << " cleared! Starting countdown for next wave...\n";
        waitingForNextWave = true;
        waveDelayTimer = 0.0f;
    }

    // Wait for 10 seconds before starting the next wave
    if (waitingForNextWave) {
        waveDelayTimer += deltaTime;
        int timeRemaining = 10 - static_cast<int>(waveDelayTimer); // Convert to integer seconds

        std::cerr << "Wave ended. Next wave in " << timeRemaining << " seconds." << std::endl;


        // start next wave
        if (waveDelayTimer >= 10.0f) {  // 10-second delay
            currentWave++;
            startWave(critterView);
        }
    }


    // Spawn critters every 5 seconds
    critterSpawnTimer += deltaTime;
    if (!spawnQueue.empty() && critterSpawnTimer >= 5.0f) {
        activeCritters.push_back(spawnQueue.front());  // Add one critter to activeCritters list
        spawnQueue.erase(spawnQueue.begin());         // Remove it from the queue
        critterSpawnTimer = 0.0f;  // Reset timer
    }
}



// Main Game Loop
void displayGame(sf::RenderWindow& window) {

    CritterView critterView(window);

    // load font
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        std::cerr << "Failed to load font!" << std::endl;
        return;
    }



    // Load textures and initialize the first wave
    if (!damageTowerTextureGame.loadFromFile("tower.png") ||
        !grassTextureGame.loadFromFile("grass_3.png") ||
        !pathTextureGame.loadFromFile("path.png") ||
        !critterTexture.loadFromFile("critter.jpg")) {

        std::cerr << "Failed to load texture!" << std::endl;
        return; // Stop execution if textures fail to load
    }
    


    int mapWidth = (WINDOWSIZE * 2) / 3;
    int infoPanelWidth = WINDOWSIZE / 3;


    // display an info panel on the right
    // the info panel contains several info (number of towers, money, etc.)
    sf::RectangleShape infoPanel(sf::Vector2f(infoPanelWidth, WINDOWSIZE));
    infoPanel.setFillColor(sf::Color(255, 255, 255));
    infoPanel.setPosition(WINDOWSIZE, 0);



    storeTowerPositions(); // Get tower positions 
    spawnTowers();         // Now spawn towers
    startWave(critterView);           // Start first wave


    /*
    Info panel    
    */
    // critter counter
    sf::Text critterCountText("Critters Remaining: " + numberOfCrittersRemaining, font, 15);
    critterCountText.setFillColor(sf::Color::Black);
    critterCountText.setPosition(WINDOWSIZE + 15, 30);


    // display the player coins
    sf::Text playerCoinsText("Coins: " + playerCoins, font, 15);
    playerCoinsText.setFillColor(sf::Color::Black);
    playerCoinsText.setPosition(WINDOWSIZE + 15, 70);



    sf::Clock clock, gameClock;

    while (window.isOpen()) {
        sf::Event event;
        


        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            else if (event.type == sf::Event::Resized) {
                // Adjust the viewport when the window is resized
                sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
                window.setView(sf::View(visibleArea));
                cellSize = (event.size.width * 2 / 3) / ROWS;
           

                // Resize and reposition info panel
                mapWidth = (event.size.width * 2) / 3;
                int infoPanelWidth = (event.size.width) / 3;

                infoPanel.setSize(sf::Vector2f(infoPanelWidth, (cellSize * ROWS)));
                infoPanel.setPosition(mapWidth, 0);

                // Update all critters' positions based on new cellSize
                for (auto& critter : activeCritters) {
                    critter.sprite.setPosition(
                        pathCells[critter.pathIndex].x * cellSize,
                        pathCells[critter.pathIndex].y * cellSize
                    );
                }
            }         
        }



        float deltaTime = clock.restart().asSeconds();
        float currentTime = gameClock.getElapsedTime().asSeconds();
        critterView.currentTime = currentTime;

        // Clear screen at the beginning of the loop
        window.clear(sf::Color::Black);

        // Draw the grid
        for (int i = 0; i < ROWS; i++) {
            for (int j = 0; j < COLS; j++) {
                sf::Sprite sprite;

              
                sprite.setPosition(j * cellSize, i * cellSize);

                if (grid[i][j] == 0) {
                    sprite.setTexture(grassTextureGame);
                }
                else if (grid[i][j] == 1) {
                    sprite.setTexture(pathTextureGame);
                }

                if (sprite.getTexture() != nullptr) {
                    sprite.setScale(
                        static_cast<float>(cellSize) / sprite.getTexture()->getSize().x,
                        static_cast<float>(cellSize) / sprite.getTexture()->getSize().y
                    );
                }

                window.draw(sprite);
            }
        }

        // display information about the wave
        sf::Text waveMessage;
        waveMessage.setFont(font);
        waveMessage.setCharacterSize(24);
        waveMessage.setFillColor(sf::Color::White);
        waveMessage.setPosition(20, 20); // Adjust position on screen

        if (waitingForNextWave) {
            int timeRemaining = 10 - static_cast<int>(waveDelayTimer);
            waveMessage.setString("Wave ended. Next wave in " + std::to_string(timeRemaining) + " seconds");
            window.draw(waveMessage);
        }

        window.draw(infoPanel);

        // Update game logic
        updateWave(deltaTime, currentTime, critterView);
        updateCritters(deltaTime, currentTime);
        updateTowers(currentTime);

        // Draw game objects
        drawTowers(window);

        // display the critter counter 
        critterCountText.setString("Critters Remaining: " + std::to_string(numberOfCrittersRemaining));
        window.draw(critterCountText);

        // display player coins text
        playerCoinsText.setString("Coins: " + std::to_string(playerCoins));
        window.draw(playerCoinsText);

        window.display(); 
    }
}



