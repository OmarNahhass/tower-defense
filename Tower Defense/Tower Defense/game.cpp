#include "game.h"
#include "Map.h"
#include "MapView.h"
#include "Menu.h"
#include "Critter.h"
#include "Tower.h"
#include "CritterGroupGenerator.h"
#include "SpecialTowers.h"
#include "CritterView.h"


#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>


// images for grass, path, towers, and critters
sf::Texture grassTextureGame, pathTextureGame, damageTowerTextureGame, slowDownTowerTextureGame, sniperTowerTextureGame, critterTexture;

std::vector<Critter> critters;  // List of critters
std::vector<std::unique_ptr<Tower>> towers; // List of towers

std::vector<sf::Vector2i> directDamageTowerPositions, slowDownTowerPositions, sniperTowerPositiions;


std::vector<Critter> activeCritters; 
int currentWave = 0;
bool waitingForNextWave = false;    // Indicates if we are waiting to start a new wave
float waveDelayTimer = 0.0f;        // Timer for delay between waves

std::vector<Critter> spawnQueue;  // Queue of critters waiting to be spawned
float critterSpawnTimer = 0.0f;   // Timer to control spawning intervals
int crittersSpawned = 0;          // Track number of critters spawned in current wave

int numberOfCrittersPerWave = 5;
int numberOfCrittersRemaining = numberOfCrittersPerWave;


GameState currentState = GameState::InGame;




void spawnCritter() {
    critters.emplace_back(currentWave, critterTexture); // Construct directly in place
    std::cerr << "Spawned a critter! Current size: " << critters.size() << std::endl;
}

void storeTowerPositions() {
    directDamageTowerPositions.clear(); // Reset before scanning
    slowDownTowerPositions.clear(); // Reset before scanning
    sniperTowerPositiions.clear(); // Reset before scanning

    for (int i = 0; i < numberOfColumns; i++) {  
        for (int j = 0; j < numberOfRows; j++) {  

            // Store cell coordinates correctly
            if (mapGrid[j][i] == 2) { 
                directDamageTowerPositions.emplace_back(i, j);
            }else if (mapGrid[j][i] == 3) {
                slowDownTowerPositions.emplace_back(i, j); 
            }
            else if (mapGrid[j][i] == 4) {
                sniperTowerPositiions.emplace_back(i, j); 
            }
        }
    }
}


// spawn towners at their corresponding location on the map
void spawnTowers() {
    towers.clear();

    for (const auto& pos : directDamageTowerPositions) {
        towers.emplace_back(std::make_unique<DirectDamageTower>(pos.x, pos.y, damageTowerTextureGame));

    }
    for (const auto& pos : slowDownTowerPositions) {
        towers.emplace_back(std::make_unique<SlowingTower>(pos.x, pos.y, slowDownTowerTextureGame));

    }
    for (const auto& pos : sniperTowerPositiions) {
        towers.emplace_back(std::make_unique<SniperTower>(pos.x, pos.y, sniperTowerTextureGame));
    }
}


// Draw towers
void drawTowers(sf::RenderWindow& window) {
    for (const auto& tower : towers) { 
        sf::Sprite towerSprite = tower->sprite; 
        towerSprite.setPosition(tower->position.x * cellSize, tower->position.y * cellSize);

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
        tower->shoot(activeCritters, currentTime);
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

    currentState = GameState::InGame;
}



void updateWave(float deltaTime, float currentTime, CritterView& critterView, sf::RenderWindow& window) {
    int timeRemaining = 0;

    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        std::cerr << "Failed to load font!" << std::endl;
        return;
    }

    sf::Text waveMessage;

    

    // check the states of the game
    switch (currentState) {

    // a new wave has started
    case GameState:: WaveStart:
        currentWave++;
        numberOfCrittersRemaining = numberOfCrittersPerWave;
        waveDelayTimer = 0.0f;  

        startWave(critterView);

        break;

    // after starting a new wave -> ongoing game
    case GameState::InGame:
        // Check if the wave is completed
        if (spawnQueue.empty() && activeCritters.empty() && !waitingForNextWave) {
            std::cerr << "Wave " << currentWave << " cleared! Starting countdown for next wave...\n";
            waveDelayTimer = 0.0f; 
            currentState = GameState::WaveEnd;
        }

        // Spawn critters every 5 seconds
        critterSpawnTimer += deltaTime;
        if (!spawnQueue.empty() && critterSpawnTimer >= 5.0f) {
            activeCritters.push_back(spawnQueue.front());  // Add one critter to activeCritters list
            spawnQueue.erase(spawnQueue.begin());         // Remove it from the queue
            critterSpawnTimer = 0.0f;  // Reset spawn timer after each critter spawn
        }

        break;
    
    // a wave has ended. Display message
    case GameState::WaveEnd:
        waveDelayTimer += deltaTime;
        timeRemaining = 5 - static_cast<int>(waveDelayTimer); // Convert to integer seconds

        waveMessage.setFont(font);
        waveMessage.setCharacterSize(12);
        waveMessage.setFillColor(sf::Color(0, 94, 17));
        waveMessage.setPosition(mapWidth + 10, 200); // Adjust position on screen

        //std::cerr << "Wave ended. Changing screen in " << timeRemaining << " seconds." << std::endl;
        waveMessage.setString("Wave ended. Changing screen in " + std::to_string(timeRemaining) + " seconds");
        window.draw(waveMessage);

        // Start next wave after 5-second delay
        if (waveDelayTimer >= 5.0f) {  
            currentState = GameState::MapCustomization;
        }
        break;

    // Allow the player to change the map and add towers
    case GameState::MapCustomization:

        // close game window and transition to map creation screen
        window.close();
        displayMap(windowWidth, windowHeight, numberOfRows, numberOfColumns);

        break;
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
        !slowDownTowerTextureGame.loadFromFile("towerSlowDown.png") ||
        !sniperTowerTextureGame.loadFromFile("towerSniper.png") ||
        !grassTextureGame.loadFromFile("grass_3.png") ||
        !pathTextureGame.loadFromFile("path.png") ||
        !critterTexture.loadFromFile("critter.jpg")) {

        std::cerr << "Failed to load texture!" << std::endl;
        return; // Stop execution if textures fail to load
    }
   


    // display an info panel on the right
    // the info panel contains several info (number of towers, money, etc.)
    sf::RectangleShape infoPanel(sf::Vector2f(infoPanelWidth, infoPanelHeight));
    infoPanel.setFillColor(sf::Color(211, 217, 227));
    infoPanel.setPosition(mapWidth, 0);



    storeTowerPositions(); // Get tower positions 
    spawnTowers();         // Now spawn towers


    /*
    Info panel    
    */
    // wave counter
    sf::Text waveCountText("WAVE #" + std::to_string(currentWave+1), font, 20);
    waveCountText.setStyle(sf::Text::Bold);
    waveCountText.setFillColor(sf::Color::Black);
    waveCountText.setPosition(mapWidth + 15, 20);


    // critter counter
    sf::Text critterCountText("Critters Remaining: " + numberOfCrittersRemaining, font, 15);
    critterCountText.setFillColor(sf::Color::Black);
    critterCountText.setPosition(mapWidth + 15, 100);


    // display the player coins
    sf::Text playerCoinsText("Coins: " + playerCoins, font, 15);
    playerCoinsText.setFillColor(sf::Color::Black);
    playerCoinsText.setPosition(mapWidth + 15, 140);



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

                maxMapWidth = (event.size.width * 3) / 4;
                maxMapHeight = (event.size.height * 9) / 10;


                cellSize = std::min(maxMapWidth / numberOfColumns, maxMapHeight / numberOfRows);

                mapHeight = (event.size.height * 9) / 10;
                mapWidth = cellSize * numberOfColumns;

                // resize and reposition the info panel
                infoPanelWidth = event.size.width - mapWidth;
                infoPanelHeight = mapHeight;
                infoPanel.setSize(sf::Vector2f(infoPanelWidth, infoPanelHeight));
                infoPanel.setPosition(mapWidth, 0);

                unsigned int newFontSize = static_cast<unsigned int>(event.size.height / 25);

                // Resize and reposition the texts in the Info Panel
                critterCountText.setPosition(mapWidth + 20, 30);
                playerCoinsText.setPosition(mapWidth + 20, 80);

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
        for (int i = 0; i < numberOfRows; i++) {
            for (int j = 0; j < numberOfColumns; j++) {
                sf::Sprite sprite;

              
                sprite.setPosition(j * cellSize, i * cellSize);

                if (mapGrid[i][j] == 0) {
                    sprite.setTexture(grassTextureGame);
                }
                else if (mapGrid[i][j] == 1) {
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



        window.draw(infoPanel);

        // Update game logic
        updateWave(deltaTime, currentTime, critterView, window);
        updateCritters(deltaTime, currentTime);
        updateTowers(currentTime);

        // Draw game objects
        drawTowers(window);

        window.draw(waveCountText);

        // display the critter counter 
        critterCountText.setString("Critters Remaining: " + std::to_string(numberOfCrittersRemaining));
        window.draw(critterCountText);

        // display player coins text
        playerCoinsText.setString("Coins: " + std::to_string(playerCoins));
        window.draw(playerCoinsText);

        window.display(); 
    }
}



